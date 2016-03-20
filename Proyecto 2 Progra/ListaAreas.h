#pragma once
#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include "Nodo.h"
#include "Area.h"
#include <fstream>

class ListaArea
{
public:
	ListaArea() : primerPtr(nullptr), ultimoPtr(nullptr)
	{
	}

	~ListaArea()
	{
		if (!Vacio())
		{
			cout << "Destruyendo nodos ...\n";
			auto actualPtr = primerPtr;
			Nodo<Area>* tempPtr;
			while (actualPtr != nullptr)
			{
				tempPtr = actualPtr;
				actualPtr = actualPtr->sigPtr;
				delete tempPtr;
			}
		}
		cout << "Todos los nodos destruidos\n\n";
	}

	void Insertar(const Area& valor)
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

	void ordenarRuta() const
	{
		auto actualPtr = primerPtr;
		while (actualPtr != nullptr)
		{
			actualPtr->data.ordenar();
			actualPtr = actualPtr->sigPtr;
		}
	}

	void imprimirArea() const
	{
		if (Vacio())
		{
			cout << "No hay areas disponibles\n\n";
			return;
		}
		auto actualPtr = primerPtr;
		cout << "Areas/Destinos disponibles: ";
		while (actualPtr != nullptr)
		{
			cout << "\n" << actualPtr->data.getNom() << "\n";
			actualPtr = actualPtr->sigPtr;
		}
		cout << "\n\n";
	}

	Nodo<Area>* buscarArea(string opc) const
	{
		if (Vacio())
		{
			cout << "La lista esta vacia\n\n";
			return nullptr;
		}
		Nodo<Area>* actualPtr = primerPtr;
		while (actualPtr != nullptr)
		{
			if (actualPtr->data.getNom() == opc)
				return actualPtr;
			else
				actualPtr = actualPtr->sigPtr;
		}
		return nullptr;
	}

	void respaldoArea() const
	{ //escribir datos a archivos
		ofstream area;
		area.open("areas.txt"); //abrir archivo
		if (area.is_open())
		{
			auto actualPtr = primerPtr;
			while (actualPtr != nullptr)
			{
				area << actualPtr->data.getNom();
				if (actualPtr != ultimoPtr)
				{
					area << endl;
				}
				actualPtr = actualPtr->sigPtr;
			}
		}
		else
			cout << "Unable to open file\n";
		area.close();
	}

	void restaurarAreas()
	{//leer de archivos
		ifstream area;
		string line;
		area.open("areas.txt");
		while (!area.eof())
		{
			getline(area, line);//nombre
			Area ar(line);
			Insertar(ar);
		}
		area.close();
	}

	void resRuta() const
	{
		auto actualPtr = primerPtr;
		while (actualPtr != nullptr)
		{
			actualPtr->data.respaldoRutas();
			actualPtr = actualPtr->sigPtr;
		}
	}

	void restaRuta() const
	{
		auto actualPtr = primerPtr;
		while (actualPtr != nullptr)
		{
			actualPtr->data.restaurarRutas();
			actualPtr = actualPtr->sigPtr;
		}
	}

private:
	Nodo<Area>* primerPtr;
	Nodo<Area>* ultimoPtr;

	static Nodo<Area>* obtNuevoNodo(const Area& valor)
	{
		return new Nodo<Area>(valor);
	}
};
#endif

