#include <cstring>
#include <errno.h>
#include <iostream>
#include <netinet/in.h>
#include <sstream>
#include <sys/socket.h>
#include <unistd.h>
#include <vector>
#include <arpa/inet.h>

void usage(){
    printf("\nUsage:\n  tester <port> [options]\n\nOptions:\n");
    printf("  -len <size>  expected number of bytes from socketter. default = 7\n");
    printf("  -req <ms>    request value every <ms> milliseconds from server (default is continuous receive)\n");
    printf("  -udp         connect via UDP (default TCP)\n");
}

int validatePort(char* port_in) {
    int port = 0;
    try{
        port = std::stoi(port_in);
    } catch (std::invalid_argument const& ex) {
        fprintf(stderr, "\ninvalid port '%s'\n", port_in);
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

unsigned int validateMillis(char* ms_in) {

    int ms = 0;
    try {
        ms = std::stoi(ms_in, nullptr);
    } catch (std::invalid_argument const& ex) {
        fprintf(stderr, "\ninvalid millisecond input '%s'\n", ms_in);
        usage();
        std::exit(-1);
    } catch (std::out_of_range const& ex) {
        fprintf(stderr, "\nport out of range '%s'\n", ms_in);
        std::exit(-1);
    }
    if (ms < 0) {
        fprintf(stderr, "non-negative time intervals only");
        std::exit(-1);
    }
    return ms;
}

static unsigned getBit(unsigned char bit, unsigned value) {
    return (value >> bit) & 1;
}

static void printBits(unsigned char * data, int len) {
    printf("\x1b[39;49mRead %d bytes:", len);
    int i;
    for (i = 0; i < len; ++i) {
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

enum READ_MODE {
    CONTINUOUS = 0,
    REQUEST = 1,
};

int main (int argc, char **args) {
    if (argc <= 1) {
        usage();
        return 0;
    }

    // process arguments
    unsigned short port = validatePort(args[1]);

    bool tcp = true;
    int sockType = SOCK_STREAM;
    READ_MODE readMode = CONTINUOUS;
    int period = 0;
    unsigned short expected = 7;

    for (int i = 2; i < argc; ++i) {
        if (strcmp(args[i], "-udp") == 0) {
            tcp = false;
            sockType = SOCK_DGRAM;
        } else if (strcmp(args[i], "-req") == 0) {
            readMode = REQUEST;
            ++i;
            period = validateMillis(args[i]);
        } else if (strcmp(args[i], "-len") == 0) {
            expected = std::stoi(args[++i]);
        } else {
            fprintf(stderr, "unrecognized argument '%s'\n", args[i]);
            usage();
            std::exit(-1);
        }
    }

    int server = socket(AF_INET, sockType, 0);
    if ( errno > 0) {
        perror("failed to create socket");
    }

    
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
        sendto(server, greeting, sizeof(greeting), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
        srcAddr = (struct sockaddr *)&serverAddr;
        srcAddrLen = &serverAddrLen;
    }

    if (readMode == REQUEST) {
        // send first request
        sendto(server, greeting, sizeof(greeting), 0, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    }

    int bytesRecvd = 0;
    unsigned bytesTotal = 0;
    unsigned char data[1024] = { 0 };
    unsigned char readBuff[1024] = { 0 };

    while(1) {
        bytesRecvd = 0;
        bytesTotal = 0;
        memset(&data, 0 , sizeof(data));
        memset(&readBuff, 0 , sizeof(readBuff));
        while(bytesTotal < expected) {
            bytesRecvd = recvfrom(server, &readBuff[bytesTotal], expected-bytesTotal, MSG_DONTWAIT, srcAddr, srcAddrLen);
            if (bytesRecvd < 0) {
                if (errno == EAGAIN || errno == EINTR) {
                    continue;
                } 
                perror("no data recieved from server:");
                break;
            } else if (bytesRecvd == 0) {
                continue;
            } else {
                if (bytesRecvd < expected) {
                    printf("only got %d bytes. read again\n", bytesRecvd);
                }
                // memcpy(&data[bytesTotal], &readBuff, bytesRecvd);
                bytesTotal += bytesRecvd;
            }
        }
        if (bytesTotal > 0) {
            memcpy(&data, &readBuff, expected);
            printBits(data, bytesTotal);
        }

        if (readMode == REQUEST) {
            usleep(period*1000);
            sendto(server, greeting, sizeof(greeting), 0,(struct sockaddr*)&serverAddr, sizeof(serverAddr));
        } else {
            usleep(1);
        }
    }

    close(server);
}