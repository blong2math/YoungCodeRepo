%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/7/22
%% Company: Chongqing University
%% Intro:
% This code is entropy method, using for determining weights. You should
% give a matrix of data, each row is one item, each colomn is one
% indicator. Each column may be positive-better or nagative-better.
% positive-better means higher, better. negative-better means lower,
% better.
%% Parameter(Sample):
% data matrix
data = [ 80 94 99 94 89 99;
         79 92 91 95 83 94;
         70 80 77 91 80 100;
         76 80 90 93 90 88; ];

% positive-better or nagative-better(1 is p, 0 is n);
label = [ 1, 1, 1, 1, 0, 1 ];

%% Calculation:
% normalization;
data = abs(data);
for i = 1:size(data, 2)
    temp_data = data(:, i);
    if label(i) == 1
        data(:, i) = (temp_data - min(temp_data)) / (max(temp_data) - min(temp_data)) * 100;
    else
        data(:, i) = (max(temp_data) - temp_data) / (max(temp_data) - min(temp_data)) * 100;
    end
end

% calculate the probability of each indicator
s = sum(data);
temp_divisor = [];
for r = 1:size(data, 1)
    temp_divisor = [temp_divisor; sum(data)]; %#ok<AGROW>
end
data = data ./ temp_divisor; 

e = zeros(1, size(data, 2));
for i = 1:size(data, 2)
    temp_sum = 0;
    for j = 1:size(data, 1)
        if data(j, i) ~= 0
           temp_sum = temp_sum - data(j, i) * log(data(j, i)) / log(size(data, 1));
        end
    end
    e(i) = temp_sum;
end
w = (1 - e) / (length(e) - sum(e));
disp('决策的权值为:'); disp(w);
point = zeros(1, size(data, 1));
for i = 1:size(data, 1)
    point(i) = sum(data(i, :) .* w);
end
disp('得分分别为:'); disp(point);