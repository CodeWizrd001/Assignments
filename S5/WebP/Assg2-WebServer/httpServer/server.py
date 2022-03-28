from http.server import HTTPServer, BaseHTTPRequestHandler
from socketserver import ThreadingMixIn
import threading
import time

HOST = '0.0.0.0'
PORT = 5050             #Task 1 Modification

class ThreadedSimpleServer(ThreadingMixIn,HTTPServer):
    pass

class ClientHandler(BaseHTTPRequestHandler):
    Routes = {
        '':'index.html',
        '/page2':'page2.html',
        '/modify' : 'modify.html'       #Task 2 Modification
    }
    def do_GET(self):
        print("Request received from, ",self.client_address)
        #time.sleep(3.0)
        #print("Continuing with ",self.client_address)
        self.path = self.path.rstrip('/')
        print(self.path)
        try:
            resource = self.Routes[self.path]
            try:
                f = open(resource).read()
                self.send_response(200)
            except:
                f = "[Error : 404]\nFile Not Found"
                self.send_response(404)
        except:
            if self.path=='/getmoved.html':
                self.send_response(301)
                self.send_header('Location','https://www.google.com')
                self.end_headers()
                return
            else:
                f = "[Error : 404]\nURL Not Found"
                self.send_response(404)
        f = bytes(f,'utf-8')
        self.send_header('Content-Length',len(f))
        self.send_header('Content-Type','text/html; charset=utf-8')
        self.end_headers()
        self.wfile.write(f)

if __name__ == "__main__":
    print(f"\n[SERVER LISTENING AT PORT {PORT}]")
    print("================================")
    ThreadedServer = ThreadedSimpleServer((HOST, PORT),ClientHandler)
    ThreadedServer.serve_forever()
