#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

int main() {

    // Creating server socket
    int server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (server_socket < 0) {
        cerr << "Failed to create socket" << endl;
        return 1;
    }
    cout << "Socket created successfully" << endl;


    // Prepare server address (IP + port)
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(55555); // Port
    server_address.sin_addr.s_addr = INADDR_ANY; // IP


    // Bind socket to the address
    int result = bind(server_socket, (sockaddr*)&server_address, sizeof(server_address));
    if (result < 0) {
        cout << "Bind Failed :(\n";
        return 1;
    } else {
        cout << "Socket Binding Successful :)\n";
    }


    // Start listening for incoming connections
    int listen_result = listen(server_socket, SOMAXCONN);
    if (listen_result < 0) {
        cout << "Server Listen Failed. Welcome Socket can't be initialized !\n";
        return 1;
    } else {
        cout << "Welcome Socket Initialized :) Server is Listening...\n\n";
    }


    // Accept a client connection (blocking code)
    sockaddr_in client_address;
    socklen_t client_size = sizeof(client_address);
    int client_socket = accept(server_socket, (sockaddr*)&client_address, &client_size);

    if (client_socket < 0) {
        cout << "Accept Failed :(\n";
        return 1;
    } else {
        cout << "Client connected successfuly. TCP 3-way Handshake Successful.\n";
    }


    // Convert client IP to human-readable form and print
    char client_ip[INET_ADDRSTRLEN];
    inet_ntop(AF_INET, &client_address.sin_addr, client_ip, INET_ADDRSTRLEN);

    cout << "IP: " << client_ip << endl;
    cout << "Port: " << ntohs(client_address.sin_port) << endl;



    // Now once the connection req is accepted by server, it needs to send a "pong" msg back to client's "ping".

    // Receiving clients msg
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
    cout << "\nClient says: " << buffer << endl;

    // Sending Reply
    string reply = "Hmm Client Bhai, Kaan Khule hai mere !";
    send(client_socket, reply.c_str(), reply.size(), 0);
    cout << "You said: " << reply << endl;
    cout << "\nClosing Connection For Now. Goodbye !\n\n";


    // Close the both sockets
    close(server_socket);
    close(client_socket);
    return 0;
}