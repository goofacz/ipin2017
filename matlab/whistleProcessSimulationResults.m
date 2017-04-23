function positions = whistleProcessSimulationResults(filePath)

% Input CSV columns
ANCHOR_ADDR = 1;
IS_ECHO_FRAME = 2; % 1 - replied frame, 0 - original frame
SEQ_NO = 3;
RX_TS = 4;
TX_TS = 5;
ANCH_COORD_X = 6;
ANCH_COORD_Y = 7;
MOB_COORD_X = 8;
MOB_COORD_Y = 9;

C = 0.000299792458; % m/ps
DELAY = 1000000000; % ps

baseAnchorAddr = hex2dec('DEADBEEF1001'); % Anchor 1

results = csvread(filePath);
positions = [];
 
% Get original messeges' sequence numbers
origSeqNums = results(results(:,IS_ECHO_FRAME) == 0, SEQ_NO);
origSeqNums = unique(origSeqNums);

for origSeqNoIdx = 1 : length(origSeqNums)
    % Get original and echo frames
    origSeqNo = origSeqNums(origSeqNoIdx);
    origFramesIndices = results(:,SEQ_NO) == origSeqNo & results(:,IS_ECHO_FRAME) == 0;
    origFrames = results(origFramesIndices, :);

    echoFramesIndices = results(:,SEQ_NO) == origSeqNo & results(:,IS_ECHO_FRAME) == 1;
    echoFrames = results(echoFramesIndices, :);

    % Get base an nonbase anchors
    baseAnchIdx = origFrames(:, ANCHOR_ADDR) == baseAnchorAddr;

    baseAnchOrigFrame = origFrames(baseAnchIdx, :);
    nonbaseAnchOrigFrame = origFrames(~baseAnchIdx, :);
    baseAnchEchoFrame = echoFrames(baseAnchIdx, :);
    nonbaseAnchEchoFrame = echoFrames(~baseAnchIdx, :);

    % TD2S for pairs (Anchor 1, Anchor 2) and (Anchor 1, Anchor 3)
    tD2S = zeros(1,2);
    for i = 1:2
        distance = pdist([baseAnchOrigFrame(ANCH_COORD_X) baseAnchOrigFrame(ANCH_COORD_Y);
                          nonbaseAnchOrigFrame(i,ANCH_COORD_X) nonbaseAnchOrigFrame(i,ANCH_COORD_Y)], 'euclidean');

        tA2S = baseAnchEchoFrame(RX_TS) - baseAnchOrigFrame(RX_TS);
        tB2S = nonbaseAnchEchoFrame(i,RX_TS) - nonbaseAnchOrigFrame(i,RX_TS);

        tD2S(i) = distance/C - (tB2S - tA2S);
    end;

    coordinates123 = [baseAnchOrigFrame(ANCH_COORD_X) baseAnchOrigFrame(ANCH_COORD_Y);
                      nonbaseAnchOrigFrame(1,ANCH_COORD_X) nonbaseAnchOrigFrame(1,ANCH_COORD_Y);
                      nonbaseAnchOrigFrame(2,ANCH_COORD_X) nonbaseAnchOrigFrame(2,ANCH_COORD_Y)];

    position123 = tdoa_analytical_original(coordinates123, ...
                                           [NaN, tD2S(1), tD2S(2)] .* C);
                                       
    % Compute reference position
    refPosition = [(baseAnchEchoFrame(MOB_COORD_X) + baseAnchOrigFrame(MOB_COORD_X)) / 2, ...
                   (baseAnchEchoFrame(MOB_COORD_Y) + baseAnchOrigFrame(MOB_COORD_Y)) / 2];
             
    positions = [positions; position123', refPosition];
end