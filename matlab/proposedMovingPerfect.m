function proposedMovingPerfect(resultsDir)

% absPosErrs columns
MIN = 1;
MAX = 2;
MEAN = 3;
STD = 4;

x = 100;
sufX = linspace(110, 490, 39);
y = [100, 200, 300, 400, 500];
speed = 10; %mps
angle = 0; % deg

allAbsPosErrs = [];

for yIdx = 1 : length(y)
    [approxPos, realPos, absPosErrs, absErrStats]=analyzeMovingNode(resultsDir, 'tdoa', x, y(yIdx), speed, angle);
    allAbsPosErrs = [allAbsPosErrs absPosErrs];
end 

surf(sufX,y,allAbsPosErrs');
hold on;
title('Proposed method (moving node)');
xlabel('X coordinate');
ylabel('Y coordinate');
zlabel('Mean absolute position error [m]');
hold off;

figure;
boxplot(allAbsPosErrs,'Labels',{'(100, 100)', '(100, 200)', '(100, 300)', '(100, 400)', '(100, 500)'});
hold on;
title('Proposed method (moving node)');
ylabel('Absolute position error [m]');
xlabel('Initial position ([m], [m])');
hold off;

end