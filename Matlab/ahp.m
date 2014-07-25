%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/7/22
%% Company: Chongqing University
%% Intro:
% This code is analytic hierarchy process, using for determining weights
% and making decisions intuitively but by a quite simple way;
% You have to give the hierarchy of determining model and give judgment
% matrix of each layer, next is a example of ahp model.
%% Parameters(Sample):
% The number of layers of hierarchy model
num_layers = 4;
% The number of factors(length of vectors = num_layers)
num_units = [2, 6, 3, 1];
% The structure or connection of hierarchy model. eg. See in structure{2},
% 6 factors in layer 2, and 3 factors in layer 3, in layer 2, factor 1 and
% 2 connect to factor 1 in layer 3; 3 and 4 to 2; 5 and 6 to 3. The element
% of structures{2} in row m and column n means the connection of factor n
% in layer 2 to factor m in layer 3. If connected, it is not zero. To make
% programming easily, in the same line, the connected terms should be
% incremental like 1, 2, ..
structures = cell(1, num_layers - 1);
structures{3} = [ 1, 2, 3 ];
structures{2} = [ 1, 2, 0, 0, 0, 0
                  0, 0, 1, 2, 0, 0
                  0, 0, 0, 0, 1, 2 ];
structures{1} = [ 1, 2 
                  1, 2 
                  1, 2 
                  1, 2 
                  1, 2 
                  1, 2 ];
% The judgment matrix of each layer;
matrix = cell(1, num_layers - 1);
for layer = 1:num_layers - 1
    matrix{layer} = cell(1, num_units(layer + 1)); 
end
matrix{1}{1} = [ 1,  5
                1/5, 1 ];
matrix{1}{2} = [ 1,  3
                1/3, 1 ];
matrix{1}{3} = [ 1, 1/5
                 5,  1 ];
matrix{1}{4} = [ 1,  7
                1/7, 1 ];
matrix{1}{5} = [ 1, 1/5
                 5,  1 ];
matrix{1}{6} = [ 1, 1/3
                 3,  1 ];
matrix{2}{1} = [ 1, 1
                 1, 1 ];
matrix{2}{2} = [ 1,  3
                1/3, 1 ];
matrix{2}{3} = [ 1,  3
                1/3, 1 ];
matrix{3}{1} = [ 1, 1/3, 1/3
                 3,  1,   1
                 3,  1,   1 ];
%% Constants:
% RI for consistency check (matrix level no more than 15)
ri = [0, 0, 0.58, 0.90, 1.12, 1.24, 1.32, 1.41, 1.45, 1.49, 1.52, 1.54, 1.56, 1.58, 1.59];

%% Calculations:
% Calculate the weights of each layer
weights = cell(1, num_layers - 1);
for layer = 1:num_layers - 1
    weights{layer} = cell(1, num_units(layer + 1)); 
end
for layer = 1:num_layers - 1
    for factor = 1:num_units(layer + 1)
        % Weights(sum method)
        weights{layer}{factor} = matrix{layer}{factor}(:,1) / sum(matrix{layer}{factor}(:,1));
        fprintf('层%d对层%d的第%d因素的权重是.\n', layer, layer + 1, factor);
        disp(weights{layer}{factor});

        % Consistency check Using eigenvectors
        [x,y] = eig(matrix{layer}{factor});
        eigenvalue = diag(y);
        lamda = max(eigenvalue); 
        line = structures{layer}; n = length(find(line(factor, :)~=0));
        ci = (lamda - n) / (n - 1);
        cr = ci / ri(n);
        if cr > 0.1
            fprintf('层%d对层%d的第%d因素的矩阵不一致.\n', layer, factor, layer + 1); 
        end
    end
end

% Calculate the total weights of hierarchy
points = cell(1, num_layers);
points{num_layers} = 1; % last layer is 1;
for layer = num_layers - 1:-1:1
    for factor = 1:num_units(layer)
        temp_sum = 0;
        connect = structures{layer}(:, factor);
        for point = 1:length(points{layer + 1});
            if connect(point) ~= 0
                temp_sum = temp_sum + points{layer + 1}(point) * weights{layer}{point}(connect(point));
            end
        end
        points{layer} = [points{layer}; temp_sum];
    end
end
disp('决策的总权值排序为:'); disp(points{1});