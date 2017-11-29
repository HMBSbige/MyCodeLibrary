t=30;   %迭代次数
n=7;
rh=(2*pi)/(2*(n-1));
hold on;
for i=1:t
    l=linspace(0,2*pi,n);
    l=l+rh*(i-1);
    x=((sqrt(3)/2)^(i-1))*cos(l);
    y=((sqrt(3)/2)^(i-1))*sin(l);
    plot(x,y,'r');
    axis equal;
    axis([-1 1 -1 1]);
end