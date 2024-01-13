function [ L,U ] = my_lu( A )
%A=LU

N=size(A,1);
EYE=eye(N);

for k=1:N-1
    Lk=EYE;
    for j=k+1:N
       Lk(j,k)=-A(j,k)/A(k,k);
    end
    A=Lk*A;
    invL{k}=2*EYE-Lk;
end

INV_L=EYE;
for k=1:N-1
    INV_L=INV_L+invL{k}-EYE;
end

L=INV_L;
U=A;
end

