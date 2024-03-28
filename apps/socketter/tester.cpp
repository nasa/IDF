#include <cstring>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <arpa/inet.h>

static unsigned getBit(unsigned char bit, unsigned value) {
    return (value >> bit) & 1;
}

void usage(){
    printf("\nUsage:\n\tsocketter <port> [-udp]\n\n");
}

int validatePort(char* port_in) {
    int port = 0;
    try{
        port = std::stoi(port_in);
    } catch (std::invalid_argument const& ex) {
        fprintf(stderr, "\ninvalid input '%s'\n", port_in);
        usage();
        std::exit(-1);
    } catch (std::out_of_range const& ex) {
        fprintf(stderr, "\nport out of range '%s'\n", port_in);
        std::exit(-1);
    }
    if (port > 65535) {
        fprintf(stderr, "\nport out of valid range 1024-65535\n\n");
        std::exit(-1);
    } else if (port == 0) {
        printf("\nWARNING: port 0 will bind a random port\n");
    }
    return (unsigned short) port;
}


int main (int argc, char **args) {
    if (argc <= 1) {
        usage();
        return 0;
    }

    bool tcp = true;
    int sockType = SOCK_STREAM;

    if (argc >= 3 && strcmp("-udp", args[2]) == 0 ) {
        tcp = false;
        sockType = SOCK_DGRAM;
    }

    int server = socket(AF_INET, sockType, 0);
    if ( errno > 0) {
        perror("failed to create socket");
    }

    unsigned short port = validatePort(args[1]);
    
    struct sockaddr_in serverAddr;
    socklen_t serverAddrLen = sizeof(serverAddr);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = INADDR_ANY;//inet_addr("127.0.0.1");

    sockaddr * srcAddr = NULL;
    socklen_t  * srcAddrLen;

    char greeting[] = "give me HC";

    if (tcp) {
        if (connect(server, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
            perror("failed to connect to server");
            return -1;
        }
    } else {
        sendto(server, greeting, sizeof(greeting), MSG_CONFIRM, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        srcAddr = (struct sockaddr *)&serverAddr;
        srcAddrLen = &serverAddrLen;
    }

    int bytesRecvd = 0;
    unsigned char data[1024] = { 0 };

    while(1) {
        bytesRecvd = recvfrom(server, data, sizeof(data), 0, srcAddr, srcAddrLen);
        if (bytesRecvd < 0) {
            perror("no data recieved from server:");
            break;
        }
        printf("\x1b[39;49mRead %d bytes:", bytesRecvd);
        int i;
        for (i = 0; i < bytesRecvd; ++i) {
            printf("  ");
            printf("\033[0;3%dm", i % 7 + 1);
            int j = 7;
            while(j > 3) {
                printf("%u", getBit(j--, data[i]));
            }
            printf(" ");
            while (j >= 0) {
                printf("%u", getBit(j--, data[i]));
            }
        }
        printf("\n");
    }

    close(server);
}