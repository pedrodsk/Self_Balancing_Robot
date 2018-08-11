M =  0.07;
m = 0.2;
b = 0.1;
i = 0.00128;
g = 9.81;
l = 0.08;

p = i*(M+m)+M*m*l^2; %denominator
A2 = [0      1             0        0;
     0 -(i+m*l^2)*b/p (m^2*g*l^2)/p  0;
     0      0             0        1;
     0 -(m*l*b)/p    m*g*l*(M+m)/p 0];
B2 = [0; (i+m*l^2)/p; 0; m*l/p];
C2 = [1 0 0 0;
     0 0 1 0];
D2 = [0;0];

p = eig(A2)

x=175;
y=500;
Q=[x 0 0 0;
   0 0 0 0;
   0 0 y 0;
   0 0 0 0];
R = 1;
K = lqr(A2,B2,Q,R)
Ac = [(A2-B2*K)];
Bc = [B2];
Cc = [C2];
Dc = [0;
      0];
%impulse(Ac,Bc,Cc,Dc,1);

p = eig(Ac)

P = [-10 -11 -12 -13];
L = place(A2',C2',P)'

Ace = [A2-B2*K B2*K;
      zeros(size(A2)) (A2-L*C2)];
Bce = [B2;
      zeros(size(B2))];
Cce = [Cc zeros(size(Cc))];
Dce = [0;0];
t=0:0.01:10;
impulse(Ace,Bce,Cce,Dce,1,t);
axis([0 2 -1 1])