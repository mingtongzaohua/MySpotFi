clear;
% sample CSI trace is a 90x1 vector where first 30 elements correspond to subcarriers for first rx antenna, second 30 correspond to CSI from next 30 subcarriers and so on.
% replace sample_csi_trace with CSI from Intel 5300 converted to 90x1 vector
sample_csi_traceTmp = load('sample_csi_trace');
sample_csi_trace = sample_csi_traceTmp.sample_csi_trace;
%方向矩阵X是sample_csi_trace
fc = 5.63e9; % center frequency
M = 3;    % number of rx antennas
fs = 40e6; % channel bandwidth
c = 3e8;  % speed of light
d = 2.6e-2;  % distance between adjacent antennas in the linear antenna array
% dTx = 2.6e-2; 
SubCarrInd = [-58,-54,-50,-46,-42,-38,-34,-30,-26,-22,-18,-14,-10,-6,-2,2,6,10,14,18,22,26,30,34,38,42,46,50,54,58]; 
% WiFi subcarrier indices at which CSI is available 论文中的方向矩阵A?steering matrix？
N = length(SubCarrInd); % number of subcarriers
% subCarrSize = 128;  % total number fo
fgap = 312.5e3; % frequency gap in Hz between successive subcarriers in WiFi
%WiFi中连续子载波之间的频率间隔（Hz）
lambda = c/fc;  % wavelength  波长
T = 1; % number of transmitter antennas 发射端天线数量

% MUSIC algorithm requires estimating MUSIC spectrum in a grid. paramRange captures parameters for this grid
% For the following example, MUSIC spectrum is caluclated for 101 ToF (Time of flight) values spaced equally between -25 ns and 25 ns. MUSIC spectrum is calculated for for 101 AoA (Angle of Arrival) values between -90 and 90 degrees.
% MUSIC算法需要估算网格中的MUSIC频谱。 paramRange捕获此网格的参数
% 对于以下示例，MUSIC频谱被计算为101 ToF（飞行时间）值，在-25 ns和25 ns之间平均间隔。 对于在-90和90度之间的101 AoA（到达角）值计算MUSIC谱。 
paramRange = struct;
paramRange.GridPts = [101 101 1]; % number of grid points in the format [number of grid points for ToF (Time of flight), number of grid points for angle of arrival (AoA), 1]
paramRange.delayRange = [-50 50]*1e-9; % lowest and highest values to consider for ToF grid. 
paramRange.angleRange = 90*[-1 1]; % lowest and values to consider for AoA grid.
do_second_iter = 0;
% paramRange.seconditerGridPts = [1 51 21 21];
paramRange.K = floor(M/2)+1; % parameter related to smoothing.  
paramRange.L = floor(N/2); % parameter related to smoothing.  
paramRange.T = 1;
paramRange.deltaRange = [0 0]; 

maxRapIters = Inf;
useNoise = 0;
paramRange.generateAtot = 2;

% ToF sanitization code (Algorithm 1 in SpotFi paper)
csi_plot = reshape(sample_csi_trace, N, M);
% 将sample_csi_trace的-复数数组[90]->
% 转化为N*M的矩阵csi_plot
[PhsSlope, PhsCons] = removePhsSlope(csi_plot,M,SubCarrInd,N);
%2018年09月30日22:51:50---X=AF，得到增益矩阵F?
ToMult = exp(1i* (-PhsSlope*repmat(SubCarrInd(:),1,M) - PhsCons*ones(N,M) ));
%repmat将SubCarrInd堆叠到1*M中
csi_plot = csi_plot.*ToMult;
relChannel_noSlope = reshape(csi_plot, N, M, T);%csi_plot转为N*M*T的矩阵
sample_csi_trace_sanitized = relChannel_noSlope(:);

% MUSIC algorithm for estimating angle of arrival
% aoaEstimateMatrix is (nComps x 5) matrix where nComps is the number of paths in the environment.
% First column is ToF in ns and second column is AoA in degrees as defined in SpotFi paper
% aoaEstimateMatrix是（nComps x 5）矩阵，其中nComps是环境中的路径数。
% 第一列是ns中的ToF，第二列是SpotFi纸张中定义的AoA度数
aoaEstimateMatrix = backscatterEstimationMusic(sample_csi_trace_sanitized, M, N, c, fc,...
                    T, fgap, SubCarrInd, d, paramRange, maxRapIters, useNoise, do_second_iter, ones(2));   
tofEstimate = aoaEstimateMatrix(:,1); % ToF in nanoseconds
aoaEstomate = aoaEstimateMatrix(:,2); % AoA in degrees