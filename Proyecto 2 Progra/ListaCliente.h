#pragma once
#ifndef LISTAC_H
#define LISTAC_H
#include <iostream>
#include "Nodo.h"
#include "Cliente.h"
#include <fstream>

class ListaCliente
{
	friend class THL;
public:
	ListaCliente() : primerPtr(nullptr), ultimoPtr(nullptr)
	{
	}

	~ListaCliente()
	{
		if (!Vacio())
		{
			cout << "Destruyendo nodos ...\n";
			auto actualPtr = primerPtr;
			Nodo<Cliente>* tempPtr;
			while (actualPtr != nullptr)
			{
				tempPtr = actualPtr;
				actualPtr = actualPtr->sigPtr;
				delete tempPtr;
			}
		}
		cout << "Todos los nodos destruidos\n\n";
	}

	void Insertar(const Cliente& valor)
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
		Nodo<Cliente>* actualPtr = primerPtr;
		cout << "La lista es: ";
		while (actualPtr != nullptr)
		{
			actualPtr->data.imprimir();
			actualPtr = actualPtr->sigPtr;
		}
		cout << "\n\n";
	}

	Nodo<Cliente>* buscar(string opc) const
	{
		if (Vacio())
		{
			cout << "La lista esta vacia\n\n";
			return nullptr;
		}
		Nodo<Cliente>* actualPtr = primerPtr;
		while (actualPtr != nullptr)
		{
			if (actualPtr->data.getID() == opc)
				return actualPtr;
			actualPtr = actualPtr->sigPtr;
		}
		return nullptr;
	}

	bool encontrarCliente(string ide) const
	{
		if (Vacio())
		{
			return false;
		}
		Nodo<Cliente>* actualPtr = primerPtr;
		while (actualPtr != nullptr)
		{
			if (actualPtr->data.getID() == ide)
				return true;
			actualPtr = actualPtr->sigPtr;
		}
		return false;
	}

	void consultar(string ide) const
	{
		buscar(ide)->data.imprimir();
		system("pause");
	}

	void respaldoClientes() const
	{ //escribir datos a archivos
		ofstream cliente;
		cliente.open("clientes.txt"); //abrir archivo
		if (cliente.is_open())
		{
			auto actualPtr = primerPtr;
			while (actualPtr != nullptr)
			{
				cliente << actualPtr->data.getNom() << "\n";
				cliente << actualPtr->data.getID() << "\n";
				cliente << actualPtr->data.getDirec() << "\n";
				cliente << actualPtr->data.getTel() << "\n";
				cliente << actualPtr->data.getEnvios() << "\n";
				cliente << actualPtr->data.getTotal();
				if (actualPtr != ultimoPtr)
				{
					cliente << endl;
				}

				actualPtr = actualPtr->sigPtr;
			}
		}
		else
			cout << "Unable to open file\n";
		cliente.close();
	}

	void restaurarClientes()
	{//leer de archivos
		ifstream cliente;
		string line;
		cliente.open("clientes.txt");
		while (!cliente.eof())
		{
			string nombre, id, direccion;
			int numTel, envios;
			float montoTot;
			getline(cliente, nombre);//nombre
			getline(cliente, id);//id
			getline(cliente, direccion);//direccion
			getline(cliente, line);//telefono
			size_t sz;
			numTel = stof(line, &sz);
			getline(cliente, line);//envios
			envios = stof(line, &sz);
			getline(cliente, line);//montoTotal
			montoTot = stof(line, &sz);
			Cliente c(nombre, id, direccion, numTel, envios, montoTot);
			Insertar(c);
		}
		cliente.close();
	}

private:
	Nodo<Cliente>* primerPtr;
	Nodo<Cliente>* ultimoPtr;

	static Nodo<Cliente>* obtNuevoNodo(const Cliente& valor)
	{
		return new Nodo<Cliente>(valor);
	}
};
#endif

