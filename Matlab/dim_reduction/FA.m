%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/8/22
%% Company: Chongqing University
%% Intro:
% This code is factor analysis, using for dimension reduction. You should
% give a matrix of data and a constant m; FA will transiform X into a m
% dimention data(m < dim(X));

%% Parameter(Sample):
m = 2;

%% Calculations:
[lambda, psi, T, stats, F] = factoran(X, m);