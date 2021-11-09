import numpy as np

import warnings
warnings.filterwarnings("ignore", category=RuntimeWarning) 

data = {
    'W1': np.array([
        [-5.01, -8.12, -3.68],
        [-5.43, -3.48, -3.54],
        [1.08, -5.52, 1.66],
        [0.86, -3.78, -4.11],
        [-2.67, 0.63, 7.39],
        [4.94, 3.29, 2.08],
        [-2.51, 2.09, -2.59],
        [-2.25, -2.13, -6.94],
        [5.56, 2.86, -2.26],
        [1.03, -3.33, 4.33]
    ]),
    'W2': np.array([
        [-0.91, -0.18, -0.05],
        [1.30, -2.06, -3.53],
        [-7.75, -4.54, -0.95],
        [-5.47, 0.50, 3.92],
        [6.14, 5.72, -4.85],
        [3.60, 1.26, 4.36],
        [5.37, -4.63, -3.65],
        [7.18, 1.46, -6.66],
        [-7.39, 1.17, 6.30],
        [-7.50, -6.32, -0.31]
    ]),
    'W3' : np.array([
        [5.35, 2.26, 8.13],
        [5.12, 3.22, -2.66],
        [-1.34, -5.31, -9.87],
        [4.48, 3.42, 5.19],
        [7.11, 2.39, 9.21],
        [7.17, 4.33, -0.98],
        [5.75, 3.97, 6.65],
        [0.77, 0.27, 2.41],
        [0.90, -0.43, -8.71],
        [3.52, -0.36, 6.43]
    ]),
}

means = {}
covs = {}
for key in data:
    means[key] = np.mean(data[key], axis=0)
    covs[key] = np.cov(data[key].T)

def discriminant(x,mean,cov,feats,p) :
    x = x[0:feats]
    mean = mean[0:feats]
    cov = cov[0:feats,0:feats]

    temp = -0.5*np.dot(np.dot((x-mean).T,np.linalg.inv(cov)),(x-mean))
    temp += -0.5*feats*np.log(2*np.pi)
    temp += -0.5*np.log(np.linalg.det(cov))

    temp += np.log(p)

    return temp

Allfeatures = ['X1','X2','X3']

def classifyWithFeaturesWithError(features=1,verbose=True) :
    if verbose :
        print(f'Classifying using {Allfeatures[:features]}')
    totalCorrect = 0
    totalWrong = 0
    for w in data :
        if verbose :
            print("-"*35)
            print(" "*10+"Class : ",w)
            print("-"*35)
        classCorrect = 0
        classWrong = 0
        for i in range(len(data[w])) :
            x = data[w][i]
            discVals = {}
            P = {
                'W1': 0.5,
                'W2': 0.5,
                'W3': 0
            }
            for key in ['W1','W2','W3'] :
                mean = means[key]
                cov = covs[key]
                p = P[key]
                discVals[key] = discriminant(x,mean,cov,features,p)
            val = np.argmax(np.array(list(discVals.values())))
            if w == f'W{val+1}' :
                classCorrect += 1
            else :
                classWrong += 1
            if verbose :
                print(f'Classified data   {str(x):24s} as  W{val+1}')
        misclassifed = 100 * classWrong / (classWrong + classCorrect)
        if verbose :
            print('-'*35)
            print(f'Percentage Misclassifed : {misclassifed:.2f}%')
        totalCorrect += classCorrect
        totalWrong += classWrong
    totalMisclassifed = 100 * totalWrong / (totalWrong + totalCorrect)
    if verbose :
        print('-'*50)
        print(f'Total Percentage Misclassifed : {totalMisclassifed:.2f}%')
        print('-'*50)
    return totalMisclassifed
    
classifyWithFeaturesWithError(3)