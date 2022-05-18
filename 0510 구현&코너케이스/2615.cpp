#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 19;

//������ ���� ������ ��ȿ���� Ȯ��
bool promising(int r, int c, int stone, vector<vector<int>>& board) {
    return r >= 0 && r < SIZE&& c >= 0 && c < SIZE&& board[r][c] == stone;
}

bool validDir(int r, int c, int d, int stone, vector<vector<int>>& board) {
    //����, ����, ������ �밢��, ����� �밢��
    int dr[4] = { 0, 1, 1, -1 };
    int dc[4] = { 1, 0, 1, 1 };

    //(r, c) ������ ��ġ�� �̾����� ���� �ֳ�?
    if (promising(r - dr[d], c - dc[d], stone, board)) {
        return false;
    }
    int cnt = 0;
    while (cnt < 6 && promising(r, c, stone, board)) { //(r, c)�� ���� �������� �ϴ� �̾����� �ٵϾ��� ����
        cnt++;
        r += dr[d];
        c += dc[d];
    }
    return cnt == 5;
}

bool isEnd(int r, int c, vector<vector<int>>& board) {
    for (int i = 0; i < 4; i++) { //����, ����, ������ �밢��, ����� �밢��
        if (validDir(r, c, i, board[r][c], board)) {
            return true;
        }
    }
    return false;
}

int main() {
    vector<vector<int>> board(SIZE, vector<int>(SIZE, 0));

    //�Է�
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cin >> board[i][j];
        }
    }

    //���� & ���
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (!board[i][j]) { //���� ����
                continue;
            }
            if (isEnd(i, j, board)) { //������ �̰峪?
                cout << board[i][j] << '\n' << i + 1 << ' ' << j + 1;
                return 0;
            }
        }
    }
    cout << 0;
    return 0;
}