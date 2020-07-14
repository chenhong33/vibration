close all
clear all
clc
%%面拟合

data = getxyz();
N = [13,8,11,13,13,13];
n = length(N);
temp = 0;
JN(1) = 0;
for i = 2:n+1
    temp = temp+N(i-1);
    JN(i) = temp;
end
%
for j = 1:n
    s = JN(j)+1;
    e = JN(j+1);
    pData = data(s:e,:);
    [NV(j,:),D(j,:),C(j,:),CP(j,:),R(j),theta(j),ST(j),LE(j),] = CFT(pData);
end
scatter3(CP(:,1),CP(:,2),CP(:,3))
fprintf('J1-J6平面度（μ+3*δ）：%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n',ST);
fprintf('J1-J6平面度（3*m）：%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n',LE);
fprintf('J1-J6半径：%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n',R);
fprintf('J1-J6关节空间角：%.3f,%.3f,%.3f,%.3f,%.3f,%.3f\n',theta);
for i = 1:n
    for j = i+1:n
        alpha(i,j-1) = acos(NV(i,:)*NV(j,:)'./norm(NV(i,:))./norm(NV(j,:))).*180./pi;
    end
end
alpha