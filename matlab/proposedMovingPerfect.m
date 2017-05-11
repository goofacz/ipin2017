function proposedMovingPerfect(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

x = 100;
sufX = linspace(110, 490, 39);
y = linspace(100, 500, 21);
speed = 10; %mps
angle = 0; % deg

labels = {'(100,100)', '(100, 120)', '(100, 140)', '(100, 160)', '(100, 180)', ...
          '(100,100)', '(100, 220)', '(100, 240)', '(100, 260)', '(100, 280)', ...
          '(100,100)', '(100, 320)', '(100, 340)', '(100, 360)', '(100, 380)', ...
          '(100,100)', '(100, 420)', '(100, 440)', '(100, 460)', '(100, 480)', ...
          '(100,500)'};

allAbsPosErrs = [];

for yIdx = 1 : length(y)
    [approxPos, realPos, absPosErrs, absErrStats]=analyzeMovingNode(resultsDir, 'tdoa', x, y(yIdx), speed, angle);
    allAbsPosErrs = [allAbsPosErrs absPosErrs];
end 

figure;
surf(sufX,y,allAbsPosErrs');
title('Proposed method (moving node)');
xlabel('X coordinate');
ylabel('Y coordinate');
zlabel('Mean absolute position error [m]');

figure;
boxplot(allAbsPosErrs,'Labels',labels);
title('Proposed method (moving node)');
ylabel('Absolute position error [m]');
xlabel('Initial position ([m], [m])');

end