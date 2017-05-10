function positions = tdoaProcessSimulationResults(filePath)
SEQ_NO = 1;
ANCH_ADDR = 2;
RX_TS = 3;
ANCH_X_COORD = 4;
ANCH_Y_COORD = 5;
MOB_X_COORD = 6;
MOB_Y_COORD = 7;

C = 0.000299792458; % m/ps
DELAY = 35000000000; % ps

results = csvread(filePath);
positions = [];

for seqNo = 1 : max(results(:,SEQ_NO))
    % Filter out beacons with the same sequence no.
    roundResults = results(results(:,SEQ_NO) == seqNo, :);
    anchorTxDelays = zeros(size(roundResults,1),1);
    
    if size(roundResults,1) < 3
        display('Too few beacons received in this round , skipping');
        continue
    end

    for beaconIdx = 2 : size(roundResults,1)
        prevBeacon = roundResults(beaconIdx - 1, :);
        currBeacon = roundResults(beaconIdx, :);
        
        anchorDist = pdist([prevBeacon(ANCH_X_COORD), prevBeacon(ANCH_Y_COORD); ...
                            currBeacon(ANCH_X_COORD), currBeacon(ANCH_Y_COORD)], ...
                            'euclidean');
                        
        anchorTxDelays(beaconIdx) = anchorDist / C + DELAY;
    end

%    syms x y;

    %
    % Less error-accumulating algorithm, where TDoA is applied to pairs of anchors: [anchor i-1; anchor i] etc.
    %
    
%     eq21 = (((roundResults(2,RX_TS) - roundResults(1,RX_TS))) - sum(anchorTxDelays(2)))  * C == ...
%            ((x - roundResults(2,ANCH_X_COORD))^2 + (y - roundResults(2,ANCH_Y_COORD))^2)^0.5 - ...
%             ((x - roundResults(1,ANCH_X_COORD))^2 + (y - roundResults(1,ANCH_Y_COORD))^2)^0.5;
%     eq32 = ((((roundResults(3,RX_TS) - roundResults(2,RX_TS))) - sum(anchorTxDelays(3)))  * C) == ...
%            (((x - roundResults(3,ANCH_X_COORD))^2 + (y - roundResults(3,ANCH_Y_COORD))^2)^0.5 - ...
%             ((x - roundResults(2,ANCH_X_COORD))^2 + (y - roundResults(2,ANCH_Y_COORD))^2)^0.5);
%     eq43 = ((((roundResults(4,RX_TS) - roundResults(3,RX_TS))) - sum(anchorTxDelays(4))) * C) == ...
%            (((x - roundResults(4,ANCH_X_COORD))^2 + (y - roundResults(4,ANCH_Y_COORD))^2)^0.5 - ...
%             ((x - roundResults(3,ANCH_X_COORD))^2 + (y - roundResults(3,ANCH_Y_COORD))^2)^0.5);
    
%     positionSolver = @(position) ...
%         [
         % Partial TDoA for Mobile and <Anchor1, Anchor2>
%          -power((roundResults(2,RX_TS) - roundResults(1,RX_TS) - sum(anchorTxDelays(2)))  * C, 2) + ...
%           power(((position(1) - roundResults(2,ANCH_X_COORD))^2 + (position(2) - roundResults(2,ANCH_Y_COORD))^2)^0.5 - ...
%                 ((position(1) - roundResults(1,ANCH_X_COORD))^2 + (position(2) - roundResults(1,ANCH_Y_COORD))^2)^0.5, 2); ...
% 
%          % Partial TDoA for Mobile and <Anchor2, Anchor3>
%          -power((roundResults(3,RX_TS) - roundResults(2,RX_TS) - sum(anchorTxDelays(3)))  * C, 2) + ...
%           power(((position(1) - roundResults(3,ANCH_X_COORD))^2 + (position(2) - roundResults(3,ANCH_Y_COORD))^2)^0.5 - ...
%                 ((position(1) - roundResults(2,ANCH_X_COORD))^2 + (position(2) - roundResults(2,ANCH_Y_COORD))^2)^0.5, 2); ...
% 
%          % Partial TDoA for Mobile and <Anchor3, Anchor4>
%          -power((roundResults(4,RX_TS) - roundResults(3,RX_TS) - sum(anchorTxDelays(4))) * C, 2) + ...
%           power(((position(1) - roundResults(4,ANCH_X_COORD))^2 + (position(2) - roundResults(4,ANCH_Y_COORD))^2)^0.5 - ...
%                 ((position(1) - roundResults(3,ANCH_X_COORD))^2 + (position(2) - roundResults(3,ANCH_Y_COORD))^2)^0.5, 2) ...
%        ];
   
%     result = fsolve(positionSolver, [550 350]);
    
    %
    % "Normal" TDoA, where all differences are computed against "master" anchor
    %

%     eq21 = (roundResults(2,RX_TS) - roundResults(1,RX_TS) - sum(anchorTxDelays(2))) * C == ...
%            ((x - roundResults(2,ANCH_X_COORD))^2 + (y - roundResults(2,ANCH_Y_COORD))^2)^0.5 - ...
%            ((x - roundResults(1,ANCH_X_COORD))^2 + (y - roundResults(1,ANCH_Y_COORD))^2)^0.5;
%        
%     eq32 = (roundResults(3,RX_TS) - roundResults(1,RX_TS) - sum(anchorTxDelays(2:3))) * C== ...
%            ((x - roundResults(3,ANCH_X_COORD))^2 + (y - roundResults(3,ANCH_Y_COORD))^2)^0.5 - ...
%            ((x - roundResults(1,ANCH_X_COORD))^2 + (y - roundResults(1,ANCH_Y_COORD))^2)^0.5;
%        
%      eq43 = (roundResults(4,RX_TS) - roundResults(1,RX_TS) - sum(anchorTxDelays(2:4))) * C== ...
%            ((x - roundResults(4,ANCH_X_COORD))^2 + (y - roundResults(4,ANCH_Y_COORD))^2)^0.5 - ...
%            ((x - roundResults(1,ANCH_X_COORD))^2 + (y - roundResults(1,ANCH_Y_COORD))^2)^0.5;
    
%    position = solve([eq21 eq32 eq43], [x y])
%    positions = [positions; vpa(position.x) vpa(position.y)];
    
    %
    % Analytic solution
    %    

    % Anchors 1 and 3 against anchor 2
    coordinates123 = [roundResults(2,ANCH_X_COORD), roundResults(2,ANCH_Y_COORD);
                      roundResults(1,ANCH_X_COORD), roundResults(1,ANCH_Y_COORD);
                      roundResults(3,ANCH_X_COORD), roundResults(3,ANCH_Y_COORD)];

    timestamps123 = [NaN, ...
                     (((roundResults(2,RX_TS) - roundResults(1,RX_TS))) - sum(anchorTxDelays(2))) * C, ...
                     (((roundResults(3,RX_TS) - roundResults(2,RX_TS))) - sum(anchorTxDelays(3))) * C];

    position123 = tdoa_analytical(coordinates123, timestamps123);
    
    % Anchors 2 and 4 against anchor 3
%     coordinates234 = [roundResults(3,ANCH_X_COORD), roundResults(3,ANCH_Y_COORD);
%                       roundResults(2,ANCH_X_COORD), roundResults(2,ANCH_Y_COORD);
%                       roundResults(4,ANCH_X_COORD), roundResults(4,ANCH_Y_COORD)];
%        
%     timestamps234 = [NaN, ...
%                      (((roundResults(3,RX_TS) - roundResults(2,RX_TS))) - sum(anchorTxDelays(3))) * C, ...
%                      (((roundResults(4,RX_TS) - roundResults(3,RX_TS))) - sum(anchorTxDelays(4))) * C];
% 
%     position234 = tdoa_analytical(coordinates234, timestamps234);

    % Reference mobile position
    refPosition = roundResults(2,MOB_X_COORD:MOB_Y_COORD);
    
    positions = [positions; position123' refPosition];
end

