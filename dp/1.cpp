#include<bits/stdc++.h>

using namespace std;


// 1) minimum cost of climbing stairs  -
// https://leetcode.com/problems/min-cost-climbing-stairs/solutions/3496292/memoization-tabulation-space-optimization-1-space-optimization-2-3-lines-code/

// Memoization - top-down

int helper(vector<int>& cost, int curr, vector<int>& dp,int n){

    if(curr>=n) return 0;

    if(dp[curr]!=-1) return dp[curr];

    int output1= cost[curr] + helper(cost,curr+1,dp,n);
    int output2= cost[curr] + helper(cost,curr+2,dp,n);

    return min(output1,output2);
}

int minCostClimbingStairs1(vector<int>& cost){
    int n= cost.size();

    if(n==1) return cost[0];

    vector<int> dp(n,-1);
    
    int output1= helper(cost,0,dp,n);
    int output2= helper(cost,1,dp,n);

    return min(output1,output2);
}


// Tabulation - bottom-up

int minCostClimbingStairs2(vector<int>& cost){
    int n= cost.size();

    if(n==1) return cost[0];

    vector<int> dp(n);

    for(int i=0;i<n;i++)
    {
        if(i<2) dp[i]=cost[i];

        else dp[i] = cost[i] + min(dp[i-1],dp[i-2]);
    }
    return min(dp[n-1],dp[n-2]); //? why didnt we take only dp[n-1] as it was the last stair 
}



// space optimisation on bottom-up 

int minCostClimbingStairs3(vector<int>& cost){
    int n= cost.size();

    if(n==1) return cost[0];

    int first= cost[0];
    int second = cost[1];
    int curr;
    for(int i=2;i<n;i++){
        curr= cost[i]+min(first,second);
        first=second;
        second=curr;
    }
    return min(first,second); //second has become curr before loop ended
    //? why did we take first, just like above, we should take only second(=curr)
}


// space optimisation // this will edit cost vector

int minCostClimbingStairs4(vector<int>& cost){
    int n= cost.size();

    if(n==1) return cost[0];

    for(int i=2;i<n;i++){
        cost[i]+= min(cost[i-1],cost[i-2]);
    }
    return min(cost[n-1],cost[n-2]);
}


///////////////////////////

// 2) minimum no of coins that make a change
// https://www.geeksforgeeks.org/find-minimum-number-of-coins-that-make-a-change/

// Recursion 

int minCoins1(int coins[], int m, int V) //m is size of coins, V is total sum of
{
    //base case
    if(V==0) return 0;

    //intialise result
    int res = INT_MAX;

    for(int j=0;j<m;j++)
    {
        if(coins[j]<=V){
            int sub_res = minCoins1(coins,m,V-coins[j]);

            if(sub_res != INT_MAX && res > sub_res+1) res = sub_res+1;
        }
    }
    return res;
}

// Memoisation - top-down

int minCoins2Util(int coins[], int m,int V, int dp[]){
    if(V==0) return 0; // base case

    if(dp[V]!=-1) return dp[V]; // if subproblem is already solved then return res from dp table

    int res = INT_MAX;

    // iterate over all coins and recursively solve for subproblems
    for(int i=0;i<m;i++){
        if(coins[i]<=V){
            int sub_res = minCoins2Util(coins,m,V-coins[i],dp);

            if(sub_res!=INT_MAX && res> sub_res+1) res = sub_res+1;
        }
    }
    dp[V] = res;

    return res;
}


int minCoins2(int coins[],int m,int V){
    int dp[V+1] = {-1};

    return minCoins2Util(coins,m,V,dp);
}



// Tabulation - bottom-up

int minCoins3(int coins[], int m, int V){
    int res[V+1] = {INT_MAX}; // intialise 

    res[0]=0; //base case

    for(int i=1;i<=V;i++)
    {
        for(int j=0;j<m;j++)
        {
            if(coins[j]<=i){
                int sub_res = res[i-coins[j]];

                if(sub_res!=INT_MAX && res[i] > sub_res+1) res[i] = sub_res+1;
            }
        }
    }
    
    if(res[V]==INT_MAX) return -1;

    return res[V];
}



//////////////

//3) Maximum sum such that no two elements are adjacent
// https://www.geeksforgeeks.org/maximum-sum-such-that-no-two-elements-are-adjacent/


// recursion

int maxSum(int nums[],int i, int size){
    if(i>=size) return 0;

    //return (nums[i] + maxSum(nums, i+2,size) > maxSum(nums, i+1, size)) 
    //? nums[i] + maxSum(nums, i+2,size) : maxSum(nums, i+1,size);

    return max(nums[i] + maxSum(nums, i+2,size),maxSum(nums, i+1, size));
}


int findMaxSum1(int nums[],int N){return maxSum(nums,0,N);}



// memoisation

int rec(int nums[],int id,int dp[],int size){
    if(id>=size) return 0;
    if(dp[id]!=-1) return dp[id];

    dp[id] = max(nums[id] + rec(nums,id+2,dp,size),rec(nums,id+1,dp,size));
    return dp[id];
}


int findMaxSum2(int nums[],int N){
    int dp[N+1]={-1};

    int result = rec(nums,0,dp,N);
    free(dp);
    return result;
}


// Tabulation

int findMaxSum3(int nums[],int N){
    if(N==1) return nums[0];

    int dp[N][2]; // dp[i][0] stores maximum subsequence sum till ith index with arr[i] excluded 
                  // and dp[i][1] stores the sum when arr[i] is included.

    dp[0][0] = 0;
    dp[0][1] = nums[0];

    for(int i=1;i<N;i++){
        dp[i][0] = max(dp[i-1][1], dp[i-1][0]); // max sum till (i-1) excluding self(i)
        dp[i][1] = dp[i-1][0] + nums[i]; // max sum till (i-1) excluding (i-1)  + self(including i)
    }

    return max(dp[N-1][0],dp[N-1][1]);// max sum till (N-1) considering both possibilities
}


// space optimisation on above

int findMaxSum4(int nums[], int N){
    int excl = 0;
    int incl = nums[0];
    int temp;
    for(int i=1;i<N;i++){
        temp = max(excl,incl);
        incl = excl + nums[i];
        excl = temp;
    }
    return max(incl,excl);
}



////////////

//4) Maximize the number of segments of length x, y and z
// https://www.geeksforgeeks.org/maximize-the-number-of-segments-of-length-p-q-and-r/

// ye mincoins wale jesa hi qn h, bas isme sign change krna h

int maxseg1(int lengths[], int m, int L) //m is size of coins, V is total sum of
{
    //base case
    if(L==0) return 0;

    //intialise result
    int res = INT_MIN; // yha change kia h max ko min

    for(int j=0;j<m;j++)
    {
        if(lengths[j]<=L){
            int sub_res = maxseg1(lengths,m,L-lengths[j]);

            if(sub_res != INT_MIN && res < sub_res+1) res = sub_res+1; // yha change kia h > to <,  max ko min
        }
    }
    return res;
}

// approach in article

int maxSeg1(int n, int x, int y, int z){
    if(n==0) return 0;
    if(n<0) return INT_MIN;

    int a= maxSeg1(n-x,x,y,z)+1;
    int b= maxSeg1(n-y,x,y,z)+1;
    int c= maxSeg1(n-z,x,y,z)+1;
    
    return max(a,max(b,c));
}


//memoisation

int maxSeg2rec(int l, int x, int y, int z,int dp[]){
    if(l<0) return INT_MIN;

    if(dp[l]!=-1) return dp[l];

    int a= maxSeg2rec(l-x,x,y,z,dp)+1;
    int b= maxSeg2rec(l-y,x,y,z,dp)+1;
    int c= maxSeg2rec(l-z,x,y,z,dp)+1;
    
    return max(a,max(b,c));
}
int maxSeg2(int l,int x,int y,int z){
    if(!(x<=l && y<=l && z<=l)) return INT_MIN;

    int dp[l+1]={-1};
    dp[0]=0;
    return maxSeg2rec(l,x,y,z,dp);
}


// tabulation

int maxSeg3(int l, int x, int y, int z){
    int dp[l+1] ={-1};
    dp[0]=0;

    for(int i=0; i<l;i++){
        if(dp[i]==-1) continue;
        if(i+x<=l) dp[i+x]= max(dp[i+x],dp[i]+1);
        if(i+y<=l) dp[i+y]= max(dp[i+y],dp[i]+1);
        if(i+z<=l) dp[i+z]= max(dp[i+z],dp[i]+1);
    }
    if(dp[l]==-1) return 0;
    return dp[l];
}



/////////////
// 5) Count derangements
// https://youtu.be/NW-BLDQHFXk
// f(n) = (n-1)*(f(n-2)+f(n-1))

#define MOD 100000007

//recursion
long long int countderangement1(int n){
    if(n==1) return 0;
    if(n==2) return 1;

    return (((n-1)%MOD)*(countderangement1(n-2)%MOD+countderangement1(n-1)%MOD))%MOD;
}

//memoisation
long long int countderRec(int n, long long int dp[]){
    if(n==1) return 0;
    if(n==2) return 1;

    if(dp[n]!=-1) return dp[n];

    return (((n-1)%MOD)*(countderangement1(n-2)%MOD+countderangement1(n-1)%MOD))%MOD;
}

long long int countderangement2(int n){
    long long int dp[n]={-1};
    return countderRec( n, dp);
}

// space optimisation on tabulation
long long int countderangement3(int n){
    long long int count  =2; // for 3 
    long long int count_1=1; // for 2
    long long int count_2=0; // for 1
    long long int temp;

    for(int i=3;i<=n;i++){
        temp=count;
        count=(((i-1)%MOD)*(count_2%MOD + count_1%MOD))%MOD;

        count_2=count_1;
        count_1=temp;
    }
    return count;
}



int main(){
    return 0;
}

