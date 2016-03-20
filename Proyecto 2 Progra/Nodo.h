#pragma once
#ifndef Nodo_H
#define Nodo_H                 
template< typename TIPONODO >
class Nodo {
   friend class ListaArea;
   friend class ListaPaquete;
   friend class ListaCliente;
   friend class THL;
   friend class Area;
public:
   Nodo( const TIPONODO &info ) : data( info ), sigPtr(nullptr ) { }
   TIPONODO getData() const { 
   return data; }
private:
   TIPONODO data;
   Nodo< TIPONODO > *sigPtr;
}; 
#endif