clear

N=3000;
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

x_fft=ifft(diag(1./fft(A(:,1)))*fft(b));         %ѭ������������ÿ��ٸ���Ҷ�任����

time4=cputime;
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

error=norm(x_inv-x_fft)+norm(x_inv-x_gauss)+norm(x_inv-x_PLU);         %�������
time_inv=time1-time0;
time_gauss=time2-time1;
time_plu=time3-time2;
time_fft=time4-time3;

% fprintf('����A������Ϊ%f\n', cond(A));
fprintf('ֱ���������ʱ��Ϊ%f\n', time_inv);
fprintf('��˹��ȥ������ʱ��Ϊ%f\n', time_gauss);
fprintf('PLU�ֽ����ʱ��Ϊ%f\n', time_plu);
fprintf('FFT����ʱ��Ϊ%f\n', time_fft);

error
