%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/8/13
%% Company: Chongqing University
%% Intro:
% This code is neural network.
%% Parameters(Sample):
% 输入样本原始数据，n×l的矩阵，n为变量个数，l为样本个数
X = load('sampleFeatures.txt');
% 输出样本原始数据，1×l的矩阵，l为样本个数
y = load('sampleLabels.txt');

%% Calculations:
% train the neural net
net = feedforwardnet([4, 4]);
net.trainParam.showWindow = 0;
net.trainParam.max_fail = 100;
net = train(net, X', y');
% Plot the boundary of neural net
label = find(y == 1);
xaxis = X(:, 1);  yaxis = X(:, 2);
plot(xaxis(label), yaxis(label), 'b*');
hold on;
label = find(y == 0);
xaxis = X(:, 1);  yaxis = X(:, 2);
plot(xaxis(label), yaxis(label), 'r*');
x1plot = linspace(min(X(:,1)), max(X(:,1)), 50)';
x2plot = linspace(min(X(:,2)), max(X(:,2)), 50)';
[X1, X2] = meshgrid(x1plot, x2plot);
vals = zeros(size(X1));
for i = 1:size(X1, 2)
    for j = 1:size(X1, 1)
        this_X = [X1(j, i), X2(j, i)];
        temp = net(this_X');
        if abs(temp - 1) < abs(temp - 0)
            vals(j, i) = 1;
        end
    end
end
contour(X1, X2, vals, [0 0], 'Color', 'b');
hold off;