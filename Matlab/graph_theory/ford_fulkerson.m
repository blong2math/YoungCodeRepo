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
while 1              %�����ù����������������·��
    isvisit = 1;            %�൱��closed���ѷ��ʹ��Ľڵ� 
    head = 1;
    tail = 1;
    queue = 1;
    head = head + 1;

    pa = zeros(1, m);      %ÿ���ڵ��ǰ��
    pa(1) = 1;            %Դ�ڵ�ǰ�����Լ�
    while tail ~= head    %�����������������ϸ�ھͲ�ע����
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
    if pa(m) == 0     %�������������ڵ㣬�˳�ѭ��
        break;
    end
    path = [];
    i = m;                %�ӻ�ڵ㿪ʼ
    k = 0;                %·�������ıߵĸ���
    while i ~= 1          %ʹ��ǰ�������Դ�ڵ㵽��ڵ��·��
        path = [path; pa(i) i flow(pa(i), i)];   %#ok<AGROW> %����·�� 
        i = pa(i);            %ʹ��ǰ��������Ѱ�����Dijsktra�е��ɳڷ���
        k = k + 1;             
    end
    Mi = min(path(:, 3));        %Ѱ������·������С��������
    for i = 1:k  
        flow(path(i, 1), path(i, 2)) = flow(path(i, 1), path(i, 2)) - Mi;     
        maxflow(path(i, 1), path(i, 2)) = maxflow(path(i, 1), path(i, 2)) + Mi;
    end                     %ʹ���µ�ͼflow������һѭ�������¿�ʼ������·��
end    
fprintf('���������Ϊ:\n'); disp(maxflow);