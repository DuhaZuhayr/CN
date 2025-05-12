import socket

SERVER_IP = "127.0.0.1"  # Change to the server's IP if needed
PORT = 8000
BUFFER_SIZE = 70000

def send_file(sock, file_name, server_address):
    """Function to send a file to the server."""
    try:
        with open(file_name, "rb") as f:
            file_data = f.read()

        sock.sendto(file_name.encode(), server_address)
        sock.sendto(file_data, server_address)

        print(f"{file_name} sent successfully.\n")

    except FileNotFoundError:
        print("File not found. Please check the file name.")


def main():
    sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = (SERVER_IP, PORT)

    while True:
        print("Enter choice:\n 1. Text File\n 2. Audio File\n 3. Video File\n 4. Exit")
        choice = int(input("Enter your choice: "))

        sock.sendto(choice.to_bytes(1, byteorder='big'), server_address)

        if choice in [1, 2, 3]:
            file_name = input("Enter file name to send: ")
            send_file(sock, file_name, server_address)

        elif choice == 4:
            print("Closing client...")
            sock.close()
            break


if __name__ == "__main__":
    main()
