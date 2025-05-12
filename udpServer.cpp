#include <iostream>
#include <string>
#include <winsock2.h>
// #include <ws2tcpip.h>  // Not needed for inet_ntoa

#pragma comment(lib, "Ws2_32.lib")

#define PORT 65433

int main()
{
    // Initialize Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        std::cerr << "WSAStartup failed: " << WSAGetLastError() << std::endl;
        return 1;
    }

    // Create UDP socket
    SOCKET server_fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (server_fd == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Enable address reuse
    int opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, (const char *)&opt, sizeof(opt)) == SOCKET_ERROR)
    {
        std::cerr << "Setsockopt failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    // Set up server address structure
    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind socket
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed: " << WSAGetLastError() << std::endl;
        closesocket(server_fd);
        WSACleanup();
        return 1;
    }

    std::cout << "UDP Server listening on port " << PORT << " (Ctrl+C to exit)" << std::endl;

    while (true)
    {
        sockaddr_in client_addr{};
        int client_len = sizeof(client_addr);
        char buffer[1024] = {0};

        std::cout << "Waiting for message..." << std::endl;
        int bytes_received = recvfrom(server_fd, buffer, 1023, 0,
                                      (struct sockaddr *)&client_addr, &client_len);
        if (bytes_received == SOCKET_ERROR)
        {
            std::cerr << "Receive failed: " << WSAGetLastError() << std::endl;
            continue;
        }

        buffer[bytes_received] = '\0'; // Ensure null termination
        // Use inet_ntoa instead of inet_ntop
        std::string client_ip = inet_ntoa(client_addr.sin_addr);
        std::cout << "Received from " << client_ip << ":" << ntohs(client_addr.sin_port)
                  << ": " << buffer << std::endl;

        // Send response
        std::string response = "Hello from UDP Server!";
        if (sendto(server_fd, response.c_str(), response.length(), 0,
                   (struct sockaddr *)&client_addr, client_len) == SOCKET_ERROR)
        {
            std::cerr << "Send failed: " << WSAGetLastError() << std::endl;
            continue;
        }
        std::cout << "Response sent" << std::endl;
    }

    closesocket(server_fd);
    WSACleanup();
    return 0;
}
//g++ udpClient.cpp -o udpClient -lws2_32
//g++ udpServer.cpp -o udpServer -lws2_32
//.\udpServer
//.\udpClient