%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/8/22
%% Company: Chongqing University
%% Intro:
% This code is principle components analysis, using for dimension
% reduction. You should give a matrix of data.
%% Parameters(Sample):
% data
load('data.mat');
data = sub;

% threshold to cut off less contributed principle components
threshold = 85;

%% Calculation:
% data normalization
% principle components calculation
[coeff, score, latent, tsquared, explained] = pca(data, 'Centered', 'off');
sum_score = 0;
for count = 1:size(data, 2)
    sum_score = sum_score + explained(count);
    if sum_score > threshold
        break;
    end
end
disp('主成分为:'); disp(score(:, 1:count));