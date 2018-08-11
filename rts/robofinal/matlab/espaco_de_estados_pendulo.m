% Variáveis do modelo:
M =  0.07; %massa das rodas + motores = 70 gm
m = 0.2; %massa do corpo do pêndulo = 200 gm
b = 0.1; %coeficiente de atrito = 0.1 (N/m/seg)
i = 0.00128; %momento de inércia do pêndulo = 0.00128 (kg*m^2)
g = 9.81; %aceleração da gravidade = 9,81 m/s2
l = 0.08; %distância do centro de massa do pêndulo = 8 cm

%Espaço de Estados:
p = i*(M+m)+M*m*l^2; %denominador para as matrizes A e B  do modelo de espaço de estados
%definição da matriz A
A = [0      1              0           0;
     0 -(i+m*l^2)*b/p  (m^2*g*l^2)/p   0;
     0      0              0           1;
     0 -(m*l*b)/p       m*g*l*(M+m)/p  0]
%definição da matriz B
B = [0; 
    (i+m*l^2)/p;
     0;
     m*l/p]
%definição da matriz C
C = [1 0 0 0;
     0 0 1 0]
%definição da matriz D
D = [0;
     0]
%Função de Tranferência do sistema
[num,den] = ss2tf(A,B,C,D)
%Exclusão dos valores nulos do numerador; resultado em função do ângulo
num = [num(2,3) num(2,4) num(2,5)]
%Parâmtros do controlador PID
kd = 4; %derivativo
kp = 100; %proporcional
ki = 1; %integral
%Função do controlador PID
numPID = [kd kp ki];
denPID = [1 0];
%Função da malha fechada PID + Sistema
numc = conv(num,denPID)
denc = polyadd(conv(denPID,den),conv(numPID,num))
%Resposta ao impulso do sistema em malha fechada
t=0:0.01:5;
impulse(numc,denc)
axis([0 2 -0.5 0.5])
