#include <stdio.h>
#include"NeuronDataReader.h"
#include"DataType.h"

// typedef void (* FUNC_POINTER)(char *); 

// void callback1(char *s){
//     printf("%s\n",s);
// }
// void func(char *s,FUNC_POINTER p){
//     // コールバック関数を呼び出す
//     p(s);
// }
//typedef void (* FrameDataReceived)(void* customedObj, SOCKET_REF sender, BvhDataHeader* header, float* data);
uint32_t tmp = 5;
float* data;

void callback(void* _customObj, SOCKET_REF _sender, BvhDataHeader* _header, float* _data) {
    tmp = _header->Token1;
    data = _data;
    //if (tmp != 0){
        for(int i = 0;i < 59;i++){
            printf("%f\t", data[i]);
            if((i + 1)%6 == 0){
                printf("\n");
            }
        }
        printf("\n\n");
    //}
    // tmp = _customObj;
    // printf("%d\n", (uint32_t)_customObj);
    //printf("callback\n");
}


int main()
{

    // FUNC_POINTER p;
    // p = callback1;
    // func("コールバック", p);


    char ip[] = "192.168.100.19";
    int port = 7001;
    uint32_t sample=1;

    BvhDataHeader streamData;

    FrameDataReceived p;
    p = callback;

    SocketStatus status;

    BRRegisterFrameDataCallback(&sample, p);
    
    SOCKET_REF socket;
    socket = BRConnectTo(ip, port);
         
    // while(1) {
    //    p(&sample, socket, &streamData, data);
    // }

    char *str = BRGetLastErrorMessage();
    printf("%s\n", str);

    //BRCloseSocket (socket);

    status = BRGetSocketStatus(socket);


    switch(status) {
        case CS_Running:
            printf("running\n");
            break;
        case CS_Starting:
            printf("starting\n");
            break;
        case CS_OffWork:
            printf("offwork\n");
            break;
        default: 
            printf("default");
            break;
    }

    //while(1){}

    BRCloseSocket (socket);

    return 0;
}