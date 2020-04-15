#pragma once
class CRobot{
private:
	int m_i_posicion;

public:
	CRobot();//Creador por defecto
	~CRobot();//Destructor
	void actualizarposicion(int pos);//Actualiza la posicion del robot
};
