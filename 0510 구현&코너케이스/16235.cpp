#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <tuple>
#include <algorithm>

using namespace std;
typedef vector<vector<int>> matrix;
typedef tuple<int, int, int> tp;

queue<tp> spring(matrix& land, deque<tp>& tree, queue<pair<int, int>>& breeding_tree) {
    queue<tp> dead_tree;
    int size = tree.size();
    while (size--) { //모든 나무 검사
        int age = get<0>(tree.front()); //나이
        int row = get<1>(tree.front()); //행
        int col = get<2>(tree.front()); //열
        tree.pop_front();

        if (land[row][col] < age) { //자신의 나이만큼 양분을 먹을 수 없다면
            dead_tree.push({ age, row, col });
            continue;
        }
        land[row][col] -= age;
        tree.emplace_back(age + 1, row, col);
        if ((age + 1) % 5 == 0) { //나이가 5의 배수라면
            breeding_tree.push({ row, col });
        }
    }
    return dead_tree;
}

void summer(queue<tp>& dead_tree, matrix& land) {
    while (!dead_tree.empty()) {
        int age = get<0>(dead_tree.front()); //죽은 나무의 나이
        int row = get<1>(dead_tree.front()); //죽은 나무의 행 위치
        int col = get<2>(dead_tree.front()); //죽은 나무의 열 위치
        dead_tree.pop();
        land[row][col] += (age / 2);
    }
}

void fall(int n, deque<tp>& tree, queue<pair<int, int>>& breeding_tree) {
    int dr[8] = { -1, 1, 0, 0, -1, -1, 1, 1 };
    int dc[8] = { 0, 0, -1, 1, -1, 1, -1, 1 };

    while (!breeding_tree.empty()) {
        int row = breeding_tree.front().first; //번식할 나무의 행
        int col = breeding_tree.front().second; //번식할 나무의 열
        breeding_tree.pop();

        for (int j = 0; j < 8; j++) {
            int nr = row + dr[j];
            int nc = col + dc[j];
            if (nr < 0 || nr >= n || nc < 0 || nc >= n) {
                continue;
            }
            tree.push_front({ 1, nr, nc }); //새로 생긴 나무
        }
    }
}

void winter(int n, matrix& a, matrix& land) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            land[i][j] += a[i][j];
        }
    }
}

int main() {
    int n, m, k, x, y, z;

    //입력
    cin >> n >> m >> k;
    matrix a(n, vector<int>(n, 0));
    matrix land(n, vector<int>(n, 5)); //처음 양분 모든 칸에 5
    queue<pair<int, int>> breeding_tree; //번식할 트리
    deque<tp> tree;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    while (m--) {
        cin >> x >> y >> z;
        tree.emplace_back(z, x - 1, y - 1); //(0, 0)부터 시작하도록 구현하기위해 1을 빼준 인덱스에 접근
    }

    //연산
    sort(tree.begin(), tree.end()); //어린 나이 순으로 정렬
    while (k--) {
        queue<tp> dead_tree = spring(land, tree, breeding_tree); //봄이 지나고 죽은 나무
        summer(dead_tree, land);
        fall(n, tree, breeding_tree);
        winter(n, a, land);
    }

    //출력
    cout << tree.size();
    return 0;
}