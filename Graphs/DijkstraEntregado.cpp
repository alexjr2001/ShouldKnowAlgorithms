/*
Project: Dijkstra algorithm

Code that aims at two tasks related to the Dijkstra algorithm, one is to enter two existing nodes 
to find their shortest way between the two and the second task is to get the shortest way to all the 
nodes from the only existing node entered.

@author Alexander Sebasti�n G�mez Del Carpio
*/
#include<iostream>
#include<list>
#include<vector>  

using namespace std;

template<class G>
struct CNode {			
	typedef typename G::N N;
	typedef typename G::Edge Edge;
	N m_n;
	list<Edge*> m_edges;

	typedef typename G::E E;
	typedef typename G::Node Node;
	E dk_n;			//Save the value of the sum of the edges
	Node* dk_prev;   //Save the previous graph


	CNode(N v) {
		m_n = v;
		dk_n = 0;
		dk_prev = nullptr;
	}
};

template<class G>
struct CEdge {
	typedef typename G::E E;
	typedef typename G::Node Node;

	E m_e;
	Node* m_nodes[2];
	bool dir;			// True Direction = Bidirectional Direction

	CEdge(Node* a, Node* b, E e, bool _dir) {
		m_e = e;
		m_nodes[0] = a;
		m_nodes[1] = b;
		dir = _dir;
	}
};

template<class _N, class _E>
class CGraph {
public:
	typedef CGraph<_N, _E> G;
	typedef CNode<G> Node;
	typedef CEdge<G> Edge;
	typedef _N N;
	typedef _E E;

	vector<Node*> nodes;
	//Methods
	bool InsNode(N);
	bool InsEdge(N, N,E,bool);
	bool RemNode(N);
	bool RemEdge(N,N,E);
};

template<class _N, class _E>
bool CGraph<_N,_E>::InsNode(N n) {		//Insert nodes flying around in the list of the graph
	for (typename vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
		if ((*it)->m_n == n) return 0;
	}
	Node* p = new Node(n);
	nodes.push_back(p);  
	return 1;	
}   
template<class _N, class _E>
bool CGraph<_N, _E>::InsEdge(N node1, N node2, E e, bool dir){  //Connects two nodes 
	Node* a = nullptr;	//a and b point to the respective nodes
	Node* b = nullptr; 
	int i = 0;	 //Saves how many nodes were found
	for (typename vector<Node*>::iterator it = nodes.begin(); i<2 && it != nodes.end(); ++it) {
		if ((*it)->m_n == node1) {
			i++;
			a = *it;
		}
		if ((*it)->m_n == node2) {
			i++;
			b = *it;
		}
	}
	if (a && b) {    //If we found the nodes we join them
		Edge* p = new Edge(a, b, e, dir);
		if (a != b) {
			a->m_edges.push_back(p);
			b->m_edges.push_back(p);
		}
		else {
			a->m_edges.push_back(p);
		}
		return 1;
	}
	else {
		cout << "\nNo existe alguno de los nodos " << node1 << " " << node2 << "para conectar\n";
		return 0;
	}
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemNode(N n){
	Node* p=nullptr;   //Points to the node to delete
	typename vector<Node*>::iterator n_erase;	//Iterator that saves the position to delete
	for (typename vector<Node*>::iterator it = nodes.begin();it != nodes.end(); ++it) {
		if ((*it)->m_n == n) {
			p = *it;
			n_erase = it;
		}
	}
	if (p) {
		Node* q = nullptr;  //Points to nodes that have some connection with the node to delete
		Edge* e_erase = nullptr;  //Points to edges that are connected to the node to be removed
		for (typename list<Edge*>::iterator it = p->m_edges.begin(); it != p->m_edges.end();) {		//We found the edge involved
			if ((*it)->m_nodes[0] != p) {
				q = (*it)->m_nodes[0];
			}
			else {
				q = (*it)->m_nodes[1];
			}
			bool erased = false;   //Let us know if the edge is removed
			for (typename list<Edge*>::iterator it2 = q->m_edges.begin();!erased && it2 != q->m_edges.end(); ) {		//We’ll erase edge by edge
				if ((*it2)->m_nodes[0]->m_n == n || (*it2)->m_nodes[1]->m_n == n) {
					q->m_edges.erase(it2);
					erased = true; 
				}
				else {
					++it2;
				}
			}
			e_erase = *it;         
			it=p->m_edges.erase(it);  //We erase the edge one by one
			delete e_erase;
		}
		nodes.erase(n_erase);		//Finally we delete the node
		delete p;
		return 1;
	}
	else {
		cout << "\nNo existe el nodo "<< n <<endl;
		return 0;
	}
}

template<class _N, class _E>
bool CGraph<_N, _E>::RemEdge(N node1, N node2, E e) {
	Node* n_erase = nullptr;   //Points to a node that has the edge to erase
	Edge* e_erase = nullptr;	//Points to the edge to erase
	for (typename vector<Node*>::iterator it = nodes.begin();it != nodes.end(); ++it) {
		if((*it)->m_n==node1){    //We find the node that has the edge to remove 
			for (typename list<Edge*>::iterator it2 = (*it)->m_edges.begin(); it2 != (*it)->m_edges.end();){	//We look edge by edge
				if ((*it2)->m_e == e) {		//We look for if that node has an edge with the indicated value
					if ((*it2)->m_nodes[1]->m_n == node2) {   //We look for if that edge points to the second correct node
						n_erase = (*it2)->m_nodes[1];
					}
					else if ((*it2)->m_nodes[0]->m_n == node2) {
						n_erase = (*it2)->m_nodes[0];
					}
					if (n_erase) {
						bool erased = false;
						for (typename list<Edge*>::iterator it3 = n_erase->m_edges.begin(); !erased && it3 != n_erase->m_edges.end();) {  //We look for the edge on the second node
							if ((*it3)->m_e == e && ((*it3)->m_nodes[1]->m_n == node1 || (*it3)->m_nodes[0]->m_n == node1)) {
								it3=n_erase->m_edges.erase(it3);    //We delete the edge of the second node
								erased = true;
							}
							else {
								++it3;
							}
						}
						e_erase = *it2;
						it2 = (*it)->m_edges.erase(it2);	//We delete the edge of the first node
						delete e_erase;
						return 1;
					}
				}
				else {
					++it2;
				}
			}
		}
	}
	return 0;
}

class GraphNumNum :public CGraph<int,int>{
public:
	void restart() {	//Function that restarts values for a new Dijkstra
		for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			(*it)->dk_n = 0;
			(*it)->dk_prev = 0;
		}
	}
	bool DijkstraAlg(Node*& o, int _o, Node*& d, int _d = -1) {		//Dijkstra Algorithm
		vector<Node*>::iterator newBegin;    //Locate where the origin is
		for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {
			if ((*it)->m_n == _o) {
				newBegin = it;
				o = *it;
			}
			if ((*it)->m_n == _d) {
				d = *it;
			}
		}
		if ((o&&d)||(o && _d==-1)) {
			Node* post = nullptr;		//Apuntan al par de nodos a analizar
			Node* prev = nullptr;
			bool vuelta = 0;		//Check if I’ve already traversed all the nodes
			vector<Node*>::iterator almostEnd;
			for (vector<Node*>::iterator it2 = newBegin;it2 != newBegin || !vuelta;) {
				vuelta = 1;
				prev = *it2;
				for (list<Edge*>::iterator it = prev->m_edges.begin(); it != prev->m_edges.end(); ++it) {		//Find all edges of the first node
					if ((*it)->dir && (*it)->m_nodes[0]->m_n != prev->m_n && (*it)->m_nodes[0]->m_n!=o->m_n) {		//If it is bidirectional 
						post = (*it)->m_nodes[0];
					}
					else if ((*it)->m_nodes[1]->m_n != prev->m_n && (*it)->m_nodes[1]->m_n != o->m_n) {			//If it’s one direction
						post = (*it)->m_nodes[1];
					}
					if (post) {				//If the respective nodes are found
						if (post->dk_n == 0 || post->dk_n > prev->dk_n + (*it)->m_e) {		// If the second node has a longer path we replace it
							post->dk_n = prev->dk_n + (*it)->m_e;
							post->dk_prev = prev;
						}
						if ((*it)->dir && prev->dk_n > post->dk_n + (*it)->m_e) {			//If the first node has a longer path for other side we replace it
							prev->dk_n = post->dk_n + (*it)->m_e;
							prev->dk_prev = post;
						}
					}
				}
				post = nullptr;
				almostEnd = it2;
				if (++almostEnd == nodes.end()) it2 = nodes.begin();
				else { ++it2; }
			}
			return 1;
		}
		else {
			return 0;
		}
	}

	bool Dijkstra(int _o) {		//Use DijkstraAlgorithm() to print the shortest paths from the parameter to the rest
		Node* o = nullptr;
		Node* all = nullptr;  //Pointer not to be used
		if (!DijkstraAlg(o,_o,all)) {
			cout << "No existe el nodo " << _o;
			return 0;
		}
		for (vector<Node*>::iterator it = nodes.begin(); it != nodes.end(); ++it) {   //We go node by node to see its way to _o
			if (*it != o) {
				list<int> path;		//We create a list to store nodes that has its way
				for (Node* p = *it; p != o; p = p->dk_prev) {
					path.push_front(p->m_n);
				}
				cout << "[" << _o;
				for (list<int>::iterator it = path.begin(); it != path.end(); ++it) {
					cout << "," << (*it);
				}
				cout << "] ";
			}
		}
		restart();	//We leave everything as the beginning
		return 1;
	}
	bool Dijkstra(int _o, int _d) {		//Use DijkstraAlg() to discover the shortest way from or to d.
		Node* o = nullptr;  //Will point to the origin node
		Node* d = nullptr;  //Will point to the destination node
		if (!DijkstraAlg(o,_o,d, _d)) {
			cout << "No existe el origen " << _o << " y/o el destino " << _d;
			return 0;
		}
		list<int> path;		//We create a list to store the nodes that the origin is in its path
		for (Node* p = d; p != o; p = p->dk_prev) {
			path.push_front(p->m_n);
		}
		cout << "[" << _o;
		for (list<int>::iterator it = path.begin(); it != path.end(); ++it) {
			cout << ","<< (*it);
		}
		cout << "]"<<endl;
		restart(); //We leave everything as the beginning
		return 1;
	}
};


int main() {
	//First exercise
	cout << "First exercise: ";
	GraphNumNum Graph1;
	for (int i = 1; i < 10; i++) {
		Graph1.InsNode(i);
	}
	Graph1.InsEdge(1,2,2,1);
	Graph1.InsEdge(1,3,5,1);
	Graph1.InsEdge(1,4,2,1);
	Graph1.InsEdge(2,3,3,1);
	Graph1.InsEdge(2,5,1,1);
	Graph1.InsEdge(3,5,1,1);
	Graph1.InsEdge(3,4,3,1);
	Graph1.InsEdge(3,6,1,1);
	Graph1.InsEdge(3,8,1,1);
	Graph1.InsEdge(4,7,2,1);
	Graph1.InsEdge(5,9,7,1);
	Graph1.InsEdge(6,8,3,1);
	Graph1.InsEdge(6,7,2,1);
	Graph1.InsEdge(8,9,1,1);
	Graph1.Dijkstra(1, 9);

	//Second exercise
	cout << "\nSecond exercise: ";
	GraphNumNum Graph2;
	for (int i = 0; i < 9; i++) {
		Graph2.InsNode(i);
	}
	Graph2.InsEdge(0,1,2,1);
	Graph2.InsEdge(0,2,5,1);
	Graph2.InsEdge(0,3,2,1);
	Graph2.InsEdge(1,4,1,1);
	Graph2.InsEdge(2,4,1,1);
	Graph2.InsEdge(2,7,1,1);
	Graph2.InsEdge(2,5,1,1);
	Graph2.InsEdge(2,3,3,1);
	Graph2.InsEdge(3,6,2,1);
	Graph2.InsEdge(4,8,7,1);
	Graph2.InsEdge(5,7,3,1);
	Graph2.InsEdge(5,6,2,1);
	Graph2.InsEdge(7,8,1,1);
	Graph2.Dijkstra(0);

	return 0;
}