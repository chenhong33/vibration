 function [NV,D,C,CP,R,theta,ST,LE] = CFT(pData)
[m,n] = size(pData);
[NV,D,ST,LE]= Planefit(pData);
C = -NV./D;

B = zeros(m-1,n);
L = zeros(m-1,1);
for i =1:m-1
    B(i,:) = pData(i+1,:)-pData(i,:);
    L(i) = (pData(i+1,:)*pData(i+1,:)'-pData(i,:)*pData(i,:)')/2;
end

% P = eye(m);
% M = [C;B];
% L = [1;L];
% CP = inv(M'*M)*M'*L;
% for i =1:m
%     DR(i) = norm(pData(i,:)-CP);
% end
% R = mean(DR);

P = eye(m-1);
M11 =  B'*P*B;
M = [M11,C';C,0];
BPL = B'*P*L;
W = [BPL;1];
Y = pinv(M)*W;
CP = Y(1:3)';
for i =1:m
    DR(i) = norm(pData(i,:)-CP);
end
R = mean(DR);

PP = Projection_P2S(NV,D,pData);
plot3(PP(:,1),PP(:,2),PP(:,3),'o-')
hold on

a1 = norm(PP(1,:)-CP);
a2 = norm(PP(end,:)-CP);
a3 = norm(PP(end,:)-PP(1,:));
theta = acos((a1*a1+a2*a2-a3*a3)./(2*a1*a2))*180/pi;
end