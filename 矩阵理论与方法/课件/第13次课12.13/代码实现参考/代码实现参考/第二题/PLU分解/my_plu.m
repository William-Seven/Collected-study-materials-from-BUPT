function [ P,L,U ] = my_plu( A )
%A=LU(P^-1)

N=size(A,1);
EYE=eye(N);

a=zeros(N,1);

for k=1:N-1
    
    a=A(k,:);
    m=find(abs(a)==max(abs(a)));
    Pk=EYE;
    Pk(:,[k m])=Pk(:,[m k]);
    A=A*Pk;
    PP{k}=Pk;
    
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

P=EYE;
for k=1:N-1
    P=P*PP{k};
end

end

