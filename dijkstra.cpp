const int INF = 1e18;
struct node {
	bool used = 0;
	vector<pair<int, int>> edges;
};
 
vector<node> g;
vector<int> dist;
 
void DJS(int start, int n)
{
	priority_queue<pair<int, int>> que;
	vector<bool> processed(n);
 
	que.push({ 0, start });
	dist[start] = 0;
 
	while (!que.empty())
	{
		int a = que.top().second;
		que.pop();
 
		if (processed[a]) continue;
 
		processed[a] = true;
 
		for (auto u : g[a].edges)
		{
			int b = u.first, w = u.second;
 
			if (dist[b] > dist[a] + w)
			{
				dist[b] = dist[a] + w;
				que.push({ -dist[b], b });
			}
		}
	}
}
