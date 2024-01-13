# -*- coding: utf-8 -*-
#!/usr/bin/python
from __future__ import division
import numpy as np  

data   = []  
labels = []  

with open("data.txt") as ifile:  
        for line in ifile:  
            tokens = line.strip().split('\t')  
            if tokens != ['']:
                data.append([float(tk) for tk in tokens[:-1]])  
                labels.append(tokens[-1]) 
x = np.array(data) 
y = np.array(labels) 
            
from sklearn.model_selection import train_test_split
x_train, x_test, y_train, y_test = train_test_split(x, y, test_size = 0.01) 

''' LinearRegression '''  
import sklearn.linear_model as skl

lr = skl.LinearRegression()
lr.fit(x_train, y_train)

y_predict_train = lr.predict(x_train)

print('w=', lr.coef_, 'b=', lr.intercept_)
''' LinearRegression '''  

y_predict = lr.predict(x_test)

N = y_test.size
X = range(0,N)
Y1 = np.double(y_test)
Y2 = np.double(y_predict)

GError = np.abs(Y1-Y2)
RMSE = np.sqrt(np.dot(GError, GError)/N)

print("RMSE_test=", RMSE)

import matplotlib.pyplot as plt  

fig = plt.figure('fig')
plt.plot(X, Y1, 'b', lw=1)
plt.plot(X, Y2, 'r+')
