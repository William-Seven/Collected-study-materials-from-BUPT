clear

N=300;
b=rand(N,1);             %�����������b

A=zeros(N);
a0=rand(N,1);
for k=0:N-1
   A(:,k+1)=circshift(a0,k);        %�������ѭ������A
end

% ���Ax=b

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
time0=cputime;

x_inv=inv(A)*b;             %ֱ���������

time1=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

x_gauss=A\b;             %��˹��ȥ������

time2=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[L,U,P]=lu(A);
x_PLU=U\(L\(P*b));             %PLU�ֽ���㣬����ԪLU�ֽ⣬����PA=LU

time3=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

[L,U]=my_lu(A);
x_my_lu=U\(L\b);             %LU�ֽ���㣬����A=LU

time4=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

error=norm(x_inv-x_my_lu)+norm(x_inv-x_gauss)+norm(x_inv-x_PLU);         %�������
time_inv=time1-time0;
time_gauss=time2-time1;
time_plu=time3-time2;
time_my_lu=time4-time3;

% fprintf('����A������Ϊ%f\n', cond(A));
fprintf('ֱ���������ʱ��Ϊ%f\n', time_inv);
fprintf('��˹��ȥ������ʱ��Ϊ%f\n', time_gauss);
fprintf('PLU�ֽ����ʱ��Ϊ%f\n', time_plu);
fprintf('my_lu����ʱ��Ϊ%f\n', time_my_lu);

error
