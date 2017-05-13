function [res, test_res]=clockTest2(res)
%UNTITLED Summary of this function goes here
%   Detailed explanation goes here

Anchors=[150    50; ...
         650   150; ...
         400   550];
   
if ~exist('res','var')
    res=csvread('res/movingImperf/tdoa_imperf_1e-05_10mps_0deg_1seed_100m_480m');
end

[r,~]=size(res);

C = 0.000299792458;  % speed of light m/ps

anchorDelay = zeros(1,3);
anchorDelay(2) = norm(Anchors(1,:)-Anchors(2,:)) / C;
anchorDelay(3) = norm(Anchors(2,:)-Anchors(3,:)) / C;

for ind=1:r
    d(ind) = norm(res(ind,4:7));
    tof(ind) = d(ind)/C; % ToF in ps
    anchDelInd = mod(ind,3);
    if anchDelInd==0
        anchDelInd = 3;
    end
    
    driftAndToF(ind) = res(ind,3)- floor(res(ind,3)/10^9)*10^9 - anchorDelay(anchDelInd);
    drift(ind) = driftAndToF(ind) - tof(ind);
end

test_res = [d' tof' driftAndToF' drift'];

figure;
plot(test_res(:,4)/10^12*10^6); % 10^12 - time is in ps; 10^6 - convert to ppm's
title('Clock drift');
xlabel('Sample');
ylabel('Drift [ppm]');
end

