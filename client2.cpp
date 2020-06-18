#include <iostream>
#include "NeuronDataReader.h"
#include "DataType.h"
#include <iostream>
#include <string>
#include <unistd.h>
using namespace std;

//Callback que sera activada en cada lectura del Neuron
void bvhFrameDataReceived(void* customedObj, SOCKET_REF sender, BvhDataHeader* header, float* data)
{
	//Numero del sensor, 0 es el sensor ubicado en la cadera
	int CurSel = 40;
	//Calcular el indice
	int dataIndex = CurSel * 6;
	if(header->WithReference)
	{
		dataIndex += 6;
	}
	//Optener las coordenadas
	float dispX = data[dataIndex + 0];
	float dispY = data[dataIndex + 1];
	float dispZ = data[dataIndex + 2];
	float angX = data[dataIndex + 3];
	float angY = data[dataIndex + 4];
	float angZ = data[dataIndex + 5];
	char strBuff[32];
	//Convertir float en strings e imprimir en pantalla
	sprintf(strBuff,"%0.3f", dispX);
	cout << "X = {" << strBuff;
	sprintf(strBuff,"%0.3f", angX);
	cout << ", " << strBuff << "}";
	sprintf(strBuff,"%0.3f", dispY);
	cout << ", Y = " << strBuff;
	sprintf(strBuff,"%0.3f", angY);
	cout << ", " << strBuff << "}";
	sprintf(strBuff,"%0.3f", dispZ);
	cout << ", Z = " << strBuff;
	sprintf(strBuff,"%0.3f", angZ);
	cout << ", " << strBuff << "}";
	cout << endl;
}

int main()
{
	SOCKET_REF mySocket;
    uint32_t sample;
	//Registrar el callback
	BRRegisterFrameDataCallback(&sample, bvhFrameDataReceived);
	//Abrir la conexion (IP, PUERTO)
	char ip[] = "192.168.100.19";
	mySocket = BRConnectTo(ip, 7001);
	while(true)
	{
		//Comprobar el estado de la conexion
		SocketStatus status = BRGetSocketStatus(mySocket);
		if(mySocket)
		{
			switch (status)
			{
			case CS_Running:
					cout << "Conectado\n";		
				break;
			case CS_Starting:
					cout << "Iniciando...\n";
				break;
			case CS_OffWork:
					cout << "OffLine\n";
				break;
			}
		}
		else
		{
			cout << "Desconectado\n";
		}
		//Detener durante unos 500 milisegundos
		//Sleep(500);
		usleep(500000);
	}
	//Cerrar la conexion
	BRCloseSocket(mySocket);
	//Esperar a input de usuario
	cin.get();
	//Regresar 0, operacion exitosa
	return 0;
}