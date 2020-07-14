function distance = Distance_P2A(SP,NV,CP)
D = -dot(NV,CP);
distance = abs(dot(NV,SP)+D)/norm(NV);
end