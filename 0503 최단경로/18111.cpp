#include <iostream>
#include <vector>

using namespace std;
const int INF = 1e9;

int mineLand(int n, int m, int b, int height, vector<vector<int>> &land) {
    //height: 기준 높이
    int tot_time = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (land[i][j] > height) { //기준 높이보다 땅이 높다면
                b += (land[i][j] - height); //제거
                tot_time += 2 * (land[i][j] - height);
            } else if (land[i][j] < height) { //기준 높이보다 땅이 낮다면
                b -= (height - land[i][j]); //쌓기
                tot_time += (height - land[i][j]);
            }
        }
    }
    if (b < 0) 
        return INF + 1;
    return tot_time;
}


int main() {
    int n, m, b, min_height = 256, max_height = 0;

    cin >> n >> m >> b;
    vector<vector<int>> land(n, vector<int>(m, 0));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> land[i][j];
            min_height = min(min_height, land[i][j]); //가장 낮은 땅 확인해서 입력
            max_height = max(max_height, land[i][j]); //가장 높은 땅 확인해서 입력
        }
    }

    int min_time = INF, height = 0;
    for (int i = min_height; i <= max_height; i++) {//가장 낮은 땅 ~ 가장 높은 땅이 기준이 되는 경우 모두 확인
        int t = mineLand(n, m, b, i, land);//소요시간 반환
        if (t <= min_time) { 
            min_time = t;
            height = i;
        }
    }

    cout << min_time << ' ' << height;
    return 0;
}