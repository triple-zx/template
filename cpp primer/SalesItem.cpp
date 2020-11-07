#include<bits/stdc++.h>
#define int long long
using namespace std;

const int maxn=10007;
int p[maxn][17],arr[maxn],pw[17],for_sort[maxn],s1[maxn],s2[maxn];
int n,a,b,c,t,d;
int cost[maxn];

signed main(){
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    p[0][1]=1;
    for (int i=1;i<16;++i){
        for (int j=0;j<=i*(i-1)/2;++j){
            for (int k=0;k<=i;++k){
                p[j+k][i+1]+=p[j][i];
            }
        }
    }
    pw[0]=1;
    for (int i=0;i<16;++i){
        pw[i+1]=pw[i]*(i+1);
    }
    cin>>t;
    while (t--){
        cin>>n>>a>>b>>c>>d;
        for (int i=0;i<=n*(n-1)/2;++i){
            cost[i]=min(i*a,(n*(n-1)/2-i)*a+b);
            for_sort[i]=i;
        }
        sort(for_sort,for_sort+n*(n-1)/2+1,[&](int u,int v){return cost[u]<cost[v];});
        s1[0]=p[for_sort[0]][n], s2[0]=cost[for_sort[0]]*p[for_sort[0]][n];
        for (int i=1;i<=n*(n-1)/2;++i){
            s1[i]=s1[i-1]+p[for_sort[i]][n];
            s2[i]=s2[i-1]+p[for_sort[i]][n]*cost[for_sort[i]];    
        }
        auto f=[&](int u)->pair<int,int>{
            int ret=s2[u];
            int sum=s1[u];
            ret+=c*pw[n];
            return {ret,sum};
        };
        double min_res=1e18, index=-1;
        for (int i=0;i<=n*(n-1)/2;++i){
            if (i<n*(n-1)/2&&cost[for_sort[i]]==cost[for_sort[i+1]]) continue;
            pair<int,int> res=f(i);
            if (1.0*res.first/res.second<min_res) min_res=1.0*res.first/res.second, index=i;
        }
        while (d--){
            for (int i=0;i<n;++i){
                cin>>arr[i];
            }
            int rev=0;
            for (int i=0;i<n;++i){
                for (int j=0;j<i;++j){
                    rev+=(arr[i]<arr[j]);
                }
            }
            if (min(a*rev,(n*(n-1)/2-rev)*a+b)<min_res){cout<<min(a*rev,(n*(n-1)/2-rev)*a+b)<<"/"<<1<<"\n"; continue;}
            pair<int,int> res=f(index);
            int g=__gcd(res.first,res.second);
            cout<<res.first/g<<"/"<<res.second/g<<"\n";
        }
    }
}