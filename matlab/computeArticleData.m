% Computes basic statistics used in article. Function computes absolute 
% localization error (difference between position obtained from localization 
% method and real position).
%
% INPUT (mandatory):
% - results: data in format compliant with result of tdoaProcessSimulationResults()
% 
% OUTPUT:
% - approxPos: n x 2 matrix with computed positions (X, Y) 
% - realPos: n x 2 matrix with true positions (X, Y) 
% - absPosErrs: vector with n elements containing absolute position errors 
% - absErrStats: 1 x 4 matrix with statistics: min, max, avg, std 
%                respectively.

function [approxPos, realPos, absPosErrs, absErrStats] = computeArticleData(results)

% Columns
COORD_X = 1;
COORD_Y = 2;
REAL_COORD_X = 3;
REAL_COORD_Y = 4;

% Variables
absPosErrs = zeros(size(results,1),1);

% Computations
for i = 1:size(results,1)
    absPosErrs(i) = pdist([results(i,COORD_X) results(i,COORD_Y);
                           results(i,REAL_COORD_X) results(i,REAL_COORD_Y)],'euclidean');
end

approxPos = [results(:,COORD_X), results(:,COORD_Y)];
realPos = [results(:,REAL_COORD_X), results(:,REAL_COORD_Y)];
absErrStats = [min(absPosErrs), max(absPosErrs), mean(absPosErrs), std(absPosErrs), median(absPosErrs)];

end

