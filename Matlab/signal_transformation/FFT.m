%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/9/3
%% Company: Chongqing University
%% Intro:
% This code is fast fourier transformation for 1-dimentional signal. It
% will change descrete time series signal into frequency signal.
%% Parameter(Sample):
% data
data = load('data.txt');

% frequency
fs = 100;

%% Calculations:
% data length
N = length(data);
% fft
phasers = fft(data);
frequency = (0:N-1) * fs / N;
lengths = abs(phasers);
plot(frequency, lengths);
title('f-Aͼ');