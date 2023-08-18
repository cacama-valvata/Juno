import socket

HOST = "10.0.0.190"
PORT = 65432

with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    s.sendall(b"game 5 1")

print("sent")
