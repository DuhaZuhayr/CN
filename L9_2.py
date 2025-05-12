import socket

def client():
    client = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    client.connect(("127.0.0.1", 9999))

    print("Choose an option:\n1. Say Hello\n2. File Transfer\n3. Calculator")
    option = input("Enter option: ")
    client.send(option.encode())

    if option == "1":
        print("Server:", client.recv(1024).decode())

    elif option == "2":
        filename = input("Enter filename to send: ")
        client.send(filename.encode())
        data = client.recv(1024)
        if data.decode() == "File not found":
            print("File not found on server.")
        else:
            with open("received_" + filename, "wb") as file:
                file.write(data)
            print("File received successfully.")

    elif option == "3":
        expression = input("Enter arithmetic expression (e.g., 5+3): ")
        client.send(expression.encode())
        print("Result from server:", client.recv(1024).decode())

    client.close()

if __name__ == "__main__":
    client()
