% ip_data is a MAT File (MATLAB specific binary file),
% with variables I, Kf, Km, Lp, M, b, g, l, m, r, tau
%run ip_data.m

%          E(s)         U(s)
%Vpot --->O--->[ G2(s) ]--->[ G1(s) ]---+---> Theta (s)
%       - ^                             |
%         |                             |            Theta = SYS * E
%         +----------[ H(s) ]<----------+
%             V viper


% G2(s) = U(s) / E(s)
% u represents the input force on the cart by the pulley chain mechanism,
% e represents the input to the motor driving pulley-chain mechanism.
num_U_E = [((Km * (M + m))*r) 0];
den_U_E = [tau 1];
G2 = tf (num_U_E, den_U_E);

% G(s) = Theta(s) / E(s)
% Open Loop Transfer Function (Without Feedback)
disp 'Forward Path Transfer Function of Inverted Pendulum System is:'
G = series (G2, G1)

% H(s) (Feedback)
num_H = Kf;
den_H = 1;
H = tf (num_H, den_H);

% Closed Loop (Unity Feedback) Transfer Function
% Gc(s) = G(s) / (1 + G(s) * H(s))
disp 'Closed-Loop Transfer Function of Inverted Pendulum System is:'
Gc = feedback(G, H)

% GH(s)
% Open Loop Transfer Function
GH = series (G, H);