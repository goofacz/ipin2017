function generateStatistics()

% Columns
MIN_ERR = 1;
MAX_ERR = 2;
AVG_ERR = 3;
STDDEV_ERR = 4;

% Rows fo 'propImperf'
STATION = 1;
MOV_5_KMH = 2;
MOV_10_KMH = 3;
MOV_20_KMH = 4;
MOV_40_KMH = 5;

% Rows fo 'propImperfDiffClck'
CLK_100_PPB = 1;
CLK_1_PPM = 2;
CLK_5_PPM = 3;
CLK_10_PPM = 4;
CLK_20_PPM = 5;

propImperf = zeros(5,4);
whistImperf = zeros(5,4);

[~, propImperf(STATION,MIN_ERR) propImperf(STATION,MAX_ERR) ...
 propImperf(STATION,AVG_ERR) propImperf(STATION,STDDEV_ERR)] = ...
 computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_0kmh_imperfect'));
[~, propImperf(MOV_5_KMH,MIN_ERR) propImperf(MOV_5_KMH,MAX_ERR) ...
 propImperf(MOV_5_KMH,AVG_ERR) propImperf(MOV_5_KMH,STDDEV_ERR)] = ...
 computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_5kmh_imperfect'));
[~, propImperf(MOV_10_KMH,MIN_ERR) propImperf(MOV_10_KMH,MAX_ERR) ...
 propImperf(MOV_10_KMH,AVG_ERR) propImperf(MOV_10_KMH,STDDEV_ERR)] = ...
 computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect'));
[~, propImperf(MOV_20_KMH,MIN_ERR) propImperf(MOV_20_KMH,MAX_ERR) ...
 propImperf(MOV_20_KMH,AVG_ERR) propImperf(MOV_20_KMH,STDDEV_ERR)] = ...
 computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_20kmh_imperfect'));
[~, propImperf(MOV_40_KMH,MIN_ERR) propImperf(MOV_40_KMH,MAX_ERR) ...
 propImperf(MOV_40_KMH,AVG_ERR) propImperf(MOV_40_KMH,STDDEV_ERR)] = ...
 computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_40kmh_imperfect'));

[~, whistImperf(STATION,MIN_ERR) whistImperf(STATION,MAX_ERR) ...
 whistImperf(STATION,AVG_ERR) whistImperf(STATION,STDDEV_ERR)] = ...
 computeArticleData(whistleProcessSimulationResults('../simulations/whistle_0kmh_imperfect'));
[~, whistImperf(MOV_5_KMH,MIN_ERR) whistImperf(MOV_5_KMH,MAX_ERR) ...
 whistImperf(MOV_5_KMH,AVG_ERR) whistImperf(MOV_5_KMH,STDDEV_ERR)] = ...
 computeArticleData(whistleProcessSimulationResults('../simulations/whistle_5kmh_imperfect'));
[~, whistImperf(MOV_10_KMH,MIN_ERR) whistImperf(MOV_10_KMH,MAX_ERR) ...
 whistImperf(MOV_10_KMH,AVG_ERR) whistImperf(MOV_10_KMH,STDDEV_ERR)] = ...
 computeArticleData(whistleProcessSimulationResults('../simulations/whistle_10kmh_imperfect'));
[~, whistImperf(MOV_20_KMH,MIN_ERR) whistImperf(MOV_20_KMH,MAX_ERR) ...
 whistImperf(MOV_20_KMH,AVG_ERR) whistImperf(MOV_20_KMH,STDDEV_ERR)] = ...
 computeArticleData(whistleProcessSimulationResults('../simulations/whistle_20kmh_imperfect'));
[~, whistImperf(MOV_40_KMH,MIN_ERR) whistImperf(MOV_40_KMH,MAX_ERR) ...
 whistImperf(MOV_40_KMH,AVG_ERR) whistImperf(MOV_40_KMH,STDDEV_ERR)] = ...
 computeArticleData(whistleProcessSimulationResults('../simulations/whistle_40kmh_imperfect'));

propImperDiffClks_AbsErrs = [ ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect_100ppb')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect_1ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect_2ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect_5ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect_10ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect_20ppm'))
];

figure;
boxplot(propImperDiffClks_AbsErrs,'Labels',{'0.1','1','2','5','10','20'});
ylabel('Absolute position error [m]');
xlabel('Clock drift [ppm]');

propSyncAnch_10kmh_100ppb = computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect_anch_sync_100ppb'));
propSyncAnch_10kmh_10ppm = computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect'));
propSyncAnch_20kmh_100ppb = computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_20kmh_imperfect_anch_sync_100ppb'));
propSyncAnch_20kmh_10ppm = computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_20kmh_imperfect'));
propSyncAnch_40kmh_100ppb = computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_40kmh_imperfect_anch_sync_100ppb'));
propSyncAnch_40kmh_10ppm = computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_40kmh_imperfect'));

propSyncAnch = [propSyncAnch_10kmh_100ppb', propSyncAnch_10kmh_10ppm', ...
                propSyncAnch_20kmh_100ppb', propSyncAnch_20kmh_10ppm', ...
                propSyncAnch_40kmh_100ppb', propSyncAnch_40kmh_10ppm'];
            
propSyncAnch_group = [ones(1,length(propSyncAnch_10kmh_100ppb)) .* 1, ones(1,length(propSyncAnch_10kmh_10ppm)) .* 2, ...
                      ones(1,length(propSyncAnch_20kmh_100ppb)) .* 3, ones(1,length(propSyncAnch_20kmh_10ppm)) .* 4, ...
                      ones(1,length(propSyncAnch_40kmh_100ppb)) .* 5, ones(1,length(propSyncAnch_40kmh_10ppm)) .* 6];

propSyncAnch_positions = [1 1.4 2 2.4 3 3.4];

propSyncAnch_colors = ['w', 'c', 'w', 'c', 'w', 'c'];
                  
figure;
boxplot(propSyncAnch, propSyncAnch_group, ...
        'Positions', propSyncAnch_positions);
    
set(gca,'xtick',[mean(propSyncAnch_positions(1:2)) mean(propSyncAnch_positions(3:4)) mean(propSyncAnch_positions(5:6))]);
set(gca,'xticklabel',{'10', '20', '40'});

ylabel('Absolute position error [m]');
xlabel('Mobile node speed [km/h]');

h = findobj(gca,'Tag','Box');
for j=1:length(h)
    patch(get(h(j),'XData'),get(h(j),'YData'),propSyncAnch_colors(j),'FaceAlpha',.5);
end

end
