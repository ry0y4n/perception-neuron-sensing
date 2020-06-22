#include <iostream>
#include "NeuronDataReader.h"
#include "DataType.h"
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

//Neuronの読み取りごとに起動されるコールバック
void CalculationDataReceivedCallback(void* customedObj, SOCKET_REF sender, CalcDataHeader* header, float* data)
{
	//センサー番号、0はヒップにあるセンサー
	int CurSel = 37;
	//インデックスの計算
	int dataIndex = CurSel * 16;

	// // コーディングのための最適化
	// float posX = data[dataIndex + 0];
	// float posY = data[dataIndex + 1];
	// float posZ = data[dataIndex + 2];
	// float veloX = data[dataIndex + 3];
	// float veloY = data[dataIndex + 4];
	// float veloZ = data[dataIndex + 5];
	// char strBuff[32];
	// //浮動小数点を文字列に変換して画面に表示
	// sprintf(strBuff,"%0.3f", posX);
	// cout << "X = {" << strBuff;
	// sprintf(strBuff,"%0.3f", veloX);
	// cout << ", " << strBuff << "}";
	// sprintf(strBuff,"%0.3f", posY);
	// cout << ", Y = " << strBuff;
	// sprintf(strBuff,"%0.3f", veloY);
	// cout << ", " << strBuff << "}";
	// sprintf(strBuff,"%0.3f", posZ);
	// cout << ", Z = " << strBuff;
	// sprintf(strBuff,"%0.3f", veloZ);
	// cout << ", " << strBuff << "}";
	// cout << endl;

	int j = 37;
	for (int i = 592; i < 933; i++) {
		float sample = data[i];
		char strBuff[32];
		sprintf(strBuff, "%0.3f", sample);

		if (i % 16 == 0) {
			printf("%d	| ", j);
			j++;
		}
		printf("\t%s", strBuff);
		if ((i+1) % 16 == 0) printf("\n");
	}
	printf("\n\n");
}

int main()
{
	SOCKET_REF mySocket;
    uint32_t sample;
	//コールバックの登録
	// BRRegisterFrameDataCallback(&sample, bvhFrameDataReceived);
    BRRegisterCalculationDataCallback(&sample, CalculationDataReceivedCallback);
	//TCP接続
	char ip[] = "192.168.100.44";
	mySocket = BRConnectTo(ip, 7003);
	while(true)
	{
		//接続状態の確認
		SocketStatus status = BRGetSocketStatus(mySocket);
		if(mySocket)
		{
			switch (status)
			{
			case CS_Running:
					cout << "Running...\n";		
				break;
			case CS_Starting:
					cout << "Starting...\n";
				break;
			case CS_OffWork:
					cout << "OffWork...\n";
				break;
			}
		}
		else
		{
			cout << "接続なし\n";
		}
		//500msのスリープ
		usleep(500000);
	}
	//接続を閉じる
	BRCloseSocket(mySocket);
	//ユーザーの入力待ち
	cin.get();

	return 0;
}