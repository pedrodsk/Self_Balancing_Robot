%------------------------------------------------------------------------
% data_exp_ip.m
% Design and Development of Closed Loop Control for INVERTED PENDULUM
% By IIEE Visionaries
% Copyright 2003
% Experimental Data of the Inverted Pendulum System
%------------------------------------------------------------------------
% expdata is a MAT File (MATLAB specific binary file),
% with variables exp_data & tout
load expdata
plot (tout,exp_data);
xLabel ('Time (Seconds)');
yLabel('Pendulum Position From Vertical (Degrees)');
Title('Experimental Data');
axis ([0 0.15 -40 40]);
Grid;