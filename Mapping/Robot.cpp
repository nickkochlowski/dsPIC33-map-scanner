#include "Robot.h"
#include "Mapa.h"
#include <iostream>
using namespace std;


CRobot::CRobot()
{
	int m_i_posicion = 0;
	cout << "Robot creado"<< endl;

}


CRobot::~CRobot()
{
	cout << "Robot se ha eliminado" << endl;
}

void CRobot::actualizarposicion(int pos)
{
	m_i_posicion = pos;
}
