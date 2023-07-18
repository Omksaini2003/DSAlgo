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
};



//using kahn's algo 
vector<int> topologicalSort(Graph g){

    //find all indegrees
    unordered_map<int,int> indegree;
    for(auto i: g.adj){
        indegree[i.first]=0;
    }
    // cout<<"indegree -"<<endl;
    // for(int i=1;i<=30;i++){
    //     cout<<i<<" "<<indegree[i]<<endl;
    // }

    //cout<<"-----------"<<endl;
    for(auto i: g.adj){
        //cout<<i.first<<" -> ";
        for(auto j:i.second){
            //if(j.first==1) cout<<i.first<<endl;
            //cout<<j.first<<" ";
            indegree[j.first]++;
        }
        //cout<<endl;
    }

    // cout<<"indegree -"<<endl;
    // for(int i=1;i<=30;i++){
    //     cout<<i<<" "<<indegree[i]<<endl;
    // }

    // 0 indegree walo ko push krdo
    queue<int> q;

    for(auto i: g.adj){
        if(!indegree[i.first]) q.push(i.first);
    }

    //cout<<"q size = "<<q.size()<<endl;
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

    // cout<<"topo - "<<ans.size()<<endl;
    // for(auto i: ans){
    //     cout<<i<<endl;
    // }

    return ans;
}


//finding shortest path in acyclic directed weighted graph between two points
pair<int,vector<int>> shortestPath(Graph g, int start, int end)//shortest dist, path
{
    vector<int> topo = topologicalSort(g); //this makes sure we are following correct sequence

    //cout<<"topological sort done! "<<topo.size()<<endl;


    unordered_map<int,pair<int,int>> distp; //this would store min dist of every node from start and parent to every node which would lead to start
    for(auto i:topo)
    {
        //cout<<i<<endl;
        distp[i].first=INT_MAX;
    }


    distp[start].first=0; //initialising dist of start from start =0

    //cout<<"distp initialised"<<endl;

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

    //cout<<"half done "<<distp[end].first<<endl;

    // for(int i=1;i<=30;i++){
    //     cout<<i<<" "<<distp[i].first<<" "<<distp[i].second<<endl;
    // }

    //finding shortest path using on distp we created
    vector<int> path;
    int currentNode=end;
    path.push_back(currentNode);
    
    while(currentNode!=start){
        currentNode=distp[currentNode].second;
        path.push_back(currentNode);
        //cout<<"its me, hy, im the problem its me"<<endl;
    }
    
    reverse(path.begin(),path.end());
    //cout<<"returning"<<endl;
    
    return make_pair(distp[end].first,path);
}






int solve(int arr[],int n){
    Graph g;

    for(int i=1;i<30;i++){
        g.addEdge(i,i+1,1,1);
    }

    for(int i=0;i<2*n-1;i+=2){
        if(arr[i]<arr[i+1]) g.addEdge(arr[i],arr[i+1],1,1);
    }

    //cout<<"g prepare kar lia vro"<<endl;
    //g.printAdj();

    pair<int,vector<int>> out = shortestPath(g,1,30);
    //cout<<"shortesPath bhi nikal lia"<<endl;

    int dice=0;
    int prev=1;
    int count=1;
    for(auto curr: out.second){
        if(curr==1) continue;
        if(curr-prev==1) {
            count++;
        }
        else{
            dice+= count/6 + (count%6!=0);
            count=0;
        }
        prev=curr;
    }
    if(count){
        dice+= count/6 + (count%6!=0);
        count=0;
    }

    return dice;
}

int main(){
    //cout<<"yo im in"<<endl;
    int n=8;
    int arr[2*n] = {3,22,5,8,11,26,20,29,17,4,19,7,27,1,21,9};

    int dice = solve(arr,n);

    cout<<dice<<endl;


    return 0;
}
