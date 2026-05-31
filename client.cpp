#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {

    // Step1 --> Creating the TCP Endpoint for Client
    int client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (client_socket < 0) {
        cout << "Client Socket Creation Failed :(\n";
        return 1;
    }
    else {
        cout << "Client Socket Created Successfuly !\n";
    }

    // Step2 --> No need for bind and listen here. connect() implcitly gives the client an ephemeral port number, which is temporary, but for server this port number needs to be fixed, so bind was needed for server.
    // connect() needs to know Server information -> Which Server ? Which IP ? Which Port ?
    // defining server_information
    sockaddr_in server_address;
    server_address.sin_family = AF_INET;
    // Setting Server Port. (Destination Port)
    server_address.sin_port = htons(54000); // 54000  is the Server Port number, should be known to client.
    // Setting Server IP Address (Destination IP Address)
    // inet_pton converts human redable IPs to Binary Machine understandable IPs. It then stores the Server Machine IP into the sin_addr field of the server_address struct. 
    inet_pton(AF_INET, "127.0.0.1", &server_address.sin_addr); 

    // Now,  we have the server's "Map" in clients hand. Now client needs to reach out the server using this map. Time to connect !
    if (connect(client_socket, (sockaddr*)&server_address, sizeof(server_address)) < 0) {
        cerr << "Connection Failed :(\n";
        return 1;
    }
    else {
        cout << "Client Successfuly connected to Server ! :)\n";
    }


    
    return 0;  
}