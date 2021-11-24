#include "socket.h"
#include <string>

void print_error_state(string msg, SOCKET_STATE state){
    cout<<"["<<msg<<"]"<<"with Error code"<<state<<endl;
    throw msg;
}

int main(){
    string ip = "140.112.14.208";
    int port = 8520;
    SOCKET_STATE check;
    char buffer[4096] = {0}; //1024x N 初始化
    string msg = "nick is boss";
    SocketClient *s_client = new SocketClient(ip, port);
    cout<<"check initialize"<<endl;
    check = s_client->initialize();
    if(check != SUCCESS)
        print_error_state("Fail initialize", check);
    
    check = s_client->connect_to_remote();
    if(check != SUCCESS)
        print_error_state("Fail connect", check);
    
    check = s_client->recv_data(buffer);
    if(check != SUCCESS)
        print_error_state("Fail recv data", check);
    
    cout<<buffer<<endl;

    check = s_client->send_data(msg.c_str());
    if(check != SUCCESS)
        print_error_state("Fail send data", check);
}
