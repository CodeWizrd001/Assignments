import socket
import time
from threading import Thread

notifySocket = socket.socket(socket.AF_INET,socket.SOCK_STREAM)

HOST = "192.168.122.1"
PORT = 5678
SERVER_PORT = 5679
BUFFER_SIZE = 2048

notifySocket.connect((HOST,PORT))
notifySocket.send("RegNewServer".encode())

server = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
server.bind(("0.0.0.0",SERVER_PORT))
server.listen(5)

print(f'[+] Listening to connections on : 0.0.0.0:{SERVER_PORT}')

def handle_connected(conn=None,addr="") :
    data = float(conn.recv(BUFFER_SIZE).decode())
    endTime = time.time() + data
    while time.time() < endTime :
        x = 2*2
    conn.send("DONE".encode())

while True :
    connection , client_addr = server.accept()
    connectionThread = Thread(target=handle_connected,args=(connection,client_addr,))
    connectionThread.start() 