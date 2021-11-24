import socket
import traceback

class SocketServer():
    def __init__(self, host="127.0.0.1", port=8080):
        self.host = host
        self.port = port
        self.sock = None

    def initialize(self):
        # AF_INET : IPV4
        # SOCK_STREAM : TCP
        self.sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

    def listen(self):
        try:
            # () -> tuple (any, any) -> (int, str)
            self.sock.bind((self.host, self.port))
            # f-string f""
            print(f"listen on {self.host}, {self.port}")
            self.sock.listen() # blocking -> sleep
            (conn, address) = self.sock.accept()
            """
                listen : 8080
                client -> server 44468 -> 8080
                44468
            """
            print(f"Successfully from {address}")
            return conn
        except:
            traceback.print_exc()

    def send_text(self, conn, text):
        """
        byte 0x121245
        str "1234"
        utf-8
        0~128 0xff -> utf-8
        """
        print("HIHI".encode('utf-8'))
        conn.send(text.encode('utf-8'))

        """
        1. send
        2. send_all 60000000/(4096 | 1024) for image
        """

    def recv_text(self, conn):
        msg = conn.recv(4096)
    
if __name__ == "__main__":
    socket_server = SocketServer("127.0.0.1", 7585)
    socket_server.initialize()
    conn = socket_server.listen()
    socket_server.send_text(conn, "HIHI")

