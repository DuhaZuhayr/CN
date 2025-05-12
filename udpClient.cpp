#include <iostream>
#include <string>
#include <winsock2.h>

#pragma comment(lib, "Ws2_32.lib")

#define PORT 65433

int main()
{
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    SOCKET sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    const char *server_ip = "127.0.0.1";

    // Use inet_addr instead of inet_pton
    server_addr.sin_addr.s_addr = inet_addr(server_ip);
    if (server_addr.sin_addr.s_addr == INADDR_NONE)
    {
        std::cerr << "Invalid address: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::string message = "Hello from UDP Client!";
    int server_len = sizeof(server_addr);
    std::cout << "Sending message to " << server_ip << ":" << PORT << "..." << std::endl;

    if (sendto(sock, message.c_str(), message.length(), 0,
               (struct sockaddr *)&server_addr, server_len) == SOCKET_ERROR)
    {
        std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }
    std::cout << "Message sent" << std::endl;

    char buffer[1024] = {0};
    int bytes_received = recvfrom(sock, buffer, 1023, 0,
                                  (struct sockaddr *)&server_addr, &server_len);
    if (bytes_received == SOCKET_ERROR)
    {
        std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
    }
    else
    {
        buffer[bytes_received] = '\0';
        std::cout << "Server response: " << buffer << std::endl;
    }

    closesocket(sock);
    WSACleanup();
    return 0;
}
