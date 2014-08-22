%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/8/22
%% Company: Chongqing University
%% Intro:
% This code is k-means algorithm of machine learning. You can use it to
% classify data points without giving labels in hyperspace into k classes.
% You should give the data points and the parameter k to classify this
% points.(This sample is in 2 dimensions.)
%% Parameters(Sample):
% data points
points = load('dataPoints.txt');

% the number of clustering centroids
k = 3;

% iteration counts
iter_count = 10;

%% Calculation:
% data initialize
dimension = size(points, 2);
centroids = rand(k, dimension);
for d = 1:dimension
    max_x = max(points(:, d)); min_x = min(points(:, d));
    centroids(:, d) = centroids(:, d) * (max_x - min_x) + min_x;
end
labels = zeros(1, size(points, 1));
% k-means iterations
plot(points(:,1), points(:, 2), 'b*', centroids(:, 1), centroids(:, 2), 'r*');
for i = 1:iter_count
    % decide the label of data points
    for point = 1:length(labels)
        min_dist = inf;
        for centroid = 1:k
            if sum((points(point, :) - centroids(centroid, :)) .^2) < min_dist
                min_dist = sum((points(point, :) - centroids(centroid, :)) .^2);
                labels(point) = centroid;
            end
        end
    end
    % re-locate the clustering centroids
    for centroid = 1:k
        centroids(centroid, :) = mean(points(labels==centroid, :));
    end
    pause; dist('按回车键看下一次迭代结果.');
    plot(points(:,1), points(:, 2), 'b*', centroids(:, 1), centroids(:, 2), 'r*');
end