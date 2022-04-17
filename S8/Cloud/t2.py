import time

print("Hello World",end="")

for i in range(100) :
    print(f'\r{i}\n',end="")
    time.sleep(0.5)