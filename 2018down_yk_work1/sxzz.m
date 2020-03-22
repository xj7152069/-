%射线层析matlab求解

clear all
close all

X=40;
Y=20;
wc=0.001;

L=zeros(X*X,X*Y);

L=load("L");
v=load("v");
T=load("T");
sx=load("sx");

I=zeros(X*Y,X*Y);
for i=1:X*Y
    I(i,i)=wc;
end

s=zeros(X*Y,1);
s=((L'*L+I)\speye(X*Y))*L'*T;

s1=zeros(Y,X);
for i=1:Y
    for j=1:X
        s1(i,j)=1.0/s((i-1)*X+j);
    end
end

figure(1)
contourf(s1(:,1:X-1))

figure(2)
contourf(v)

figure(3)             %绘制射线路径
for i=1:2*(X-1)*(X-1)
    a=sx(i,1);
    b=sx(i,2);
    x=0:X;
    y=0:Y;
        y=a*x+b;
    plot(x,y)
    axis([0,X,0,Y])
    hold on
end


figure(4)

    s2=L(40,:);
    for i=1:Y
      for j=1:X
        s3(i,j)=s2((i-1)*X+j);
      end
    end
    contourf(s3)
    hold on



