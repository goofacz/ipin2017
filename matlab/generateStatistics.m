function generateStatistics()

% Columns
MIN_ERR = 1;
MAX_ERR = 2;
AVG_ERR = 3;
STDDEV_ERR = 4;
MEDIAN_ERR = 5;

% Rows fo 'propMovPerf'
MOV_5_KMH = 1;
MOV_10_KMH = 2;
MOV_20_KMH = 3;
MOV_30_KMH = 4;

% Rows fo 'propImperfDiffClck'
CLK_100_PPB = 1;
CLK_1_PPM = 2;
CLK_5_PPM = 3;
CLK_10_PPM = 4;
CLK_20_PPM = 5;

%% Proposed method for stationary node (perfect clock)
propStatPerfFiles = [...
  '../simulations/tdoa_stat_perf_350_150';...
  '../simulations/tdoa_stat_perf_350_200';...
  '../simulations/tdoa_stat_perf_350_250';...
  '../simulations/tdoa_stat_perf_350_300';...
  '../simulations/tdoa_stat_perf_400_150';...
  '../simulations/tdoa_stat_perf_400_200';...
  '../simulations/tdoa_stat_perf_400_250';...
  '../simulations/tdoa_stat_perf_400_300';...
  '../simulations/tdoa_stat_perf_450_150';...
  '../simulations/tdoa_stat_perf_450_200';...
  '../simulations/tdoa_stat_perf_450_250';...
  '../simulations/tdoa_stat_perf_450_300';...
  '../simulations/tdoa_stat_perf_500_150';...
  '../simulations/tdoa_stat_perf_500_200';...
  '../simulations/tdoa_stat_perf_500_250';...
  '../simulations/tdoa_stat_perf_500_300'
];

propStatPerf = [];
propStatPerfErrs = [];

for i = 1:size(propStatPerfFiles,1)
    [absErrs, absErrStats] = computeArticleData(tdoaProcessSimulationResults(propStatPerfFiles(i,:)));
    propStatPerf = [propStatPerf; absErrStats];
    propStatPerfErrs = [propStatPerfErrs; absErrs'];
end

%% Proposed method for stationary node (imperfect clock)
propStatImperfFiles = [...
  '../simulations/tdoa_stat_imperf_350_150';...
  '../simulations/tdoa_stat_imperf_350_200';...
  '../simulations/tdoa_stat_imperf_350_250';...
  '../simulations/tdoa_stat_imperf_350_300';...
  '../simulations/tdoa_stat_imperf_400_150';...
  '../simulations/tdoa_stat_imperf_400_200';...
  '../simulations/tdoa_stat_imperf_400_250';...
  '../simulations/tdoa_stat_imperf_400_300';...
  '../simulations/tdoa_stat_imperf_450_150';...
  '../simulations/tdoa_stat_imperf_450_200';...
  '../simulations/tdoa_stat_imperf_450_250';...
  '../simulations/tdoa_stat_imperf_450_300';...
  '../simulations/tdoa_stat_imperf_500_150';...
  '../simulations/tdoa_stat_imperf_500_200';...
  '../simulations/tdoa_stat_imperf_500_250';...
  '../simulations/tdoa_stat_imperf_500_300'
];

propStatImperf = [];
propStatImperfErrs = [];

for i = 1:size(propStatPerfFiles,1)
    [absErrs, absErrStats] = computeArticleData(tdoaProcessSimulationResults(propStatImperfFiles(i,:)));
    propStatImperf = [propStatImperf; absErrStats];
    propStatImperfErrs = [propStatImperfErrs; absErrs'];
end

% figure;
% boxplot(propStatImperfErrs');
% ylabel('Absolute position error [m]');
% xlabel('Mobile node no.');

%% Proposed method for moving node (perfect clock)
% Stationary nodes are indexed directly
propMovPerf = zeros(4,4);

[~, propMovPerf(MOV_5_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_5kmh_perf'));
[~, propMovPerf(MOV_10_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_perf'));
[~, propMovPerf(MOV_20_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_20kmh_perf'));
[~, propMovPerf(MOV_30_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_30kmh_perf'));

%% Proposed method for moving node (imperfect clock)

propMovImperf = zeros(4,4);

[propMovImperf_5kmh, propMovImperf(MOV_5_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_5kmh_imperf'));
[propMovImperf_10kmh, propMovImperf(MOV_10_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf'));
[propMovImperf_20kmh, propMovImperf(MOV_20_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_20kmh_imperf'));
[propMovImperf_30kmh, propMovImperf(MOV_30_KMH,:)] = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_30kmh_imperf'));
return
%% Proposed method for moving node (imperfect clock, anchors clocks with diffrent ppm)
propImperDiffClks_AbsErrs = [ ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf_100ppb')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf_1ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf_2ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf_5ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf_10ppm')), ...
    computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf_20ppm'))
];

figure;
boxplot(propImperDiffClks_AbsErrs,'Labels',{'0.1','1','2','5','10','20'});
ylabel('Absolute position error [m]');
xlabel('Clock drift [ppm]');

%%
propSyncAnch_10kmh_100ppb = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf_synch_anch_100ppb'));
propSyncAnch_10kmh_10ppm = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_10kmh_imperf'));
propSyncAnch_20kmh_100ppb = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_20kmh_imperf_synch_anch_100ppb'));
propSyncAnch_20kmh_10ppm = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_20kmh_imperf'));
propSyncAnch_30kmh_100ppb = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_30kmh_imperf_synch_anch_100ppb'));
propSyncAnch_30kmh_10ppm = computeArticleData(tdoaProcessSimulationResults('../simulations/tdoa_30kmh_imperf'));

propSyncAnch = [propSyncAnch_10kmh_100ppb', propSyncAnch_10kmh_10ppm', ...
                propSyncAnch_20kmh_100ppb', propSyncAnch_20kmh_10ppm', ...
                propSyncAnch_30kmh_100ppb', propSyncAnch_30kmh_10ppm'];
            
propSyncAnch_group = [ones(1,length(propSyncAnch_10kmh_100ppb)) .* 1, ones(1,length(propSyncAnch_10kmh_10ppm)) .* 2, ...
                      ones(1,length(propSyncAnch_20kmh_100ppb)) .* 3, ones(1,length(propSyncAnch_20kmh_10ppm)) .* 4, ...
                      ones(1,length(propSyncAnch_30kmh_100ppb)) .* 5, ones(1,length(propSyncAnch_30kmh_10ppm)) .* 6];

propSyncAnch_positions = [1 1.4 2 2.4 3 3.4];

propSyncAnch_colors = ['w', 'c', 'w', 'c', 'w', 'c'];
                  
figure;
boxplot(propSyncAnch, propSyncAnch_group, ...
        'Positions', propSyncAnch_positions);
    
set(gca,'xtick',[mean(propSyncAnch_positions(1:2)) mean(propSyncAnch_positions(3:4)) mean(propSyncAnch_positions(5:6))]);
set(gca,'xticklabel',{'10', '20', '30'});

ylabel('Absolute position error [m]');
xlabel('Mobile node speed [km/h]');

h = findobj(gca,'Tag','Box');
for j=1:length(h)
    patch(get(h(j),'XData'),get(h(j),'YData'),propSyncAnch_colors(j),'FaceAlpha',.5);
end

%% Put proposed method and Whistle aside (moving node, imperfect clock)

whistleMovImperf = zeros(4,4);

[whistleMovImperf_5kmh whistleMovImperf(MOV_5_KMH,:)] = computeArticleData(whistleProcessSimulationResults('../simulations/whistle_5kmh_imperf'));
[whistleMovImperf_10kmh whistleMovImperf(MOV_10_KMH,:)] = computeArticleData(whistleProcessSimulationResults('../simulations/whistle_10kmh_imperf'));
[whistleMovImperf_20kmh whistleMovImperf(MOV_20_KMH,:)] = computeArticleData(whistleProcessSimulationResults('../simulations/whistle_20kmh_imperf'));
[whistleMovImperf_30kmh whistleMovImperf(MOV_30_KMH,:)] = computeArticleData(whistleProcessSimulationResults('../simulations/whistle_30kmh_imperf'));

propVsWhistle = [propMovImperf_5kmh', whistleMovImperf_5kmh', ...
                 propMovImperf_10kmh', whistleMovImperf_10kmh', ...
                 propMovImperf_20kmh', whistleMovImperf_20kmh', ...
                 propMovImperf_30kmh', whistleMovImperf_30kmh'];
            
propVsWhistle_group = [ones(1,length(propMovImperf_5kmh)) .* 1, ones(1,length(whistleMovImperf_5kmh)) .* 2, ...
                       ones(1,length(propMovImperf_10kmh)) .* 3, ones(1,length (whistleMovImperf_10kmh)) .* 4, ...
                       ones(1,length(propMovImperf_20kmh)) .* 5, ones(1,length(whistleMovImperf_20kmh)) .* 6, ...
                       ones(1,length(propMovImperf_30kmh)) .* 7, ones(1,length(whistleMovImperf_30kmh)) .* 8];

propVsWhistle_positions = [1, 1.4, 2 2.4, 3 3.4, 4 4.4];

propVsWhistle_colors = ['w', 'c', 'w', 'c', 'w', 'c', 'w', 'c'];
                  
figure;
boxplot(propVsWhistle, propVsWhistle_group, ...
        'Positions', propVsWhistle_positions);
    
set(gca,'xtick',[mean(propVsWhistle_positions(1:2)) mean(propVsWhistle_positions(3:4)) mean(propVsWhistle_positions(5:6)) mean(propVsWhistle_positions(7:8))]);
set(gca,'xticklabel',{'5', '10', '20', '30'});

ylabel('Absolute position error [m]');
xlabel('Mobile node speed [km/h]');

h = findobj(gca,'Tag','Box');
for j=1:length(h)
    patch(get(h(j),'XData'),get(h(j),'YData'),propVsWhistle_colors(j),'FaceAlpha',.5);
end


return

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%                           OLD
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

propImperf = zeros(5,4);
whistImperf = zeros(5,4);

% [~, propImperf(STATION,MIN_ERR) propImperf(STATION,MAX_ERR) ...
%  propImperf(STATION,AVG_ERR) propImperf(STATION,STDDEV_ERR)] = ...
%  computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_0kmh_imperfect'));
% [~, propImperf(MOV_5_KMH,MIN_ERR) propImperf(MOV_5_KMH,MAX_ERR) ...
%  propImperf(MOV_5_KMH,AVG_ERR) propImperf(MOV_5_KMH,STDDEV_ERR)] = ...
%  computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_5kmh_imperfect'));
% [~, propImperf(MOV_10_KMH,MIN_ERR) propImperf(MOV_10_KMH,MAX_ERR) ...
%  propImperf(MOV_10_KMH,AVG_ERR) propImperf(MOV_10_KMH,STDDEV_ERR)] = ...
%  computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_10kmh_imperfect'));
% [~, propImperf(MOV_20_KMH,MIN_ERR) propImperf(MOV_20_KMH,MAX_ERR) ...
%  propImperf(MOV_20_KMH,AVG_ERR) propImperf(MOV_20_KMH,STDDEV_ERR)] = ...
%  computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_20kmh_imperfect'));
% [~, propImperf(MOV_30_KMH,MIN_ERR) propImperf(MOV_30_KMH,MAX_ERR) ...
%  propImperf(MOV_30_KMH,AVG_ERR) propImperf(MOV_30_KMH,STDDEV_ERR)] = ...
%  computeArticleData(tdoaProcessSimulationResults('../simulations/proposed_30kmh_imperfect'));
% 
% [~, whistImperf(STATION,MIN_ERR) whistImperf(STATION,MAX_ERR) ...
%  whistImperf(STATION,AVG_ERR) whistImperf(STATION,STDDEV_ERR)] = ...
%  computeArticleData(whistleProcessSimulationResults('../simulations/whistle_0kmh_imperfect'));
% [~, whistImperf(MOV_5_KMH,MIN_ERR) whistImperf(MOV_5_KMH,MAX_ERR) ...
%  whistImperf(MOV_5_KMH,AVG_ERR) whistImperf(MOV_5_KMH,STDDEV_ERR)] = ...
%  computeArticleData(whistleProcessSimulationResults('../simulations/whistle_5kmh_imperfect'));
% [~, whistImperf(MOV_10_KMH,MIN_ERR) whistImperf(MOV_10_KMH,MAX_ERR) ...
%  whistImperf(MOV_10_KMH,AVG_ERR) whistImperf(MOV_10_KMH,STDDEV_ERR)] = ...
%  computeArticleData(whistleProcessSimulationResults('../simulations/whistle_10kmh_imperfect'));
% [~, whistImperf(MOV_20_KMH,MIN_ERR) whistImperf(MOV_20_KMH,MAX_ERR) ...
%  whistImperf(MOV_20_KMH,AVG_ERR) whistImperf(MOV_20_KMH,STDDEV_ERR)] = ...
%  computeArticleData(whistleProcessSimulationResults('../simulations/whistle_20kmh_imperfect'));
% [~, whistImperf(MOV_30_KMH,MIN_ERR) whistImperf(MOV_30_KMH,MAX_ERR) ...
%  whistImperf(MOV_30_KMH,AVG_ERR) whistImperf(MOV_30_KMH,STDDEV_ERR)] = ...
%  computeArticleData(whistleProcessSimulationResults('../simulations/whistle_30kmh_imperfect'));

end
