%%平面拟合
function [NV,D,ST,LE] = Planefit(pData)
% 空间点的显示
plot3(pData(:,1),pData(:,2),pData(:,3),'*-')
hold on
% 空间点的坐标平均值
MP=mean(pData,1);
% 空间各点对齐到原点，空间各点的坐标减去平均坐标
centeredP=bsxfun(@minus,pData,MP);
% 空间对齐点的SVD分解
[~,~,V]=svd(centeredP);
% 协矩阵的SVD变换中，最小奇异值对应的奇异向量就是平面的方向
NV = V(:,3)';
% aX+bY+cZ+d=0,求d
D = -dot(NV,MP);
% 平面图形绘制
% xfit = min(pData(:,1)):10:max(pData(:,1));
% yfit = min(pData(:,2)):10:max(pData(:,2));
% [XFIT,YFIT]= meshgrid (xfit,yfit);
% ZFIT = -(D + NV(1) * XFIT + NV(2) * YFIT)/NV(3);
% mesh(XFIT,YFIT,ZFIT);
% 各点到拟合平面的距离
n = size(pData,1);
SD = zeros(n,1);
for i =1:n
    SD(i) = Distance_P2A(pData(i,:),NV,MP);
end
%% 平均值
mu = mean(SD);
sigma = std(SD);
%% 平面度
ST = mu + 3*sigma;
%% 中误差
ME = sqrt(SD'*SD./n);
%% 误差限
LE = 3*ME;
end