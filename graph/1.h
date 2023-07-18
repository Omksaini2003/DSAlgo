// class, BFS, DFS, cyclic detection, topological sort

#include <bits/stdc++.h>
using namespace std;

template<typename T>

class graph {
    public:
    map<T, list<T>> adj;

    void addEdge(T u, T v, bool direction){
        //direction= 0 => undirected graph
        //direction= 1 => directed graph

        //create an edge from u to v
        adj[u].push_back(v);
        if(direction==0){
            adj[v].push_back(u);
        }
    }

    void printNodes(){
        for(auto i: adj){
            cout<<i.first<<" ";
        }
        cout<<endl;
    }

    void printAdjList(){
        for(auto i: adj){
            cout<<i.first<<" -> ";
            for(auto j: i.second){
                cout<<j<<", ";
            }
            cout<<endl;
        }
    }

    int V(){
        return adj.size();
    }

    int E(bool direction){
        int e=0;
        for(int i=0;i<adj.size();i++){
            e+=adj[i].size();
        }
        if(direction){
            return e;
        }
        return e/2;
    }
};

//we can also make adjList in here for better speed ig
//s for source
void BFS(graph<int> g, int s)
{
    queue<int> q; //bfs wise elements daalenge isme
    q.push(s);

    unordered_map<int,bool> visited; //mark kr denge taki bar bar element print na ho 
    for(auto i: g.adj){
        visited[i.first]=false;
    }

    while(!q.empty())
    {
        int front = q.front();
        q.pop();

        if(!visited[front])
        {
            cout<<front<<" ";
            visited[front]=true;

            for(auto i:g.adj[front]){
                if(!visited[i]){
                    q.push(i);
                }
            }
        }
    }
}



void dfs(graph<int> g,unordered_map<int,bool> &visited, int s){
    for(auto i: g.adj[s]){
        if(!visited[i]){
            cout<<i<<" ";
            visited[i]=true;
            dfs(g,visited,i);
        }
    }
}

void DFS(graph<int> g, int s)
{
    unordered_map<int,bool> visited; //mark kr denge taki bar bar element print na ho 
    for(auto i: g.adj){
        visited[i.first]=false;
    }

    cout<<s<<" ";
    visited[s]=true;
    dfs(g,visited,s);
}



bool cycleDetectionBFS(graph<int> g, int s)
{
    queue<int> q; //bfs wise elements daalenge isme
    q.push(s);

    unordered_map<int,int> parent;
    parent[s]=-1;

    unordered_map<int,bool> visited; //mark kr denge taki bar bar element print na ho 
    for(auto i: g.adj){
        visited[i.first]=false;
    }

    while(!q.empty()){
        int front = q.front();
        q.pop();

        for(auto neighbour: g.adj[front]){
            if(visited[neighbour]==true && neighbour!=parent[front]){
                return true;
            }
            else if(!visited[neighbour]){
                q.push(neighbour);
                visited[neighbour]= true;
                parent[neighbour]=front;
            }
        }
    }
    return false;
}



bool isCyclicDFS(int node, int parent, unordered_map<int,bool> &visited, graph<int> g)
{
    visited[node]=true;

    for(auto neighbour: g.adj[node]){
        if(!visited[neighbour]){
            bool cycleDet = isCyclicDFS(neighbour, node, visited,g);
            if(cycleDet) return true;
        }
        else if(neighbour!= parent && visited[neighbour]){
            return true;
        }
    }
    return false;
}

bool cycleDetectionDFS(graph<int> g, int s){

    unordered_map<int,int> parent;
    parent[s]=-1;

    unordered_map<int,bool> visited; //mark kr denge taki bar bar element print na ho 
    for(auto i: g.adj){
        visited[i.first]=false;
    }

    return isCyclicDFS(s,-1, visited, g);
    
}



// topoogical sort is possible for acyclic unidirectional graphs only
//topological sort using dfs
void topoSort(int node, unordered_map<int,bool> &visited, stack<int> &s, graph<int> g){
    visited[node]=1;

    for(auto neighbour: g.adj[node]){
        if(!visited[neighbour]){
            topoSort(neighbour,visited,s,g);
        }
    }

    s.push(node);
}

vector<int> topologicalSort(graph<int> g,int e){
    unordered_map<int,bool> visited;
    for(auto i: g.adj){
        visited[i.first]=false;
    }
    stack<int> s;
    
    for(auto i: g.adj){
        if(!visited[i.first]){
            topoSort(i.first,visited,s,g);
        }
    }

    vector<int> ans;
    while(!s.empty()){
        ans.push_back(s.top());
        s.pop();
    }

    return ans;
}



//topological sort using bfs-  (kahn's algorithm)

vector<int> kahnAlgo(graph<int> g, int e,int v){

    //find all indegrees
    vector<int> indegree(v);
    for(auto i: g.adj){
        for(auto j:i.second){
            indegree[j]++;
        }
    }

    // 0 indegree walo ko push krdo
    queue<int> q;
    for(int i=0;i<v;i++){
        if(!indegree[i]){
            q.push(i);
        }
    }

    //do bfs
    vector<int> ans;
    while(!q.empty()){
        int front = q.front();
        q.pop();

        //ans store
        ans.push_back(front);

        //neighbour indegree update
        for(auto neighbour: g.adj[front]){
            indegree[neighbour]--;
            if(indegree[neighbour]==0){
                q.push(neighbour);
            }
        }
    }

    return ans;

}

// we can use above to detect cyclic graphs too, since indegree wouldnt be 0 for any node



/////////////////

