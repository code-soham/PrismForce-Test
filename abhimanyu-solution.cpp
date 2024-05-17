		/*
    Author : code_soham : SOHAM CHOWDHURY
    Jalpaiguri Government Engineering College
*/
#include<bits/stdc++.h>
#define ll long long int
#define ff(i,a,n) for(ll i=a;i<n;i++)
#define fr(i,a,b) for(ll i=a;i>=b;i--)
#define ffs(i,a,b,step) for(ll i=a;i<b;i+=step)
#define frs(i,a,b,step) for(ll i=a;i>=b;i-=step)
#define FAST                          \
    ios_base::sync_with_stdio(false); \
    cin.tie(NULL);                        \
    cout.tie(NULL);
#define MOD 1000000007
#define pb push_back
#define prio priority_queue
#define all(v) v.begin(),v.end()
#define endl "\n"
#define sayyes cout<<"YES\n";
#define sayno cout<<"NO\n";
#define fs first
#define sc second
#define vi vector<int>
#define pii pair<int,int>
#define N 100005
using namespace std;
/**
 * Considerations :
 * 1) Abhimanyu must have health > 0 at end to claim victory and return TRUE response
 * 2) He can heal and fight current enemy itself in a move
 * 3) Initialized DP array globally
 * */

int initialPower;
int dp[20][201][20][20];


bool recursivelyFightDP(int index,int power,int skip,int heal,vi k){	
	if(dp[index][power][skip][heal] != -1)return dp[index][power][skip][heal];

	// cout<<index<<" "<<power<<" "<<skip<<" "<<heal<<" ";
	// if(index == k.size())
	// cout<<"end\n";
	// else
	// 	cout<<k[index]<<endl;
	// case : reached end with power>=0
	
	if(index == k.size()){
		if(power>=0)return true;
		
			return false;
	}

		//store all probabilities
		bool possible = false;
		//case : normal progression
		if(power >= k[index]){
			possible|=recursivelyFightDP(index+1,power-k[index],skip,heal,k);
		}

		//regen if 3rd or 7th
		if(index == 2 || index == 6)
			k[index+1] += k[index]/2;

		// case : skip
		if(skip>0)
		possible = possible || recursivelyFightDP(index+1,power,skip-1,heal,k);
		// case : heal
		if(heal>0)
		possible = possible || recursivelyFightDP(index,initialPower,skip,heal-1,k);

		return dp[index][power][skip][heal]=possible;
}


bool recursivelyFight(int index,int power,int skip,int heal,vi k){	
	if(power < 0)return false;
	// cout<<index<<" "<<power<<" "<<skip<<" "<<heal<<" ";
	// if(index == k.size())
	// cout<<"end\n";
	// else
	// 	cout<<k[index]<<endl;
	// case : reached end with power>=0

	if(index == k.size()){
		if(power>=0)return true;
		else
			return false;
	}
	else{
		//store all probabilities
		bool possible = false;
		//case : normal progression
		possible  = possible || recursivelyFight(index+1,power-k[index],skip,heal,k);
		//regen if 3rd or 7th
		if(index == 2 || index == 6)
			k[index+1] += k[index]/2;
		// case : skip
		if(skip>0)
		possible = possible || recursivelyFight(index+1,power,skip-1,heal,k);
		// case : heal
		if(heal>0)
		possible = possible || recursivelyFight(index,initialPower,skip,heal-1,k);

		return possible;
	}
}
void solve()
{
	memset(dp,-1,sizeof dp);

	int n,p,a,b;
	cin>>n>>p>>a>>b;
	vi k(n,0);
	ff(i,0,n)cin>>k[i];
	initialPower = p;
	bool canDefeat = NULL;
	bool canDeafeatRec = recursivelyFight(0,p,a,b,k);
	canDefeat = recursivelyFightDP(0,p,a,b,k);
	cout<<"\nRecursion : ";
	if(canDeafeatRec) cout<<"Won"; else cout<<"Lost";
	cout<<" | Memoization : ";
	if(canDefeat) cout<<"Won"; else cout<<"Lost";
}
int main(){
    FAST
    #ifndef ONLINE_JUDGE 
        freopen("input.txt", "r", stdin); 
        freopen("output.txt", "w", stdout); 
        //freopen("error.txt", "w", stderr); 
    #endif 
        int n=1;
        cin>>n;
        while(n--)
        solve();
    return 0;
}
