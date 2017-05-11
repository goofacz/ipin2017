function proposedStationaryImperfect100(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

seedNo = 1;
drift = [10e-8, 1e-6, 2e-6, 5e-6, 10e-6, 20e-6];
x = linspace(195,555,10);
y = linspace(120,480,10);

for driftIdx = 1 : length(drift)
    for xIdx = 1 : length(x)
       for yIdx = 1 : length(y)
            [~, ~, ~, absErrStats]=analyzeStationaryNode(resultsDir, 'tdoa', x(xIdx), y(yIdx), drift(driftIdx), seedNo);
            meaPosErrs(xIdx,yIdx) = absErrStats(MEAN);
        end 
    end
    
    figure;
    surf(x,y,smooth2d(meaPosErrs',1,'max'));
    title(sprintf('Proposed method (stationary node) %f ppm',drift(driftIdx) * 1000000));
    xlabel('X coordinate');
    ylabel('Y coordinate');
    zlabel('Mean absolute position error [m]');
end

% TODO

end