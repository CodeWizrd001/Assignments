import socket
import sys

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

HOST = "192.168.122.1"
PORT = 5679
BUFFER_SIZE = 2048
address = (HOST,PORT)

try :
    count = sys.argv[1]
except IndexError as e :
    count = input("Seconds : ")
except Exception as e :
    print(f'[+] InputException : {e}')

sock.connect(address)
sock.send(count.encode())
res = sock.recv(BUFFER_SIZE).decode()
print(f'[+] Server Response : {res}')