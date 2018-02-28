#include<bits/stdc++.h>
using namespace std;
vector<long long>adj[100001];
bool visited[100001];
long long lib,road;
long long bfs(long long i)
{
	queue<long long>q;
	q.push(i);
	visited[i]=true;
	long long cnt=0;
	while(!q.empty())
	{
		long long p=q.front();
		q.pop();
		for(vector<long long>::iterator itr=adj[p].begin();itr!=adj[p].end();itr++)
		{
			if(!visited[*itr])
			{
				q.push(*itr);
				visited[*itr]=true;
				cnt++;
			}
		}
	}
	return min(lib+cnt*road,(cnt+1)*lib);	
}
int main()
{
   long long t;
   cin>>t;
   for(long long a=0;a<t;a++)
   {
   	 long long n,q;
   	 cin>>n>>q>>lib>>road;
   	 for(long long i=0;i<q;i++)
   	 {
   	 	long long b,c;
   	 	cin>>b>>c;
   	 	adj[b].push_back(c);
   	 	adj[c].push_back(b);
	}
	for(long long i=0;i<=n;i++)
	visited[i]=false;
	long long ans=0;
	 for(long long i=1;i<=n;i++)
	 if(!visited[i])
	 {
	 	long long s=0;
	    s=bfs(i);
	    ans+=s;
     }
     cout<<ans<<endl;
     for(long long i=0;i<=n;i++)
     adj[i].clear();
}
}