%% Author: Young(CQU 2014 777#)
%% Date: 2014/7/26
%% Company: Chongqing University
%% Intro:
% This code is a method to calculate minimal cost-max flow in a directed
% graph. 
% You should give the capacity of each edge and cost of per flow each edge
% and source intensity.
%% Parameter(Sample):
% capacity of flow;
capacity = [ 0 15 16  0  0 
             0  0  0 13 14 
             0 11  0 17  0 
             0  0  0  0  8  
             0  0  0  0  0 ];
% price of flow;
cost = [ 0  4  1  0  0 
         0  0  0  6  1
         0  2  0  3  0 
         0  0  0  0  2
         0  0  0  0  0 ];
% source intensity;
source = 22;
%% Calculations:
num = size(capacity, 1); 
M = sum(sum(capacity)) * num^2;
flow = zeros(size(capacity));
allflow = sum(flow(1, :));
if nargin < 3
    source = M;
end
while allflow < source
    w=(flow < capacity) .* cost - ((flow > 0) .* cost)';
    w = w + ((w == 0) - eye(num)) * M;
    p = zeros(num);
    for k = 1:num
        for i = 1:num
            for j = 1:num
                if w(i,j) > w(i,k) + w(k,j)
                    w(i,j) = w(i,k) + w(k,j);
                    p(i,j) = k;
                end
            end
        end
    end
    if w(1, num) == M
        path = [];
    else
        path = zeros(num);
        s = 1;
        t = num;
        m = p(s, t);
        while ~isempty(m)
            if m(1)
                s = [s, m(1)]; %#ok<AGROW>
                t = [t, t(1)]; %#ok<AGROW>
                t(1) = m(1);
                m(1) = [];
                m = [p(s(1), t(1)), m, p(s(end), t(end))]; %#ok<AGROW>
            else
                path(s(1), t(1)) = 1;
                s(1) = [];
                m(1) = [];
                t(1) = [];
            end
        end
    end
    if isempty(path)
        val = sum(sum(flow .* cost));
        return;
    end
    theta = min(min(path .* (capacity - flow) + (path .* (capacity - flow) == 0) .* M));
    theta = min([min(path' .* flow + (path' .* flow == 0) .* M), theta]);
    checkover = flow + (capacity > 0) .* (path - path') .* theta;
    if sum(checkover(1, :)) > source
        inc = (capacity > 0) .* (path - path') .* theta;
        for i = 1:length(inc)
            for j = 1:length(inc)
                if inc(i, j) ~= 0
                    inc(i, j) = inc(i, j) * ((source - allflow) / abs(inc(i, j)));
                end
            end
        end
        flow = flow + inc;
    else
        flow = flow + ((capacity > 0) .* (path - path') .* theta);
    end
    allflow = sum(flow(1, :));
end
fprintf('最小费用最大流的流量矩阵为：\n'); disp(flow);
fprintf('最小费用最大流的价格为：%d\n', sum(sum(flow .* cost)));