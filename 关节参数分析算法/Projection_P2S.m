function proj_P = Projection_P2S(V,D,PSET)
%% 点集到指定面的投影点，V为平面法向量
if nargin ~= 3
    error('Projection_P2S(V,P,PSET)参数缺失！！');
end
if length(V) ~= 3
    error('V参数维度错误！！');
end
if size(PSET,2)~=3
    error('PSET参数维度错误！！');
end
if length(D)~=1
    error('D参数维度错误！！');
end
A = V(1);
B = V(2);
C = V(3);
% D = -(A*P(1)+B*P(2)+C*P(3));
F = V*V';
% F = sum(V.^2);
m = size(PSET,1);
proj_P = zeros(m,3);
for i=1:m
    proj_P(i,1) = ((B^2+C^2)*PSET(i,1) - A*(B*PSET(i,2)+C*PSET(i,3)+D))/F;
    proj_P(i,2) = ((A^2+C^2)*PSET(i,2) - B*(A*PSET(i,1)+C*PSET(i,3)+D))/F;
    proj_P(i,3) = ((A^2+B^2)*PSET(i,3) - C*(A*PSET(i,1)+B*PSET(i,2)+D))/F;
end
end