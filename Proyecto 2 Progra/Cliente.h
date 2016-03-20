#pragma once
#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <string>
using namespace std;

class Cliente
{
	friend class THL;
	friend class ListaCliente;
private:
	string nombre;
	string id;
	string direccion;
	int numTel;
	int envios;
	float montoTot;
private:
	Cliente(string nom, string ide, string direc, int tel): nombre(nom), id(ide), direccion(direc), numTel(tel), envios(1), montoTot(0)
	{
	};

	Cliente(string nom, string ide, string direc, int tel, int env, float mon): nombre(nom), id(ide), direccion(direc), numTel(tel), envios(env), montoTot(mon)
	{
	};

	string getNom() const
	{
		return nombre;
	}

	string getID() const
	{
		return id;
	}

	string getDirec() const
	{
		return direccion;
	}

	int getTel() const
	{
		return numTel;
	}

	int getEnvios() const
	{
		return envios;
	}

	float getTotal() const
	{
		return montoTot;
	}

	void setNom(string nom)
	{
		nombre = nom;
	}

	void setID(string ide)
	{
		id = ide;
	}

	void setDirec(string direc)
	{
		direccion = direc;
	}

	void setTel(int tel)
	{
		numTel = tel;
	}

	void agregarEnvio()
	{
		envios++;
	}

	void sumarPrecio(float price)
	{
		montoTot += price;
	}

	void imprimir() const
	{
		cout << "Nombre: " << nombre
			<< "\nID: \n" << id
			<< "\nDireccion: " << direccion
			<< "\nTelefono: " << numTel
			<< "\nEnvios registrados: " << envios
			<< "\nMonto total de envios: " << montoTot << endl
			<< "\n\n";
	}
};
#endif

