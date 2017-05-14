
res_1e7=proposedMovingImperfect('res/moving10mpsDiffDrifts',1e-07);
res_1e6=proposedMovingImperfect('res/moving10mpsDiffDrifts',1e-06);
res_2e6=proposedMovingImperfect('res/moving10mpsDiffDrifts',2e-06);
res_5e6=proposedMovingImperfect('res/moving10mpsDiffDrifts',5e-06);
res_1e5=proposedMovingImperfect('res/moving10mpsDiffDrifts',1e-05);
res_2e5=proposedMovingImperfect('res/moving10mpsDiffDrifts',2e-05);

a=res_1e7; a=reshape(a, size(a,1)*size(a,2),1); res_1e7=a;
a=res_1e6; a=reshape(a, size(a,1)*size(a,2),1); res_1e6=a;
a=res_1e5; a=reshape(a, size(a,1)*size(a,2),1); res_1e5=a;
a=res_2e5; a=reshape(a, size(a,1)*size(a,2),1); res_2e5=a;
a=res_2e6; a=reshape(a, size(a,1)*size(a,2),1); res_2e6=a;
a=res_5e6; a=reshape(a, size(a,1)*size(a,2),1); res_5e6=a;

figure;
boxplot([res_1e7, res_1e6, res_2e6, res_5e6, res_1e5]);
set(gca,'XTickLabels',{'0.1 ppm','1 ppm','2 ppm','5 ppm','10 ppm'});
xlabel('Clock drifft [ppm]');
ylabel('Error [m]');
title('Error for nodes moving 10m/s running different clocks');
