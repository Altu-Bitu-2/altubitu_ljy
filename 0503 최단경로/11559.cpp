#include <iostream>
#include <stack>
#include <queue>

using namespace std;

//상하
int dy[4] = { -1,1,0,0 };
//좌우
int dx[4] = { 0,0,-1,1 };

char puyo[12][6];
int visited_puyo[12][6] = {0};
int N;//실시간 행의 수
bool is_pop_puyo = false; //뿌요가 터졌는가?

queue <pair<int, int>> q; //bfs 큐
vector <pair<int, int>> v; //4개 이상의 뿌요가 모이는 벡터


void bfs(int x, int y){
    q.push({y,x});
    v.push_back({y,x});
    
    while(!q.empty()){
        int idxY = q.front().first; 
		int idxX = q.front().second; //현재 바라보는 뿌요 좌표
		visited_puyo[idxY][idxX] = 1;
		q.pop();
		
		for(int i=0; i<4; i++){
		    int ty = idxY + dy[i];
			int tx = idxX + dx[i];
			
			if(ty < N && ty >= 0 && tx < 6 && tx >= 0){
			    if(!visited_puyo[ty][tx] && puyo[idxY][idxX] == puyo[ty][tx]){
			        q.push({ ty, tx }); // 그 다음 이동할 칸
				    v.push_back({ ty,tx }); // 함께 모여있는 뿌요들
				    visited_puyo[ty][tx] = 1;
			    }
			}
		}
    }
}

//아래에 공간이 생기면 뿌요들이 떨어지는 함수. 떨어진 위치의 y좌표를 리턴 
int fall_puyo(int x, int y){
    int tempY = -1; 
    for(int i=y; i<N;i++){
        if(puyo[i][x] == '.')
        tempY = i;
    }
    return tempY;
}

int pop_puyo(){
    int tempY = -1;
    N=12;
    int pop_cnt = 0;
    while(1){
        for(int i=0; i<N; i++){
            for(int j=0; j<6; j++){
                if(puyo[i][j]!= '.' && visited_puyo[i][j] != 1)
					bfs(i, j);
					
				if(v.size() >=4)
				    is_pop_puyo = true; //4개 이상의 뿌요가 모이면 참
				else {
				    for (int i = 0; i < v.size(); i++) {
						visited_puyo[v[i].first][v[i].second] = 0;
					}
				}
				v.clear(); 
            }
        }
        
        if (is_pop_puyo == true )
            pop_cnt++;
        else
            break;
        
        //뿌요가 터지고 남은 자리는 .으로 대체
        for (int i = 0; i < N; i++) {
			for (int j = 0; j < 6; j++) {
				if (visited_puyo[i][j] == 1) {
					puyo[i][j] = '.';
				}
			}
		}
		
		//.이 아래에 있을 시 밑으로 내려주기
		for (int i = N - 2; i >= 0; i--) {
			for (int j = 0; j < 6; j++) {
				tempY = -1;
				if (puyo[i][j] != '.') {
					tempY = fall_puyo(i, j);
				}
				if (tempY != -1) {
					puyo[tempY][j] = puyo[i][j]; // 가장 마지막 . 이 나온 곳으로 옮기고,
					puyo[i][j] = '.'; // 그 자리에 . 을 대입한다.
				}
			}
		}
		
		//초기화
		is_pop_puyo = false;
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < 6; j++) {
				visited_puyo[i][j] = 0;
			}
		}
    }
    
    return pop_cnt;
    
}






int main() {
    //입력
    for(int i=0; i<12; i++){
        for(int j=0; j<6; j++){
            cin >> puyo[i][j];
        }
    }
    
    int answer = pop_puyo();
     
    cout << answer;
}