#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 26;

//���ĺ��� ����Ƚ�� ����
vector<int> alphaMap(string str) {
    vector<int> result(SIZE, 0);
    for (int i = 0; i < str.size(); i++) {
        result[str[i] - 'A']++;
    }
    return result;
}

int main() {
    int n, ans = 0;
    string source, target;

    //�Է�
    cin >> n >> source;

    //����
    vector<int> source_alpha = alphaMap(source);
    while (--n) {
        cin >> target;

        int diff = 0;
        vector<int> target_alpha = alphaMap(target);
        for (int i = 0; i < SIZE; i++) { //�� �ܾ��� ����
            diff += abs(source_alpha[i] - target_alpha[i]);
        }
        if (diff <= 1 || (diff == 2 && source.size() == target.size())) { //���ڸ� ���ϰų�, ���ų�, �ٲٰų�
            ans++;
        }
    }

    //���
    cout << ans;
    return 0;
}