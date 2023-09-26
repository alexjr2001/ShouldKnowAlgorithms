//Project: Simple linked list

#include<iostream>

template <class T>
struct nodo {           //Node with a pointer to the front
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
	bool find(T, nodo<T>*&);
	void add(T);
	void del(T);//revisar
	void print();
};

template <class T>
bool LE<T>::find(T v, nodo<T>*&ant) {
	bool result = false;
	for (nodo<T>* p = head; p && p->valor <= v; p = p->next) {          //We look out for the node when we traverse all the list
		if (p->valor == v) {
			result = true;
			break;
		}
		ant = p;
	}
	return result;
}
template <class T>
void LE<T>::add(T v) {
	nodo<T>* ant = nullptr;
	if (!find(v, ant)) {
		if (ant) {          //In case it is not the first
			ant->next = new nodo<T>(v, ant->next);
		}
		else {
			head = new nodo<T>(v, head);
		}
		std::cout << "\nNode added: " << v << std::endl;	
	}
	else {
		std::cout << "\nNode already exists: " << v << std::endl;
	}
	return;
}
template <class T>
void LE<T>::del(T v) {
	nodo<T>* ant=nullptr;
	nodo<T>* temp=nullptr;
	if (find(v, ant)) {
		if (ant) {              //In case it is not the first
			temp = ant->next->next;
			delete ant->next;
			ant->next = temp;
		}
		else {
			temp = head->next;
			delete head;
			head = temp;
		}
		std::cout << "\nNode deleted: " << v << std::endl;
	}
	else {
		std::cout << "\nNode does not exist: " << v << std::endl;
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

template <class T>
void menu(LE<T>& L) {
	int input, input2,play;
	bool play2 = true;

	while (play2) {
		system("CLS");
		std::cout << "MENU\n 1) Add Node \n 2) Delete Node \n 3) Print list \n Input: ";
		std::cin >> input;

		switch (input)
		{
		case 1:
			std::cout << "\nWhich is the value? ";
			std::cin >> input2;
			L.add(input2);
			L.print();
			break;
		case 2:
			std::cout << "\nWhich is the value? ";
			std::cin >> input2;
			L.del(input2);
			L.print();
			break;
		case 3:
			L.print();
			break;
		default:
			break;
		}

		std::cout << "\nDo you want to keep modifying the list? Yes(1) o No(0): ";
		std::cin >> play;
		if (play != 0 && play != 1) {
			play = 1;
		}
		play2 = play;
	}
	return; 
}

int main() {
	LE<int> lista;
	menu(lista);
	return 0;
}