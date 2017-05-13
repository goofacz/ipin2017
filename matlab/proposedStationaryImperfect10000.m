function [x,y,meaPosErrs,absPosError] = proposedStationaryImperfect10000(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

seedNo = 1;
drift = 10e-6;
x = linspace(177,573,100);
y = linspace(102,498,100);

for xIdx = 1 : length(x)
   for yIdx = 1 : length(y)
        [~, ~, absPosError, absErrStats]=analyzeStationaryNode(resultsDir, 'tdoa', x(xIdx), y(yIdx), drift, seedNo);
        meaPosErrs(xIdx,yIdx) = absErrStats(MAX);
    end 
end

figure;
surf(x,y,smooth2d(meaPosErrs',3),'EdgeColor','none');
title(sprintf('Proposed method (stationary nodes, 10 ppm clock)'));
xlabel('X coordinate');
ylabel('Y coordinate');
zlabel('Mean absolute position error [m]');
set(gca,'Ydir','reverse')


% TODO

end