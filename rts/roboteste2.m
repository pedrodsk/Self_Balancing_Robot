% Massa do motor + rodas = 270g / novo 374
% Massa do corpo = 200g / novo 304
% Massa motor direito = 35g
% Massa motor esquerdo 35g
% diametro da roda 68mm
% altura do corpo = 12.5cm
% 
% Especificações dos motores:
% – Tensão de Operação: 3-6VDC
% – Torque: 0,35 Kgf/cm (3V) e 0,80 Kgf/cm (6V)
% – Sistema magnético com anti-interferência
% – Engrenagem com eixo duplo
% – Redução: 1:48
% – Corrente sem carga: =200mA @ 6V, =150mA @ 3V
% – Velocidade sem carga: 200 ± 10%RPM @ 6V, 90 ± 10%RPM @ 3V
%torque 0.8kgf/cm -> 0.078 Nm


r = 34*10^(-3);
L = 8*10^(-2);
mp = 304*10^(-3);
mw = 35*10^(-3);
ip = mp*L^2; %MP*L^2;
iw=mw*r^2; %1/2*MW*r^2
b = 0.002;
g = 9.81;

tmax = (2*mw+mp)*L*g*sin(deg2rad(5));
P = tmax/2*(127/60)*2*pi;


ke=P;
km=tmax/2;

q = ((2*mw+mp)*(ip+mp*L^2)-(mp*L)^2);
num=[mp*L/q 0];
A=1; %s^3
B=(b*(ip+(mp*L^2)))/q; %s^2
C = -((2*mw+mp)*mp*g*L)/q; %s
D = -(b*mp*g*L/q); %termo independente

den = [A B C D];

H = tf(num,den);
% pzmap(H);
% grid(on);
kp = 39.4946;
ki = 0.0215;
kd = 15.3942;
%model(pidexemplo1);