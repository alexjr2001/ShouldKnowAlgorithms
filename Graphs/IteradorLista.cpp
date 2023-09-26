/*
Nombre del proyecto: Iteradores propios para una lista enlazada simple

[EN]
Project in spanish with all explained, it is about a simple linked list structure which can be traversed with iterators that
were created from scratch. We can prove it with the printing methods. 

[ES]
Lista enlazada simple la cual se puede recorrer mediante iteradores creados desde cero.
Se incluye la impresión de estos para comprobar su buen funcionamiento.

@author Alexander Sebastián Gómez Del Carpio
Curso: Algoritmos y estructura de datos
*/

#include<iostream>

template <class T>
struct nodo {
	T valor;
	nodo<T>* next;
	nodo(T v=0, nodo<T>* n=nullptr):valor(v),next(n){}
};

template <class T>
struct LE {
	nodo<T>* head;
	LE(nodo<T>* h=nullptr):head(h){}

	~LE() {
		nodo<T>* t = nullptr;
		for (nodo<T>* p = head; p; p = t)
		{
			t = p->next;
			delete p;
		}
	}
	nodo<T>* end();			//Devuelve un puntero que apunta al siguiente espacio del final
	nodo<T>* begin();		//Devuele un puntero que apunta al inicio
	nodo<T>* rbegin();
	nodo<T>* rend();
	bool find(T, nodo<T>**&);
	void add(T);
	void del(T);//revisar
	void print();
};

template <class T>
nodo<T>* LE<T>::begin() {
	return head;
}

template <class T>
nodo<T>* LE<T>::end() {
	nodo<T>* p;
	for (p = head; p; p = p->next);
	return p;
}
template <class T>
nodo<T>* LE<T>::rbegin() {
	return end();
}
template <class T>
nodo<T>* LE<T>::rend() {
	return begin();
}

template <class T>
bool LE<T>::find(T v, nodo<T>**&p) {
	for (p = &head; *p && (*p)->valor < v; p = &((*p)->next)) {}
	return *p && (*p)->valor == v;
}
template <class T>
void LE<T>::add(T v) {
	nodo<T>** p = nullptr;
	if (!find(v, p)) {
		*p = new nodo<T>(v, *p);
		std::cout << "Se agrego nodo: " << v << std::endl;
	}
	else {
		std::cout << "Ya existe el nodo: " << v << std::endl;
	}
	return;
}
template <class T>
void LE<T>::del(T v) {
	nodo<T>** p = nullptr;
	nodo<T>* temp = nullptr;
	if (find(v, p)) {
		temp = (*p)->next;
		delete (*p);
		*p = temp;
		std::cout << "Se borro el nodo: " << v << std::endl;
	}
	else {
		std::cout << "No existe el nodo: " << v << std::endl;
	}
	return;
}

template <class T>
void LE<T>::print() {
	std::cout << "head->";
	for (nodo<T>* p = head; p; p = p->next) {
		std::cout << p->valor << "->";
	}
	std::cout << "NULL";
	return;
}


template<class T>
class Iterator{			//Clase que contiene todas las sobrecargas necesarias
protected:
	nodo<T>* puntero;
public:
	Iterator() {
		puntero = nullptr;
	};
	~Iterator() {};
	nodo<T>* operator*() {
		return puntero;
	}
	void operator=(nodo<T>*p) {
		puntero = p;
		return;
	}
	bool operator ==(nodo<T>*p) {
		return puntero == p;
	}
	bool operator!=(nodo<T>* p) {
		return puntero != p;
	}
	nodo<T>* operator++(){
		puntero = puntero->next;
		return puntero;
	}
};

	


int main()
{
	LE<int> L;
	Iterator<int> it;
	L.add(3);
	L.add(7);
	L.add(12);
	L.add(4);
	L.add(100);
	L.add(1);
	
	for (it = L.begin(); it != L.end(); ++it) {
		std::cout << (*it)->valor << "->";
	}
	std::cout << "NULL";
	return 0;
}

