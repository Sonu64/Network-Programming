#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;


int main() {

    // Create client socket
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket < 0) {
        cout << "Client Socket Creation Failed :(\n";
        return 1;
    } else {
        cout << "Client Socket Created Successfully !\n";
    }


    // Prepare server address (IP + port)
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(55555); // Port
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr);


    // Connect to server
    if (connect(client_socket, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        cerr << "Connection Failed :(\n";
        return 1;
    } else {
        cout << "Successfully connected to Server ! :)\n";
    }

    // --- SEND MESSAGE --- //
    string msg = "Sun rahe ho Server ?";
    cout << "You said: " << msg << endl;
    send(client_socket, msg.c_str(), msg.size() ,0);
    // --- RECEIVE SERVER REPLY --- //
    char buffer[1024] = {0};
    recv(client_socket, buffer, sizeof(buffer), 0);
     cout << "Server Replied: " << buffer << endl;
    cout << "\nClosing Connection For Now. Goodbye !\n\n";
    // Close socket and exit
    close(client_socket);
    return 0;
}