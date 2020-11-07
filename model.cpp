#include<bits/stdc++.h>
#define int long long
using namespace std;

#define maxn 1000005
#define INF (1 << 30)

mt19937 rng(1234);
int cnta=0;
struct treap {
  int l[maxn], r[maxn], val[maxn], rnd[maxn], sum[maxn], w[maxn];
  int sz, ans, rt;
  inline void pushup(int x) { sum[x] = sum[l[x]] + sum[r[x]] + w[x] * val[x]; }
  void lrotate(int &k) {
    int t = r[k];
    r[k] = l[t];
    l[t] = k;
    sum[t] = sum[k];
    pushup(k);
    k = t;
  }
  void rrotate(int &k) {
    int t = l[k];
    l[k] = r[t];
    r[t] = k;
    sum[t] = sum[k];
    pushup(k);
    k = t;
  }
  void insert(int &k, int x) {
    if (!k) {
      sz++;
      k = sz;
      sum[k] = x;
      w[k] = 1;
      val[k] = x;
      rnd[k] = ++cnta;
      return;
    }
    sum[k]+=x;
    if (val[k] == x) {
      w[k]++;
    } else if (val[k] < x) {
      insert(r[k], x);
      if (rnd[r[k]] < rnd[k]) lrotate(k);
    } else {
      insert(l[k], x);
      if (rnd[l[k]] < rnd[k]) rrotate(k);
    }
  }

  int del(int &k, int x) {
    int ret=0;
    if (!k) return 0;
    if (val[k] == x) {
      if (w[k] > 1) {
        w[k]--;
        sum[k]-=x;
        assert(sum[k]>=0);
        return w[k]+1;
      }
      if (l[k] == 0 || r[k] == 0)
        k = l[k] + r[k];
      else if (rnd[l[k]] < rnd[r[k]]) {
        rrotate(k);
        del(k, x);
      } else {
        lrotate(k);
        del(k, x);
      }
      ret=1;
    } else if (val[k] < x) {
      ret=del(r[k], x);
      if (ret) sum[k]-=x;
      assert(sum[k]>=0);
    } else {
      ret=del(l[k], x);
      if (ret) sum[k]-=x;
      assert(sum[k]>=0);
    }
    return ret;
  }
  int calc(int &k,int x){
    if (!k) return 0;
    if (val[k]==x) return sum[l[k]]+w[k]*val[k];
    if (val[k]>x){
        return calc(l[k],x); 
    }
    else{
        return calc(r[k],x)+sum[l[k]]+w[k]*val[k];
    }
  }
  
} T;

int q,mod,lans=0;

signed main() {
  ios::sync_with_stdio(false);
  cin.tie(0), cout.tie(0);
  cin>>q>>mod;
  while (q--){
    int op,u,r;
    cin>>op>>u;
    u=(u+lans)%mod;
    if (op==0) T.insert(T.rt,u);
    if (op==1) cout<<T.del(T.rt,u)<<"\n";
    if (op==2) {cin>>r; r=(r+lans)%mod; if (u>r) swap(u,r); int res = T.calc(T.rt,r) - T.calc(T.rt,u); assert(res>=0); cout<<res<<"\n"; lans = res;}
  }
  return 0;
}