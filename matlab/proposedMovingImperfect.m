function proposedMovingImperfect(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

x = 100;
y = linspace(100, 500, 21);
speed = [1 2 5 10]; %mps
angle = 0; % deg
drift = 10e-06;
seedNo = 1;

global correctDriftPPM;
correctDriftPPM = 0; % if 0 then no drift correction

for speedIdx = 1 : length(speed)
    allAbsPosErrs = [];
    for yIdx = 1 : length(y)
        [~, realPos, absPosErrs, ~]=analyzeMovingNode(resultsDir, 'tdoa', x, y(yIdx), speed(speedIdx), angle, drift, seedNo);
        allAbsPosErrs = [allAbsPosErrs absPosErrs];
    end 
    
    allAbsPosErrs(allAbsPosErrs>10^3)=NaN;

    surfX = linspace(100 + speed(speedIdx), 500 - speed(speedIdx), length(absPosErrs));
    
    figure;
    surf(surfX,y,smooth2d(allAbsPosErrs',1,'mean'),'EdgeColor','none');
    title(sprintf('Proposed method (moving node at %d m/s)',speed(speedIdx)));
    xlabel('X coordinate');
    ylabel('Y coordinate');
    zlabel('Mean absolute position error [m]');
    set(gca,'Ydir','reverse')
end

% TODO

end