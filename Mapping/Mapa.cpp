#include "Mapa.h"
#include <iostream>
using namespace std;

CMapa::CMapa()
{
	m_i_size = 0;


}


CMapa::~CMapa()
{
	cout << "i have been deleted" << endl;
}

CMapa::CMapa(int x)
{
	int i;
	m_i_size = x;
	for (i = 0; i < x; i++)
	{
		m_v_i_mapa[i] = 0;
	}
	cout << "Mapa creado de tam: " << m_i_size << endl;
}

int CMapa::getSquare(int x, CMapa& v)
{
	return v.m_v_i_mapa[x];
}

void clearMap(CMapa& v)
{
	for (int i = 0; i < v.m_i_size; i++)
	{
		v.m_v_i_mapa[i] = 0;
	}
}

void PrintMap(CMapa& a)
{
	for (int i = 1; i <= a.m_i_size; i++)
	{
		cout << "Celda " << i << ": " << a.m_v_i_mapa[i] << endl;
	}
}
void CMapa::createMap(CMapa& map,int x,int a)
{
	map.m_v_i_mapa[x] = a;


}
int CMapa::getSize()
{
	return m_i_size;
}
