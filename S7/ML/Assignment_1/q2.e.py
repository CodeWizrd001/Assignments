from Question2 import *

errors = {}

for i in [1,2,3] :
    errors[tuple(Allfeatures[:i])] = classifyWithFeaturesWithError(i,False)

print("Misclassifications : ")

print(' '*5+'-'*40)
print(' '*5+f'|  {"Features":20s}  |  {"Error":9s}  |')
print(' '*5+'-'*40)
for f in errors :
    print(' '*5+f'|  {str(f):20s}  |  {str(errors[f])+"%":9s}  |')
print(' '*5+'-'*40)