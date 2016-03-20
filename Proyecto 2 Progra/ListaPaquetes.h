#pragma once
#ifndef LISTAP_H
#define LISTAP_H
#include <iostream>
#include "Nodo.h"
#include "Paquete.h"
#include <fstream>

class ListaPaquete
{
public:
	ListaPaquete() : primerPtr(nullptr), ultimoPtr(nullptr)
	{
	}

	~ListaPaquete()
	{
		if (!Vacio())
		{
			cout << "Destruyendo nodos ...\n";
			auto actualPtr = primerPtr;
			Nodo<Paquete>* tempPtr;
			while (actualPtr != nullptr)
			{
				tempPtr = actualPtr;
				actualPtr = actualPtr->sigPtr;
				delete tempPtr;
			}
		}
		cout << "Todos los nodos destruidos\n\n";
	}

	void Insertar(const Paquete& valor)
	{
		auto newPtr = obtNuevoNodo(valor);
		if (Vacio())
			primerPtr = ultimoPtr = newPtr;
		else
		{
			newPtr->sigPtr = primerPtr;
			primerPtr = newPtr;
		}
	}

	bool Vacio() const
	{
		return primerPtr == nullptr;
	}

	void imprimir() const
	{
		if (Vacio())
		{
			cout << "La lista esta vacia\n\n";
			return;
		}
		auto actualPtr = primerPtr;
		cout << "La lista es: ";
		while (actualPtr != nullptr)
		{
			actualPtr->data.imprimir();
			actualPtr = actualPtr->sigPtr;
		}
		cout << "\n\n";
	}

	Nodo<Paquete>* buscarPaquete(int opc) const
	{
		if (Vacio())
		{
			cout << "No hay paquetes\n\n";
			return nullptr;
		}
		auto actualPtr = primerPtr;
		while (actualPtr != nullptr)
		{
			if (actualPtr->data.getID() == opc)
				return actualPtr;
			actualPtr = actualPtr->sigPtr;
		}
		return nullptr;
	}

	void respaldoPaquetes() const
	{ //escribir datos a archivos
		ofstream paquete;
		paquete.open("paquetes.txt"); //abrir archivo
		if (paquete.is_open())
		{
			auto actualPtr = primerPtr;
			while (actualPtr != nullptr)
			{
				paquete << actualPtr->data.getidC() << "\n";
				paquete << actualPtr->data.getArea() << "\n";
				paquete << actualPtr->data.getRuta() << "\n";
				paquete << actualPtr->data.getTrans() << "\n";
				paquete << actualPtr->data.getPeso() << "\n";
				paquete << actualPtr->data.getDestino() << "\n";
				paquete << actualPtr->data.getCosto() << "\n";
				paquete << actualPtr->data.getID() << "\n";
				paquete << actualPtr->data.getSeg();
				if (actualPtr != ultimoPtr)
				{
					paquete << endl;
				}
				actualPtr = actualPtr->sigPtr;
			}
		}
		else
			cout << "Unable to open file\n";
		paquete.close();
	}

	void restaurarPaquetes()
	{//leer de archivos
		ifstream paquete;
		string line;
		paquete.open("paquetes.txt");
		while (!paquete.eof())
		{
			string idCliente, area, ruta, transporte, seguridad, destino;
			float peso, costo;
			int id;
			getline(paquete, idCliente);//idcliente
			getline(paquete, area);//area
			getline(paquete, ruta);//ruta
			getline(paquete, transporte);//transporte
			size_t sz;
			getline(paquete, line);//peso
			peso = stof(line, &sz);
			getline(paquete, destino);//destino
			getline(paquete, line);//costo
			costo = stof(line, &sz);
			getline(paquete, line);//idPa
			id = stof(line, &sz);
			getline(paquete, seguridad);//seguridad
			Paquete p(peso, destino, idCliente, area, ruta, transporte, costo, id, seguridad);
			Insertar(p);
		}
		paquete.close();
	}

private:
	Nodo<Paquete>* primerPtr;
	Nodo<Paquete>* ultimoPtr;

	static Nodo<Paquete>* obtNuevoNodo(const Paquete& valor)
	{
		return new Nodo<Paquete>(valor);
	}
};
#endif

