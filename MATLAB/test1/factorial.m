function [res] = factorial(n)
%FACTORIAL 此处显示有关此函数的摘要
%   此处显示详细说明
if n==0
    res=1;
else
    res=n*factorial(n-1);
end