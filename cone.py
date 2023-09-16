import os
import socket
import sys
import data

class Service:
    def __init__(self,sock):
        self.s = sock
        self.dir = os.getcwd()+"/Data/Data"
    def serve(self):
        os.chdir(self.dir)
        s = data.data(self.s)
        s.add("fileUpdate".encode())
        s.send()
        dat  = [x.decode() for x in s.recv()]
        file = os.listdir()
        required = []
        print(dat)
        for i in dat:
            if i not in file and i != "Data":
                required.append(i)
                s.add(i.encode())
        print(required)
        s.send()
        resp = s.recv()
        if resp[0] == "Granted".encode():
            s.add("Ready".encode())
            s.send()
        print("B2")
        for i in required:
            f = open(i,'wb')
            dt = s.recv()
            print("B1")
            for i in dt:
                f.write(i)
            f.close()
        s.close()
        

sock = socket.socket()
sock.connect(("localhost",1200))
Service(sock).serve()
