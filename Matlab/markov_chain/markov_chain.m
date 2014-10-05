%% Author: ZC Young(CQU 2014 #777)
%% Date: 2014/9/3
%% Company: Chongqing University
%% Intro:
% This code is markov chain model. It is a simple random process. You
% should give a transfer matrix and a initial distribution vector.
%% Parameter(Sample):
% transfer matrix
X = [ 0.8 0.1 0.1;
      0.5 0.1 0.4; 
      0.5 0.3 0.2; ];
% initial distribution vector
p = [ 0.2, 0.4, 0.4];

%% Calculations:
p_last = zeros(size(p));
while norm(p - p_last) > 1e-5
    p_last = p;
    p = p_last * X;
end
disp('ÎÈ¶¨¸ÅÂÊÎª:'); disp(p);