%-----------------------------------------------------------------------------
% analysis_uc_ip.m
% Design and Development of Closed Loop Control for INVERTED PENDULUM
% By IIEE Visionaries
% Copyright 2003
% Analysis of the Uncompensated Inverted Pendulum System
%-----------------------------------------------------------------------------
%
% func_ip is a MAT File (MATLAB specific binary file),
% with variables G, GH, H, Th_U, U_E
%load func_ip

% Locations of Poles and Zeroes of Open-Loop Transfer Function in Complex Plane
figure
pzmap (G)
title ('Pole-Zero Map of Open-Loop Uncompensated Inverted Pendulum System')

% Impulse Response
figure
impulse (G)
title ('Impulse Response of Open Loop Uncompensated Inverted Pendulum System')

% Step Response
figure
step (G)
title ('Step Response of Open Loop Uncompensated Inverted Pendulum System')

% Locations of Poles and Zeroes of Closed-Loop Transfer Function in Complex Plane
figure
pzmap (feedback (G, H))
title ('Unity Feedback Closed-Loop Uncompensated Inverted Pendulum System')

% Root Locus Plot of Uncompensated System
figure
rlocus (GH)
title ('Root Locus of Uncompensated Inverted Pendulum System')