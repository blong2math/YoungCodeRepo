%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/7/22
%% Company: Chongqing University
%% Intro:
% This code is variant parameters method, using for determining weights.
% You should give a matrix of data, each row is an observe, each colomn is
% every observe of one paramemter. If data is numerical imbalance, please
% give an igvnorance label;
%% Parameter(Sample):
% data matrix(at least 2 observe of each column)
data = [80 94  0 94  0 99;
        79 92 99 95  0  0;
        70  0  0 91 80 100;
        76  0 90  0 90 88;
        74  0 91 83 93  0;
        71 80  0  0 89 94; 
        66 80 77  0 89  0  ];

% ignorance label
ignorance_label = 0;

%% Calculation:
% calculate the variant parameter of each column;
m = zeros(1, size(data, 2));
s = zeros(1, size(data, 2));
for c = 1:size(data, 2)
    idx = find(data(:, c) ~= ignorance_label);
    temp_data = data(:, c);
    temp_data = temp_data(idx);
    m(c) = mean(temp_data);
    s(c) = var(temp_data);
end
v = m ./ s;
% calculate the weights
w = zeros(1, size(data, 2));
for c = 1:size(data, 2)
    w(c) = v(c) / sum(v);
end
disp('决策的权值为:'); disp(w);
