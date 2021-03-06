f = str2func('@(x) x.^(cos(x))');
fp1 = str2func('@(x) x.^(-1 + cos(x)).*(cos(x) - x.*log(x).*sin(x))');
h=0.1;
n=10;
a=0;
b=10;
hold on
fplot(f, [0, 10]);
fplot(fp1)
ylim([-10, 10])
x = 1:0.01:10;
fp2=@(x)((f(x+h)-f(x))./h);
fplot(fp2);
fp3=@(x)((f(x+h)-f(x-h))./(2*h));
fplot(fp3);
fp5=@(x)((1./(12*h))*(f(x-2*h)-8*f(x-h)+8*f(x+h)-f(x+2*h)));
fplot(fp5);
legend('F', 'Wolfram', '2-punkt', '3-punkt', '5-punkt')
hold off

calka = 0;
dx = (b-a)/n;
for i = 1:(b-dx)
    calka=calka+f(i);
end
calka = calka*dx

calka2 = 0;
for i=a:(b-dx)
    calka2 = calka2+f(i);
end
calka2 = calka2+(f(a)+f(b))/2;
calka2 = calka2*dx

% s = 0;
% for i=a:(b-dx)
%     x = a + i*dx;
%     s = s+f(x-dx/2);
%     calka3 = calka3+f(x);
% end
% s=s+f(b-dx/2);
% calka3 = (dx/6) * (f(a) + f(b) + 2*calka3 + 4*s)

% parzyste = 0;
% nieparzyste = 0;
% for i = a+dx:b-dx
%     if mod(i,2)==0
%         parzyste = parzyste + f(i);
%     else
%         nieparzyste = nieparzyste + f(i);
%     end
% end
% calka3 = dx/3*(f(a)+4*parzyste+2*nieparzyste+f(b))
xp = a+dx:2*dx:b-dx;
xn = a+2*dx:2*dx:b-2*dx;
calka3 = dx/3*(f(a)+4*sum(f(xp))+2*sum(f(xn))+f(b))

figure()
hold on
E = 10000;
underCount = 0;
fplot(f);
xlim([0,10])
ylim([0,10])
for i = 1:E
    x = b*rand();
    y = 7*rand();
    if(f(x)>y)
        underCount = underCount+1;
        plot(x, y, 'ob');
    else
        plot(x, y, 'or');
    end
end
calka4 = b*7*underCount/E










    
