#include<stdio.h>
#include"NeuronDataReader.h"
#include"DataType.h"
typedef void (* FUNC_POINTER)(char *); 
typedef void (* FrameDataReceived)(void* customedObj, SOCKET_REF sender, BvhDataHeader* header, float* data);


// コーバック関数1
void callback1(char *s){
    printf("%s\n",s);
}

// コールバック関数2
void callback2(char *s){
    printf("[");
    printf("%s",s);
    printf("].\n");
}

// コールバック関数を呼び出す関数
void func(char *s,FUNC_POINTER p){
    // コールバック関数を呼び出す
    p(s);
}

int main(){
    char ip[] = "192.168.100.19";
    int port = 7001;
    FUNC_POINTER p;

    p = callback1;
    // コールバック関数1を呼び出す
    func("コーバック関数1",p);

    p = callback2;
    // コールバック関数2を呼び出す
    func("コーバック関数2",p);
    return 0;
}