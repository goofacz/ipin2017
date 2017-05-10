function proposedStationaryImperfect(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

seedNo = 1;
drift = [10e-8, 1e-6, 2e-6, 5e-6, 10e-6, 20e-6];
x = [215, 295, 375, 455, 535];
y = [140, 220, 300, 380, 460];

for driftIdx = 1 : length(drift)
    for xIdx = 1 : length(x)
       for yIdx = 1 : length(y)
            [approxPos, realPos, absPosErrs, absErrStats]=analyzeStationaryNode(resultsDir, 'tdoa', x(xIdx), y(yIdx), drift(driftIdx), seedNo);
            meaPosErrs(xIdx,yIdx) = absErrStats(MEAN);
        end 
    end
end

% TODO

end