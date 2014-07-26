%% Author: Young(CQU 2014 777#)
%% Date: 2014/7/26
%% Company: Chongqing University
%% Intro:
% This code is ford-fulkerson algorithm, which is used to calculate the
% maximum flow in a directed graph when there is only one source node and
% one sink node and without any point flow limits. TIP: multi-source and
% multi-sink and node flow limits problems can be convert to this kind of
% simple problems. 
% The sink node is default thought as the last node and the source node
% is default thought as the 1st node in flow matrix. And the parameters you
% should give is flow matrix represented edge flow limits. 
%% Parameters(Sample):
flow = [ 0 16  0 13  0  0;
         0  0 12 10  0  0;
         0  0  0  9  0 20;
         0  4  0  0 14  0;
         0  0  7  0  0  7;
         0  0  0  0  0  0; ];
m = length(flow);
maxflow = zeros(m, m);
%% Calculations:
while 1              %下面用广度优先搜索找增广路径
    isvisit = 1;            %相当于closed表，已访问过的节点 
    head = 1;
    tail = 1;
    queue = 1;
    head = head + 1;

    pa = zeros(1, m);      %每个节点的前趋
    pa(1) = 1;            %源节点前趋是自己
    while tail ~= head    %广度优先搜索，具体细节就不注释了
        i = queue(tail);
        for j = 1:m
            if flow(i,j) > 0 && isempty(find(isvisit == j,1))
                queue(head) = j; %#ok<SAGROW>
                head = head + 1;
                isvisit = [isvisit j]; %#ok<AGROW>
                pa(j) = i;
            end
        end
        tail = tail + 1;
    end
    if pa(m) == 0     %如果搜索不到汇节点，退出循环
        break;
    end
    path = [];
    i = m;                %从汇节点开始
    k = 0;                %路径包含的边的个数
    while i ~= 1          %使用前趋构造从源节点到汇节点的路径
        path = [path; pa(i) i flow(pa(i), i)];   %#ok<AGROW> %存入路径 
        i = pa(i);            %使用前趋表反向搜寻，借鉴Dijsktra中的松弛方法
        k = k + 1;             
    end
    Mi = min(path(:, 3));        %寻找增广路径中最小的那条边
    for i = 1:k  
        flow(path(i, 1), path(i, 2)) = flow(path(i, 1), path(i, 2)) - Mi;     
        maxflow(path(i, 1), path(i, 2)) = maxflow(path(i, 1), path(i, 2)) + Mi;
    end                     %使用新的图flow进入下一循环，从新开始找增广路径
end    
fprintf('最大流矩阵为:\n'); disp(maxflow);