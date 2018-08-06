%------------------------------------------------------------------------
% data_ip.m
% Design and Development of Closed Loop Control for INVERTED PENDULUM
% By IIEE Visionaries
% Copyright 2003
% Data of the Inverted Pendulum System
%------------------------------------------------------------------------
% tf('s')
%GH2 = zpk([],[0,-4,-2+4i,-2-4i],1)
%p = pole(GH2)
%for 1:10:101
%pzmap(feedback(GH2*k,1));
%hold on
%end
%hold off
%rlocus(GH2);

% Mass of the Cart = 900 gm
M = 0.9; % in Kg

% Mass of the Pendulum = 100 gm
m = 0.1; % in Kg

% Length of Pendulum = 47 cm
Lp = 0.47; % in m

% Length of pendulum to Center of Gravity = 23.5 cm
l = 0.235; % in m

% Moment of Inertia of Pendulum = 5.3 gm-m^2
I = 0.0053; % in Kg.m^2 (m*l²)

% Radius of Pulley = 2.3 cm
r = 0.023; % in m

% Time Constant of Motor = 0.5 second
tau = 0.5; % in seconds

% Gain of Feedback = 9/pi V/rad/sec
Kf = e; % in V/rad/sec

% Gain of Motor = 17 rad/sec/V
Km =17; % in rad/sec/V

% Friction of the Cart = 0.000 N/m/sec
b = 0; % in N/m/sec

% Acceleration due to Gravity = 9.8 m/sec^2
g = 9.8;% in m/sec^2

% Force applied to the cart by the pulley chain mechanism = u
% Cart Position Coordinate = x
% Pendulum Angle with the vertical = theta
Kp = 1 / ((M + m) * g);
K = Kf * Kp * Km * r * (M + m);
Ap = sqrt ((M + m) * m * g * l / ((M + m)*(I + (m * (l ^ 2)))- ((m * l)^2)));

% G1(s) = Theta(s) / U(s)
% ø represents a small angle from the vertical upward direction,
% u represents the input (impulse) force on the cart by pulley chain mechanism.
num_Th_U = [0 0 Kp];
den_Th_U = [Ap^(-2) 0 -1];
G1 = tf (num_Th_U, den_Th_U);
