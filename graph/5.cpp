// TARJAN'S ALGO
// bridges and articulation points

#include <bits/stdc++.h>
#include "1.h"
using namespace std;


// FINDING BRIDGES // time- O(V+E), space- O(V)

//LOGIC- Suppose there exists a edge from u -> v, now after removal of this edge 
//if v can’t be reached by any other edges then u -> v edge is bridge.

void bridgeUtil(graph<int> g, vector<bool>&visited, 
vector<int>&disc, vector<int>&low,
int parent, int u){

    //cout<<" - "<<u<<endl;
    static int time=0;

    visited[u]=true;
    disc[u]= low[u] = ++time;

    list<int>::iterator i;
    for(i= g.adj[u].begin(); i!=g.adj[u].end();++i){
        int v= *i;

        //1) if v is parent
        if(v==parent){
            continue;
        }

        //2) if v is visited
        // this is a back edge basically
        if(visited[v]){
            low[u] = min(low[u],disc[v]);
        }

        //3) if v is not visited
        else{
            parent=u;
            bridgeUtil(g,visited,disc,low,parent,v);

            low[u] = min(low[u],low[v]); // low[u] will be updated if u-v is linked to back edge

            if(low[v]>disc[u]){ //bridge
                cout<<u<<"-"<<v<<endl;
            }
        }
    }

}


void bridge(graph<int> g){

    int V= g.adj.size(); // no of vertices

    vector<bool> visited (V,false); // visited nodes in dfs traversal
    vector<int> disc (V,-1); // discovery time according to dfs traversal
    
    // min disc of all adjacent nodes **except parent node**
    vector<int> low (V,-1); 

    int parent = -1;
    
    for(int i=0;i<V;i++){ // checks for bridges in all components of graph
        if(visited[i]==false){
            bridgeUtil(g,visited,disc,low,parent,i); // checks for bridges in one component of graph
        }
    }
    
}



// FINDING ARTICULATION POINTS // time- O(V+E), space- O(V+E)

//LOGIC- u is articulation pt if
//1) u is the *root* of the DFS tree and it has *at least two children*. 
//2) u is *not the root* of the DFS tree and it has a child v such that -
// no vertex in the subtree rooted with v 
// has a back edge to one of the ancestors in DFS tree of u.

void APutil(graph<int> g, bool visited[], int disc[], int low[], bool isAP[], 
int& time, int parent, int u){

    int children=0;

    visited[u]=true;

    disc[u] = low[u] = ++time;

    for(auto v: g.adj[u]){
        if(!visited[v]){
            children++;
            APutil(g,visited,disc,low,isAP,time, u, v);

            low[u] = min(low[u],low[v]);

            if(parent!=-1 && low[v]>=disc[u]){ // (2)
            // if low[v]>=disc[u] that means that the v rooted subtrees 
            // dont have any back edge with ancestors of u
                isAP[u] = true;
            }
        }
        else if (v!=parent){
            low[u] = min(low[u],disc[v]);
        }
    }

    if(parent==-1 && children>=2){ // (1)
        isAP[u]=true;
    }

}


void AP(graph<int> g){
    int V= g.adj.size();

    int disc[V]={0}; // discovery time acc to dfs traversal
    int low[V]; // min disc of all adjacent nodes **except parent node and visited nodes**

    bool visited[V]={false}; // marks for visited nodes
    bool isAP[V]={false}; 

    static int time=0; 
    int parent =-1;

    for(int u=0;u<V;u++){ // for all the disconnected components of graph 
        if(!visited[u]){
            APutil(g,visited,disc,low,isAP,time,parent,u);
        }
    }

    for(int u=0;u<V;u++){
        if(isAP[u]){
            cout<<u<<" ";
        }
    }
}



// qn - make minimum number of edges in the graph 
//      so that there is no ap and bridges
//eg - 5  1 0  0 2  2 1  0 3  3 4
//ans -  1-4 







int main(){

// 5  1 0  0 2  2 1  0 3  3 4
// 3  0 1  1 2  2 3
// 8  0 1  1 2  2 0  1 3  1 4  1 6  3 5  4 5

    graph<int> g;

    int edgecount;
    cin>>edgecount;

    int u,v;
    for(int i=0;i<edgecount;i++){
        cin>>u>>v;
        g.addEdge(u,v,0);
    }

    g.printAdjList();

    cout<<endl<<"Articulation pts are - "<<endl;
    AP(g);

    cout<<endl<<"Bridges are - "<<endl;
    bridge(g);
    

    return 0;
}
