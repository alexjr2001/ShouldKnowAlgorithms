//Project: Hash Table
//Date: 10/2022
//We adapt the hash table model to work with some different structures such as lists, sets, stacks.

#include<iostream>
#include <list>
#include <stack>
#include <set>
#include <vector>

template<class T>
class F {			//Hash Code
public:	
	unsigned int operator()(T x) {
		return (x*x);
	}
};


//All the following adaptors have insertion method (ins), remove (rem), find and print.
template <class T>
class listAdaptor {
public:
	std::list<T> L;
	void ins(T x) {
		L.push_back(x);
	}
	void rem(T x) {
		L.remove(x);
	}
	bool find(T x) {
		for (std::list<char>::iterator it = L.begin(); it != L.end(); ++it) {
			if (*it == x) return 1;
		}
		return 0;
	}
	void print(int x) {
		std::cout << "tabla " << x << " | ";
		for (std::list<char>::iterator it = L.begin(); it != L.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
};

template <class T>
class setAdaptor {
	std::set<T> BTree;
public:
	void ins(T x) {
		BTree.insert(x);
	}
	void rem(T x) {
		BTree.erase(x);
	}
	bool find(T x) {
		return BTree.find(x)!=BTree.end(); //return	
	}
	void print(T x) {
		std::cout << "tabla " << x << " | ";
		for (std::set<int>::iterator it = BTree.begin(); it != BTree.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
	}
};

template <class T>
class stackAdaptor {
	std::stack<T> stack;
	std::stack<T> stack2;
public:
	void ins(T x) {
		stack.push(x);
	}
	void rem(T x) {
		stack.pop();
	}
	bool find(T x, T eliminado = 0) {
		if (eliminado == x || stack.empty()) {
			while (!stack2.empty()) {
				stack.push(stack2.top());
				stack2.pop();
			}
			return eliminado==x;
		}

		eliminado = stack.top();
		stack2.push(eliminado);
		stack.pop();
		find(x, eliminado);
	}
	void print(int x) {
		std::cout << "tabla " << x << " | ";
		while (!stack.empty()) {	//vaciar
			stack2.push(stack.top());
			stack.pop();
		}
		while (!stack2.empty()) {		//rellenar e imprimir
			stack.push(stack2.top());
			std::cout << stack.top() << " ";
			stack2.pop();
		}
		std::cout << std::endl;
	}
};


template<class T, class Fx, class S, unsigned long size>
class CHashTable {
public:
	S m_ht[size];		//Structure
	Fx m_fx;			//Hash Code
	//We make polymorphism according the structure we call its method
	void insert(T x) {					
		m_ht[m_fx(x)%size].ins(x);
	}
	void remove(T x) {
		m_ht[m_fx(x) % size].rem(x);
	}
	bool find(T x) {
		return m_ht[m_fx(x) % size].find(x);
	}
	void print() {
		for (int i = 0; i < size; i++) {
			m_ht[i].print(i);
		}
	}
};



int main() {
	//We try with every available structure
	CHashTable<char, F<char>, listAdaptor<char>, 17> ht;
	ht.insert('2');
	ht.insert('w');
	std::cout << ht.find('w');
	ht.print();
	CHashTable<int, F<int>, setAdaptor<int>, 7> ht1;
	ht1.insert(10);
	ht1.insert(11);
	ht1.insert(1);
	std::cout << ht1.find(2);
	ht1.print();
	CHashTable<int, F<int>, stackAdaptor<int>, 7> ht2;
	ht2.insert(5);
	ht2.insert(1);
	std::cout<< ht2.find(1);
	ht2.remove(1);
	std::cout << ht2.find(1);
	ht2.print();
	return 0;
}