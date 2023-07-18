//shortest path

#include <bits/stdc++.h>
#include "1.h"
using namespace std;


// shortest path in undirected unweighted graph
//eg = 8 9 1 2 1 3 1 4 2 5 3 8 4 6 5 8 6 7 7 8
vector<int> shortestPath(graph<int> g, int start, int end){


    //do bfs
    unordered_map<int,bool> visited;
    unordered_map<int,int> parent;
    queue<int> q;

    q.push(start);
    parent[start]=-1;
    visited[start]= true;

    while(!q.empty()){
        int front = q.front();
        q.pop();

        for(auto i: g.adj[front]){
            if(!visited[i]){
                visited[i]=true;
                parent[i] = front;
                q.push(i);
            }
        }
    }

    //prepare shortest path
    vector<int> ans;
    int currentNode=end;
    ans.push_back(currentNode);

    while(currentNode!=start){
        currentNode=parent[currentNode];
        ans.push_back(currentNode);
    }

    reverse(ans.begin(),ans.end());

    return ans;

}



///////////////////

int main(){

    int n;
    cout<<"enter the number of nodes ";
    cin>>n;

    int m;
    cout<<"enter the number of edges ";
    cin>>m;

    graph<int> g;

    // 0 1  1 3  1 2  2 3  3 4  4 0
    for(int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        //creating an undirected graph
        g.addEdge(u,v,1);
    }

    //g.printAdjList();

    //g.printNodes();
    //g.printAdjList();

    //DFS(g,0);
     
   // map<int, list<int>>::iterator itr;
  //  for (itr = g.adj.begin(); 
  //     itr != g.adj.end(); itr++) 
  //{
  //  cout << itr->first << " -> ";
  //  for(auto i: itr->second){
  //      cout<<i<<", ";
  //  }
  //  cout<<endl;
  //}

  //cout<<cycleDetectionDFS(g,0);
    
    vector<int> ans= shortestPath(g, 1,8);
    //cout<<ans.size();
    cout<<endl;
    for(auto i:ans){
        cout<<i<<"  ";
    }

    return 0;
}
