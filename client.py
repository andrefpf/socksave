from socket import socket, AF_INET, SOCK_STREAM

HOST = '127.0.0.1'
PORT = 1235

with socket(AF_INET, SOCK_STREAM) as s:
    s.connect((HOST, PORT))
    
    while True:
        message = input()
        if not message:
            break
        s.sendall(bytes(message, 'utf-8'))