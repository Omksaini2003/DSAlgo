// shortest path
#include <bits/stdc++.h>
using namespace std;

//weighted graph
class Graph {
    public:
    unordered_map<int, list<pair<int,int>>> adj;//node1, node2, weight

    void addEdge(int u, int v, int weight, int direction){
        // direction = 0 means undirected, else directed
        // u to v
        adj[u].push_back(make_pair(v,weight));

        if(!direction){
            // v to u
            adj[v].push_back(make_pair(u,weight));
        }
    }

    void printAdj(){
        for(auto i: adj){
            cout<<i.first<<" -> ";
            for(auto j: i.second){
                cout<<"("<<j.first<<","<<j.second<<"), ";
            }
            cout<<endl;
        }
    }

    int totalWeight(int direction){
        int weight=0;
        for(auto i: adj){
            for(auto j: i.second){
                weight+=j.second;
            }
        }
        if(direction){
            return weight;
        }
        return weight/2;
    }

    int V(){
        return adj.size();
    }

    int E(int dir){
        int s=0;
        //int dir=0;
        int vertices=adj.size();
        for(int i=0;i<vertices;i++){
            s+=adj[i].size();
        }
        if(dir){
            return s;
        }
        return s/2;
    }
};



//using kahn's algo 
vector<int> topologicalSort(Graph g){

    //find all indegrees
    unordered_map<int,int> indegree;
    for(auto i: g.adj){
        indegree[i.first]=0;
    }

    for(auto i: g.adj){
        for(auto j:i.second){
            indegree[j.first]++;
        }
    }

    // 0 indegree walo ko push krdo
    queue<int> q;

    for(auto i: g.adj){
        if(!indegree[i.first]) q.push(i.first);
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
            indegree[neighbour.first]--;
            if(indegree[neighbour.first]==0) q.push(neighbour.first);   
        }
    }

    return ans;
}


//finding shortest path in acyclic directed weighted graph between two points
pair<int,vector<int>> shortestPath(Graph g, int start, int end)//shortest dist, path
{
    vector<int> topo = topologicalSort(g); //this makes sure we are following correct sequence

    unordered_map<int,pair<int,int>> distp; //this would store min dist of every node from start and parent to every node which would lead to start
    for(auto i:topo)
    {
        distp[i].first=INT_MAX;
    }

    distp[start].first=0; //initialising dist of start from start =0


    int go=0; //ensures we start only when we reach start
    for(auto i:topo)
    {
        if(!go && i!=start)  
        {
            distp[i].first=INT_MAX;
            distp[i].second=-1;
        }
        else
        {
            for(auto j:g.adj[i])
            {
                //if(j.first!=start)
                if(distp[j.first].first > j.second + distp[i].first)
                {
                    distp[j.first].first= j.second + distp[i].first;
                    distp[j.first].second= i;
                }
            }
            go=1;
        }

        if(i==end){
            if(!go){
                cout<<"impossible to go from "<<start<<" to "<<end<<endl;
                vector<int> ret;
                ret.push_back(start);
                ret.push_back(end);

                return make_pair(INT_MAX,ret);
            }
            break;
        }
    }


    //finding shortest path using on distp we created
    vector<int> path;
    int currentNode=end;
    path.push_back(currentNode);
    
    while(currentNode!=start){
        currentNode=distp[currentNode].second;
        path.push_back(currentNode);
    }
    
    reverse(path.begin(),path.end());
    
    return make_pair(distp[end].first,path);
}




//1.h wale bfs ko copy krke thoda bht change kia 
vector<int> BFS(Graph g, int s)
{
    vector<int> ans;
    queue<int> q; //bfs wise elements daalenge isme
    q.push(s);

    unordered_map<int,bool> visited; //mark kr denge taki bar bar element print na ho 
    for(auto i: g.adj){
        visited[i.first]=false;
    }

    while(!q.empty()){
        int front = q.front();
        q.pop();

        if(!visited[front])
        {
            ans.push_back(front);
            visited[front]=true;

            for(auto i:g.adj[front]){
                if(!visited[i.first]) q.push(i.first);
            }
        }
    }
    return ans;
}

//dijkstra algo
//finding shortest path in undirected weighted graph between two points
//same as above, used bfs instead of topo, did some minor changes
//**cant use negative weight as it will reduce path by using negative weight multiple times**
pair<int,vector<int>> shortestpath(Graph g, int start, int end){
    vector<int> bfs =  BFS(g,start);

    unordered_map<int,pair<int,int>> distp; //this would store min dist of every node from start and parent to every node which would lead to start
    for(auto i:bfs)
    {
        distp[i].first=INT_MAX;
    }
    distp[start].first=0; //initialising dist of start from start =0

    for(auto i:bfs)
    {
        for(auto j:g.adj[i])
        {
            //if prev distance is greater than curr, then update distance and parent
            if(distp[j.first].first > j.second + distp[i].first) distp[j.first] = make_pair(j.second + distp[i].first, i);
        }
    }

    //finding shortest path using on distp we created
    vector<int> path;
    int currentNode=end;
    path.push_back(currentNode);
    
    while(currentNode!=start){
        currentNode=distp[currentNode].second;
        path.push_back(currentNode);
    }
    
    reverse(path.begin(),path.end());
    
    return make_pair(distp[end].first,path);
}



//bellman ford algorithm -- works even for negative weights (but without negative cycle)
// logic - 
// 1) check for every edge - dist[u]+ weight < dist[v], and update dist
// 2) do this vertices-1 times
// 3) do this one more time separately, and if this time if any dist[] gets updates
// that means graph have negative cycle and return null
// else return dist[destiny]

//8  1 2 -1  1 3 4  2 3 3  2 4 2  2 5 2  4 3 5  4 2 1  5 4 -3 

void BellmanFord(Graph g,int V, int start, int end){
    int dist[V]={INT_MAX};
    dist[start]=0;

    //1) and 2)
    for(int i=1;i<=V-1;i++){
        for(auto u : g.adj){
            for(auto v : g.adj[u.first]){
                if(dist[u.first]!=INT_MAX &&
                dist[u.first]+v.second < dist[v.first]){
                    dist[v.first] = dist[u.first] + v.second;
                }
            }
        }
    }

    //3)
    for(auto u : g.adj){
        for(auto v : g.adj[u.first]){
            if(dist[u.first]!=INT_MAX &&
            dist[u.first]+v.second < dist[v.first]){
                cout<<"Graph contains negative weight cycles"<<endl;
                return;
            }
        }
    }

    cout<<dist[end]<<endl;
}




/////////////////////////////////

// int main(){

//     int e;
//     cout<<" no of edges ";
//     cin>>e;


// // 9   0 1 5  0 2 3  1 2 2  1 3 6  2 3 7  2 4 4  2 5 2  3 4 -1  4 5 -2
// // 9   0 1 5  0 2 3  1 2 2  1 3 6  2 3 7  2 4 4  2 6 2  3 4 -1  4 6 -2
    
//     Graph g;
//     for(int i=0;i<e;i++){
//         int u,v,weight;
//         cin>>u>>v>>weight;
//         g.addEdge(u,v,weight,1);
//     }

//     g.printAdj();

    
//     vector<int> ans = BFS(g,1);
//     for(auto i:ans){
//         //cout<<i<<" ";
//     }
//     cout<<endl;

//     pair<int,vector<int>> shortest = shortestPath(g,1,6);

//     cout<<shortest.first<<endl;

//     for(auto i: shortest.second){
//         cout<<i<<" ";
//     }

//     return 0;
// }

