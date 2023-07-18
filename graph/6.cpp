//kosaraju algo

#include <bits/stdc++.h>
#include "3.h"
using namespace std;



// find strongly connected components in the given graph
// kosaraju algo --
// 1) make a stack of dfs traversal
// 2) transpose the graph
// 3) pop vertices from stack and traverse dfs, each component made by dfs is a scc
// input eg - 5  0 3  3 4  0 2  2 1  1 0
// output - 0 1 2 /n 3 /n 4


void dfs(Graph g, bool visited[], int src,stack<int>& Stack){
    visited[src]=true;
    for(auto i: g.adj[src]){
        if(!visited[i.first]){
            dfs(g,visited,i.first,Stack);
            Stack.push(i.first);
        }
    }
}

void printSCC(Graph g,int V){

    //making stack of dfs traversal
    
    stack<int> Stack;

    bool visited[V]={false};

    for(int i=0;i<V;i++){
        if(visited[i]==false){
            dfs(g,visited,i,Stack);
            Stack.push(i);
        }
    }


    //transposing graph

    Graph gT;
    
    for(int i=0;i<V;i++){
        for(auto j: g.adj[i]){
            gT.addEdge(j.first,i,1,1);
        }
        visited[i]=false; //for next dfs
    }


    //finding scc for real this time
    
    while(!Stack.empty()){
        int curr = Stack.top();
        Stack.pop();

        if(!visited[curr]){
            stack<int> scc;
            dfs(gT,visited,curr,scc);
            scc.push(curr);

            while(!scc.empty()){
                cout<<scc.top()<<" ";
                scc.pop();
            }
            cout<<endl;
        }
    }
}




// 5  0 3  3 4  0 2  2 1  1 0

int main(){

    Graph g;
    
    int e;
    cin>>e;

    for(int i=0;i<e;i++){
        int u,v,weight;
        cin>>u>>v>>weight;
        g.addEdge(u,v,weight,1);
    }

    BellmanFord(g,5,1,4);

    return 0;
}


