import os
import socket
import sys
import data

class server:
    def __init__(self,sock:socket.socket):
        self.s = sock
        self.dir = os.getcwd() + "/Data/"
    def serve(self):
        os.chdir(self.dir)
        s = data.data(self.s)
        req = s.recv()[0].decode()
        if req == "fileUpdate":
            print(req)
            for i in os.listdir():
                s.add(i.encode())
            print(s.s_buff)
            s.send()
        required = [x.decode() for x in s.recv()]
        s.add("Granted".encode())
        s.send()
        resp = s.recv()
        print(resp)
        if resp[0] == b"Ready":
            for i in required:
                print("Sending %s"%(i))
                f = open(i,'rb')
                context = f.read()
                for i in range(0,len(context),4096):
                    print(i)
                    s.add(context[i:i+4096])
                s.send()
                f.close()

        s.close()
sock = socket.socket()
sock.bind(("localhost",1200))
sock.listen(1)
s,addr = sock.accept()
server(s).serve()
