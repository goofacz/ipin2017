function positions = whistleProcessSimulationResults(filePath)

% Input CSV columns
ANCHOR_ADDR = 1;
IS_ECHO_FRAME = 2; % 1 - replied frame, 0 - original frame
SEQ_NO = 3;
RX_TS = 4;
TX_TS = 5;

C = 0.000299792458; % m/ps
DELAY = 1000000000; % ps

baseAnchorAddr = hex2dec('DEADBEEF1001');

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
    
    echoSeqNo = origSeqNo + 1;
    echoFramesIndices = results(:,SEQ_NO) == echoSeqNo & results(:,IS_ECHO_FRAME) == 1;
    echoFrames = results(echoFramesIndices, :);
    
    % Get base an nonbase anchors
    baseAnchIdx = origFrames(:, ANCHOR_ADDR) == baseAnchorAddr;
    baseAnchOrigFrame = origFrames(baseAnchIdx, :);
    nonbaseAnchOrigFrame = origFrames(~baseAnchIdx, :);
    baseAnchEchoFrame = echoFrames(baseAnchIdx, :);
    nonbaseAnchEchoFrame = echoFrames(~baseAnchIdx, :);
    
    % TODO
end