#include <iostream>
#include <vector>
#include <queue>

using namespace std;
typedef pair<int, int> ci;
const int INF = 1e7; 

ci dijkstra(int start, int v, vector<vector<ci>> &graph) { //의존도 그래프
    priority_queue<ci, vector<ci>, greater<>> pq; 
    vector<int> dist(v + 1, INF); 

    dist[start] = 0;
    pq.push({0, start});
    int cnt = 0, t = 0;
    while (!pq.empty()) { //큐가 비어있지 않을 동안
        int weight = pq.top().first; //소요 시간
        int node = pq.top().second; //컴퓨터
        pq.pop();

        if (weight > dist[node]) {
            continue;
        }
        cnt++;
        t = weight;
        for (int i = 0; i < graph[node].size(); i++) {
            int next_node = graph[node][i].first; 
            int next_weight = weight + graph[node][i].second;
            if (next_weight < dist[next_node]) {
                dist[next_node] = next_weight;
                pq.push({next_weight, next_node});
            }
        }
    }
    return {cnt, t};
}

int main() {
    int t, n, d, c, a, b, s;

    cin >> t;
    while (t--) {
        cin >> n >> d >> c;
        vector<vector<ci>> graph(n + 1, vector<ci>(0)); //방향 그래프
        while (d--) {
            cin >> a >> b >> s;
            graph[b].push_back({a, s});
        }

        ci ans = dijkstra(c, n, graph);

        cout << ans.first << ' ' << ans.second << '\n';
    }
    return 0;
}