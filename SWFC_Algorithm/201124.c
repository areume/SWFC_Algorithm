#pragma warning(disable: 4996)
#pragma warning(disable: 4477)
#pragma warning(disable: 4313)

/********************************************/
// 숫자근
/********************************************/

#if 0

#include <stdio.h>

int N;
int num[1000 + 10];

int Calc(int number)
{
	int root = 0, val = 100;

	while (val > 1) {
		root += number / val;
		number = number % val;

		val /= 10;
	}
	root += number;

	if (root / 10 != 0) root = Calc(root);

	return root;
}

int main()
{
	int temp, idx = -1, max = 0;

	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}

	for (int i = 0; i < N; i++) {
		temp = Calc(num[i]);
		if (temp > max) {
			max = temp;
			idx = i;
		}
		if (temp == max) {
			if (num[i] < num[idx]) idx = i;
		}
	}
	printf("%d\n", num[idx]);
}

#endif

/********************************************/
// 미로탈출로봇
/********************************************/

#if 0

#include <stdio.h>

typedef struct st {
	int r, c, cnt;
}POS;

POS que[100 * 100 + 50];

int rp, wp;

int R, C;
int map[100 + 10][100 + 10];

int dr[4] = { -1,1,0,0 };
int dc[4] = { 0,0,-1,1 };

int sr, sc, er, ec;

void push(int r, int c, int cnt)
{
	que[wp].r = r;
	que[wp].c = c;
	que[wp].cnt = cnt;
	wp++;
}

POS pop()
{
	return que[rp++];
}

int Empty()
{
	return rp == wp;
}

int BFS(int sr, int sc)
{
	// 출발점 큐에 저장
	push(sr, sc, 0);
	map[sr][sc] = 1;

	while (!Empty()) {
		// 큐에서 하나 꺼내오기
		POS cur = pop();

		// 탈출 조건
		if (cur.r == er && cur.c == ec) return cur.cnt;

		// 4방향 탐색
		for (int k = 0; k < 4; k++) {
			int nr = cur.r + dr[k];
			int nc = cur.c + dc[k];

			if (nr<1 || nr>R || nc<1 || nc>C) continue;
			if (map[nr][nc] == 1) continue;

			map[nr][nc] = 1;
			push(nr, nc, cur.cnt + 1);
		}
	}
	return -1;
}

int main()
{
	scanf("%d %d", &C, &R);
	scanf("%d %d %d %d", &sc, &sr, &ec, &er);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			scanf("%1d", &map[i][j]);
		}
	}
	printf("%d\n", BFS(sr, sc));
}

#endif

/********************************************/
// 장기
/********************************************/

#if 0

#include <stdio.h>

int N, M;
int sr, sc, er, ec;
int map[100 + 10][100 + 10];

typedef struct _st {
	int r, c, time;
}POS;

POS queue[100 * 100 + 100];
int rp, wp;

void Enqueue(int r, int c, int time) {
	queue[wp].r = r; queue[wp].c = c;
	queue[wp].time = time; wp++;
}

POS Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

int dr[] = { -1,-2,-2,-1,1,2,2,1 };
int dc[] = { -2,-1,1,2,2,1,-1,-2 };

int BFS() {
	Enqueue(sr, sc, 0);
	map[sr][sc] = 1;

	while (!Empty()) {
		POS cur = Dequeue();
		if (cur.r == er && cur.c == ec) return cur.time;

		for (int i = 0; i < 8; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr<1 || nr>N || nc<1 || nc>M) continue;
			if (map[nr][nc] == 1) continue;

			map[nr][nc] = 1;
			Enqueue(nr, nc, cur.time + 1);

		}
	}
	return -1;
}

void InputData() {
	scanf("%d %d", &N, &M);
	scanf("%d %d %d %d", &sr, &sc, &er, &ec);
}

int main() {
	InputData();
	printf("%d\n", BFS());
}

#endif

/********************************************/
// 토마토(고)
/********************************************/

#if 0

#include <stdio.h>

int R, C;
int map[1000 + 10][1000 + 10];

typedef struct _st {
	int r, c, time;
}POS;

POS queue[1000 * 1000 + 100];
int rp, wp;

void Enqueue(int r, int c, int time) {
	queue[wp].r = r; queue[wp].c = c;
	queue[wp].time = time; wp++;
}

POS Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int Count() {
	int cnt = 0;
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j] == 0) cnt++;
		}
	}
	return cnt;
}

int BFS() {

	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j] == 1) {
				Enqueue(i, j, 0);
			}
		}
	}

	while (!Empty()) {
		POS cur = Dequeue();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr<1 || nr>R || nc<1 || nc>C) continue;
			if (map[nr][nc] == 0) {
				map[nr][nc] = 1;
				Enqueue(nr, nc, cur.time + 1);
			}
		}
	}
	if (Count() == 0) return queue[--rp].time;
	else return -1;
}

void InputData() {
	scanf("%d %d", &C, &R);
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

int main()
{
	InputData();
	printf("%d\n", BFS());
}

#endif

/********************************************/
// 단지 번호 붙이기
/********************************************/

#if 0

#include <stdio.h>

int N, sol, cnt;
int map[25 + 5][25 + 5];
int danji[25 * 25 + 10];

typedef struct _st {
	int r, c;
}POS;

POS queue[25 * 25 + 10];
int rp, wp;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

void Enqueue(int r, int c) {
	queue[wp].r = r; queue[wp].c = c;
	wp++;
}

POS Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

int BFS(int i, int j) {
	Enqueue(i, j);
	map[i][j] = 0;
	cnt++;

	while (!Empty()) {
		POS cur = Dequeue();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (map[nr][nc] == 0) continue;

			Enqueue(nr, nc);
			map[nr][nc] = 0;
			cnt++;
		}
	}
	return cnt;
}

void Solve() {

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i][j] == 1) {
				cnt = 0;
				wp = rp = 0;
				danji[sol++] = BFS(i, j);
			}
		}
	}
}

void Sort() {
	for (int i = 0; i < sol - 1; i++) {
		for (int j = i + 1; j < sol; j++) {
			if (danji[i] > danji[j]) {
				int temp = danji[i];
				danji[i] = danji[j];
				danji[j] = temp;
			}
		}
	}
}

void InputData() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			scanf("%1d", &map[i][j]);
		}
	}
}

int main()
{
	InputData();
	Solve();
	Sort();
	printf("%d\n", sol);
	for (int i = 0; i < sol; i++) {
		printf("%d\n", danji[i]);
	}
	return 0;
}

#endif

/********************************************/
// 바이러스
/********************************************/

#if 0

#include <stdio.h>

int N, M, cnt;
int map[100 + 10][100 + 10];
int vis[100 + 10];

typedef struct _st {
	int pc;
}POS;

POS queue[100 * 100 + 10];
int wp, rp;

void Enqueue(int pc) {
	queue[wp++].pc = pc;
}

POS Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

void BFS() {
	wp = rp = 0;

	vis[1] = 1;
	Enqueue(1);
	// 1번 PC는 카운트에 포함하지 않는다.

	while (!Empty()) {
		POS cur = Dequeue();

		for (int k = 2; k <= N; k++) {
			if (map[cur.pc][k] == 0) continue;	// 연결되어 있지 않으면 패스.
			if (vis[k] == 1) continue;			// 이미 방문한 곳이면 패스.

			Enqueue(k);
			vis[k] = 1;
			cnt++;
		}
	}
}

void InputData() {
	int r, c;
	scanf("%d", &N);
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		scanf("%d %d", &r, &c);
		map[r][c] = map[c][r] = 1;
	}
}

int main()
{
	InputData();
	BFS();
	printf("%d\n", cnt);
}

#endif
