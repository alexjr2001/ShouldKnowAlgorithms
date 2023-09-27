/*
Nombre del proyecto: Iteradores propios para un Arbol binario

[EN]
Project in spanish with all explained, it is about a binary tree structure which can be traversed with iterators that
were created from scratch. We can prove it with the printing methods. 

[ES]
�rbol binario el cual se puede recorrer mediante iteradores creados desde cero.
Se incluye la impresi�n de estos para comprobar su buen funcionamiento.

@author Alexander Sebasti�n G�mez Del Carpio
Curso: Algoritmos y estructura de datos
*/



#include <iostream>
#include <math.h>

template <class T>
struct CNode {		//Estructura Nodo con m�s par�metros
	T m_v;   //Valor
	CNode<T>* nodes[2];  //Donde apunta
	CNode<T>* next;      //Next ayuda a la impresion por niveles
	int estado;			//estado y pila_abajo ayudan a impresion con la pila
	CNode<T>* pila_abajo;  //Apunta al nodo abajo en la pila
	CNode<T>* pila_arriba;
	CNode(T v) {
		m_v = v;
		nodes[0] = nullptr;
		nodes[1] = nullptr;
		next = nullptr;
		estado = 0;
		pila_abajo = nullptr;
		pila_arriba = nullptr;
	}
};

template<class T>
struct Stack { //Pila para impresiones Preorder, posorder,etc.
	CNode<T>* fondo = nullptr;    //Apuntan a los nodos del fondo y encima de la pila
	CNode<T>* cima = nullptr;
	int orden[4] = { 0, 1, 2, 3 };
	Stack(CNode<T>* nodo = nullptr) {
		fondo = nodo;
		cima = nodo;
	}
	void print() {
		for (CNode<T>* i = fondo; i!=cima&&i->pila_arriba; i=i->pila_arriba)
		{
			std::cout << i->m_v << "|->";
		}
	}
	bool insert(CNode<T>*nodo) {	//Se inserta un nodo arriba de la pila
		if (cima) {
			cima->pila_arriba = nodo; /
			nodo->pila_abajo = cima;
			cima = nodo;
		}
		else {
			fondo = nodo;
			cima = nodo;
		}
		return 1;
	}
	bool insert2(CNode<T>*nodo) {	//Se inserta un nodo arriba de la pila
		if (cima) {
			nodo->next = cima;
			cima = nodo;
		}
		else {
			fondo = nodo;
			cima = nodo;
		}
		return 1;
	}
	bool del() {   //Elimina los datos de la pila, no la pila
		while(cima) {
			CNode<T>* t = cima;
			cima->pila_arriba = nullptr;
			cima = cima->pila_abajo;
			t->pila_abajo = nullptr;
		}
		return 1;
	}
	void llenarStack(CNode<T>*root, int o=0) {
		del(); 
		if (o == 1) {
			orden[0] = 1;
			orden[1] = 0;
		}
		else if (o == 2) {
			orden[1] = 2;
			orden[2] = 1;
		}
		Stack<T> Aux(root); //stack auxiliar
		while (Aux.cima) {  //Si la pila no est� vac�a
			if (Aux.cima->estado == orden[0]) {
				Aux.cima->estado++;
				if (Aux.cima->nodes[0]) Aux.insert2(Aux.cima->nodes[0]);

			}
			else if (Aux.cima->estado == orden[1]) {
				Aux.cima->estado++;
				insert(Aux.cima);

			}
			else if (Aux.cima->estado == orden[2]) {
				Aux.cima->estado++;
				if (Aux.cima->nodes[1]) Aux.insert2(Aux.cima->nodes[1]);
			}
			else if (Aux.cima->estado == orden[3]) {
				Aux.cima->estado = 0;
				CNode<T>* t = Aux.cima;
				Aux.cima = Aux.cima->next;
				t->next = nullptr;
			}
		}
	}
};


template<class T>
class BinaryTree {
public:
	CNode<T>* root;
	Stack<T> inorder;
	Stack<T> preorder;
	Stack<T> posorder;
	BinaryTree() { root = nullptr; }
	~BinaryTree() {}
	
	CNode<T>* inorder_begin() {
		inorder.llenarStack(root);
		return inorder.fondo; 
	}
	CNode<T>* preorder_begin() { 
		preorder.llenarStack(root, 1);
		return root;
	}
	CNode<T>* posorder_begin() { 
		posorder.llenarStack(root,2);
		return posorder.fondo;
	}
	CNode<T>* reverse_begin() { 
		inorder.llenarStack(root);
		return inorder.cima;
	}
	CNode<T>* inorder_end() {
		inorder.llenarStack(root);
		return inorder.cima->pila_arriba; //Apuntar una despues del ultimo
	}
	CNode<T>* preorder_end() { 
		preorder.llenarStack(root,1);
		return preorder.cima->pila_arriba; //Apuntar una despues del ultimo
	}
	CNode<T>* posorder_end() { 
		posorder.llenarStack(root, 2);   
		return posorder.cima->pila_arriba;

	}
	CNode<T>* reverse_end() { 
		inorder.llenarStack(root);	
		return inorder.fondo->pila_abajo;
	}

	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void extremos(CNode<T>**& p, CNode<T>**& q);  //Encuentra el extremos interno del arbol el mayor de los menores 
	void print(int input);    //Imprime preorder, inorder, reversa o posorder
};
template<class T>
bool BinaryTree<T>::find(T x, CNode<T>**& p) {
	for (p = &root; *p && (*p)->m_v != x; p = &((*p)->nodes[(*p)->m_v < x])) {}
	return !!*p; //*p!=nullptr; Ayuda que salga tipo bool y no puntero
}
template<class T>
bool BinaryTree<T>::insert(T x) { //Inserta al final
	CNode<T>** p;
	if (!find(x, p)) {
		*p = new CNode<T>(x);
		return 1;
	}
	return 0;
}
template<class T>
void BinaryTree<T>::extremos(CNode<T>**& p, CNode<T>**& q) { //Encuentra el extremos interno del arbol el mayor de los menores
	q = p;
	p = &((*p)->nodes[0]);

	for (; (*p)->nodes[1]; p = &((*p)->nodes[1])) {}    //Va a izquierda 1 vez y luego, todo derecha
	(*q)->m_v = (*p)->m_v;
	return;
}
template <class T>
bool BinaryTree<T>::remove(T v) {
	CNode<T>** p;
	CNode<T>** q;
	CNode <T>* t;
	bool del = 0;  //Para saber si se borra el de la derecha o izquierda
	if (find(v, p)) {
		if ((*p)->nodes[0] && (*p)->nodes[1]) {
			//Extremos internos
			extremos(p, q);
		}
		if ((*p)->nodes[0]) {
			del = 1;
		}
		t = *p;
		*p = (*p)->nodes[!del];
		delete t;
		return 1;
	}
	return 0;
}
template <class T>
void BinaryTree<T>::print(int input) {
	Stack<T> S(root);
	int orden[4] = { 0, 1, 2, 3 };   //Array que se modifica para ayudar a cualquier tipo de impresion
	if (input == 2) {    //Si es preorden se deben cambiar algunos valores
		orden[0] = 1;
		orden[1] = 0;
	}
	else if (input == 3) {
		orden[1] = 2;
		orden[2] = 1;
	}
	else if (input == 4) {
		for (int i = 2, j = 0; i >= 0; i--, j++) {
			orden[j] = i;
		}
	}

	while (S.cima) {  //Si la pila no est� vac�a
		if (S.cima->estado == orden[0]) {
			S.cima->estado++;
			if (S.cima->nodes[0]) S.insert(S.cima->nodes[0]);
		}
		else if (S.cima->estado == orden[1]) {
			std::cout << S.cima->m_v << " ";
			S.cima->estado++;
		}
		else if (S.cima->estado == orden[2]) {
			S.cima->estado++;
			if (S.cima->nodes[1]) S.insert(S.cima->nodes[1]);
		}
		else if (S.cima->estado == orden[3]) {
			S.cima->estado = 0;
			S.cima = S.cima->pila_abajo;
		}
	}
	return;
}


template <class T>
class Iterator{				//Clase que dar� las sobrecargas a los dem�s iteradores
protected:
	CNode<T>* puntero;
public:
	Iterator() {
		puntero = nullptr;
	};
	~Iterator() {};

	void operator=(CNode<T>* p) {
		puntero = p;
		return;
	}
	void igual(CNode<T>* p) {
		puntero=p;
		return;
	}
	CNode<T>* operator*() {
		return puntero;
	}
	bool operator!=(CNode<T>*p) {
		return puntero!=p;
	}
	bool operator==(CNode<T>* p) {
		return puntero == p;
	}
	virtual void operator++() {
		puntero = puntero->pila_arriba;
		return;
	}
};
template<class T>
class inorder_iterator :public Iterator<T> {
public:
	inorder_iterator(){
	};
	~inorder_iterator() {};
	void operator=(CNode<T>* p) {
		this->igual(p);
	}
};
template<class T>
class preorder_iterator :public Iterator<T> {
public:
	preorder_iterator() {};
	~preorder_iterator(){};
	void operator = (CNode<T>* p) {
		this->igual(p);
	}
};
template<class T>
class posorder_iterator :public Iterator<T> {
public:
	posorder_iterator() {
	};
	~posorder_iterator() {};
	void operator=(CNode<T>* p) {
		this->igual(p);
	}
	
}; 
template<class T>
class reverse_iterator:public Iterator<T>{
public:
	reverse_iterator() {
	};
	~reverse_iterator() {};
	void operator=(CNode<T>* p) {
		this->igual(p);
	}
	void operator++() {
		this->puntero = this->puntero->pila_abajo;
	}
};



int main() {
	BinaryTree<int> bt;
	bt.insert(10);
	bt.insert(7);
	bt.insert(1);
	bt.insert(2);
	bt.insert(8);
	bt.insert(11);
	bt.insert(5);
	bt.insert(100);
	inorder_iterator<int> it;
	std::cout << "\nPrint INORDER: ";
	for (it = bt.inorder_begin(); it != bt.inorder_end(); ++it) {  //inorder_end=nullptr
		std::cout << (*it)->m_v << "->";
	}
	preorder_iterator<int> it2;
	std::cout << "\nPrint PREORDER: ";
	for (it2 = bt.preorder_begin(); it2 != bt.preorder_end(); ++it2) {  //inorder_end=nullptr
		std::cout << (*it2)->m_v << "->";
	}
	posorder_iterator<int> it3;
	std::cout << "\nPrint POSORDER: ";
	for (it3 = bt.posorder_begin(); it3 != bt.posorder_end(); ++it3) {  //inorder_end=nullptr
		std::cout << (*it3)->m_v << "->";
	}
	reverse_iterator<int> it4;
	std::cout << "\nPrint REVERSE: ";
	for (it4 = bt.reverse_begin(); it4 != bt.reverse_end(); ++it4) {  //inorder_end=nullptr
		std::cout << (*it4)->m_v << "->";
	}




	return 0;
}
