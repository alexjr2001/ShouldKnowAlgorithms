//Project: Priority Queue
//Date: 03/07/2023
#include <iostream>
#include <vector>
#include <memory>
#include <string>

using namespace std;

template<class T>
class Node{
    public:
        T name;
        int priority;       //Value
        //Pointers
        Node<T>* up;
        Node<T>* down;
    Node(T _name, int _p=0, Node<T>* _up=nullptr, Node<T>* _down=nullptr){
        name=_name;
        priority=_p;
        up=_up;
        down=_down;
    }
};

template<class T>
class pQueue{
    public:
        Node<T>* first;

    pQueue(Node<T>* N=nullptr){
        first=N;
    }
    bool insert(T name, int prio=0){
        if(first==nullptr){ 
            first=new Node<T>(name,prio);         //In case there is no values
            return true;
        }   
        Node<T>* p;
        Node<T>* prev;
        Node<T>* location;
        Node<T>* tmp;
        bool found=false;
        for(p=first,prev=nullptr,location=nullptr;p!=nullptr; prev=p,p=p->up){    //We go through all the queue
            if(p->name==name){
                cout<< name <<" IT'S ALREADY IN THE QUEUE\n";
                return false;
            }
            if(p->priority>prio && !found){     //In case the priority is lower, the previous node is the location for the new node
                location=prev;
                found=true;
            }
        }
        if(location==nullptr){
            if(found){      //If location is null is the new first node
                first->down=new Node<T>(name, prio, first);
                first=first->down;
                return true;
            }
            else{           //In case is the top of the queue
                prev->up=new Node<T>(name,prio,nullptr,prev);
                return true;
            }
        }

        //We insert in case it is not at the top or at the bottom
        tmp=location->up;
        location->up=new Node<T>(name, prio);
        location->up->up=tmp;
        location->up->down=location;
        tmp->down=location->up;
    }
    Node<T>* find(T name){      //Find the position of the node
        Node<T>* p;
        for(p=first;p!=nullptr && p->name!=name ;p=p->up);
        return p;
    }
    bool erase(T name){
        Node<T>* tmp;
        Node<T>* p=find(name);
        if(p!=nullptr){     //If we found a node with that name we delete it
            if(p->up!=nullptr){     //In case it is at the top
                if(p==first) first=p->up;
                p->up->down=p->down;
            }
            if(p->down!=nullptr) p->down->up=p->up;     //In case it is the first node
            delete p;
            cout<<"The node was successfully deleted\n";
            return true;
        }
        cout<<"The value was not found\n";
        return false;
    }
    bool setPriority(T name, int newPrio){
        Node<T>* p=find(name);
        if(p){
            return modifyPriority(p,newPrio);
        }
        else{
            cout<<"The name was not found"<<endl;
            return false;
        }
    }
    void print(){
        cout<<"Name\tPriority\n";
        for(Node<T>* p=first;p!=nullptr;p=p->up){
            cout<<p->name<<"\t"<<p->priority<<endl;
        }
    }
    private:
    bool modifyPriority(Node<T>* p, int newPrio){       //The node already found receives a new priority value
        bool located=false;
        Node<T>* newPos=p;
        while(!located){
            if(newPrio<p->priority){
                newPos=newPos->down;
            }
            else{
                newPos=newPos->up;
            }
        }
        return true;
    }
};


int main(){
    Node<string>* p=new Node<string>("Primero",12);
    pQueue<string> pQ(p);

    //Inserting random values with a priority value
    pQ.insert("Segundo",14);
    pQ.insert("Segund",11);
    pQ.insert("Seund",20);
    pQ.insert("Sgund",9);
    pQ.insert("Sund");
    pQ.insert("Segud",12);
    pQ.insert("Segu",19);
    pQ.print();
    p=pQ.find("Seund");
    //if(p) cout<<p->name<<p->priority<<endl;
    pQ.erase("Sund");
    pQ.print();
    return 0;
}
