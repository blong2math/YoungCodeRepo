%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/7/25
%% Company: Chongqing University
%% Intro:
% This code is floyd-warshall algorithm to solve the shortest path of
% every point pair ina complex graph model.
% You should give the archietecture of this graph.
%% Parameters(Sample):
% The distance matrix;
Dist = [  0,  50, inf,  40,  25,  10;
         50,   0,  15,  20, inf,  25;
        inf,  15,   0,  10,  20, inf;
         40,  20,  10,   0,  10,  25;
         25, inf,  20,  10,   0,  55;
         10,  25, inf,  25,  55,   0; ];
num_points = size(Dist, 1);
%% Calculations:
% Floyd-Warshall process
D = Dist;
for i = 1:num_points
    for j = 1:num_points
        R(i,j) = j; %#ok<SAGROW>It is in the path of i to j and post of i
    end
end
for k = 1:num_points
    for i = 1:num_points
        for j = 1:num_points
            if D(i,k) + D(k,j) < D(i,j)
                D(i,j) = D(i,k) + D(k,j); R(i,j) = R(i,k); %#ok<SAGROW>
            end
        end
    end
end
% Print result
fprintf('每个点到另一个点的距离矩阵如下：\n'); disp(D);
for i = 1:num_points
    for j = 1:num_points
        if D(i, j) == inf
            fprintf('点%d到点%d不可达。\n', i, j);
            continue;
        end
        fprintf('点%d到点%d的最短路径为：%d->', i, j, i);
        temp = R(i, j);
        while temp ~= j
            fprintf('%d->', temp);
            temp = R(temp, j);
        end
        if temp == j, fprintf('%d\n', temp); end
    end
end