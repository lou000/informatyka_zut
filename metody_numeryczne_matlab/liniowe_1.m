%PROGRAMOWANIE LINIOWE ZADANIE 1
A = [4,6,15;2,2,0;5,3,4;7,3,12];
f = [2,1.5,3];
b = [250,60,100,220];
Aeq = [];
beq = [];
lb = [0,0,0];
ub = [];

[x,fval] = linprog(f,-A,-b,Aeq,beq,lb,ub);
x = ceil(x);
fval = f * x;
wartosci = A * x;

disp('Iloœci produktów:')
fprintf('kanapki  - %d\npierogi  - %d\ns³odycze - %d\n\n', x(1), x(2), x(3))
disp('Wartoœci od¿ywcze:')
fprintf('bia³ko - %d\nt³uszcz - %d\nwitaminy - %d\nwêglowodany - %d\n\nKoszt diety: %.2f\n',wartosci(1),wartosci(2),wartosci(3),wartosci(4),fval)
