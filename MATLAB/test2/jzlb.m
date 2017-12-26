I=imread('D:\Downloads\lena1.jpg');
subplot(1,2,1);
imshow(I);
n=5;
t=ones(n);
[h,w]=size(I);
x1=double(I);
x2=x1;
for i=1:h-n+1
    for j=1:w-n+1
        c=x1(i:i+n-1,j:j+n-1).*t;
        s=sum(sum(c));
        x2(i+(n-1)/2,j+(n-1)/2)=s/(n*n);
    end
end
G=uint8(x2);
subplot(1,2,2);
imshow(G);