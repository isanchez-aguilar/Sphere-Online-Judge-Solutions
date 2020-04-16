/*
*	User: Isanchez_Aguilar
*	Problem: SPOJ EC_P - Critical Edges
*/
#include <bits/stdc++.h>

using namespace std;

int currTime = 0;
vector<int> minTime;
vector<int> dfsTime;
vector< vector<int> > graph;
vector< pair<int, int> > bridges;

void dfs(int u, int prevNode)
{
	dfsTime[u] = currTime;
	minTime[u] = currTime;
	++currTime;

	for (int i = 0; i < graph[u].size(); ++i)
	{
		int v = graph[u][i];
		
		if (prevNode != v)
		{
			// Not visited yet.
			if (dfsTime[v] == -1)
			{
				dfs(v, u);
				minTime[u] = min(minTime[u], minTime[v]);
			}
			else
				minTime[u] = min(minTime[u], dfsTime[v]);
	
			if (dfsTime[u] < minTime[v])
				bridges.emplace_back(min(u, v), max(u, v));
		}
	}
	
	return;
}

void findBridges()
{
	const int nodes = graph.size();

	currTime = 0;
	bridges.clear();
	minTime = vector<int>(nodes, -1);
	dfsTime = vector<int>(nodes, -1);

	for (int u = 0; u < nodes; ++u)
	{
		if (minTime[u] == -1)
			dfs(u, u);
	}
	
	return;	
}

int main(void)
{
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);

	int testCases;
	cin >> testCases;	
	
	for (int t = 1; t <= testCases; ++t)
	{
		int nodes, edges;
		cin >> nodes >> edges;

		graph = vector< vector<int> >(nodes);
	
		for (int i = 0; i < edges; ++i)
		{
			int u, v;
			cin >> u >> v;
			
			--u, --v;
			graph[u].emplace_back(v);
			graph[v].emplace_back(u);
		}

		findBridges();
		
		sort(begin(bridges), end(bridges));

		cout << "Caso #" << t << "\n";
			
		if (bridges.size() == 0)
			cout << "Sin bloqueos\n";
		else
		{		
			cout << bridges.size() << "\n";
	
			for (int i = 0; i < bridges.size(); ++i)
				cout << bridges[i].first + 1 << " " << bridges[i].second + 1 << "\n";
		}
	}
	
	return 0;
}
