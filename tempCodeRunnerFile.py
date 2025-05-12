import socket

def start_server():
    server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server.bind(("0.0.0.0", 9999))
    server.listen(5)
    print("Server started. Listening on port 9999...")

    while True:
        client_socket, addr = server.accept()
        print(f"Connection established with {addr}")

        option = client_socket.recv(1024).decode()

        if option == "1":
            client_socket.send("Hello, Client!".encode())

        elif option == "2":
            filename = client_socket.recv(1024).decode()
            try:
                with open(filename, "rb") as file:
                    data = file.read()
                    client_socket.sendall(data)
            except FileNotFoundError:
                client_socket.send("File not found".encode())

        elif option == "3":
            expression = client_socket.recv(1024).decode()
            try:
                result = str(eval(expression))
            except:
                result = "Error"
            client_socket.send(result.encode())

        client_socket.close()

if __name__ == "__main__":
    start_server()
