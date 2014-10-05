%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/8/22
%% Company: Chongqing University
%% Intro:
% This code is k-means algorithm of machine learning. You can use it to
% classify data points without giving labels in hyperspace into k classes.
% You should give the data points and the parameter k to classify this
% points.(This sample is in 2 dimensions.)
%% Parameters(Sample):
% data
load('data_unlabeled.mat');
data = sub';

% dimensions(This means data will be separated into 2 * 2 classes);
dimension1 = 2;
dimension2 = 2;

%% Calculations:
% construct net
net = selforgmap([dimension1 dimension2]);
% train net
[net,tr] = train(net,data);
% output data
group = net(data);