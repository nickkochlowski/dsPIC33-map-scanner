#include "stdafx.h"
#include "Serial.h"
#include "Robot.h"
#include "Mapa.h"
#include <iostream>
using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int j = 0;
	int Celdas;
	CMapa mapa(6);
	Celdas = mapa.getSize();
	unsigned char buffer[1]; 	//1 porque imagino que sólo mandáis 1 dato cada vez y así evitáis problemas
	unsigned long recibido = 0;
   	 int contador = 1;  //contador es para saber posición del robot en el mapa
	mapa.actualizarposicion(contador);
	CSerial port;// creamos port de la clase CSerial para comunicación con el micro
	port.PortWrite(Celdas);// Enviamos al micro el tamaño del mapa
	while (j < Celdas)
    {

        port.PortRead(1, buffer, &recibido); //Leemos entrada de datos

        if(recibido == 1)// Bucle cuando se recibe algo
        {
        	int lectura = int(buffer[0]);			// guarda valor leido en lectura
			mapa.createMap(mapa,contador,lectura);		// setea cuadrado en objeto mapa1

            contador++;
			mapa.actualizarposicion(contador);// Actualiza posición del robot
			j++;

        }

     }
	PrintMap(mapa);//Sale el mapa por pantalla
	return 0;
}
