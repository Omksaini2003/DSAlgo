//minimum spanning tree

#include <bits/stdc++.h>
#include "3.h"
using namespace std;


//prim's algo
// visit https://www.geeksforgeeks.org/prims-minimum-spanning-tree-mst-greedy-algo-5/

bool allTrue(unordered_map<int,pair<bool,int>> kmw){
    for(auto i:kmw){
        if(!i.second.first){
            return false;
        }
    }
    return true;
}
Graph minSpanningTree(Graph g){
    
    Graph ret; //mst graph // node1, node2, weight
    unordered_map<int,pair<bool,int>> kmw; //key, is in mst?, weight

    int arbs; //arbitrary source
    for(auto i:g.adj){
        kmw[i.first].first=false;
        kmw[i.first].second= INT_MAX;
        arbs = i.first;
    }
 
    kmw[arbs].first=true;
    kmw[arbs].second=0;
 
    while(!allTrue(kmw)){
        int min1,min2,w; //will tell us minimum weighted edge 
        w=INT_MAX;

        for(auto i:kmw){
            if(i.second.first)//traverse included ones
            {
                for(auto j: g.adj[i.first])//traverse adjacent nodes of i.first
                {
                    if(!kmw[j.first].first && (kmw[j.first].second>=j.second)) //traverse not included ones whose weight can be minimised
                    {                
                        kmw[j.first].second=j.second;
                        if(w>j.second){
                            w=j.second;
                            min1=i.first;
                            min2=j.first;
                        }
                    }
                }
            }
        }

        ret.addEdge(min1,min2,w,0);
        kmw[min2].first=true;
        
    }
    return ret;
}


//kruskal's algo -- always select a minimum cost edge but if it is forming cycle then discard that edge
// it takes more time than prims so im not really learning it lol

void makeSet(unordered_map<int,pair<int,int>> &parentrank,int size)
{
    for(int i=0;i<size;i++){
        parentrank[i].first = i; //parent of i = i
        parentrank[i].second = 0; // rank of i = 0
    }
}

int findParent(unordered_map<int,pair<int,int>> &parentrank, int node){
    if(parentrank[node].first==node){
        return node;
    }
    return 
}

int minspanningtree(Graph g){
    int size= g.size(0);
    unordered_map<int,pair<int,int>> parentrank; //node, parent, rank of parent
    makeSet(parentrank,size);
}


int main()
{
     int e;
     cout<<" no of edges ";
     cin>>e;
 // 9   0 1 5  0 2 3  1 2 2  1 3 6  2 3 7  2 4 4  2 5 2  3 4 -1  4 5 -2
 // 9   0 1 5  0 2 3  1 2 2  1 3 6  2 3 7  2 4 4  2 6 2  3 4 -1  4 6 -2
// 14   0 1 4   0 7 8   1 2 8   1 7 11   7 8 7   7 6 1   2 8 2   6 8 6   2 3 7   2 5 4   6 5 2   5 3 14   3 4 9   4 5 10   


     Graph g;
     for(int i=0;i<e;i++){
         int u,v,weight;
         cin>>u>>v>>weight;
         g.addEdge(u,v,weight,0);
     }
     g.printAdj();
 
     //vector<int> ans = BFS(g,1);
     //for(auto i:ans){
     //    //cout<<i<<" ";
     //}
     
    Graph min= minSpanningTree(g);
    cout<<"min ahead"<<endl;
    cout<<"weight  = "<<min.totalWeight(0)<<endl;
    min.printAdj();

     return 0;
 }




