% Analyze all sort of simulation results. 
% Simulation results have to be in "simulations" in parent folder. 
%
% INPUT (mandatory):
% - algoName: 'tdoa' or 'whisle' string
% - x: X coordinate
% - y: Y coordinate
% - speeds: vector with node speeds ('0' for stationary simulations)
% 
% INPUT (optional):
% - drift: clock drift (e.g. pass 10e-6 to analyze 10ppm dritf)
% - seedNo: seed set used for simulation (values from 1 to 3)
% 
% OUTPUT:
% Matrix m x n, where m (rows) represent consecutive speeds and n (columns) 
% represents statistics: min, max, avg, std respectively.
% 
% EXAMPLE:
% To analyze perfect clock simulation omit "drift" and "seedNo" for 
% stationary nodes:
% 
%     [result]=analyzeMovingNode('tdoa', 100, 400, [0])
%     
% To analyze imperfect clock simulation pass "drift" and "seedNo" for nodes 
% running at different speeds ([5, 10, 20, 40]):
% 
%     [result]=analyzeMovingNode('tdoa', 100, 300, [5, 10, 20, 40], 10e-6, 3)
%

function [absErrStats] = analyzeData(algoName, x, y, speeds, drift, seedNo)

if exist('drift', 'var') == 0
    drift = 0;
end

if exist('seedNo', 'var') == 0
    seedNo = 0;
end

absErrStats = zeros(length(speeds),4);

for i = 1:length(speeds)
    [~, absErrStats(i,:)] = analyzeSingleSimulation(algoName, speeds(i), x, y, drift, seedNo);
end

end

%% Helper function
function [absPosErrs, absErrStats] = analyzeSingleSimulation(algoName, speed,  x, y, drift, seedNo)

if drift == 0
    clockText = strcat('perf');
else
    clockText = strcat('imperf_', num2str(drift));
end

if seedNo > 0
    seedText = strcat('_', num2str(seedNo), 'seed', '_');
else
    seedText = '_';
end

filePath = strcat('../simulations/', algoName, '_', clockText, '_', int2str(speed), 'kmph', seedText, int2str(x), 'm_', int2str(y), 'm');

if strcmp(algoName, 'tdoa') == 1
    results = tdoaProcessSimulationResults(filePath);
else
    results = whistleProcessSimulationResults(filePath);
end

[absPosErrs, absErrStats] = computeArticleData(results);
end