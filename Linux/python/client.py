import socket
import traceback

class SocketClient():
    def __init__(self, remote = "127.0.0.1", port = 8080):
        self.remote = remote
        self.port = port
        self.sock = None

    def initialize(self):
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def connect(self):
        try:
            self.sock.connect((self.remote, self.port))
            print(f"Successfully connect to {self.remote} {self.port}")
        except:
            traceback.print_exc()

    def recv_text(self):
        msg = self.sock.recv(4096)
        print(msg)

if __name__ == "__main__":
    socket_client = SocketClient(remote = "127.0.0.1", port = 7585)
    socket_client.initialize()
    socket_client.connect()
    socket_client.recv_text()
