#if defined(_WIN32) || defined(_WIN64)


#elif __linux__

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#endif

#include <unistd.h>
#include <string.h>
#include <iostream>

using namespace std;

typedef enum SOCKET_STATE{
    SUCCESS = 0,
    FAIL_INITIAL,
    FAIL_CONNECT,
    FAIL_BIND,
    FAIL_RECV,
    FAIL_SEND,
    FAIL_CLOSE
} SOCKET_STATE;

class SocketClient{

public:    
    SocketClient(string ip_addr, int port): m_ip(ip_addr), m_port(port){}

    SOCKET_STATE initialize();
    SOCKET_STATE connect_to_remote();
    SOCKET_STATE recv_data(char *buffer);
    SOCKET_STATE send_data(const char *msg);
    SOCKET_STATE disconnect();

private:
    string m_ip;
    int m_port;

#if defined(_WIN32) || defined(_WIN64)


#elif __linux__
    struct sockaddr_in m_addr;
    int m_conn;

#endif

};
