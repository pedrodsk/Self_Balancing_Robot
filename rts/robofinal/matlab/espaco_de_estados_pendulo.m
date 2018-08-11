% Vari�veis do modelo:
M =  0.07; %massa das rodas + motores = 70 gm
m = 0.2; %massa do corpo do p�ndulo = 200 gm
b = 0.1; %coeficiente de atrito = 0.1 (N/m/seg)
i = 0.00128; %momento de in�rcia do p�ndulo = 0.00128 (kg*m^2)
g = 9.81; %acelera��o da gravidade = 9,81 m/s2
l = 0.08; %dist�ncia do centro de massa do p�ndulo = 8 cm

%Espa�o de Estados:
p = i*(M+m)+M*m*l^2; %denominador para as matrizes A e B  do modelo de espa�o de estados
%defini��o da matriz A
A = [0      1              0           0;
     0 -(i+m*l^2)*b/p  (m^2*g*l^2)/p   0;
     0      0              0           1;
     0 -(m*l*b)/p       m*g*l*(M+m)/p  0]
%defini��o da matriz B
B = [0; 
    (i+m*l^2)/p;
     0;
     m*l/p]
%defini��o da matriz C
C = [1 0 0 0;
     0 0 1 0]
%defini��o da matriz D
D = [0;
     0]
%Fun��o de Tranfer�ncia do sistema
[num,den] = ss2tf(A,B,C,D)
%Exclus�o dos valores nulos do numerador; resultado em fun��o do �ngulo
num = [num(2,3) num(2,4) num(2,5)]
%Par�mtros do controlador PID
kd = 4; %derivativo
kp = 100; %proporcional
ki = 1; %integral
%Fun��o do controlador PID
numPID = [kd kp ki];
denPID = [1 0];
%Fun��o da malha fechada PID + Sistema
numc = conv(num,denPID)
denc = polyadd(conv(denPID,den),conv(numPID,num))
%Resposta ao impulso do sistema em malha fechada
t=0:0.01:5;
impulse(numc,denc)
axis([0 2 -0.5 0.5])
