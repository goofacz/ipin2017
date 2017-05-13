function [ res ] = simulateNewDrift(res, ppm)
% Function replaces drift from OMNET simulation with reference drift
% values. The values come from reference ONET simulation. The replacement
% is due to the error in drift simulation that from time to time sets drift
% to fixed value.
%
% Reference grift was generated with 10ppm clock
%
SEQ_NO = 1;
ANCH_ADDR = 2;
RX_TS = 3;
ANCH_X_COORD = 4;
ANCH_Y_COORD = 5;
MOB_X_COORD = 6;
MOB_Y_COORD = 7;

if ~exist('ppm','var')
    ppm = 10;
end

load('referenceDrift.mat', 'drifts'); 

[r,~]=size(res);

scale = ppm/10;

C = 0.000299792458;  % speed of light m/ps
%for ind=1:r
for seqNo = 1 : max(res(:,SEQ_NO))
    % Filter out beacons with the same sequence no.
    indicies       = find(res(:,SEQ_NO) == seqNo);
    roundResults   = res(indicies, :);
    anchorTxDelays = zeros(size(roundResults,1),1);
    
    if size(roundResults,1) < 3
        continue
    end

    for beaconIdx = 2 : size(roundResults,1)
        prevBeacon = roundResults(beaconIdx - 1, :);
        currBeacon = roundResults(beaconIdx, :);
        
        anchorDist = pdist([prevBeacon(ANCH_X_COORD), prevBeacon(ANCH_Y_COORD); ...
                            currBeacon(ANCH_X_COORD), currBeacon(ANCH_Y_COORD)], ...
                            'euclidean');
                        
        anchorTxDelays(beaconIdx) = anchorDist / C ;
    end
    
    for ind=1:size(roundResults,1)
        d           = norm(res(indicies(ind),ANCH_X_COORD:MOB_Y_COORD)); % distance from node to anchor
        tof         = d/C;                % ToF in ps
        idealTXtime = floor(res(indicies(ind), RX_TS)/10^9)*10^9;

        % take next value of reference drift
        driftInd = max([1, mod(indicies(ind),length(drifts)+1)]);
        newDrift  = drifts(driftInd)*scale;
        newRXtime = idealTXtime + anchorTxDelays(ind) + tof;% + newDrift;

        res(indicies(ind), RX_TS) = newRXtime;
    end
end


end

