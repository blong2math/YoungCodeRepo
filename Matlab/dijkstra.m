%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/7/25
%% Company: Chongqing University
%% Intro:
% This code is dijkstra algorithm to solve the shortest path of a single
% source point to any other points in a complex graph model.
% You should give the archietecture of this graph and the source point is
% the point with index 1 default. 
%% Parameters(Sample):
% The number of points in the graph;
num_points = 6;
% The direct distance of every two connected points;
graph = zeros(num_points);
graph(1,2)=50;graph(1,4)=40;graph(1,5)=25;graph(1,6)=10;
graph(2,3)=15;graph(2,4)=20;graph(2,6)=25;
graph(3,4)=10;graph(3,5)=20;
graph(4,5)=10;graph(4,6)=25;
graph(5,6)=55;
% Pre-process of this graph
graph = graph + graph';
graph(graph == 0) = inf;
%% Calculations
% Initialization path, distance and isvisit
isvisit = zeros(1, num_points); isvisit(1) = 1;
distance(1:length(graph)) = inf; distance(1) = 0;
tree_root = ones(1,length(graph));
visitseq = 1;
temp = 1;
% Dijkstra process(Greedy algorithm)
while sum(isvisit) < length(graph)
    notvisit = find(isvisit == 0);
    distance(notvisit) = min(distance(notvisit), distance(temp) + graph(temp, notvisit));
    tmisvisit = find(distance(notvisit) == min(distance(notvisit)));
    temp = notvisit(tmisvisit(1)); isvisit(temp) = 1; 
    visitseq = [visitseq, temp]; %#ok<AGROW>
    temp2 = find(distance(visitseq) == distance(temp) - graph(temp,visitseq));
    tree_root(temp) = visitseq(temp2(1));
end
% Print result
fprintf('最短路径距离依次为:\n');
disp(distance);
for point = 1:num_points
    fprintf('源点到点%d的最短路径为：%d<-', point, point);
    temp = tree_root(point);
    while temp ~= 1
        fprintf('%d<-', temp);
        temp = tree_root(temp);
    end
    if temp == 1, fprintf('%d\n', temp); end
end