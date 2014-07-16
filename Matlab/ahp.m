%%
% Parameters
%%
a=[ 1 1 1/3 1/3 1/5 1/5 1/8;
    1 1 1/3 1/3 1/5 1/5 1/8; 
    3 3  1   1  1/2 1/2 1/5;
    3 3  1   1   1  1/2 1/5;
    5 5  2   1   1   1  1/4; 
    5 5  2   1   1   1  1/4; 
    8 8  5   5   4   4   1];
%%
% Constants
%%

[x,y]=eig(a);
eigenvalue=diag(y);
lamda=max(eigenvalue); 
ci=(lamda-7)/6;
cr = ci/1.32
w = x(:,1)/sum(x(:,1))