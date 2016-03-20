#pragma once
#ifndef AREA_H
#define AREA_H
#include <iostream>
#include <string>
#include "Nodo.h"
#include "Ruta.h"
#include <fstream>
using namespace std;

class Area
{
private:
	Nodo<Ruta>* primer;
	Nodo<Ruta>* ultima;
	string nombre;

	static Nodo<Ruta>* obtNuevaRuta(Ruta& info)
	{
		return new Nodo<Ruta>(info);
	}

public:
	explicit Area(string nom): primer(nullptr), ultima(nullptr), nombre(nom)
	{
	};

	string getNom() const
	{
		return nombre;
	}

	void insertarRuta(string& nom, float& cos, float& dis, string& des, int& du, int& util)
	{
		Ruta rut(nom, cos, dis, des, du, util);
		auto newPtr = obtNuevaRuta(rut);
		if (Vacio())
			primer = ultima = newPtr;
		else
		{
			newPtr->sigPtr = primer;
			primer = newPtr;
		}
	}

	bool Vacio() const
	{
		return primer == nullptr;
	}

	Nodo<Ruta>* buscar(string nom) const
	{
		if (Vacio())
		{
			cout << "No existen rutas\n\n";
			return nullptr;
		}
		auto actualPtr = primer;
		while (actualPtr != nullptr)
		{
			if (actualPtr->data.getNom() == nom)
				return actualPtr;
			else
				actualPtr = actualPtr->sigPtr;
		}
		return nullptr;
	}

	void ordenar() const
	{//ordena mas utilizadas primero
		if (Vacio())
		{
			cout << "\nNo hay rutas para ordenar en el destino de " << nombre << endl;
			return;
		}
		auto sig = primer->sigPtr, aux = primer, sel = primer; //Usar auto en vez de Nodo<Ruta>
		Ruta dato;
		while (sel != nullptr)
		{
			while (sig != nullptr)
			{
				if (aux->data.getUtilizada() > sig->data.getUtilizada())
					aux = sig;
				sig = sig->sigPtr;
			}
			dato = sel->data;
			sel->data = aux->data;
			aux->data = dato;
			sel = sel->sigPtr;
			aux = sel;
			sig = sel;
		}
	}

	void imprimir() const
	{
		if (Vacio())
		{
			cout << "No existen rutas para esta area en este momento\n\n";
			return;
		}
		auto actualPtr = primer;
		cout << "La lista es: ";
		while (actualPtr != nullptr)
		{
			actualPtr->data.imprimir();
			actualPtr = actualPtr->sigPtr;
		}
		cout << "\n\n";
	}

	void respaldoRutas() const
	{ //escribir datos a archivos
		ofstream ruta;
		string nombreF = "ruta";
		nombreF += nombre + ".txt";
		ruta.open(nombreF); //abrir archivo
		if (ruta.is_open())
		{
			auto actualPtr = primer;
			while (actualPtr != nullptr)
			{
				ruta << actualPtr->data.getNom() << "\n";
				ruta << actualPtr->data.getCos() << "\n";
				ruta << actualPtr->data.getDis() << "\n";
				ruta << actualPtr->data.getUtilizada() << "\n";
				ruta << actualPtr->data.getDias() << "\n";
				ruta << actualPtr->data.getDesc();
				if (actualPtr != ultima)
				{
					ruta << endl;
				}
				actualPtr = actualPtr->sigPtr;
			}
		}
		else
			cout << "Unable to open file\n";
		ruta.close();
	}

	void restaurarRutas()
	{//leer de archivos
		ifstream ruta;
		string line;
		string nombreF = "ruta";
		nombreF += nombre + ".txt";
		ruta.open(nombreF);
		while (!ruta.eof())
		{
			string nombre, descripcion;
			float costo, distancia;
			int utilizada, dias;
			getline(ruta, nombre);//nombre
			size_t sz;
			getline(ruta, line);//costo
			costo = stof(line, &sz);
			getline(ruta, line);//distancia
			distancia = stof(line, &sz);
			getline(ruta, line);//utilizada
			utilizada = stof(line, &sz);
			getline(ruta, line);//duracion
			dias = stof(line, &sz);
			getline(ruta, descripcion);//descripcion
			insertarRuta(nombre, costo, distancia, descripcion, dias, utilizada);
		}
		ruta.close();
	}
};
#endif

