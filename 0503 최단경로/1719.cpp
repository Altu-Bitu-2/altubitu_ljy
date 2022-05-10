#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e5 * 2; 

void floydWarshall(int n, vector<vector<int>> &graph, vector<vector<int>> &table) {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                int new_dist = graph[i][k] + graph[k][j];
                if (new_dist < graph[i][j]) {//더 작은 경로가 있다면
                    graph[i][j] = new_dist; //갱신
                    table[i][j] = table[i][k];
                }
            }
        }
    }
}

int main() {
    int n, m, s, d, c;

    cin >> n >> m;
    vector<vector<int>> graph(n + 1, vector<int>(n + 1, INF));
    vector<vector<int>> table(n + 1, vector<int>(n + 1, 0));
    for (int i = 1; i <= n; i++) {
        graph[i][i] = 0;
    }

    while (m--) {
        cin >> s >> d >> c;

        graph[s][d] = graph[d][s] = c;
        //s->d와 d->s는 동일

        table[s][d] = d;
        table[d][s] = s;
    }

    floydWarshall(n, graph, table);

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                cout << "- ";
            } else {
                cout << table[i][j] << ' ';
            }
        }
        cout << '\n';
    }
    return 0;
}