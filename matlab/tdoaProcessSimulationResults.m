function positions = tdoaProcessSimulationResults(filePath)
SEQ_NO = 1;
ANCH_ADDR = 2;
RX_TS = 3;
ANCH_X_COORD = 4;
ANCH_Y_COORD = 5;
MOB_X_COORD = 6;
MOB_Y_COORD = 7;

C = 0.000299792458; % m/ps
DELAY = 1000000000; % ps

results = csvread(filePath);
positions = [];

for seqNo = 1 : max(results(:,SEQ_NO))
    % Filter out beacons with the same sequence no.
    roundResults = results(results(:,SEQ_NO) == seqNo, :);
    anchorTxDelays = zeros(size(roundResults,1),1);
    
    if size(roundResults,1) < 4
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

    syms x y;

% Less error-accumulating algorithm, where TDoA is applied to pairs of
% anchors: [anchor i-1; anchor i] etc.
    eq21 = abs((roundResults(2,RX_TS) - roundResults(1,RX_TS) - sum(anchorTxDelays(2)))  * C) == ...
           abs(((x - roundResults(2,ANCH_X_COORD))^2 + (y - roundResults(2,ANCH_Y_COORD))^2)^0.5 - ...
               ((x - roundResults(1,ANCH_X_COORD))^2 + (y - roundResults(1,ANCH_Y_COORD))^2)^0.5);
    eq32 = abs((roundResults(3,RX_TS) - roundResults(2,RX_TS) - sum(anchorTxDelays(3)))  * C) == ...
           abs(((x - roundResults(3,ANCH_X_COORD))^2 + (y - roundResults(3,ANCH_Y_COORD))^2)^0.5 - ...
               ((x - roundResults(2,ANCH_X_COORD))^2 + (y - roundResults(2,ANCH_Y_COORD))^2)^0.5);
    eq43 = abs((roundResults(4,RX_TS) - roundResults(3,RX_TS) - sum(anchorTxDelays(4))) * C) == ...
           abs(((x - roundResults(4,ANCH_X_COORD))^2 + (y - roundResults(4,ANCH_Y_COORD))^2)^0.5 - ...
               ((x - roundResults(3,ANCH_X_COORD))^2 + (y - roundResults(3,ANCH_Y_COORD))^2)^0.5);

    positionSolver = @(position) ...
        [
         % Partial TDoA for Mobile and <Anchor1, Anchor2>
         -abs((roundResults(2,RX_TS) - roundResults(1,RX_TS) - sum(anchorTxDelays(2)))  * C) + ...
          abs(((position(1) - roundResults(2,ANCH_X_COORD))^2 + (position(2) - roundResults(2,ANCH_Y_COORD))^2)^0.5 - ...
              ((position(1) - roundResults(1,ANCH_X_COORD))^2 + (position(2) - roundResults(1,ANCH_Y_COORD))^2)^0.5); ...

         % Partial TDoA for Mobile and <Anchor2, Anchor3>
         -abs((roundResults(3,RX_TS) - roundResults(2,RX_TS) - sum(anchorTxDelays(3)))  * C) + ...
          abs(((position(1) - roundResults(3,ANCH_X_COORD))^2 + (position(2) - roundResults(3,ANCH_Y_COORD))^2)^0.5 - ...
              ((position(1) - roundResults(2,ANCH_X_COORD))^2 + (position(2) - roundResults(2,ANCH_Y_COORD))^2)^0.5); ...

         % Partial TDoA for Mobile and <Anchor3, Anchor4>
         -abs((roundResults(4,RX_TS) - roundResults(3,RX_TS) - sum(anchorTxDelays(4))) * C) + ...
          abs(((position(1) - roundResults(4,ANCH_X_COORD))^2 + (position(2) - roundResults(4,ANCH_Y_COORD))^2)^0.5 - ...
              ((position(1) - roundResults(3,ANCH_X_COORD))^2 + (position(2) - roundResults(3,ANCH_Y_COORD))^2)^0.5) ...
        ];
   
    %fsolve(positionSolver, [400 350])
    
% "Normal" TDoA, where all differences are computed against "master" anchor

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

    % TODO solve() fails to handle three equations at once, but it gives
    % correct result for any pair of eq21, eq32 and eq43 equations.

    position = solve([eq21 eq32 eq43], [x y])
    positions = [positions; vpa(position.x) vpa(position.y)];
end

