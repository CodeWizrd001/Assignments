from Question2 import *

def classifyCustomdata(data,features=1,verbose=True) :
    if verbose :
        print("-"*50)
        print(f'Classifying using {Allfeatures[:features]}')

    for i in range(len(data)) :
        x = data[i]
        discVals = {}
        for key in ['W1','W2','W3'] :
            mean = means[key]
            cov = covs[key]
            p = P[key]
            discVals[key] = discriminant(x,mean,cov,features,p)
        val = np.argmax(np.array(list(discVals.values())))
        if verbose :
            print(f'Classified data   {str(x):24s} as  W{val+1}')
    if verbose :
        print("-"*50)

newData = [
    [1,2,1],
    [5,3,2],
    [0,0,0],
    [1,0,0]
]

classifyCustomdata(newData,1)
classifyCustomdata(newData,2)
classifyCustomdata(newData,3)