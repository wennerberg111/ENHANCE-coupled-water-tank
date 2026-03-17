%% load data
clc;
clear;
tank1 = load("Measuring_Tank_1_h_and_V.mat");
tank2 = load("Measuring_Tank_2_h_and_V.mat");

%v1_0cm  = mean(tank1.data(3, 410e2:end));
v1_5cm  = mean(tank1.data(3, 385e2:395e2));
v1_10cm = mean(tank1.data(3, 350e2:360e2));
v1_15cm  = mean(tank1.data(3, 320e2:330e2));
v1_20cm = mean(tank1.data(3, 275e2:285e2));
v1_25cm  = mean(tank1.data(3, 210e2:220e2));
%v1_0  = mean(v1_0cm);
v1_5  = mean(v1_5cm);
v1_10  = mean(v1_10cm);
v1_15  = mean(v1_15cm);
v1_20  = mean(v1_20cm);
v1_25  = mean(v1_25cm);

%v2_0cm  = mean(tank2.data(2, 277e2:end));
v2_5cm  = mean(tank2.data(2, 185e2:193e2));
v2_10cm = mean(tank2.data(2, 162e2:167e2));
v2_15cm  = mean(tank2.data(2, 140e2:145e2));
v2_20cm = mean(tank2.data(2, 98e2:103e2));
v2_25cm  = mean(tank2.data(2, 67e2:72e2));
%v2_0  = mean(v2_0cm);
v2_5  = mean(v2_5cm);
v2_10  = mean(v2_10cm);
v2_15  = mean(v2_15cm);
v2_20  = mean(v2_20cm);
v2_25  = mean(v2_25cm);

%% Least square error
h = [5; 10; 15; 20; 25];
N = length(h);
v1 = [v1_5; v1_10; v1_15; v1_20; v1_25]
v2 = [v2_5; v2_10; v2_15; v2_20; v2_25];
A1 = [v1 ones(N,1)]; 
theta_LLS_1= (A1'*A1)\(A1'*h);
gain_1 = theta_LLS_1(1);
offset_1 = theta_LLS_1(2);

A2 = [v2 ones(N,1)];
theta_LLS_2= (A2'*A2)\(A2'*h);
gain_2 = theta_LLS_2(1);
offset_2 = theta_LLS_2(2);


%%
V3= load('Tank1_3_V.mat')
V5= load('Tank1_5_V.mat')
V10= load('Tank1_10_V.mat')
h =[20 10]

%area of outlet pipe, different for tank 1 and 2
D_tank1 = 0.3175;
D_tank2 = 0.55563;
A_D1 = D_tank1^2 * pi/4;
A_D2 = D_tank2^2 * pi/4;

%area of pipe big
d = 4.445;
A_d = d^2 * pi/4;


V5_vals1 = V5.data(3, 701);
V5_vals2 = V5.data(2, 701);
V10_vals1 = V10.data(3, 625);
V10_vals2 = V10.data(2, 625);

%% Least square error
h1 = [V5_vals1];
h2= [V5_vals2];
N = length(h1);
v = [5];
t_5 = V5.data(1, 701)/100;
t = [t_5];

c = t ./ A_d .* v;

%checking afterwards
A1 = [c ones(N,1)];
theta= (A1'*A1)\(A1'*[h1]);
gamma_1 = beta/ alpha;
gamma_2 = 1 - gamma_1;
%% For simulink data
v_pump = 5;
kp= 3.3;
q= v_pump*kp;
g = 981; 
h1_eq = q^2 * gamma_1^2/ (2*g*A_D1^2)
h2_eq = (q * gamma_2 + A_D1 * sqrt(2*g*h1_eq))^2/(2*g*A_D2^2)


%linearisation
k1= A_D1*g/(A_d*sqrt(2*g*h1_eq));
k2= A_D2*g/(A_d*sqrt(2*g*h2_eq));

A = [-k1, 0;
    k1, -k2]
B = [gamma_1/A_d;
    gamma_2/A_d]
C = eye(2,2);
D = [0;
    0];





