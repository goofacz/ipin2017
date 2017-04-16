data = load('../simulations/clock_test_results');

figure;
hold on;
title('Constant drift clock PPM');
constant_diff = data(:,2) - data(:,1);
constant_ppm = constant_diff ./ data(:,1);
boxplot(constant_ppm);

figure;
hold on;
title('Bounded drift clock PPM');
bounded_diff = data(:,3) - data(:,1);
bounded_ppm = bounded_diff ./ data(:,1);
boxplot(bounded_ppm);

figure;
hold on;
title('Bounded variation drift clock PPM');
bounded_variation_diff = data(:,4) - data(:,1);
bounded_variation_ppm = bounded_variation_diff ./ data(:,1);
boxplot(bounded_variation_ppm);

figure;
hold on;
title('Drifts diffs from perfect clock');
plot(data(:,1), constant_diff, 'r+');
plot(data(:,1), bounded_diff, 'g+');
plot(data(:,1), bounded_variation_diff, 'b+');
legend('constant drsrc/HardwareClock.nedift', 'bounded drift', 'bounded variation drift');