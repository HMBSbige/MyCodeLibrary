I=imread('D:\Downloads\wyz.jpg');
subplot(1,2,1);
G=rgb2gray(I);
H=histeq(G);
imshow(H);
subplot(1,2,2);
imhist(H);