f = str2func('@(x) ((x.^3)+(x.^2)-(20.*x))');
% fplot(f, [0, 6]);
a=0;
b=6;
eps = 0.0001;

%METODA PO£OWIENIA
t_a = a;
t_b = b;
if(f(t_a)*f(t_b)>0)
    disp('Funkcja nie spe³nia warunków')
else
    xmid = (t_a+t_b)/2;
    L=t_b-t_a;
    while(abs(L)>eps)
        fXM = f(xmid);
        L=t_b-t_a;
        x1 = t_a+(L/4);
        x2 = t_b-(L/4);
        fx1 = f(x1);
        fx2 = f(x2);
        if(fx1<fXM)
            t_b=xmid;
            xmid=x1;
        elseif(fx2<fXM)
            t_a=xmid;
            xmid=x2;
        else
            t_a = x1;
            t_b = x2;
        end
    end
    disp('Metoda po³owienia')
    disp(xmid)
end


%METODA Z£OTEGO PODZIA£U
k = (sqrt(5)-1)/2;
t_a = a;
t_b = b;
xL = t_b-k.*(t_b-t_a);
xR = t_a+k.*(t_b-t_a);
while((t_b-t_a) > eps)
    if(f(xL)<f(xR))
        t_b = xR;
        xR = xL;
        xL = t_b-k*(t_b-t_a);
    else
        t_a = xL;
        xL = xR;
        xR = t_a+k*(t_b-t_a);
    end
end
disp("Metoda z³otego podzia³u");
disp((t_a+t_b)/2);

%METODA NEWTONA

syms x
fp = diff((x.^3)+(x.^2)-(20.*x));
fpp = diff(fp);
fp = matlabFunction(fp);
fpp = matlabFunction(fpp);
x0=b;
prevX = 0;
while(abs(x0-prevX)>eps)
    prevX = x0;
    x0= prevX - fp(prevX)/fpp(prevX);
end
disp(x0);




