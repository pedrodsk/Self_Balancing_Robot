[num,den] = tfdata(C);
c2 = cell2mat(num);
Kd = c2(1);
Kp = c2(2);
Ki= c2(3);
display(Kp,'kp')
display(Kd,'kd')
display(Ki,'ki')

pd=1000;
num_PID = [Kd Kp Ki];
den_PID = [1 0];
PID = tf (num_PID, den_PID)
s = tf('s');
PID = Kp+Ki/s+Kd*pd*s/(s+pd)

G_comp = series (PID, G1);
Gc_comp = feedback(G_comp,H);
step(Gc_comp);





% Open Loop Transfer Function of the Compensated System
% G_comp_H(s) = G_comp(s) * H(s)
G_comp_H = series (G_comp, H);

% Closed-Loop Transfer Function of the Compensated System
% Gc_comp
disp 'Closed Loop Transfer Function of the Compensated IP System is:'
Gc_comp = feedback (G_comp, H)
