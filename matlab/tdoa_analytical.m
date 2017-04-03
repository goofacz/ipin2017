% "The Effectivity Comparison of TDOA Analytical Solution Methods"
% Sang Van Doan, Jiri Vesely
%
% (matrix form)

function position=tdoa_analytical(coordinates, t)


L = t(2);
R = t(3);
Xl = coordinates(2,1) - coordinates(1,1);
Yl = coordinates(2,2) - coordinates(1,2);
Xr = coordinates(3,1) - coordinates(1,1);
Yr = coordinates(3,2) - coordinates(1,2);

A = -2 * [Xl Yl; ...
          Xr Yr];

B = [-2 * L, L^2 - Xl^2 - Yl^2; ...
      2 * R, R^2 - Xr^2 - Yr^2];

tmp = A\B;

a = tmp(1,1)^2 + tmp(2,1)^2 - 1;
b = 2 * (tmp(1,1) * tmp(1,2) + tmp(2,1) * tmp(2,2));
c = tmp(1,2)^2 + tmp(2,2)^2;

K = max(real(roots([a b c])));

X = tmp(1,1) * K + tmp(1,2) + coordinates(1,1);
Y = tmp(2,1) * K + tmp(2,2) + coordinates(1,2);
position = [X; Y];