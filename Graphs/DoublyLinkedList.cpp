//Project: Double linked list

#include <iostream>
template<class T>
struct nodo{        //Node with two pointers
	T valor;
	nodo<T>* prev;
	nodo<T>* next;
	nodo(T v=0, nodo<T>*p=nullptr, nodo<T>*n=nullptr) {
		valor = v;
		next = n;
		prev = p;
	}
};
template<class T>
struct LE {             //List structure
	nodo<T>* head;
	LE(nodo<T>* h = nullptr) {	
		head = h;
	}
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
	void del(T);
	void print();
};
template<class T>
bool LE<T>::find(T v, nodo<T>*& ant) {
	bool result = false;
	for (nodo<T>* p = head; p&& p->valor<=v; p = p->next) {             //We traverse the list using the pointers until we find it or we get to the end
		if (p->valor == v) {
			result = true;
			break;
		}
		ant = p;
	}
	return result;
}
template<class T>
void LE<T>::add(T v){
	nodo<T>* ant = nullptr;
	if (!find(v, ant)) {
		if (ant) {          //In case it is NOT the new first node
			ant->next = new nodo<T>(v, ant, ant->next);
			if (ant->next->next) {
				ant->next->next->prev = ant->next;
			}

		}
		else {          //In case it is the new first node
			head = new nodo<T>(v, nullptr, head);
			if (head->next) {
				head->next->prev = head;
			}
		}
		std::cout << "\nNode added: " << v << std::endl;	
	}
	else {
		std::cout << "\nNode already exists: " << v << std::endl;
	}
}
template <class T>
void LE<T>::del(T v) {
	nodo<T>* ant = nullptr;
	nodo<T>* temp = nullptr;
	if (find(v, ant)) {
		if (ant) {      //In case it is NOT the first node
			temp = ant->next->next;
			delete ant->next;
			ant->next = temp;
			if(ant->next)
			ant->next->prev = ant;
		}
		else {      //In case it is the first node
			temp = head->next;
			delete head;
			head = temp;
			if (head)
			head->prev = nullptr;
		}
		std::cout << "\nNode Deleted: " << v << std::endl;
	}
	else {
		std::cout << "\nNode already exists: " << v << std::endl;
	}
	return;
}
template <class T>
void LE<T>::print() {
	nodo<T>* ult = 0;
	std::cout << "head->";
	for (nodo<T>* p = head; p; p = p->next) {
		std::cout << p->valor << "->";
		if (p->next == nullptr) {
			ult = p;
		}
	}
	std::cout << "NULL\n";
	std::cout << "tail->";
	for (; ult; ult = ult->prev) {
		std::cout << ult->valor << "->";
	}
	std::cout << "head\n";
	return;
}

template <class T>
void menu(LE<T>& L) {           //A menu to manage the structure with the console
	int input, input2,play;
	bool play2 = true;

	while (play2) {
		system("CLS");
		std::cout << "MENU\n 1) Add node \n 2) Delete node \n 3) Print list \n Input: ";
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
	LE<int> lista;
	menu(lista);
	return 0;
}
