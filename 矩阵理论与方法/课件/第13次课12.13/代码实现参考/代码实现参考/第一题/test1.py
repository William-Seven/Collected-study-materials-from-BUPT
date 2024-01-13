# -*- coding: utf-8 -*-
'''
求解Ax=b
'''

from __future__ import division
import time
import numpy as np  
from scipy import linalg as la 

N = 3000
b = np.random.random([N,1])

A = np.zeros([N,N])
a0 = np.random.random([1,N])
a1 = np.hstack((a0,a0))

for k in range(0,N):
    A[k,:] = a1[0, N-k:2*N-k]

time0 = time.process_time()


#高斯消去法
x0 = np.linalg.solve(A, b)
time1 = time.process_time()


#scipy版本plu分解
P, L, U = la.lu(A) #A=PLU
z = np.linalg.solve(P, b) #Pz = b 求z
y = np.linalg.solve(L, z) #Ly=z 求y
x1 = np.linalg.solve(U, y) #Ux=y 求x
'''
#补充, 取p为P的逆，就改成了通常所用的列主元LU分解  pA=LU
p = np.linalg.inv(P) #取p为P的逆, pA=LU
y = np.linalg.solve(L, p.dot(b)) #Ly=pb 求y
x1 = np.linalg.solve(U, y) #Ux=y 求x
#'''
time2 = time.process_time()


#循环矩阵可以用fft
Lambda = np.fft.fftn(A[:,0])
inv_lambda = np.diag(1/Lambda)
x2 = np.fft.ifftn(np.dot(inv_lambda, np.fft.fftn(b)))
time3 = time.process_time()


time_gauss = time1 - time0
time_plu = time2 - time1
time_fft = time3 - time2

print('time_gauss',time_gauss)
print('time_plu',time_plu)
print('time_fft',time_fft)
print('error',np.linalg.norm(x0-x1) + np.linalg.norm(x0-x2))