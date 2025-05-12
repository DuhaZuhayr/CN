import socket

BUFFER_SIZE = 70000
PORT = 8000


def receive_file(sock, client_addr, file_name, file_size):
    """Function to receive a file from the client and save it."""
    print(f"Receiving {file_name}...")

    data, _ = sock.recvfrom(file_size)

    with open(file_name, "wb") as f:
        f.write(data)

    print(f"{file_name} received successfully.\n")


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    sock.bind(("0.0.0.0", PORT))

    print("Server is running and waiting for connections...")

    while True:
        choice, client_addr = sock.recvfrom(1)
        choice = int.from_bytes(choice, byteorder='big')

        if choice == 1:  # Text file
            file_name, _ = sock.recvfrom(1024)
            file_name = file_name.decode()

            receive_file(sock, client_addr, file_name, BUFFER_SIZE)

        elif choice == 2:  # Audio file
            file_name, _ = sock.recvfrom(1024)
            file_name = file_name.decode()

            receive_file(sock, client_addr, file_name, BUFFER_SIZE)

        elif choice == 3:  # Video file
            file_name, _ = sock.recvfrom(1024)
            file_name = file_name.decode()

            receive_file(sock, client_addr, file_name, BUFFER_SIZE)

        elif choice == 4:  # Exit
            print("Closing server...")
            sock.close()
            break


if __name__ == "__main__":
    main()
