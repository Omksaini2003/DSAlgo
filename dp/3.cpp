#include <bits/stdc++.h>

using namespace std;



// 4) minimum cost for tickets
//2 5.... 1 4 25

// recursion
int minCoinsRec(int n,vector<int> days,vector<int> cost,int index){ //n is day //start from 0
    if(n>days[index]){

        while(n>days[index] && index<days.size()){
            index++;
        }
        if(index<days.size()) return minCoinsRec(n,days,cost,index);
        else return 0;
    }
    else if(n==days[index]){
        
        int a=cost[0]+ minCoinsRec(n+1,days,cost,index+1);
        int b=cost[1]+ minCoinsRec(n+7,days,cost,index+1);
        int c=cost[2]+ minCoinsRec(n+30,days,cost,index+1);

        return min(a,min(b,c));
    }
    else if(n<days[index]){

        n=days[index];
        return minCoinsRec(n,days,cost,index);
    }
}

int minCoinsRec2(int n,vector<int> days,vector<int> cost,int index){//n is total no of days of travel
    if(index>=n) return 0;

    int opt1 = cost[0] + minCoinsRec2(n,days,cost,index+1);

    int i;
    for(i=index; i<n && days[i]<days[index]+7; i++);

    int opt2 = cost[1] + minCoinsRec2(n,days,cost,i);

    for(i=index; i<n && days[i]<days[index]+30;i++);

    int opt3 = cost[2] + minCoinsRec2(n,days,cost,i);

    return min(opt1,min(opt2,opt3));
}


int solveMin(vector<int> days, vector<int> cost){
    return minCoinsRec2(days.size(),days,cost,0);    
    //return minCoinsRec(1,days,cost,0);
}


// memoisation - top down
int minCoinsMem(int n,vector<int> days,vector<int> cost,int index,vector<int>& dp){
    if(index>=n) return 0;
    
    if(dp[index]!=-1) return dp[index];

    int opt1 = cost[0] + minCoinsMem(n,days,cost,index+1,dp);

    int i;
    for(i=index; i<n && days[i]<days[index]+7; i++);

    int opt2 = cost[1] + minCoinsMem(n,days,cost,i,dp);

    for(i=index; i<n && days[i]<days[index]+30; i++);

    int opt3 = cost[2] + minCoinsMem(n,days,cost,i,dp);

    dp[index] = min(opt1,min(opt2,opt3));
    return dp[index];

}

int solveMinMem(vector<int> days, vector<int> cost){
    int n=days.size();
    vector<int> dp(n+1,-1);
    return minCoinsMem(n,days,cost,0,dp);
}


//tabulation --bottom up
int minCoinsTab(vector<int> days,vector<int> cost){
    int n=days.size();
    vector<int> dp(n+1,INT_MAX);
    dp[n]=0; // base case

    for(int index=n-1;index>=0;index--)
    {
        int opt1 = cost[0] + dp[index+1];

        int i;
        for(i=index;i<n && days[i]<days[index]+7;i++);
        int opt2 = cost[1] + dp[i];

        for(i=index;i<n && days[i]<days[index]+30;i++);
        int opt3 = cost[2] + dp[i];

        dp[index] = min(opt1,min(opt2,opt3));
    }
    return dp[0];
}

//***** tabulation + space optimisation , space complexity=O(1) 
int minCoinsTab2(vector<int> days,vector<int> cost){
    int ans=0;

    queue<pair<int,int>> month,week;

    for(int day:days)
    {
        //1) remove expired days
        while(!month.empty() && month.front().first + 30<=day){
            month.pop();
        }
        while(!week.empty() && week.front().first + 7<=day){
            week.pop();
        }

        //2) add cost of current day
        week.push(make_pair(day,ans+cost[1]));
        month.push(make_pair(day,ans+cost[2]));

        //3) ans update
        ans= min(ans+cost[0],min(week.front().second, month.front().second));
    }
    return ans;
}





// 5) Largest Square area in Matrix 

//recursion
int solveMaxSqRec(vector<vector<int>> mat, int i, int j, int &maxi){
    if(i>=mat.size() || j>=mat[0].size()) return 0;

    int right = solveMaxSqRec(mat,i,j+1,maxi);
    int diagonal = solveMaxSqRec(mat,i+1,j+1,maxi);
    int down = solveMaxSqRec(mat,i+1,j,maxi);

    if(mat[i][j]==1){
        int ans = 1+ min(right, min(diagonal, down));
        maxi= max(maxi,ans);
        return ans;
    }
    else return 0;
}

int maxSqRec(int n, int m, vector<vector<int>> mat){
    int maxi=0;
    solveMaxSqRec(mat,0,0,maxi);
    return maxi;
}


// memoisation // top down 
int solveMaxSqRec(vector<vector<int>> &mat, int i, int j, int &maxi, vector<vector<int>> &dp){
    if(i>=mat.size() || j>=mat[0].size()) return 0;

    if(dp[i][j]!=-1) return dp[i][j];

    int right = solveMaxSqRec(mat,i,j+1,maxi,dp);
    int diagonal = solveMaxSqRec(mat,i+1,j+1,maxi,dp);
    int down = solveMaxSqRec(mat,i+1,j,maxi,dp);

    if(mat[i][j]==1){
        dp[i][j] = 1+ min(right, min(diagonal, down));
        maxi= max(maxi,dp[i][j]);
        return dp[i][j];
    }
    else return dp[i][j]=0;
}

int maxSqMem(int n, int m, vector<vector<int>> mat){
    int maxi=0;
    vector<vector<int>> dp(n,vector<int>(m,-1));
    solveMaxSqRec(mat,0,0,maxi,dp);
    return maxi;
}


//tabulation // bottom up
int maxSqTab(vector<vector<int>> &mat){
    int row = mat.size();
    int column = mat[0].size();

    vector<vector<int>> dp(row+1,vector<int> (column+1,0));

    int right, diagonal, down;
    int maxi= INT_MIN;

    for(int i=row-1; i>=0; i--){
        for(int j=column-1; j>=0; j--){
            right = dp[i][j+1];
            diagonal = dp[i+1][j+1];
            down = dp[i+1][j];

            if(mat[i][j]==1){
                dp[i][j] = 1+ min(right, min(diagonal, down));
                maxi = max(maxi, dp[i][j]);
            }
            else{
                dp[i][j]=0;
            }
        }
    }
    return maxi;
}

//space optimisation on above
int maxSqTab2(vector<vector<int>> &mat){
    int row = mat.size();
    int column = mat[0].size();

    //vector<vector<int>> dp(row+1,vector<int> (col+1,0));
    vector<int> curr (column+1,0); // dp[i]
    vector<int> next (column+1,0); // dp[i+1]

    int right, diagonal, down;
    int maxi = INT_MIN;

    for(int i=row-1; i>=0; i--){
        for(int j=column-1; j>=0; j--){

            if(mat[i][j]){
                curr[j] = 1+ min(curr[j+1], min(next[j+1], next[j]));
                maxi = max(maxi, curr[j]);
            }
            // below code is simpler version of above if(...
            //right = curr[j+1];
            //diagonal = next[j+1];
            //down = next[j];

            //if(mat[i][j]==1){
            //    curr[j] = 1+ min(right, min(diagonal, down));
            //    maxi = max(maxi, curr[j]);
            //}
            //else{
            //    curr[j]=0;
            //}
        }
        next = curr;
    }
    return maxi;
}





// 6) min score triangulation

//recursion
int solveTriangRec(vector<int>& v,int i, int j){
    if(i+1==j) return 0;

    int ans=INT_MAX;
    for(int k=i+1;k<j;k++){
        ans = min(ans, v[i]*v[j]*v[k] + solveTriangRec(v,i,k) + solveTriangRec(v,k,j));
    }
    return ans;
}

int traingRec(vector<int> v){
    return solveTriangRec(v,0,v.size()-1);
}


//memoisation
int solveTriangMem(vector<int>& v, int i, int j, vector<vector<int>>& dp){
    if(i+1==j) return 0;

    if(dp[i][j]!=-1) return dp[i][j];

    int ans = INT_MAX;
    for(int k=i+1;k<j;k++){
        ans = min(ans, v[i]*v[j]*v[k] + solveTriangMem(v,i,k,dp) + solveTriangMem(v,k,j,dp));
    }
    dp[i][j]=ans;
    return dp[i][j];
}

int triangMem(vector<int> v){
    int n=v.size();
    vector<vector<int>> dp(n,vector<int> (n,-1));
    return solveTriangMem(v,0,n-1,dp);
}


//tabulation

int solveTriangTab(vector<int>& v){
    int n=v.size();
    vector<vector<int>> dp(n,vector<int> (n,-1));

    for(int i=n-1;i>=0;i--){
        for(int j=i+2;j<n;j++){
            int ans = INT_MAX;
            for(int k=i+1;k<j;k++){
                ans = min(ans, v[i]*v[j]*v[k] + dp[i][k] + dp[k][j]);
            }
            dp[i][j] = ans;
        }
    }
    return dp[0][n-1];
}


