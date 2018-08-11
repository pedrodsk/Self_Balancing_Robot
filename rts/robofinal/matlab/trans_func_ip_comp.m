% func_ip_uc is a MAT File (MATLAB specific binary file),
% with variables G, GH, Gc, H, Th_U, U_E, num_G, den_G
%load func_ip_uc
% C(s) = ( Kd * s^2 + Kp * s + Ki ) / s

% PID Controller to reshape the root locus
%          E(s)      U(s)
%Vpot --->O---[ C(s) ]--->[ G2(s) ]--->[ G1(s) ]---+---> Theta (s)
%       - ^                                        |
%         |                                        | Theta = SYS * E
%         +----------------[ H(s) ]<---------------+
%             V viper
% Kp = 20;
% Ki = 14;
% Kd = 6;
% Kc = 1;
% pd = 1000;
num_PID = [kd Kp Ki];
den_PID = [1 0];
%s = tf([1 0],[0 1]);
%PID = Kp+Ki/s+Kd*pd*s/(s+pd);
disp ('The transfer function of the PID Controller is:')
PID = tf (num_PID, den_PID)

% G_comp(s) = PID(s) * G(s)
% Overall Forward Transfer Function.
%num_Gcomp = conv (num_PID, num_G);
%den_Gcomp = conv (den_PID, den_G);
G_comp = series (PID, G);

% Open Loop Transfer Function of the Compensated System
% G_comp_H(s) = G_comp(s) * H(s)
G_comp_H = series (G_comp, H);

% Closed-Loop Transfer Function of the Compensated System
% Gc_comp
disp 'Closed Loop Transfer Function of the Compensated IP System is:'
Gc_comp = feedback (G_comp, H)

% DC Gain
disp ('The DC Gain of the Closed Loop Compensated IP System is:')
disp (dcgain (Gc_comp))