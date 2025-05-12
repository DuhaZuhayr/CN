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

int main()
{
    #ifdef _WIN32
        WSADATA wsaData;
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
        {
            std::cerr << "WSAStartup failed" << std::endl;
            return 1;
        }
    #endif

    SOCKET server_fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_fd == INVALID_SOCKET)
    {
        std::cerr << "Socket creation failed" << std::endl;
        #ifdef _WIN32
                WSACleanup();
        #endif
        return 1;
    }

    sockaddr_in server_addr{};
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(65432);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) == SOCKET_ERROR)
    {
        std::cerr << "Bind failed" << std::endl;
        #ifdef _WIN32
                closesocket(server_fd);
                WSACleanup();
        #endif
        return 1;
    }

    if (listen(server_fd, 1) == SOCKET_ERROR)
    {
        std::cerr << "Listen failed" << std::endl;
        #ifdef _WIN32
                closesocket(server_fd);
                WSACleanup();
        #endif
        return 1;
    }

    std::cout << "TCP Server listening on port 65432" << std::endl;

    while (true)
    {
        sockaddr_in client_addr{};
        int client_len = sizeof(client_addr);
        std::cout << "Waiting for client connection..." << std::endl;
        SOCKET client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
        if (client_fd == INVALID_SOCKET)
        {
            std::cerr << "Accept failed" << std::endl;
            continue;
        }
        std::cout << "Client connected!" << std::endl;

        char buffer[1024] = {0};
        int bytes_received = recv(client_fd, buffer, 1024, 0);
        if (bytes_received > 0)
        {
            std::cout << "Received: " << buffer << std::endl;
        }
        else
        {
            std::cout << "No data received or connection closed" << std::endl;
        }

        std::string response = "Hello from TCP Server!";
        send(client_fd, response.c_str(), response.length(), 0);
        std::cout << "Response sent to client" << std::endl;

        closesocket(client_fd);
    }

    #ifdef _WIN32
        closesocket(server_fd);
        WSACleanup();
    #endif
    return 0;
}

//g++ tcpClient.cpp -o tcpClient -lws2_32
//g++ tcpServer.cpp -o tcpServer -lws2_32
//.\tcpServer
//.\tcpClient
