I=imread('D:\Downloads\wyz.jpg');
subplot(1,3,1);
imshow(I);
G=rgb2gray(I);
p=fspecial('prewitt');
s=fspecial('sobel');
I1=imfilter(G,p);
I2=imfilter(G,s);
subplot(1,3,2);
imshow(I1);
subplot(1,3,3);
imshow(I2);