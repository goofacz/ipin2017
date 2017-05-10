function proposedMovingImperfect(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

x = 100;
sufX = linspace(110, 490, 39);
y = [100, 200, 300, 400, 500];
speed = [1 2 5 10]; %mps
angle = 0; % deg
drift = 10e-06;
seedNo = 1;

for speedIdx = 1 : length(speed)
    for yIdx = 1 : length(y)
        [approxPos, realPos, absPosErrs, absErrStats]=analyzeMovingNode(resultsDir, 'tdoa', x, y(yIdx), speed(speedIdx), angle, drift, seedNo);
    end 
end

% TODO

end