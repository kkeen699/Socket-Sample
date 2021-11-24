#include "socket.h"

SOCKET_STATE SocketClient::initialize(){

#if defined(_WIN32) || defined(_WIN64)


#elif __linux__
    this->m_conn = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    // file descriptor 1, 2,
    if(this->m_conn<0){
        cout<<"Fail initialize"<<endl;
        this->disconnect();
        return FAIL_INITIAL;
    }
    
    // write ip/port info to struct
    this->m_addr.sin_family = AF_INET;
    //this->m_addr.sin_port = htons((unsigned short)this->m_port); old write type
    this->m_addr.sin_port = htons(static_cast<u_short>(this->m_port));
    int check = inet_pton(AF_INET, this->m_ip.c_str(), &this->m_addr.sin_addr);  //m_ip.c_str() write to m_addr.sin_addr by address not value
    //char
#endif

    if(check==-1){
        cout<<"Fail pton error"<<endl;    
        this->disconnect();
        return FAIL_INITIAL;
    }
    return SUCCESS;
}

SOCKET_STATE SocketClient::connect_to_remote(){
    
#if defined(_WIN32) || defined(_WIN64)


#elif __linux__    
    int check = connect(this->m_conn, (struct sockaddr*)&this->m_addr, sizeof(this->m_addr));
#endif   
    
    if (check < 0){
        cout<<"Fail connect to remote"<<endl;
        this->disconnect();
        return FAIL_CONNECT;
    }
    return SUCCESS;
}

SOCKET_STATE SocketClient::recv_data(char *buffer){
    int check = recv(this->m_conn, buffer, 4096, 0); // 0 為Flag
    if (check < 0){
        cout<<"Error recv"<<endl;
        return FAIL_RECV;
    }
    return SUCCESS;
}

SOCKET_STATE SocketClient::send_data(const char *msg){
    int check = send(this->m_conn, msg, strlen(msg), 0);
    if (check < 0){
        cout<<"Error send"<<endl;
        return FAIL_SEND;
    }
    return SUCCESS;
}

SOCKET_STATE SocketClient::disconnect(){
    int check;
#if defined(_WIN32) || defined(_WIN64)

#elif __linux__
    check = close(this->m_conn);
#endif
    if (!check){
        cout<<"Error close"<<endl;
        return FAIL_CLOSE;
    }
    return SUCCESS;
}
