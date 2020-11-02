import socket
import argparse as ap
import time


def coords(s):
    try:
        x, y = map(int, s.split(","))
        return x, y
    except:
        print("error in coords")


endl = '\r\n'
parser = ap.ArgumentParser(description="Client To Test Ex4 in Advanced programming")
parser.add_argument("-p", default=8081, type=int, help="port to use")
parser.add_argument("-a", default="A*", choices=["A*", "BFS", "DFS", "BestFS"],
                    help="the algorithm to ask the server to use, default A*")
parser.add_argument("-s", default=(0, 0), type=coords, help="starting point separated by comma")
parser.add_argument("-e", default=(-1, -1), type=coords, help="ending point separated by comma")
args = parser.parse_args()
port = args.p
algorithm = args.a

sock = socket.socket()
sock.connect(("127.0.0.1", port))

#time.sleep(6)

sock.send(str.encode(f"solve find-graph-path {algorithm}{endl*2}"))
print(sock.recv(1000).decode())

message = "3,3\r\n1,2,3\r\n4,5,6\r\n7,8,9\r\n0,0\r\n2,2\r\n\r\n"
sock.send(str.encode(message))
print(sock.recv(1000).decode())