%METODA SPADKU WZGLÊDEM WSPÓ£RZÊDNYCH
f = str2func('@(x, y) ((2*(x.^2))+(y.^2)+(x.*y)-(6.*x)-(5.*y)+8)');
[X,Y] = meshgrid(-5:0.5:5);
Z = f(X,Y);
contour(X,Y,Z,50)
k = 0.2;
x0=-4;
y0=-4;
hold on

while(1)
   oldX = x0;
   oldY = y0;
   f0 = f(x0,y0);
   f1 = f(x0,y0+k);
   f2 = f(x0,y0-k);
   f3 = f(x0+k,y0);
   f4 = f(x0-k,y0);
   MIN = min([f0,f1,f2,f3,f4]);
   if(MIN==f1)
       y0=y0+k;
   elseif(MIN==f2)
       y0=y0-k;
   elseif(MIN==f3)
       x0=x0+k;
   elseif(MIN==f4)
       x0=x0-k;
   else
       break;
   end
   line([oldX, x0],[oldY, y0])
end
disp("X:"+x0+" Y:"+y0)
disp("MID:"+MIN)


%METODA GAUSSA-SEIDLA
x0=5;
k = (sqrt(5)-1)/2;

figure()
hold on
contour(X,Y,Z,50)
eps = 0.01;
check = 10;
while(check>eps)
    t_a = -5;
    t_b = 5;
    xL = t_b-k.*(t_b-t_a);
    xR = t_a+k.*(t_b-t_a);
    while((t_b-t_a) > eps)
        if(f(x0,xL)<f(x0,xR))
            t_b = xR;
            xR = xL;
            xL = t_b-k*(t_b-t_a);
        else
            t_a = xL;
            xL = xR;
            xR = t_a+k*(t_b-t_a);
        end
    end
    oldY = y0;
    y0=(t_a+t_b)/2;
    line([x0,x0],[oldY, y0])

    t_a = -5;
    t_b = 5;
    xL = t_b-k.*(t_b-t_a);
    xR = t_a+k.*(t_b-t_a);
    while((t_b-t_a) > eps)
        if(f(xL, y0)<f(xR, y0))
            t_b = xR;
            xR = xL;
            xL = t_b-k*(t_b-t_a);
        else
            t_a = xL;
            xL = xR;
            xR = t_a+k*(t_b-t_a);
        end
    end
    oldX = x0;
    x0 =(t_a+t_b)/2;
    line([oldX,x0],[y0, y0])
    check = sqrt((oldX-x0).^2+(oldY+y0).^2);
end
