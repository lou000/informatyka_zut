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

calka3 = 0;
s = 0;
for i=a:(b-dx)
    x = a + i*dx;
    s = s+f(x-dx./2);
    calka = calka+f(x);
end
    s=s+func(b-dx./2);
    calka = (dx/6) * (f(a) + f(b) + 2*calka + 4*s)
