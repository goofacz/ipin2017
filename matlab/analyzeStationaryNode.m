% Analyze stationary simulation results. 
% Simulation results have to be in "simulations" in parent folder. 
%
% INPUT (mandatory):
% - resultsDir: path to directory with simulation results
% - algoName: 'tdoa' or 'whisle' string
% - x: X coordinate
% - y: Y coordinate
% 
% INPUT (optional):
% - drift: clock drift (e.g. pass 10e-6 to analyze 10ppm dritf)
% - seedNo: seed set used for simulation (values from 1 to 3)
% 
% OUTPUT:
% - approxPos: n x 2 matrix with computed positions (X, Y) 
% - realPos: n x 2 matrix with true positions (X, Y) 
% - absPosErrs: vector with n elements containing absolute position errors 
% - absErrStats: 1 x 4 matrix with statistics: min, max, avg, std 
%                respectively.
% 
% EXAMPLE:
% To analyze perfect clock simulation omit "drift" and "seedNo" for 
% stationary nodes:
% 
%     [result]=analyzeMovingNode('../tmp', 'tdoa', 100, 400)
%     
% To analyze imperfect clock simulation pass "drift" and "seedNo":
% 
%     [result]=analyzeMovingNode('../tmp', 'tdoa', 100, 300, 10e-6, 3)
%

function [approxPos, realPos, absPosErrs, absErrStats] = analyzeStationaryNode(resultsDir, algoName, x, y, drift, seedNo)

if exist('drift', 'var') == 0
    drift = 0;
end

if exist('seedNo', 'var') == 0
    seedNo = 0;
end

[approxPos, realPos, absPosErrs, absErrStats] = analyzeSingleSimulation(resultsDir, algoName, x, y, drift, seedNo);

end

%% Helper function
function [approxPos, realPos, absPosErrs, absErrStats] = analyzeSingleSimulation(resultsDir, algoName,  x, y, drift, seedNo)

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

filePath = strcat(resultsDir, filesep, algoName, '_', clockText, '_0mps', seedText, int2str(x), 'm_', int2str(y), 'm');

if strcmp(algoName, 'tdoa') == 1
    results = tdoaProcessSimulationResults(filePath);
else
    results = whistleProcessSimulationResults(filePath);
end

[approxPos, realPos, absPosErrs, absErrStats] = computeArticleData(results);
end