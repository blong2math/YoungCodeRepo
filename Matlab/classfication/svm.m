%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/8/13
%% Company: Chongqing University
%% Intro:
% This code is support vector machine of machine learning. You can use it
% to classfy data points in hyperspace by creating a hyperplane(eg. in 2-d
% space, it is a line.) to separate data points. Epsilon is the error of
% training. C term is penalty term which creates a soft margin. You can
% also give a kernel function to create a non-linear classification margin.
%% Parameters(Sample):
% 输入样本原始数据，n×l的矩阵，n为变量个数，l为样本个数
X = load('sampleFeatures.txt');
% 输出样本原始数据，1×l的矩阵，l为样本个数
y = load('sampleLabels.txt');
% 不敏感损失函数的参数，Epsilon越大，支持向量越少
epsilon = 1e-3;
% 惩罚系数，C过大或过小，泛化能力变差
C = 10;
% 核函数类型
kernel_function = 'rbf';
% 如果用rbf做核函数，可以加入这个参数.
rbf_sigma = 0.1;

%% Calculations:
% train svm;
SVMSTRUCT = svmtrain(X, y, 'kernel_function', 'rbf', 'boxconstraint', C, 'rbf_sigma', rbf_sigma);
% Plot the boundary of svm
label = find(y == 1);
xaxis = X(:, 1);  yaxis = X(:, 2);
plot(xaxis(label), yaxis(label), 'b*');
hold on;
label = find(y == 0);
xaxis = X(:, 1);  yaxis = X(:, 2);
plot(xaxis(label), yaxis(label), 'r*');
x1plot = linspace(min(X(:,1)), max(X(:,1)), 100)';
x2plot = linspace(min(X(:,2)), max(X(:,2)), 100)';
[X1, X2] = meshgrid(x1plot, x2plot);
vals = zeros(size(X1));
for i = 1:size(X1, 2)
   this_X = [X1(:, i), X2(:, i)];
   vals(:, i) = svmclassify(SVMSTRUCT, this_X);
end
contour(X1, X2, vals, [0 0], 'Color', 'b');
hold off;
% classify new data point;
GROUP = svmclassify(SVMSTRUCT, [0.6210, 0.9349], 'SHOWPLOT', true);