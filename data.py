import socket


class data():
    def __init__(self,sock:socket.socket,_data=None):
        if _data != None:
            self.s_buff = [_data]
        else:
            self.s_buff = []
        self.size = []
        self.s = sock
        self.r_buff = []
    def add(self,data):
        self.s_buff.append(data)
        self.size.append(len(data))
    def remove(self,index):
        self.s_buff.remove(index)
        self.size.remove(index)
    def clear(self):
        self.s_buff.clear()
        self.size.clear()
        self.r_buff.clear()
    def sp(self):
        self.s.send("\\xff".encode())
        resp = self.s.recv(4).decode()
        if resp == "\\xff":
            return
        else:
            raise RuntimeError("Recvie Error signal : %s"%(resp))
        return
    def rp(self):
        resp = self.s.recv(4)
        if resp != "\\xff".encode():
            raise RuntimeError("Recive Error signal : %s"%(resp))
        self.s.send(resp)
    def send(self):
        self.sp()
        for i in range(len(self.s_buff)):
            self.s.send("\\xif".encode())
            resp = self.s.recv(4)
            if resp != "\\xrf".encode():
                raise RuntimeError("Recive Error signal :%s"%(resp))
            self.s.send(str(self.size[i]).encode())
            resp = self.s.recv(4)
            if resp != "\\xff".encode():
                raise RuntimeError("Recvie Error signal :%s"%(resp))
            self.s.send(self.s_buff[i])
            resp = self.s.recv(4)
            if resp != "\\xff".encode():
                raise RuntimeError("Recive Error signal :%s"%(resp))
        self.s.send("\\xfb".encode())
        if self.s.recv(4) != "\\xfb".encode():
            self.s.shutdown(1)
            self.s.close()
            raise RuntimeError("Recive Error signal :%s"%(resp))
        self.s_buff.clear()
        self.size.clear()
        return
    def recv(self):
        self.r_buff.clear()
        self.rp()
        while 1:
            signal = self.s.recv(4)
            if signal == "\\xfb".encode():
                break
            elif signal != "\\xif".encode():
                self.s.shutdown(1)
                self.s.close()
                raise RuntimeError("Recive Error signal :%s"%(signal))
            self.s.send("\\xrf".encode())
            size = self.s.recv(4).decode()
            size = int(size)
            self.s.send("\\xff".encode())
            data = self.s.recv(size)
            self.r_buff.append(data)
            self.s.send("\\xff".encode())
        self.s.send("\\xfb".encode())
        return self.r_buff
    def close(self):
        self.size.clear()
        self.s_buff.clear()
        self.r_buff.clear()
        self.s.shutdown(1)
        self.s.close()
        return





            
                
