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
	int CurSel = 14;
	//インデックスの計算
	int dataIndex = CurSel * 16; // 224

	// int j = 0;
	// for (int i = 0; i < 933; i++) {
	// 	float sample = data[i];
	// 	char strBuff[32];
	// 	sprintf(strBuff, "%0.3f", sample);

	// 	if (i % 16 == 0) {
	// 		printf("%d	| ", j);
	// 		j++;
	// 	}
	// 	printf("\t%s", strBuff);
	// 	if ((i+1) % 16 == 0) printf("\n");
	// }
	// printf("\n\n");

	// 14 * 16 = 224; 224 + 16 = 240
	float Position_X = data[dataIndex+0];
	float Position_Y = data[dataIndex+1];
	float Position_Z = data[dataIndex+2];
	float Velocity_X = data[dataIndex+3];
	float Velocity_Y = data[dataIndex+4];
	float Velocity_Z = data[dataIndex+5];
	float Quaternion_W = data[dataIndex+6];
	float Quaternion_X = data[dataIndex+7];
	float Quaternion_Y = data[dataIndex+8];
	float Quaternion_Z = data[dataIndex+9];
	float AcceleratedVelocity_X = data[dataIndex+10];
	float AcceleratedVelocity_Y = data[dataIndex+11];
	float AcceleratedVelocity_Z = data[dataIndex+12];
	float Gyro_X = data[dataIndex+13];
	float Gyro_Y = data[dataIndex+14];
	float Gyro_Z = data[dataIndex+15];
	char strBuff[32];
	
	sprintf(strBuff, "%0.3f", Position_X);
	cout << "'X' = " << strBuff << ", ";
	sprintf(strBuff, "%0.3f", Position_Y);
	cout << "'Y' = " << strBuff << ", ";
	sprintf(strBuff, "%0.3f", Position_Z);
	cout << "'Z' = " << strBuff << ", ";

	// sprintf(strBuff, "%0.3f", Velocity_X);
	// cout << "'veloX' = " << strBuff << ", ";
	// sprintf(strBuff, "%0.3f", Velocity_Y);
	// cout << "'veloY' = " << strBuff << ", ";
	// sprintf(strBuff, "%0.3f", Velocity_Z);
	// cout << "'veloZ' = " << strBuff << ", ";

	// sprintf(strBuff, "%0.3f", Quaternion_W);
	// cout << "'quatW' = " << strBuff << ", ";
	// sprintf(strBuff, "%0.3f", Quaternion_X);
	// cout << "'quatX' = " << strBuff << ", ";
	// sprintf(strBuff, "%0.3f", Quaternion_Y);
	// cout << "'quatY' = " << strBuff << ", ";
	// sprintf(strBuff, "%0.3f", Quaternion_Z);
	// cout << "'quatZ' = " << strBuff << ", ";

	sprintf(strBuff, "%0.3f", AcceleratedVelocity_X);
	cout << "'acceVeloX' = " << strBuff << ", ";
	sprintf(strBuff, "%0.3f", AcceleratedVelocity_Y);
	cout << "'acceVeloY' = " << strBuff << ", ";
	sprintf(strBuff, "%0.3f", AcceleratedVelocity_Z);
	cout << "'acceVeloZ' = " << strBuff << ", ";

	sprintf(strBuff, "%0.3f", Gyro_X);
	cout << "'gyroX' = " << strBuff << ", ";
	sprintf(strBuff, "%0.3f", Gyro_X);
	cout << "'gyroY' = " << strBuff << ", ";
	sprintf(strBuff, "%0.3f", Gyro_X);
	cout << "'gyroZ' = " << strBuff << ", ";

	printf("\n");
	
}

int main()
{
	SOCKET_REF mySocket;
    uint32_t sample;
	//コールバックの登録
    BRRegisterCalculationDataCallback(&sample, CalculationDataReceivedCallback);
	//TCP接続
	char ip[] = "192.168.100.56";
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