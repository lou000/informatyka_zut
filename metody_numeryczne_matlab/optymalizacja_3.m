%METODA GRADIENTU PROSTEGO
f = str2func('@(x, y) ((2*(x.^2))+(y.^2)+(x.*y)-(6.*x)-(5.*y)+8)');
[X,Y] = meshgrid(-5:0.5:5);
Z = f(X,Y);
contour(X,Y,Z,50)
hold on
eps = 0.001;
h = 0.01;
lambda = 0.2;
x0=5;
y0=5;


x=x0;
y=y0;
grad = [1,1];
while(norm(grad)>eps)
    
    dx=(f(x+h, y)-f(x-h, y))/.2*h;
    dy=(f(x, y+h)-f(x, y-h))/.2*h;
    grad = [dx, dy];
    step = grad/norm(grad);
    step = step*lambda;
    oldx=x;
    oldy=y;
    x = x-step(1);
    y = y-step(2);
    line([oldx, x],[oldy, y])
end

disp("X:"+x+" Y:"+y)




