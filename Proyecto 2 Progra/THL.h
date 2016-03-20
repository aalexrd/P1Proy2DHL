#pragma once
#ifndef THL_H
#define THL_H
#include <iostream>
#include "ListaAreas.h"
#include "ListaPaquetes.h"
#include "ListaCliente.h"
#include <string>
using namespace std;

class THL
{
private:
	ListaArea Areas; //lista de destinos que contiene listas de rutas
	ListaCliente Clientes;
	ListaPaquete Paquetes;
	int idPaquete;
public:
	THL(): idPaquete(0)
	{
	};

	void agregarPaquete()
	{
		idPaquete++;
		cout << "Indique cual es la identificacion del cliente(MAYUSCULAS)\n";
		string id;
		cin >> id;
		if (Clientes.encontrarCliente(id) == true)
		{ //si ya existe el cliente aumentele un envio
			Clientes.buscar(id)->data.agregarEnvio();
		}
		else
		{ //si no esta registrado
			string nom;
			string direc;
			int num;
			cout << "\nEl cliente debe registrarse\n"
				<< "\nNombre: ";
			cin >> nom;
			cout << "\nDireccion: ";
			cin >> direc;
			cout << "\nTelefono: ";
			cin >> num;
			cout << endl;
			Cliente cli(nom, id, direc, num);
			Clientes.Insertar(cli);
		}
		system("cls");
		Areas.ordenarRuta(); //ordena rutas por la mas usada
		Areas.imprimirArea(); //imrpime el nombre de los destinos disponibles
		system("pause");
		string des;
		cout << "\nIngrese el destino del paquete: ";
		cin >> des;
		cout << endl;
		system("cls");
		Areas.buscarArea(des)->data.imprimir(); //imprime las rutas disponibles para el destino con su precio por peso y todos lso detalles sobre la variacion del precio por transporte
		system("pause");
		string ruta;
		int trans;
		cout << "\nIngrese la ruta deseada: ";
		cin >> ruta;
		cout << endl;
		cout << "0 = Aereo\n 1 = Terrestre\n 2 = Maritimo";
		cout << "\nIngrese el transporte deseado(0, 1 o 2): ";
		cin >> trans;
		cout << endl;
		system("cls");
		Areas.buscarArea(des)->data.buscar(ruta)->data.seUtilizo(); //llama al metodo setUtilizo() para agregar un usuario que utiliza mas esta ruta
		float peso;
		cout << "\nIngrese el peso del paquete en Kg: ";
		cin >> peso;
		cout << endl; //peso
		string descr;
		cout << "\nIngrese la descripcion del paquete: ";
		cin >> descr;
		cout << endl; //descripcion
		float cos = Areas.buscarArea(des)->data.buscar(ruta)->data.getTransporte(trans); //obtiene el valor de la ruta por transporte
		cos = cos * peso;//multiplica el peso por el costo del transporte
		string seg;
		cout << "\nIngrese la seguridad del paquete: ";
		cin >> seg;
		cout << endl; //seguridad
		string tra;
		switch (trans)
		{ //poner el transporte en string para la creacion del paquete
		case 0:
			tra = "Aereo";
		case 1:
			tra = "Terrestre";
		case 2:
			tra = "Maritimo";
		}
		Paquete paq(peso, descr, id, des, ruta, tra, cos, idPaquete, seg); //crea el paquete para ser insertado en su lista
		Paquetes.Insertar(paq);
		Clientes.buscar(id)->data.sumarPrecio(cos); //suma el precio del paquete actual al cliente
		Paquetes.buscarPaquete(idPaquete)->data.imprimir(); //imprime informacion del paquete
		system("pause");
	}

	void restaurar()
	{
		Areas.restaurarAreas(); //restaura areas
		Clientes.restaurarClientes(); //restaura clientes
		Paquetes.restaurarPaquetes(); //restaura paquetes
		Areas.restaRuta(); //restaura rutas
	}

	void interfaz()
	{
		cout << "Bienvenido al programa de THL\n"
			<< "\nQue desea hacer?\n"
			<< "\n1) Enviar paquete."
			<< "\n2) Consultar Cliente."
			<< "\n3) Consultar Paquete."
			<< "\n4) Salir. (Guarda cambios)\n";
		//<<"\n4) Otros...\n"; //regalo de cliente
		int opc;
		cin >> opc;
		switch (opc)
		{
		case 1:
			{
				system("cls");
				agregarPaquete();
				this->interfaz();
			}
		case 2:
			{
				system("cls");
				string id;
				cout << "Ingrese el ID del cliente: ";
				cin >> id;
				Clientes.buscar(id)->data.imprimir();
				system("pause");
				this->interfaz();
			}
		case 3:
			{
				system("cls");
				int ide;
				cout << "Ingrese el ID del paquete: ";
				cin >> ide;
				Paquetes.buscarPaquete(ide)->data.imprimir();
				system("pause");
				this->interfaz();
			}
		case 4:
			{
				Areas.respaldoArea();
				Clientes.respaldoClientes();
				Paquetes.respaldoPaquetes();
				Areas.resRuta();
				return;
			}
			/*case 4: //no se sabe cuales son los regalos
				system("cls");
				...
				*/
		default:
			cout << "Esa no es una opcion\n";
			this->interfaz();
		}
	}
};
#endif

