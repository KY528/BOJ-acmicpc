#include <bits/stdc++.h>
using namespace std;

int n;
vector <int> order;
vector <int> graph[510]; /// 순위가 높은것 ---> 순위가 낮은것
vector <int> in_degree;
queue <int> que;
vector <int> ans;

int input() {
	scanf("%d", &n);
	order.clear();
	order.resize(n+10);
	in_degree.clear();
	in_degree.resize(n+10);
	ans.clear();
	while(!que.empty())
		que.pop();
	
	for(int i = 1; i <= n; i++) {
		scanf("%d", &order[i]);
	}
	
	for(int i = 1; i <= n; i++) {
		graph[order[i]].clear();
		for(int j = i + 1; j <= n; j++) {
			graph[order[i]].push_back(order[j]);
		}
	}
	
	int m, a, b;
	scanf("%d", &m);
	for(int i = 0; i < m; i++) {
		scanf("%d %d", &a, &b);
		
		int idx = find(graph[a].begin(), graph[a].end(), b) - graph[a].begin();
		
		if(idx < graph[a].size()) { /// graph[a] 에 b 가 포함됨
			graph[a].erase(graph[a].begin() + idx);
			graph[b].push_back(a);
		}
		else { /// graph[a] 에 b 포함 안됨
			idx = find(graph[b].begin(), graph[b].end(), a) - graph[b].begin();
			
			if(idx < graph[b].size()) {
				graph[b].erase(graph[b].begin() + idx);
				graph[a].push_back(b);
			}
			else 
				return 0;
		}
	}
	
	for(int i = 1; i <= n; i++) {
		for(auto j : graph[i]) {
			in_degree[j]++;
		}
	}
	
//	for(int i = 1; i <= n; i++) {
//		printf("%d : ", i);
//		for(auto j : graph[i]) {
//			printf("%d ", j);
//		}
//		puts("");
//	}
	
	return 1;
}

void topological_sort() {
	for(int i = 1; i <= n; i++) {
		if(in_degree[i] == 0) que.push(i);
	}
	
	while(!que.empty()) {
		int p = que.front(); que.pop();
		ans.push_back(p);
		
		for(auto idx : graph[p]) {
			in_degree[idx]--;
			
			if(in_degree[idx] == 0) 
				que.push(idx);
		}
	}
	
	for(int i = 1; i <= n; i++) {
		if(in_degree[i] > 0) {
			puts("IMPOSSIBLE");
			return;
		}
	}
	
	for(auto &i : ans)
		printf("%d ", i);
	puts("");
}

int main() {
	int testcase; scanf("%d", &testcase);
	while(testcase > 0) { testcase--;
		if(!input()) {
			puts("IMPOSSIBLE");
			continue;
		}
		
		topological_sort();
	}
	return 0;
}
