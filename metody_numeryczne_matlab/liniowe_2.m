%PROGRAMOWANIE LINIOWE ZADANIE 2

A = [5,25;0.5,0;100,250;10,10];
f = [100;200];
b = [500,15,7500,400];
lb = [0,0];
ub = [];
Aeq = [];
beq = [];

[x,fval] = linprog(-f,A,b,Aeq,beq,lb,ub);
x = ceil(x);
ceil(fval);
zasoby = A * x;

disp('Ilo�� mebli:')
fprintf('krzes�a - %d\nstoly - %d\n\n', x(1), x(2))
disp('Potrzebne zasoby:')
fprintf('drewno - %d\nsk�ra - %.2f\nklej - %d\nnak�ad pracy - %d\n\nZysk: %.0f\n', zasoby(1),zasoby(2),zasoby(3),zasoby(4),-fval)