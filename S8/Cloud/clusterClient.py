import time
import sys
import os

from threading import Thread

try :
    count = sys.argv[1]
    t = sys.argv[2]
except IndexError as e :
    count = input("Count : ")
    t = input("Duration : ")
except Exception as e :
    print(f'[+] InputException : {e}')

try :
    interval = sys.argv[3]
except IndexError as e :
    interval = 1
except Exception as e :
    print(f'[+] InputException : {e}')

try :
    count = int(count)
    t = float(t)
    interval = float(interval)
except Exception as e :
    count = 10
    t = 0.2
    interval = 1
    
command = f'python client.py {t}'

for i in range(count) :
    time.sleep(interval)
    rThread = Thread(target=os.system,args=(command,))
    rThread.start()

print(f'[+] Running Request')
time.sleep(t*count)
print(f'[+] Requests Done')