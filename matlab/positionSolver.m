function positionSolver()
A1 = [0 0];
A2 = [4 4];
A3 = [8 0];
A4 = [4 -4];

w = sqrt(32);
c = sqrt(32);

syms a b x y d;
eq1 = 2 * a + c == c + ((A1(1) - x)^2 + (A1(2) - y)^2)^0.5 + ((A2(1) - x)^2 + (A2(2) - y)^2)^0.5;
eq2 = 2 * b + c == c + ((A2(1) - x)^2 + (A2(2) - y)^2)^0.5 + ((A3(1) - x)^2 + (A3(2) - y)^2)^0.5;
eq3 = 2 * d + c == c + ((A3(1) - x)^2 + (A3(2) - y)^2)^0.5 + ((A4(1) - x)^2 + (A4(2) - y)^2)^0.5;
r = solve(eq1, eq2, x, a, b, y);

return
[beacons,beaconEchos,rangingReplies,rangingReplyEchos] = loadSimulationResults();

beaconSendTs = 5000000000000;
replyRecepTs = 5001002017024;
turnAroundTime = 1000000000;
c = 0.000299792458;
beaconEchoRecepTs = 5000000730505;
replyEchoRecepts = 5001001567876;

a1m = ((545 - 291)^2 + (300 - 136)^2)^(1/2);
a2m = ((545 - 510)^2 + (300 - 136)^2)^(1/2);
a1a2 = ((510 - 291)^2 + (136 - 136)^2)^(1/2);
tof = (replyRecepTs - beaconSendTs - turnAroundTime) / 2;

return

% Master
anchor1 = [hex2dec('DEADBEEF1001'), 291, 136];

% Slaves
anchor2 = [hex2dec('DEADBEEF1002'), 510, 136];
anchor3 = [hex2dec('DEADBEEF1003'), 291, 348];
anchor4 = [hex2dec('DEADBEEF1004'), 510, 348];

% Mobile
mobileMacAddr = dec2hex('DEADBEEF0001');

% Various constants
c = 0.000299792458; % m/ps
turnAroundTime = 1000000000; % ps

for i = 1:size(rangingReplies,1)
    % Get beacon
    replySeqNo = rangingReplies(i,1);
    beaconSeqNo = replySeqNo - 1;
    beaconIdx = beacons(:,1) == beaconSeqNo;
    
    % ToF between Mobile and Anchor1
    tof = (rangingReplies(i,3) - beacons(beaconIdx,3) - turnAroundTime) / 2;
    MobileAnchor2TDoA = computeEchosTDoA(replySeqNo, beaconSeqNo, anchor2(1), beaconEchos, rangingReplyEchos, turnAroundTime);
    MobileAnchor3TDoA = computeEchosTDoA(replySeqNo, beaconSeqNo, anchor3(1), beaconEchos, rangingReplyEchos, turnAroundTime);
    MobileAnchor4TDoA = computeEchosTDoA(replySeqNo, beaconSeqNo, anchor4(1), beaconEchos, rangingReplyEchos, turnAroundTime);

    syms x y;
    eq1 = tof*c == ((anchor1(2) - x)^2 + (anchor1(3) - y)^2)^(1/2);
    eq2 = MobileAnchor2TDoA*c + tof*c == ((anchor2(2) - x)^2 - (anchor2(3) - y)^2)^(1/2);
    eq3 = MobileAnchor3TDoA*c + tof*c == ((anchor3(2) - x)^2 - (anchor3(3) - y)^2)^(1/2);
    eq4 = MobileAnchor4TDoA*c + tof*c == ((anchor4(2) - x)^2 - (anchor4(3) - y)^2)^(1/2);

    result = solve([eq1 eq2 eq3 eq4], [x y]);
end

end

function h = circle(x,y,r)
th = 0:pi/50:2*pi;
xunit = r * cos(th) + x;
yunit = r * sin(th) + y;
h = plot(xunit, yunit);
end

function tdoa = computeEchosTDoA(replySeqNo, beaconSeqNo, anchorMacAddr, beaconEchos, rangingReplyEchos, turnAroundTime)
    idx = beaconEchos(:,1) == beaconSeqNo;
    idx = beaconEchos(idx,2) == anchorMacAddr;
    beaconEchoTimestamp = beaconEchos(idx,3);
    
    idx = rangingReplyEchos(:,1) == replySeqNo;
    idx = rangingReplyEchos(idx,2) == anchorMacAddr;
    replyEchoTimestamp = rangingReplyEchos(idx,3);
    
    tdoa = replyEchoTimestamp - beaconEchoTimestamp - turnAroundTime;
end