#include <iostream>
#include <string>

#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "Ws2_32.lib")
#else
    #include <unistd.h>
    #include <arpa/inet.h>
    #include <sys/socket.h>
#endif

int main() {
    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            std::cerr << "WSAStartup failed" << std::endl;
            return 1;
        }
    #endif

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Socket creation failed" << std::endl;
        #ifdef _WIN32
            WSACleanup();
        #endif
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(65432);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    std::cout << "Attempting to connect to server..." << std::endl;
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == SOCKET_ERROR) {
        std::cerr << "Connection failed" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    std::cout << "Connected to server!" << std::endl;

    std::string message = "Hello from TCP Client!";
    send(sock, message.c_str(), message.length(), 0);
    std::cout << "Message sent to server" << std::endl;

    char buffer[1024] = {0};
    int bytes_received = recv(sock, buffer, 1024, 0);
    if (bytes_received > 0) {
        std::cout << "Server response: " << buffer << std::endl;
    } else {
        std::cout << "No response received" << std::endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
