#include <iostream>
#include "NeuronDataReader.h"
#include "DataType.h"
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

//Neuronの読み取りごとに起動されるコールバック
void bvhFrameDataReceived(void* customedObj, SOCKET_REF sender, BvhDataHeader* header, float* data)
{
	//センサー番号、0はヒップにあるセンサー
	int CurSel = 37;
	//インデックスの計算
	int dataIndex = CurSel * 6;
	if(header->WithReference)
	{
		printf("with reference....");
		dataIndex += 6;
	}
	// // コーディングのための最適化
	// float dispX = data[dataIndex + 0];
	// float dispY = data[dataIndex + 1];
	// float dispZ = data[dataIndex + 2];
	// float angX = data[dataIndex + 4];
	// float angY = data[dataIndex + 3];
	// float angZ = data[dataIndex + 5];
	// char strBuff[32];
	// //浮動小数点を文字列に変換して画面に表示
	// sprintf(strBuff,"%0.3f", dispX);
	// cout << "X = {" << strBuff;
	// sprintf(strBuff,"%0.3f", angX);
	// cout << ", " << strBuff << "}";
	// sprintf(strBuff,"%0.3f", dispY);
	// cout << ", Y = " << strBuff;
	// sprintf(strBuff,"%0.3f", angY);
	// cout << ", " << strBuff << "}";
	// sprintf(strBuff,"%0.3f", dispZ);
	// cout << ", Z = " << strBuff;
	// sprintf(strBuff,"%0.3f", angZ);
	// cout << ", " << strBuff << "}";
	// cout << endl;

	int j = 0;
	for (int i = 0; i < 353; i++) {
		float sample = data[i];
		char strBuff[32];
		sprintf(strBuff, "%0.3f", sample);

		if (i % 6 == 0) {
			printf("%d	| ", j);
			j++;
		}
		printf("\t%s\t", strBuff);
		if ((i+1) % 6 == 0) printf("\n");
	}
	printf("\n\n");
}

int main()
{
	SOCKET_REF mySocket;
    uint32_t sample;
	//コールバックの登録
	BRRegisterFrameDataCallback(&sample, bvhFrameDataReceived);
	//TCP接続
	char ip[] = "192.168.100.44";
	mySocket = BRConnectTo(ip, 7001);
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