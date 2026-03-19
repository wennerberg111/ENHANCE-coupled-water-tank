%% load data
clc;
clear;
tank1 = load("Measuring_Tank_1_h_and_V.mat");
tank2 = load("Measuring_Tank_2_h_and_V.mat");
V2= load('Tank1_2_V.mat')
V5= load('Tank1_5_V.mat')
V3= load('Tank1_3_V.mat')
V8= load('Tank1_8_V.mat')
V10= load('Tank1_10_V.mat')
VA= load('Va.mat')

D_tank1 = 0.3175;
D_tank2 = 0.55563;
d = 4.445;


A_D1 = D_tank1^2 * pi/4;
A_D2 = D_tank2^2 * pi/4;
S = d^2 * pi/4;

v1_5= mean(tank1.data(3, 385e2:395e2));
v1_10 = mean(tank1.data(3, 350e2:360e2));
v1_15  = mean(tank1.data(3, 320e2:330e2));
v1_20 = mean(tank1.data(3, 275e2:285e2));
v1_25  = mean(tank1.data(3, 210e2:220e2));

v2_5  = mean(tank2.data(2, 185e2:193e2));
v2_10 = mean(tank2.data(2, 162e2:167e2));
v2_15  = mean(tank2.data(2, 140e2:145e2));
v2_20 = mean(tank2.data(2, 98e2:103e2));
v2_25  = mean(tank2.data(2, 67e2:72e2));

% Least square error
h = [5; 10; 15; 20; 25];
N = length(h);
v1 = [v1_5; v1_10; v1_15; v1_20; v1_25];
v2 = [v2_5; v2_10; v2_15; v2_20; v2_25];
A1 = [v1 ones(N,1)]; 
theta_LLS_1= (A1'*A1)\(A1'*h);
gain_1 = theta_LLS_1(1);
offset_1 = theta_LLS_1(2);
A2 = [v2 ones(N,1)];
theta_LLS_2= (A2'*A2)\(A2'*h);
gain_2 = theta_LLS_2(1);
offset_2 = theta_LLS_2(2);

final_offset = load("Data_18-Mar-2026_09-35-42.mat");
offset_1= offset_1+mean(final_offset.data(3, 45e2:50e2));
offset_2= offset_2+mean(final_offset.data(2, 45e2:50e2));

%% v=3
v=3
t_1  = V3.data(1,948)-V3.data(1,666); 
t_2 = V3.data(1, 948)-V3.data(1,666);

h2 = V3.data(2,948)-V3.data(2,666); 
h1 = V3.data(3,948)-V3.data(3,666); 
phi_1 = t_1* v / S;
A1 = [phi_1, ones(length(phi_1), 1)];
theta_h1 = A1 \ h1;
beta    = theta_h1(2);

phi_2 = (t_2 .* v) / S;
A2 = [phi_2, ones(length(phi_2), 1)];
theta_h2 = A2 \ h2;
alpha_minus_beta= theta_h2(2);
alpha = alpha_minus_beta + beta;
gain_pump = alpha;  
split = beta / alpha;  

gamma_1 = beta/ alpha;
gamma_2 = 1 - gamma_1;


%%
v_pump  = 3;
f= load('Data_for_gain.mat')

A_D1=0.070;
A_D2=0.2247;
gain_pump =12.263
%(f.data(3,28880)-f.data(3,27989))/(f.data(1,28880)-f.data(1,27989))*100

gamma_1 = 0.314;
gamma_2 = 1 - gamma_1;

g = 981;            % cm/s^2
q = gain_pump * v_pump;   % total pump flow, cm^3/s

% --- Correct equilibrium points ---

h1_eq = q^2 * gamma_1^2 / (2*g*A_D1^2)
h2_eq = q^2 / (2*g*A_D2^2)

fprintf('h1_eq = %.3f cm\n', h1_eq);
fprintf('h2_eq = %.3f cm\n', h2_eq);

% --- Correct Jacobian coefficients ---
k1 = (A_D1*g) / (S * sqrt( (2*g*h1_eq)));
k2 = (A_D2*g) / (S * sqrt( (2*g*h2_eq)));

% --- State space matrices ---
A_sys = [-k1,  0;
          k1, -k2];

B_sys = gain_pump * [(gamma_1) / S;
                           gamma_2  / S];

C_sys = eye(2,2);     % output is L2 only
D_sys = [0;
    0];
sys = ss(A_sys, B_sys,  C_sys, D_sys);
s= tf('s');
par= load('parameters.mat')
G= C_sys*((s*eye(2,2)-A_sys)^-1)*B_sys;
Tf= minreal(R*G(2),0.2)

%% state space

wanted_poles= [-0.1, -0.2];
Ka= place(A_sys, B_sys, wanted_poles)

Kff = -inv([0 1]*inv(A_sys - B_sys*Ka)*B_sys)
