# -*- coding: utf-8 -*-
#!/usr/bin/python

from __future__ import division
import numpy as np  

def fun(y, k, c):
    
    z = c[0] + np.random.random() * 0.1
    for s in range(0, k):
        z += c[s+1] * y[s]

    for s in range(0, k):
        z += c[s+1] * y[s]**2
    
    for s in range(0, k-1):
        z += c[s+1] * y[s] * y[s+1]

    return z

    
N = 4000
k = 4
J = 1

sigma = np.eye(k)
y = np.zeros(k)
f = open('data.txt','w')

c = np.random.random(k+1)
c[0] *= 30

for j in range(0,J):

    mu = np.random.random(k)*30
    A = np.random.multivariate_normal(mu, sigma, N)
    
    for n in A:
        mm=0
        for s in n:
            f.write(str(s) + '\t')
            y[mm] = s
            mm = mm + 1
        
        z = fun(y,k,c)
        f.write(str(z))
        f.write('\r\n') #\r\n为换行符  
        
f.close()
