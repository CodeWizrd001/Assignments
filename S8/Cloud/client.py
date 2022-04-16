import socket

sock = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

HOST = "127.0.0.1"
PORT = 5679
BUFFER_SIZE = 2048
address = (HOST,PORT)

count = int(input("Seconds : "))

sock.connect(address)
sock.send(count.encode())
res = sock.recv(BUFFER_SIZE).decode()
print('[+] Server Response : {res}')