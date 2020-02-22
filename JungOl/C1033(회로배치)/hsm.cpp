#include<stdio.h>
#include<iostream>
#include<vector>
#include<queue>

using namespace std;

vector<int>p;
vector<pair<int, int>> v;
vector<pair<int, int>> route;
queue<pair<int, int>>q;

int n, k;
int map[52][52];	//current map
int map2[52][52];	//visited
pair<int,int> map3[52][52];	//0:right, 1: left, 2:up, 3: down
int npos[4];		//sx, sy, ex, ey;

int dx[] = { 0,0,-1,1 };
int dy[] = { 1,-1,0,0 };

int main() {
	scanf("%d", &n);

	int npos[4];
	for (int i = 0; i < 4; i++) {
		scanf("%d", &npos[i]);
	}

	scanf("%d", &k); 
	
	int cc; 
	scanf("%d", &cc);
	for (int i = 0; i < cc; i++) {
		int t1; scanf("%d ", &t1);
		p.push_back(t1);

		while(1){
			int t2, t3;
			scanf("%d %d", &t2, &t3);
			v.push_back({ t2, t3 });
			if (t1 - 1 <= 0) {
				break;
			}
			t1--;
		}
	}

	//맵 그리기
	int cnt=0;
	for (int i = 0; i < p.size(); i++) {
		for (int j = cnt; j < cnt+p[i]-1; j++) {
			map[v[j].first][v[j].second] = 1;
			int t1, t2;
			t1 = v[j + 1].first - v[j].first;
			t2 = v[j + 1].second - v[j].second;
			
			//가로로 이동
			if(t1==0){
				//왼쪽
				if (t2 < 0) {
					for (int k = v[j].second; k >= v[j+1].second; k--) {
						map[v[j].first][k] = 1;
					}
				}
				//오른쪽
				else if (t2 > 0) {
					for (int k = v[j].second; k <= v[j+1].second; k++) {
						map[v[j].first][k] = 1;
					}
				}
			}
			//세로로 이동
			else if (t2 == 0) {
				//위
				if (t1 < 0) {
					for (int k = v[j].first; k >= v[j+1].first; k--) {
						map[k][v[j].second] = 1;
					}
				}
				//아래
				if (t1 > 0) {
					for (int k = v[j].first; k <= v[j+1].first; k++) {
						map[k][v[j].second] = 1;
					}
				}
			}
		}
		cnt += p[i];
	}

	//행제한, 열제한
	int q1, q2, q3, q4; 
	if (npos[0] >= npos[2]) {
		q1 = npos[2];
		q2 = npos[0];
	}
	else {
		q1 = npos[0];
		q2 = npos[2];
	}
	if (npos[1] >= npos[3]) {
		q3 = npos[3];
		q4 = npos[1];
	}
	else {
		q3 = npos[1];
		q4 = npos[3];
	}
	//printf("%d %d %d %d\n", q1, q2, q3, q4);
	
	//bfs
	q.push({ npos[0],npos[1] });
	(map[npos[0]][npos[1]] == 1) ? map2[npos[0]][npos[1]] = 4 : map2[npos[0]][npos[1]] = 1;
	//printf("%d\n", map2[npos[0]][npos[1]]);
	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nx = x + dx[i];
			int ny = y + dy[i];
			if (nx >= q1 && nx <= q2 && ny >= q3 && ny <= q4) {
				if (map2[nx][ny] == 0) {
					if (map[nx][ny] == 1) {
						map2[nx][ny] = map2[x][y] + 4;
					}
					else {
						map2[nx][ny] = map2[x][y] + 1;
					}
					map3[nx][ny] = {x,y};
					q.push({ nx,ny });
				}
			}
		}
	}

	//길 뒤에서부터 우선 저장
	int x = npos[2];
	int y = npos[3];
	pair<int, int> curve = { x - map3[x][y].first,y - map3[x][y].second };
	route.push_back({ x, y });

	while (1) {
		int xx = map3[x][y].first;
		int yy = map3[x][y].second;
		if (map3[xx][yy].first == 0 && map3[xx][yy].second == 0) {
			route.push_back({ xx, yy });
			break;
		}
		if (x - xx != curve.first || y - yy != curve.second) {
			curve.first = x - xx;
			curve.second = y - yy;
			route.push_back({ x,y });
		}
		x = xx;
		y = yy;
	}

	printf("%d\n", map2[npos[2]][npos[3]]);
	printf("%d ", route.size());
	for (int i = route.size() - 1; i >= 0; i--) {
		printf("%d %d ", route[i].first, route[i].second);
	}
	printf("\n");
	//system("pause");
	return 0;
}
