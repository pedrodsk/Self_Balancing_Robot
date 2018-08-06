%-----------------------------------------------------------------------------
% analysis_comp_ip.m
% Design and Development of Closed Loop Control for INVERTED PENDULUM
% By IIEE Visionaries
% Copyright 2003
% Analysis of the Compensated Inverted Pendulum System
%-----------------------------------------------------------------------------
%
% func_ip_comp is a MAT File (MATLAB specific binary file),
% with variables G_comp, G_comp_H, Gc_comp, PID
run trans_func_ip_comp

% Locations of Poles and Zeroes of Open-Loop Compensated Transfer Function in Complex Plane
figure
pzmap (G_comp_H)
axis ([-15 10 -1 1])
title ('Pole-Zero Map of Open-Loop Compensated Inverted Pendulum System')

% Root-Locus Plot of Compensated Inverted Pendulum System
figure
rlocus (G_comp_H)
sgrid (0.76,35)
title ('Root Locus of Compensated Inverted Pendulum System')

% Locations of Poles and Zeroes of Closed-Loop Transfer Function in Complex Plane
figure
pzmap (Gc_comp)
title ('Pole-Zero Map of Closed-Loop Compensated Inverted Pendulum System')

% Impulse Response of Compensated Inverted Pendulum System
figure
impulse (Gc_comp)
title ('Impulse Response of Closed-Loop Compensated Inverted Pendulum System')

% Step Response of Compensated Inverted Pendulum System
figure
step (Gc_comp)
title ('Step Response of Closed-Loop Compensated Inverted Pendulum System')