#include <iostream>
#include <vector>

using namespace std;
const int SIZE = 26;

//알파벳별 등장횟수 저장
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

    //입력
    cin >> n >> source;

    //연산
    vector<int> source_alpha = alphaMap(source);
    while (--n) {
        cin >> target;

        int diff = 0;
        vector<int> target_alpha = alphaMap(target);
        for (int i = 0; i < SIZE; i++) { //두 단어의 차이
            diff += abs(source_alpha[i] - target_alpha[i]);
        }
        if (diff <= 1 || (diff == 2 && source.size() == target.size())) { //문자를 더하거나, 빼거나, 바꾸거나
            ans++;
        }
    }

    //출력
    cout << ans;
    return 0;
}