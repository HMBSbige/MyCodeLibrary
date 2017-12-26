I=imread('D:\Downloads\wyz.jpg');
subplot(1,2,1);
G=rgb2gray(I);
imshow(G);
subplot(1,2,2);
imhist(G);