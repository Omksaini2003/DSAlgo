#include <bits/stdc++.h>

using namespace std;


//2d dp concept


//1) knapsack problem

//recursion
int solveKnapsack(vector<int>& weight, vector<int>& value, int index, int capacity){
    //base case
    if(index==0){
        if(weight[index] <= capacity) return value[index];
        else return 0;
    }

    int include = 0;
    if(weight[index] <= capacity){
        include = value[index] 
        +solveKnapsack(weight,value,index-1,capacity-weight[index]);
    }

    int exclude = 0 
        +solveKnapsack(weight,value,index-1,capacity);

    return max(include,exclude);
}

int knapsack1(vector<int>& weight, vector<int>& value,int maxCapacity){
    int n=weight.size();
    return solveKnapsack(weight, value, n-1, maxCapacity);
}


//recursion + memoisation

int solveMem(vector<int>& weight, vector<int>& value, int index, int capacity, vector<vector<int>> dp){
    //base case
    if(index==0){
        if(weight[0] <= capacity) return value[0];
        else return 0;
    }

    if(dp[index][capacity] != -1) return dp[index][capacity];

    int include = 0;
    if(weight[index] <= capacity) 
        include = value[index]+solveMem(weight,value,index-1,capacity-weight[index],dp);

    int exclude = 0+solveMem(weight,value,index-1,capacity,dp);

    dp[index][capacity]=max(include,exclude);
    return dp[index][capacity];
}

int knapsack2(vector<int>& weight, vector<int>& value,int maxCapacity){
    int n=weight.size();
    vector<vector<int>> dp(n,vector<int>(maxCapacity+1,-1)); //2d vector
    return solveMem(weight, value, n-1, maxCapacity,dp);
}

//tabulation
int solveTab(vector<int>& weight, vector<int>& value,int maxCapacity){
    int n=weight.size();
    //step 1
    vector<vector<int>> dp (n,vector<int>(maxCapacity,0));

    //step 2 - base case
    for(int w=weight[0];w<=maxCapacity;w++){
        if(weight[0]<=maxCapacity) return dp[0][w]=value[0];
        else dp[0][w]=0;
    }

    //step 3
    for(int index=1;index<n;index++){
        for(int w=0;w<=maxCapacity;w++){
            int include = 0;
            if(weight[index]<=w) 
                include = value[index]+ dp[index-1][w-weight[index]];
            
            int exclude = 0+dp[index-1][w];

            dp[index][w]=max(include,exclude);
        }
    }
    return dp[n-1][maxCapacity];
}


//space optimisation on above
int solveTab2(vector<int>& weight, vector<int>& value,int maxCapacity){
    int n=weight.size();
    //step 1
    vector<int> prev(maxCapacity+1,0);
    vector<int> curr(maxCapacity+1,0);

    //step 2 - base case
    for(int w=weight[0];w<=maxCapacity;w++){
        if(weight[0]<=maxCapacity) return prev[w]=value[0];
        else prev[w]=0;
    }

    //step 3
    for(int index=1;index<n;index++){
        for(int w=0;w<=maxCapacity;w++){
            int include = 0;
            if(weight[index]<=w) 
                include = value[index]+ prev[w-weight[index]];
            
            int exclude = 0+prev[w];

            curr[w]=max(include,exclude);
        }
        prev=curr;
    }
    return prev[maxCapacity];
}





//2) combination sum problem

//recursion
int solveComb(vector<int>& num, int tar){
    //base case
    if(tar<0) return 0;
    if(tar==0) return 1;

    int ans=0;
    for(int i=0;i<num.size();i++){
        ans+= solveComb(num,tar-num[i]);
    }
    return ans;
}

//recursion+ memoisation
int solveCombMem(vector<int>& num,int tar,int dp[]){
    if(tar<0) return 0;

    if(dp[tar]!=0) return dp[tar];

    int ans=0;
    for(int i=0;i<num.size();i++){
        ans+= solveCombMem(num,tar-num[i],dp);
    }
    dp[tar] = ans;
    return dp[tar];
}

int combMem(vector<int>& num,int tar){
    int dp[tar];
    for(int i=0;i<=tar;i++){
        dp[i]=0;
    }
    dp[0]=1;
    return solveCombMem(num,tar,dp);
}

//tabulation
int combTab(vector<int>& num,int tar){
    int dp[tar];
    for(int i=0;i<=tar;i++){
        dp[i]=0;
    }
    dp[0]=1;

    for(int i=1;i<=tar;i++){
        for(int j=0;j<num.size();j++){
            if(i-num[j]>=0) dp[i] += dp[i-num[j]];
        }
    }
    return dp[tar];
}





// 3) perfect squares problem

//recursion
int solveSq(int num){
    if(num==0) return 0;

    int ans=num; // sum of 1*1
    int temp;
    for(int i=1;i*i<=num;i++){
        temp= 1+  solveSq(num-i*i);
        ans=min(ans,temp);
    }
    return ans;
}


// memoisation
int solveSqMem(int num,int dp[]){
    if(dp[num]!=-1) return dp[num];
    
    int ans=num; // sum of 1*1
    int temp;
    for(int i=1;i*i<=num;i++){
        temp= 1+  solveSqMem(num-i*i,dp);
        ans=min(ans,temp);
    }
    dp[num]=ans;
    return dp[num];
}

int sqMem(int num){
    int dp[num];
    for(int i=0;i<=num;i++){
        dp[i]=-1;
    }
    dp[0]=0;

    return solveSqMem(num,dp);
}


//tabulation
int solveSqTab(int num){
    int dp[num];
    for(int i=0;i<=num;i++){
        dp[i]=num;
    }
    dp[0]=0;

    for(int i=1;i<=num;i++){
        for(int j=1;j*j<=i;j++){
            dp[i] = min(dp[i], 1+ dp[i-j*j]); 
        }
    }
    return dp[num];
}



int main(){

    vector<int> cost;
    cost.push_back(2);
    cost.push_back(7);
    cost.push_back(15);

    vector<int> days;
    
    days.push_back(1);
    days.push_back(4);
    days.push_back(6);
    days.push_back(7);
    days.push_back(8);
    days.push_back(20);

    cout<<minCoinsTab2(days,cost)<<endl;

    return 0;
}









