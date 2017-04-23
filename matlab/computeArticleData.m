function computeArticleData(results)

% Columns
COORD_X = 1;
COORD_Y = 2;
REAL_COORD_X = 3;
REAL_COORD_Y = 4;

% Variables
absPosErr = zeros(size(results,1),1);
absPosErrStdDev = 0;

% Computations
for i = 1:size(results,1)
    absPosErr(i) = pdist([results(i,COORD_X) results(i,COORD_Y);
                          results(i,REAL_COORD_X) results(i,REAL_COORD_Y)],'euclidean');
end

absPosErrStdDev = std(absPosErr);

end

