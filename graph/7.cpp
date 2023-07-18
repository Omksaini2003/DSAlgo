// union-find algorithm
#include <bits/stdc++.h>
#include "1.h"
using namespace std;


// union-find algorithm -- to detect whether the given undirected graph is cyclic or not

int find(int parent[],int i){
    if(parent[i]==i){
        return i;
    }
    return find(parent,parent[i]);
}

void Union(int parent[], int x, int y){
    parent[x]=y;
}

bool isCyclic(graph<int> g,int E){
    int V = g.V();
    //int E = g.E(0);


    int parent[V];

    for(int i=0;i<V;i++){
        parent[i]=i;
    }

    for(int i=0;i<V;i++){
        int x= find(parent, i);
        for(auto j : g.adj[i]){
            int y=find(parent, j);

            if(x==y){
                return 1;
            }

            Union(parent,x,y);
        }
    }
    return 0;

}


// 3  0 1  1 2  0 2


int main(){

    int e;
    cin>>e;

    graph<int> g;

    for(int i=0;i<e;i++){
        int u,v;
        cin>>u>>v;
        g.addEdge(u,v,0);
    }

    cout<<isCyclic(g,e);

    return 0;
}