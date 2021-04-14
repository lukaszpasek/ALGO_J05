#include<iostream>
#include<vector>
#include<queue>
#include<utility>
#include <time.h>
using namespace std;
const int INF=1e9;
struct edge
{
  pair<int,int>  v={-1,-1},u={-1,-1};
  int flow=0,cap=1;
};
int n,m;
pair<int,int> s,t;
vector<edge> edges;
vector<vector<char> > G(53);
vector<vector<vector<int> > > g;
vector<vector<int> > nextt(53);
int BFS()
{
    queue<pair<int,int> > q;
    for(int k=0;k<=n+2;k++)
    {
        for(int i=0;i<=m+2;i++)
            {nextt[k][i] = -1;}
    }
    nextt[s.first][s.second]=0;
    nextt[t.first][t.second]=-1;
   q.push(s);
    int flow=INF;
    while(!q.empty())
    {
        pair<int,int> p=q.front();
        //cout<<"P : "<<p.first<<" "<<p.second<<endl;
        q.pop();
        for(auto i: g[p.first][p.second])
        {
            //cerr<<"g[p][i] "<<i<<endl;
            int id=i;
            pair<int,int> where_to=edges[id].v;
            if(edges[id].flow<edges[id].cap && nextt[where_to.first][where_to.second]==-1)
            {
              flow=min(flow,edges[id].cap-edges[id].flow);
              nextt[where_to.first][where_to.second]=id;
              q.push(where_to);
            }
            if(where_to.first==t.first && where_to.second==t.second)break;
        }
    }
    if(nextt[t.first][t.second]==-1) return 0;
    pair<int,int> u=t;
    while(u!=s)
    {
         int id=nextt[u.first][u.second];
        edges[id].flow+=flow;
        edges[id^1].flow-=flow; // edge^1 jest krawędzią o przeciwnym wzrocie w grafie, poniewaz zawsze wrzucam parami krawędzie
        u=edges[id].u;
    }
    return flow;

}

void EdmondsKarp(vector<vector<char> > &G)
{
    int flow=0;
    while(true)
    {
      int path=BFS();
      //cout<<endl;
      if(path==0 || path==INF) break;
      flow+=path;
    }
   cout<<flow<<endl;
    //countReached(t);
      for(int i=1 ; i<=n ; i++)
      {
   for(int j=1 ; j<=m ; j++)
   {
       if(nextt[i][j] == -1 ) cout<<"#";
       else cout<<G[i][j];
   }
   cout<<endl;
      }
}
void make_graph(vector<vector<char> > &G)
{
       edge x,y;
       int wsk=0;
  for(int i=0 ; i<=n+1 ; i++)
   for(int j=0 ; j<=m+1 ; j++)
   {
       //cout<<"I "<<i<<" J "<<j<<endl;
       if(G[i][j]=='x')
       {
        g[s.first][s.second].push_back(wsk);
        x.u=s;
        x.v={i,j};
        x.cap=INF;
        edges[wsk++]=x;
        y.u=x.v;
        y.v=x.u;
        y.cap=0;
        g[i][j].push_back(wsk);
        edges[wsk++]=y;
       }
       else if(G[i][j]=='#')
       {
           //cout<<"HEJ "<<endl;
         g[i][j].push_back(wsk);
         x.u={i,j};
         x.v=t;
         x.cap=INF;
       edges[wsk++]=x;
         y.u=x.v;
        y.v=x.u;
        y.cap=0;
        g[t.first][t.second].push_back(wsk);
       edges[wsk++]=y;
       }
       x.cap=1;
       if(i!=0){
      g[i][j].push_back(wsk);
      x.u={i,j};
      x.v={i-1,j};
      y.u=x.v;
      y.v=x.u;
      y.cap=0;
      edges[wsk++]=x;
      g[i-1][j].push_back(wsk);
      edges[wsk++]=y;
       }
      //finish one edge
      if(i!=n+1){
      g[i][j].push_back(wsk);
      x.u={i,j};
      x.v={i+1,j};
      y.u=x.v;
      y.v=x.u;
       y.cap=0;
      edges[wsk++]=x;
      g[i+1][j].push_back(wsk);
      edges[wsk++]=y;}
      //finish another
      if(j!=0){
      g[i][j].push_back(wsk);
      x.u={i,j};
      x.v={i,j-1};
      y.u=x.v;
      y.v=x.u;
       y.cap=0;
      edges[wsk++]=x;
      g[i][j-1].push_back(wsk);
      edges[wsk++]=y;
      }
      //finish another
      if(j!=m+1){
      g[i][j].push_back(wsk);
      x.u={i,j};
      x.v={i,j+1};
      y.u=x.v;
      y.v=x.u;
       y.cap=0;
      edges[wsk++]=x;
      g[i][j+1].push_back(wsk);
      edges[wsk++]=y;
      }
      //finish another
   }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int z;
    for(int i=0 ; i<53 ; i++) nextt[i].resize(53);
    g.resize(53);
    time_t start, koniec;
        time( & start );
       double roznica;
          G[0].resize(52);
          G[51].resize(52);
          G[52].resize(2);
        for(int i=0 ; i<=52 ; i++)  {G[i].resize(52); g[i].resize(53);}
           fill(G[0].begin(),G[0].end(),'x');
    cin>>z;
    while(z--)
    {
        cin>>n>>m;
        edges.resize((n+3)*(m+3)*15+1);
        s={n+2,0};
        t={n+2,1};
       // for(int i=0; i<n+2 ; i++) {g[i].resize(m+2);}
       // g[n+2].resize(2);
        fill(G[n+1].begin(),G[n+1].end(),'x');
        for(int i=1 ; i<=n ; i++)
        {
            G[i][0]='x';
            G[i][m+1]='x';
        for(int j=1 ; j<m+1 ; j++)cin>>G[i][j];
        }
        make_graph(G);
        EdmondsKarp(G);
        for(int i=0 ; i<n+3; i++)
         for(int j=0 ; j<m+3 ; j++)
         g[i][j].clear();
         edges.clear();
    }
    /* time( & koniec );
     roznica = difftime( koniec, start );
     cout<<"CZAS "<<roznica<<endl;*/

    return 0;
}