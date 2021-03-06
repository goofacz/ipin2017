%   IPIN 2017 Localization Method Simulator
% 
%   Copyright (C) 2017 Tomasz Jankowski
%   
%   This program is free software; you can redistribute it and/or modify
%   it under the terms of the GNU General Public License as published by
%   the Free Software Foundation; either version 3 of the License, or
%   (at your option) any later version.
%      
%   This program is distributed in the hope that it will be useful,
%   but WITHOUT ANY WARRANTY; without even the implied warranty of
%   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
%   GNU General Public License for more details.
%      
%   You should have received a copy of the GNU General Public License
%   along with this program; if not, write to the Free Software Foundation,
%   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA

% Analyze moving node simulation results. 
% Simulation results have to be in "simulations" in parent folder. 
%
% INPUT (mandatory):
% - resultsDir: path to directory with simulation results
% - algoName: 'tdoa' or 'whisle' string
% - x: X coordinate
% - y: Y coordinate
% - speed: scalar with node speed ('0' for stationary simulations)
% - angle: angle of movement
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
% To analyze perfect clock simulation omit "drift" and "seedNo":
% 
%     [result]=analyzeMovingNode('../tmp', 'tdoa', 100, 400, 0, 0)
%     
% To analyze imperfect clock simulation pass "drift" and "seedNo" for bode
% moving at 5m/s and 90deg:
% 
%     [result]=analyzeMovingNode('../tmp', 'tdoa', 100, 300, 5, 90, 10e-6, 3)
%

function [approxPos, realPos, absPosErrs, absErrStats] = analyzeMovingNode(resultsDir, algoName, x, y, speed, angle, drift, seedNo)

if exist('drift', 'var') == 0
    drift = 0;
end

if exist('seedNo', 'var') == 0
    seedNo = 0;
end

[approxPos, realPos, absPosErrs, absErrStats] = analyzeSingleSimulation(resultsDir, algoName, speed, x, y, angle, drift, seedNo);

end

%% Helper function
function [approxPos, realPos, absPosErrs, absErrStats] = analyzeSingleSimulation(resultsDir, algoName, speed, x, y, angle, drift, seedNo)

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

filePath = strcat(resultsDir, filesep, algoName, '_', clockText, '_', int2str(speed), 'mps_', int2str(angle), 'deg', seedText, int2str(x), 'm_', int2str(y), 'm');

if strcmp(algoName, 'tdoa') == 1
    results = tdoaProcessSimulationResults(filePath);
else
    results = whistleProcessSimulationResults(filePath);
end

[approxPos, realPos, absPosErrs, absErrStats] = computeArticleData(results);
end
