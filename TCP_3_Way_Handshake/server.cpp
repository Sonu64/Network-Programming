#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

using namespace std;

int main() {

    // Step1 --> Creating the TCP Endpoint
    int server_listening_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); //TCP Socket, IPv4, IPPROTO_TCP is the number (stored as enum) for Protocol Type in IP Header, 6 for TCP, 17 for UDP

    if (server_listening_socket < 0) {
        cerr << "Failed to create socket" << endl;
        return 1;
    }
    cout << "Socket created successfully" << endl; 


    // Step2 --> Creating a sockaddr_in Data Structure for IP and Port number.
    sockaddr_in server_address;
    server_address.sin_family = AF_INET; // for IPv4
    server_address.sin_port = htons(54000); // Fixed Port number for Server Welcome Socket. htons is for Big Endian conversion as TCP/IP uses Big Endian and Laptops may use Little Endian.
    server_address.sin_addr.s_addr = INADDR_ANY; // We are not giving any Fixed IP to the Server Socket, Linux will figure out which interface the packet arrived on. So Port 54000 is bound to all flexible IPs. This is important for Virtual Machines.



    /// Step3 --> Bind ! ==> This can be confusing so please read the comment below.
    /*
    /* @param1 = server_socket is the the Socket Descriptor of type int. Returned from socket(). It tells Linux which socket should be bound.

    /* @param2 = (sockaddr*)&server_address is the way to treat this structure as  generic socket instead of sockaddr_in which is used to define server_address. Because bind() expects sockaddr*,which is a Pointer. But we defined using sockaddr_in. So &server_address returns sockaddr_in* and then we typecase to sockadd*. Similar to (int*)malloc(...). 

    /* @param3 = sizeof(server_address) is to tell Linux and the bind() function how  many bytes should it read. 
    */

    int result = bind (server_listening_socket, (sockaddr*)&server_address, sizeof(server_address));

    if (result < 0) {
        cout << "Bind Failed :(\n";
        return 1;
    }
    else {
        cout << "Socket Binding Successful :)\n";
    }



    // Step4 --> Listening ON the socket, this will tell Linux that it is a Server Socket and Listening for any connection requests is needed. (Server's WELCOME socket).
    // Function prototype :- listen(int sockfd, int backlog);
    // @param1 = sockfd: It should be the socket returned by socket() and already bound by bind()
   // @param2 = backlog: This value is for the Queue Size for Pending Client Connections. SOMAXCONN is for the max Size allowable by OS.
    int listen_result = listen(server_listening_socket, SOMAXCONN);

    if (listen_result < 0) {
        cout << "Server Listen Failed. Welcome Socket can't be initialized !\n";
        return 1;
    }
    else {
        cout << "Welcome Socket Initialized :) Server is Listening...\n";
    }



    // Step5 --> The Welcome Socket needs to accept connections now so that a Duplicate Socket with same port number is made to do Data Transfer with Client. This is called Connection Socket.
    //.... Before accepting connections we need some variables to store client information

    // Variable 1: Client address Structure to Store information about the client. After accept() returns, Linux will fill it with Client IP, Client Port Number and Client Family.
    sockaddr_in client_address; 
    // Variable 2: Size variable, to tell Linux how much size os available in client_address. After the call Linux will update it with the Actual Size used.
    socklen_t client_size = sizeof(client_address);
    // See in the below function client_address and client_size are passed as &client_address an &client_size so that Linux can write into those addresses !!!!!! THIS IS IMPORTANT TO UNDERSTAND. So after accept returns, Linux updates client_address and client_size with exact client information.
    int connection_socket = accept(server_listening_socket, (sockaddr*)&client_address, &client_size);
    // Now this is a Blocking Call, so Server is waiting for a Client to connect... 
    //.... Client needs to send connection requests to this Server now.

    if(connection_socket < 0) {
        cout << "Accept Failed :(\n";
        return 1;
    }
    else {
        cout << "Client connected successfuly. TCP 3-way Handshake Successful.\nWelcome Socket did its job for this client and Connection Socket\nis made dedicated for Data transfer with this particular client.\n";
    }

    // Printing Client Information, we need to convert OS written IP in client_address.sin_addr to human-readable format. This is just the reverse of inet_pton().
    char client_ip[INET_ADDRSTRLEN];
    
    inet_ntop(AF_INET,
            &client_address.sin_addr,
            client_ip,
            INET_ADDRSTRLEN);

    cout << "Client Connected Successfuly !" << endl;
    cout << "IP: " << client_ip << endl;
    cout << "Port: " << ntohs(client_address.sin_port) << endl; // Network Byte Order is Big Endian, my Laptop may use Little Endian, so normalize it.





    close(server_listening_socket);
    return 0;  
}