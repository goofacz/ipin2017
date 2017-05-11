function proposedStationaryPerfect(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

x = linspace(195,555,10);
y = linspace(120,480,10);

meaPosErrs = zeros(length(x), length(y));

for xIdx = 1 : length(x)
   for yIdx = 1 : length(y)
        [approxPos, realPos, absPosErrs, absErrStats]=analyzeStationaryNode(resultsDir, 'tdoa', x(xIdx), y(yIdx), 0);
        meaPosErrs(xIdx,yIdx) = absErrStats(MEAN);
    end 
end

surf(x,y,meaPosErrs');
title('Proposed method (stationary node)');
xlabel('X coordinate');
ylabel('Y coordinate');
zlabel('Mean absolute position error [m]');

end