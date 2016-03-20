#pragma once
#ifndef PAQUETE_H
#define PAQUETE_H
#include <iostream>
#include <string>
using namespace std;

class Paquete
{
private:
	string idCliente;
	string area;
	string ruta;
	string transporte;
	float peso;
	string destino;
	float costo;
	int id;
	string seguridad;
public:
	Paquete(): peso(0), costo(0), id(0)
	{
	};

	Paquete(float pes, string des, string id, string ar, string rut, string trans, float cos, int i, string seg): idCliente(id), area(ar), ruta(rut), transporte(trans), peso(pes), destino(des), costo(cos), id(i), seguridad(seg)
	{
	};

	string getidC() const
	{
		return idCliente;
	}

	string getArea() const
	{
		return area;
	}

	string getRuta() const
	{
		return ruta;
	}

	string getTrans() const
	{
		return transporte;
	}

	float getPeso() const
	{
		return peso;
	}

	string getDestino() const
	{
		return destino;
	}

	float getCosto() const
	{
		return costo;
	}

	string getSeg() const
	{
		return seguridad;
	}

	void imprimir() const
	{
		cout << "\nID Paquete: " << id
			<< "\nCliente: " << idCliente
			<< "\nRuta: " << ruta
			<< "\nCosto: " << costo
			<< "\nDestino: " << destino
			<< "\nPeso: " << peso
			<< "\nArea: " << area
			<< "\nSeguridad: " << seguridad
			<< "\nTransporte por via: " << transporte << endl
			<< "\n\n";
	}

	int getID() const
	{
		return id;
	}
};
#endif

