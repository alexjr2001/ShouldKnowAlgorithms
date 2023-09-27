//Project: Longest common subsequence
//Date: 19/05/2022
#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*void push(string &s, string t){
	for(int i=0;i<t.size();i++){
		s.push_back(t[i]);
	}
}*/

int main() {
	string a("BDCA");
	string b("ABCB");
	vector<vector<vector<string>>> M(a.size(),vector<vector<string>> (a.size(),vector<string>(' ')));		//DP algorithm
	for(int i=0;i<a.size();i++){
		M[0][i][0]=a[i];
	}

	string t;
	int index;
	for(int i=1;i<a.size();i++){
		for(int j=0;j<a.size()-i;j++){
			index=0;
			for(int k=j+1;k<a.size()-i+1;k++){
				for(int l=0;l<M[i-1][k][l].size();l++){
					t=M[0][j][0]+M[i-1][k][l];
					M[i][j][index]=t;
					index+=1;
					/*for(int s=0;s<M[i][j].size();s++){		//Printing
							cout<<M[i][j][s]<<" ";
					}
					cout<<endl;*/
				}
			}
		}
	}

	for(int i=0;i<a.size();i++){
		for(int j=0;j<a.size();j++){
	  	for(int k=0; k<M[i][j].size();k++){
					if(M[i][j][k].size()>0)cout<<M[i][j][k]<<" ";	
			}
			cout<<" | ";
		}
		cout<<endl;
	}
	
}
