clear

N=300;
b=rand(N,1);             %随机生成向量b

A=zeros(N);
a0=rand(N,1);
for k=0:N-1
   A(:,k+1)=circshift(a0,k);        %随机生成循环矩阵A
end

% 求解Ax=b

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
time0=cputime;

x_inv=inv(A)*b;             %直接求逆计算

time1=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

x_gauss=A\b;             %高斯消去法计算

time2=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[L,U,P]=lu(A);
x_PLU=U\(L\(P*b));             %PLU分解计算，列主元LU分解，满足PA=LU

time3=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[P,L,U]=my_plu(A);
x_my_plu=P*(U\(L\b));             %行主元LU分解计算，满足A=LU(P^-1)

time4=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

error=norm(x_inv-x_my_plu)+norm(x_inv-x_gauss)+norm(x_inv-x_PLU);         %检验误差
time_inv=time1-time0;
time_gauss=time2-time1;
time_plu=time3-time2;
time_my_plu=time4-time3;

% fprintf('矩阵A条件数为%f\n', cond(A));
fprintf('直接求逆计算时间为%f\n', time_inv);
fprintf('高斯消去法计算时间为%f\n', time_gauss);
fprintf('PLU分解计算时间为%f\n', time_plu);
fprintf('my_plu计算时间为%f\n', time_my_plu);

error
