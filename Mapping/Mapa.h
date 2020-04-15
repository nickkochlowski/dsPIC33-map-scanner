#pragma once
#include "Robot.h"
class CMapa :public CRobot
{
private:
	int m_i_size;
	int m_v_i_mapa[50];
public:
	CMapa();//creador por defecto
	~CMapa();//destructor
	CMapa(int x);//Creador personalizado
	void createMap(CMapa& map, int x, int a)//Rellena mapa;
	friend void clearMap(CMapa& v);//Borra mapa
	friend void PrintMap(CMapa& a);//Imprime mapa
	int getSquare(int x, CMapa& v);//Devuelve una posicion especifica del mapa
	int getSize(void);//Devuelve tamaño mapa

};
