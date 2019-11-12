func =str2func('@(x)exp(x) + x.^2-2');
fplot(func, [-2, 2])
a=-1;
b=1;
eps=0.001;

%FZERO
disp('Metoda FZERO')
disp(fzero(func,[-1,1]))

%METODA PO£OWIENIA
t_a = a;
t_b = b;
fA = func(t_a);
fB = func(t_b);
if(fA*fB>0)
    disp('Funkcja nie spe³nia warunków')
else
    while(abs(t_a-t_b)>eps)
        x0 = (t_a+t_b)/2;
        f0 = func(x0);
        if(abs(f0)<eps)
            break
        end
        if((func(t_a)*f0)<0)
            t_b = x0;
        else
            t_a = x0;
        end
    end
    disp('Metoda po³owienia')
    disp(x0)
end

%METODA FALSIEGO
t_a = a;
t_b = b;
fA = func(t_a);
fB = func(t_b);
x1 = a;
x0 = b;
if(fA*fB>0)
    disp('Funkcja nie spe³nia warunków')
else
    while(abs(x1-x0)>eps)
        x1 = x0;
        x0 = a-(fA*((t_b-t_a)/(fA-fB)));
        f0 = func(x0);
        
        
    end
end

