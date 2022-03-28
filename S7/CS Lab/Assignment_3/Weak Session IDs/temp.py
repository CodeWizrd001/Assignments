import hashlib

for i in range(25) :
    hex = hashlib.md5(f'{i}'.encode())
    print(hex.hexdigest(),i)