#pragma once
#ifndef RUTA_H
#define RUTA_H
#include <iostream>
#include <string>
using namespace std;

class Ruta
{
private:
	string nombre;
	float costo; //costo base de la ruta via maritimo
	float distancia;
	int utilizada;
	string descripcion;
	int dias; //duracion
public:
	Ruta(): costo(0), distancia(0), utilizada(0), dias(0)
	{
	};

	Ruta(string nom, float cos, float dis, string des, int du, int util): nombre(nom), costo(cos), distancia(dis), utilizada(util), descripcion(des), dias(du)
	{
	};

	string getNom() const
	{
		return nombre;
	}

	float getCos() const
	{
		return costo;
	}

	float getDis() const
	{
		return distancia;
	}

	int getDias() const
	{
		return dias;
	}

	string getDesc() const
	{
		return descripcion;
	}

	float getTransporte(int i) const
	{ //aumenta el costo de la ruta dependiendo del transporte
		auto temp = costo;
		if (i == 0)
		{//aereo
			temp += costo * 0.15; //15% del terrestre
			temp += costo * 0.25; //mas 25% del aereo
			return temp;
		}
		if (i == 1)
		{//terrestre
			temp += costo * 0.15; //15% del terrestre
		}
		if (i == 2)
		{//maritimo
			return costo;
		}
		return 0;
	}

	int getUtilizada() const
	{
		return utilizada;
	}

	void seUtilizo()
	{
		utilizada++;
	}

	void imprimir() const
	{
		cout << "Ruta: " << nombre
			<< "\nDescripcion: \n" << descripcion
			<< "\nDuracion aproximada(dias): " << dias
			<< "\nVeces utilizada: " << utilizada
			<< "\nCosto por kg: " << costo
			<< "\nDsitancia: " << distancia
			<< "\n(2)Valor por via maritima: " << getTransporte(2)
			<< "\n(1)Valor por via terrestre: " << getTransporte(1)
			<< "\n(0)Valor por via aerea: " << getTransporte(0) << endl
			<< "\n\n";
	}
};
#endif

