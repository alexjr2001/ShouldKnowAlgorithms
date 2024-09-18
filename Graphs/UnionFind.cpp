/*
Project: Union Find


Description:
This program implements the Union-Find (or Disjoint Set Union) data structure, which efficiently supports two operations:
1. **Find**: Determines the root representative of a given element with path compression, which helps flatten the tree and speed up future queries.
2. **Union**: Merges two disjoint sets using the union-by-size strategy, ensuring that the smaller tree is always added under the root of the larger tree, minimizing the height of the tree.
Path compression during the `find` operation helps to reduce the depth of the trees, ensuring near-constant time complexity for both operations.
The algorithm is applied to a list of node pairs (edges), where each pair represents a union operation between two elements. After processing all edges, the structure of the disjoint sets is printed.

Complexity:
- Both `find` and `union` operations have an amortized time complexity of nearly O(1), thanks to path compression and union by size.

Usage:
This implementation can be applied in solving problems like connected components, Kruskal's Minimum Spanning Tree, and dynamic connectivity queries in graphs.


@author Alexander Sebasti�n G�mez Del Carpio
*/

#include <iostream>
#include <vector>

using namespace std;

int n_nodes=10;
vector<int> parents;        //Save parent of every node
vector<int> sizeSet(10,1);


int find(int a){            //Find the last parent of a node
    if(parents[a]!=a){ 
        parents[a]=find(parents[a]);    //While path compression, last parent to all the nodes in the path, making the distance just 1
    }
    return parents[a];
}

void unionAlg(int a, int b){
    int finda=find(a);      //Find which is the last parent
    int findb=find(b);

    if(finda==findb){       
        cout<<"Ya estan en el mismo grupo "<<a<<" "<<b<<endl;
        return;
    }

    if(sizeSet[findb]>sizeSet[finda]){      //Depending on the size, the smaller set is union to the big one
        parents[finda]=findb;
        sizeSet[findb] += sizeSet[finda];
    }
    else{
        parents[findb]=finda;
        sizeSet[finda] += sizeSet[findb];
    }
    //Adicional cost, less benefits
    //find(b);  
    cout<<"Se ha unido "<<a<<" "<<b<<endl;
    for(auto x:parents) std::cout<<x<<" ";
    cout<<endl;


}

int main() {
    for (int i = 0; i < n_nodes; i++){      //Initially each node is its own parent
        parents.push_back(i);
    }

    vector<pair<int,int>> edges = {
        {0,1},{8,9},{2,3},{6,7},{4,5},{3,1},{4,7},{3,4}
    };

    for (int i = 0; i < edges.size(); i++)
    {
        unionAlg(edges[i].first,edges[i].second);
    }

    for(auto x:parents){
        cout<<x<<" ";
    }
    cout<<endl;
    

    return 0;
}