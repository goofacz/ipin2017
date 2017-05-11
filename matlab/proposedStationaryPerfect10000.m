function [x,y,meaPosErrs] = proposedStationaryPerfect10000(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

x = linspace(177,573,100);
y = linspace(102,498,100);

meaPosErrs = zeros(length(x), length(y));

for xIdx = 1 : length(x)
   for yIdx = 1 : length(y)
        [~, ~, ~, absErrStats]=analyzeStationaryNode(resultsDir, 'tdoa', x(xIdx), y(yIdx), 0);
        meaPosErrs(xIdx,yIdx) = absErrStats(MEAN);
    end 
end

figure;
surf(x,y,smooth2d(meaPosErrs'));
title('Proposed method (10k stationary nodes)');
xlabel('X coordinate');
ylabel('Y coordinate');
zlabel('Mean absolute position error [m]');

% TODO

end