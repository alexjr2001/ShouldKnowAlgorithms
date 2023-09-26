/*
Project: Binary Tree

Binary tree that can be modified, either by adding or removing nodes. Also, you can print the tree
in preorder, post-order, reverse, inorder and levels for better visualization.
For the proper handling of this, an interactive menu is included. All structures used such as Stack and Cola (Queue) were created from scratch.

@author Alexander Sebasti�n G�mez Del Carpio
*/

#include <iostream>
#include <math.h>

template <class T>
struct CNode {		
	T m_v;   //Value
	CNode<T>* nodes[2];  //Where it points (children)
	CNode<T>* next;      //Next helps printing by levels
	int estado;			//estado and pila_abajo help the printing with the stack
	CNode<T>* pila_abajo;  //Point the node down on the stack
	CNode(T v) {
		m_v = v;
		nodes[0] = nullptr;
		nodes[1] = nullptr;
		next = nullptr;
		estado = 0;
		pila_abajo = nullptr;
	}
};

template<class T>
struct Stack { //Stack fro printing in preorder, posorder, etc.
	CNode<T>* fondo=nullptr;    //Point to the nodes at the bottom and above the stack
	CNode<T>* cima=nullptr;
	Stack() {
		fondo = nullptr;
		cima = nullptr;
	}
	Stack(CNode<T>* nodo) {
		fondo = nodo;
		cima = nodo;
	}
	bool insert(CNode<T>* nodo) {	//Insert a node up the stack
		if (cima) {
			nodo->pila_abajo = cima;
			cima = nodo;
		}
		else{
			fondo = nodo;
			cima = nodo;
		}
		return 1;
	}
	bool del() {   //Delete the node of the stack
		if (cima) {
			cima = cima->pila_abajo; 
			return 1;
		}
		return 0;
	}

};

template <class T>
struct Cola {		//Structure that helps in level printing
	CNode<T>* first;
	Cola() {
		first = nullptr;
	}
	~Cola() {
		for (; first; first = first->next) {}
	}
	bool find(CNode<T>**& p) {   //Finds the end
		for (p = &first; (*p); p = &((*p)->next)) {}; 
		return 1;
	}
	bool insert(CNode<T>* nodo) {
		CNode<T>** p = nullptr;
		find(p);				
		*p = nodo;
		return 1;
	}
	bool del() {    //Delete the first and the second is now first
		CNode<T>* t = first;
		first = first->next;
		delete t;
		return 1;
	}
	void print() {
		std::cout << "FIRST->";
		for (CNode<T>* p = first; p; p = p->next) {
			std::cout << p->m_v << "->";
		}
		std::cout << "->Null";
	}
};

template<class T>
struct BinaryTree {
	CNode<T>* root;
	BinaryTree() { root = nullptr; }
	~BinaryTree() {}
	bool find(T x, CNode<T>**& p);
	bool insert(T x);
	bool remove(T x);
	void extremos(CNode<T>**& p, CNode<T>**& q);  //Find the inner end of the tree or the greater of the minors 
	void print(int input);    //Print preorder, inorder, reverse or posorder
	int size();		//Size of the tree
	void printLevels();   //Prints by levels
};
template<class T>
bool BinaryTree<T>::find(T x, CNode<T>**& p) {
	for (p = &root; *p && (*p)->m_v != x; p = &((*p)->nodes[(*p)->m_v < x])) {}
	return !!*p; //*p!=nullptr; Helps to return boolean and no pointer
}
template<class T>
bool BinaryTree<T>::insert(T x) { //Insert at the end
	CNode<T>** p;
	if (!find(x, p)) {
		*p = new CNode<T>(x);
		return 1;
	}
	return 0;
}

template<class T>
void BinaryTree<T>::extremos(CNode<T>**& p, CNode<T>**& q) { //Find the inner end of the tree or the greater of the minors
	q = p;
	p = &((*p)->nodes[0]);

	for (; (*p)->nodes[1]; p = &((*p)->nodes[1])) {}    //Go left 1 time and then all right
	(*q)->m_v = (*p)->m_v;
	return;
}

template <class T>
bool BinaryTree<T>::remove(T v) {  
	CNode<T>** p;
	CNode<T>** q;
	CNode <T>* t;
	bool del = 0;  //To know if the one on the right or left is deleted
	if (find(v, p)) {
		if ((*p)->nodes[0] && (*p)->nodes[1]) {
			//Inner ends
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
	int orden[4] = { 0, 1, 2, 3 };   //Array that is modified to help any type of printing
	if (input == 2) {    //If preorder some values must be changed
		orden[0] = 1;
		orden[1] = 0;
	}
	else if (input == 3) {
		orden[1] = 2;
		orden[2] = 1;
	}
	else if (input == 4) {
		for (int i=2, j=0; i >=0; i--, j++) {
			orden[j] = i;
		}
	}

	while (S.cima) {  //If the stack is not empty
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

template<class T>
int BinaryTree<T>::size() {		
	int sum = 1;
	int maxSum = 0;  //Tree size
	Stack<T> S(root);
	while(S.cima) {	//Go all over the tree in search of the longest branch
		if (S.cima->estado < 2) {  //If the branch has more nodes down way
			S.cima->estado++;
			if (S.cima->nodes[S.cima->estado-1]) {
				S.insert(S.cima->nodes[S.cima->estado-1]);
				sum++;
			}
		}
		else if (S.cima->estado == 2) {   //If the branch reaches its end
			S.cima->estado = 0;
			S.cima = S.cima->pila_abajo;
			if (sum > maxSum) maxSum = sum;
			sum--;
		}	
	}
	return maxSum; 
}

int imprimeEspacios(int espacios) {    //Receive the number of spaces and print them
	for (int i = 0; i < espacios; i++) {
		std::cout << " ";
	}
	return espacios;
}
int spaces(int tam) {		//Receive the size of the tree to see how many spaces are needed
	int espacios = 0;
	for (int i = 0; i < tam-1; i++) {    //Measure how much space is needed
		espacios += pow(2, i);
	}
	imprimeEspacios(espacios);
	return espacios;
}

template<class T>
void BinaryTree<T>::printLevels() {
	Cola<T> P;
	CNode<T>* t=nullptr;
	P.first = root;
	int guiones = 0;    //Count how many null there are
	int nivel = 1;		//Count on what level they go
	int cantidad = pow(2,nivel);	//Gives the number of nodes that must be in the level
	int espacioNivel=spaces(size());	//Gives the printed space on the level
	int espacioAnterior = espacioNivel;	/*Save the printed space of the previous level,
										 therefore we must know that the space between the "wall" and the first
										 level node is the same as separating nodes at the next level*/
	std::cout << "R\n"; //Root
	imprimeEspacios(espacioNivel);  //Print the space of the level
	if (P.first) {
		std::cout << P.first->m_v << std::endl;   //Root 
	}
	espacioNivel=(espacioNivel-1)/2;	//Calculate the space corresponding to the current level
	imprimeEspacios(espacioNivel);
	for (; P.first; P.first = t) {  //Fill stack with nodes depending on tree level
		if (P.first->nodes[0]) {   //Print value and fill the stack with the left node
			std::cout << P.first->nodes[0]->m_v;
			P.insert(P.first->nodes[0]);
		}
		else {
			CNode<T>* nVacio;
			nVacio = new CNode<T>(-100);   //Node for the empty spaces
			P.insert(nVacio);
			std::cout << " ";
		}
		imprimeEspacios(espacioAnterior);  //Print space from previous level for better view
		if (P.first->nodes[1]) {   //Print value and fill the stack with the left node
			std::cout << P.first->nodes[1]->m_v;
			P.insert(P.first->nodes[1]);
		}
		else {
			CNode<T>* nVacio;
			nVacio = new CNode<T>(-100);	//Node for the empty spaces
			P.insert(nVacio);
			std::cout << " ";
		}
		cantidad = cantidad - 2;  //As two nodes were read, the number of nodes at the current level is subtracted by two
		if (cantidad > 0) {    //If not new level prints the necessary space
			imprimeEspacios(espacioAnterior);
		}
		else {		//If it is new level
			std::cout << std::endl;
			espacioAnterior = espacioNivel;   //The current space now be the previous
			espacioNivel = (espacioNivel - 1) / 2;  //We found the space of the current level
			imprimeEspacios(espacioNivel);
			nivel += 1;		
			cantidad = pow(2, nivel);
			bool vacio = true;
			CNode<T>* Pf = P.first;
			for (int i = 0; i < cantidad &&Pf; Pf = Pf->next,i++) {
				if (Pf->m_v != -100) vacio = false;
			}
			if (vacio) P.first->next= nullptr;
		}
		t = P.first->next;
		P.first->next = nullptr;
	}

	return;
}


template <class T>
void menu(BinaryTree<T>& L) {
	int input, input2, play;
	bool play2 = true;

	while (play2) {
		system("CLS");
		std::cout << "MENU\n 1) Add node \n 2) Delete Node \n 3) Print\n Input: ";
		std::cin >> input;

		switch (input)
		{
		case 1:
			std::cout << "\nWhat is the value (Preferably 0 to 9)? ";
			std::cin >> input2;
			L.insert(input2);
			L.printLevels();
			break;
		case 2:
			std::cout << "\nWhich is the value? ";
			std::cin >> input2;
			L.remove(input2);
			L.printLevels();
			break;
		case 3:
			int input3;
			system("CLS");
			std::cout << "\n1)Inorder\n2)Preorder\n3)Posorder\n4)Reverse\n5)Level Printing\nInsert value: ";
			std::cin >> input3;
			if (input3!=5) L.print(input3);
			else { L.printLevels(); }
			break;
		default:
			break;
		}

		std::cout << "\nDo you want to keep modifying it? Yes(1) o No(0): ";
		std::cin >> play;
		if (play != 0 && play != 1) {
			play = 1;
		}
		play2 = play;
	}
	return;
}
int main() {
	BinaryTree<int> CB;

	//Commented part is for testing the tree without a menu

	//CB.print();
	//CB.printLevels();
	menu(CB);
	//CB.insert(1);
	//CB.insert(0);
	//CB.insert(2);
	//CB.insert(9);
	//CB.insert(1);
	//CB.insert(8);
	//CB.insert(6);
	//CB.insert(3);
	//CB.insert(7);
	//CB.insert(0);
	//std::cout << CB.size() << std::endl;
	///*CB.insert(0);*/
	////CB.insert(0);

	//CB.printLevels();
	//CB.print(1);
}