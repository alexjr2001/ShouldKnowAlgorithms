//Project: Doubly Circular Linked List

#include <iostream>
template <class T>
class nodo {			//Node with 2 pointers
public:
	T valor;
	nodo<T>* next;
	nodo<T>* prev;
	nodo(T v, nodo<T>* n = nullptr, nodo<T>*p=nullptr) :valor(v), next(n), prev(p) {}
};

template<class T>
class LDECircular {
public:
	nodo<T>* head;
	LDECircular(nodo<T>* h = nullptr) :head(h) {}
	~LDECircular() {
		nodo<T>* t = nullptr;
		for (nodo<T>* p = head; t!=head; p = t)
		{
			t = p->next;
			delete p;
		}
	}
	bool find(T v, nodo<T>*& p);
	bool insert(T v);
	bool del(T v);
	void print();
};


template<class T>
bool LDECircular<T>::find(T v, nodo<T>*& p) {		//We searcH through all the list until we arrive  for second time to head
	int vueltas = 0;
	for (nodo<T>*ant= head; head&& (ant->valor == v || ((ant != head || vueltas != 1)&&(ant->valor<v||head->valor>=v)));ant = ant->next) {  //Vueltas it means laps in the second lap we stop
		if (ant->valor == v && vueltas!=0) {
			return 1;
		}
		if (ant==head) vueltas = 1;
		p = ant;
	}

	return 0;
}

template <class T>
bool LDECircular<T>::insert(T v) {
	nodo<T>* p = nullptr;
	if (!find(v, p)) {
		if (!p) {
			head = new nodo<T>(v);
			head->next = head;
			head->prev = head;
		}
		else {
			if (p == p->next) {			
				p->next = new nodo<T>(v, p, p);
				p->prev = p->next;
			}
			else {
				p->next = new nodo<T>(v, p->next, p);
				p->next->next->prev = p->next;
			}
			if (head->valor > v) head = p->next;
		}
		return 1;
	}
	return 0;
} 

template <class T>
bool LDECircular<T>::del(T v) {
	nodo<T>* p = nullptr;
	nodo<T>* t = nullptr;
	if (find(v, p)) {
		t = p->next;
		if (p != head || p!=p->next) {		//We delete and set the new pointers at the back and front
			p->next = p->next->next;
			p->next->prev = p;
			if (t == head) head = p->next;
		}
		else {
			head = nullptr;
		}
		delete t;
		return 1;
	}
	return 0;
}

template<class T>
void LDECircular<T>::print() {			//Print all the values from both sides
	std::cout << "\nHEAD->";		//From Head
	nodo<T>* p = head;
	for (; p && p->next->valor != head->valor; p = p->next) {
		std::cout << p->valor << "->";
	}
	if (p) {
		std::cout << p->valor << "->" << p->next->valor;
	}
	else {
		std::cout << "NULL";
	}
	std::cout << "\nTAIL->";		//From tail

	for (p=head; p && p->prev->valor != head->valor; p = p->prev) {
		std::cout << p->valor << "->";
	}
	if (p) {
		std::cout << p->valor << "->" << p->prev->valor;
	}
	else {
		std::cout << "NULL";
	}
}


template <class T>
void menu(LDECircular<T>& L) {
	int input, input2, play;
	bool play2 = true;

	while (play2) {
		system("CLS");
		std::cout << "MENU\n 1) Add Node \n 2) Delete node \n 3) Print list \n Input: ";
		std::cin >> input;

		switch (input)
		{
		case 1:
			std::cout << "\nWhich is the value? ";
			std::cin >> input2;
			L.insert(input2);
			L.print();
			break;
		case 2:
			std::cout << "\nWhich is the value 2? ";
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

		std::cout << "\nDo you want to continue modifying the list? Yes(1) o No(0): ";
		std::cin >> play;
		if (play != 0 && play != 1) {
			play = 1;
		}
		play2 = play;
	}
	return;
}

int main() {
	LDECircular<int> L;
	menu(L);
	return 0;
}
