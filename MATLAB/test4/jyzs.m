I=imread('D:\Downloads\lena.bmp');
subplot(4,1,1);
imshow(I);
title('未加噪声的图像');

J=imnoise(I,'salt & pepper',0.01);
[M,N]=size(J);
for i=1:M
    for j=1:N
        if(J(i,j)==0)
            J(i,j)=255;
        end
    end
end
subplot(4,1,2);
imshow(J);
title('加入盐噪声的图像');

J=imnoise(I,'salt & pepper',0.01);
[M,N]=size(J);
for i=1:M
    for j=1:N
        if(J(i,j)==255)
            J(i,j)=0;
        end
    end
end
subplot(4,1,3);
imshow(J);
title('加入椒噪声的图像');

J=imnoise(I,'salt & pepper',0.01);
[M,N]=size(J);
subplot(4,1,4);
imshow(J);
title('加入椒盐噪声的图像');
