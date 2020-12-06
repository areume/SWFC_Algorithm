#pragma warning(disable: 4996)
#pragma warning(disable: 4477)
#pragma warning(disable: 4313)

/********************************************/
// 그래프 칠하기
/********************************************/

#if 0

#include <stdio.h>

int N, M;
int connect[12 + 5][12 + 5];
int noColor[12 + 5];

int Check(int node, int color) {
	for (int i = 1; i < node; i++) {			// node에 연결된 다른 노드들을 모두 검사해서
		if (connect[node][i] == 1) {			// 연결되어있는데
			if (noColor[i] == color) return 0;	// 같은 색이면 해당 색깔 해당 노드에 색칠 불가능.
		}
	}
	return 1;
}

int DFS(int node) {
	if (node > N) return 1;					// node번호가 N보다 크면 마지막 까지 칠한 것 -> 성공.

	for (int i = 1; i <= M; i++) {			// i는 칠할 색상의 번호를 의미한다.
		if (Check(node, i) == 0) continue;	// 해당 노드에 해당 색을 칠할 수 있는지 확인한다.

		noColor[node] = i;
		if (DFS(node + 1) == 1) return 1;		// DFS가 리턴값을 가지면 if문을 사용해준다.
		noColor[node] = 0;
	}
	return 0;								// DFS의 마지막 탐색까지 오면 실패.
}

void InputData() {
	scanf("%d %d", &N, &M);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= i; j++) {
			scanf("%d", &connect[i][j]);
			connect[j][i] = connect[i][j];
		}
	}
}

int main()
{
	InputData();
	if (DFS(1) == 1) {
		for (int i = 1; i <= N; i++) {
			printf("%d ", noColor[i]);
		}
	}
	else printf("-1");
}

#endif

/********************************************/
// 해밀턴 순환회로
/********************************************/

#if 0

#include <stdio.h>

int N;
int cost[12 + 5][12 + 5];
int vist[12 + 5];

int Min = 99999;

void DFS(int cnt, int city, int total) {
	if (cnt == N) {
		if (cost[city][1] != 0) {

			total += cost[city][1];
			if (total < Min) Min = total;
		}
		return;
	}

	for (int i = 2; i <= N; i++) {
		if (vist[i] == 1) continue;					// 이미 방문한 곳은 방문할 수 없다.
		if (cost[city][i] == 0) continue;			// 비용이 0인 곳은 방문할 수 없다.
		if (total + cost[city][i] > Min) continue;	// 이미 최소값을 넘어서면 더이상 탐색하지 않아도 된다.

		vist[i] = 1;
		DFS(cnt + 1, i, total + cost[city][i]);
		vist[i] = 0;
	}
}

void InputData() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &cost[i][j]);
		}
	}
}

int main()
{
	InputData();
	DFS(1, 1, 0);
	printf("%d", Min);
	return 0;
}

#endif

/********************************************/
// 마름모 - 아이디어 문제
/********************************************/

#if 0

#include <stdio.h>

int N, K, idx;
char arr[28 + 10];
int numb[28 + 10];

void Sort() {
	int i, j;
	for (i = 0; i < idx - 1; i++) {
		for (j = i + 1; j < idx; j++) {
			if (numb[i] < numb[j]) {		// 내림차순 정렬
				int temp = numb[i];
				numb[i] = numb[j];
				numb[j] = temp;
			}
			if (numb[i] == numb[j]) {		// 중복 제거
				numb[j] = 0;
			}
		}
	}
}

int asc2int(char c) {
	if (c >= 'A') return (int)c - 55;
	else return (int)c - 48;
}

void InputData() {
	scanf("%d %d", &N, &K);
	scanf("%s", arr);
}

int main()
{
	int len, num;

	InputData();

	len = N / 4;
	for (int turn = 0; turn < len; turn++) {					// turn은 회전 수.
		for (int i = turn; i < turn + N; i += len) {			// i는 각 문자열의 시작 위치.
			num = 0;
			for (int j = 0; j < len; j++) {				// j는 각 문자열의 글자 순서.
				num *= 16;
				num += asc2int(arr[(i + j) % N]);
			}
			numb[idx++] = num;
		}
	}
	Sort();
	printf("%d\n", numb[K - 1]);

	return 0;
}

#endif

/********************************************/
// 보물섬 - BFS
/********************************************/

#if 0

#include <stdio.h>

int R, C;
char map[50 + 10][50 + 10];
int vist[50 + 10][50 + 10];

typedef struct _st {
	int r, c, cnt;
}POS;

POS queue[50 * 50 + 10];
int rp, wp;

void Enqueue(int r, int c, int cnt) {
	queue[wp].r = r; queue[wp].c = c;
	queue[wp].cnt = cnt; wp++;
}

POS Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

void Init() {
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			vist[i][j] = 0;
		}
	}
}

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

int Min = 0;

int BFS(int r, int c, int cnt) {
	POS cur;

	Enqueue(r, c, cnt);
	vist[r][c] = 1;

	while (!Empty()) {
		cur = Dequeue();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr > R || nr<1 || nc>C || nc < 1) continue;
			if (map[nr][nc] == 'W') continue;
			if (vist[nr][nc] == 1) continue;

			Enqueue(nr, nc, cur.cnt + 1);
			vist[nr][nc] = 1;
		}
	}
	return cur.cnt;
}

void InputData() {
	scanf("%d %d", &R, &C);
	for (int i = 1; i <= R; i++) {
		scanf("%s", &map[i][1]);
	}
}

int main()
{
	int ans = -1;

	InputData();
	for (int i = 1; i <= R; i++) {
		for (int j = 1; j <= C; j++) {
			if (map[i][j] == 'L') {
				Init();
				wp = rp = 0;
				ans = BFS(i, j, 0);

				if (ans > Min) Min = ans;
			}
		}
	}
	printf("%d", Min);
	return 0;
}

#endif

/********************************************/
// 양팔저울 - DFS
/********************************************/

#if 0

#include <stdio.h>

int N, G;			// 추의 개수, 구슬의 개수.
int wei[12 + 10];	// 추의 무게를 저장할 배열.
int goo[7 + 10];	// 구슬의 무게를 저장할 배열.

char msg[] = { 'N','Y' };

int DFS(int cnt, int left, int right) {

	if (left == right) return 1;
	if (cnt > N)  return 0;

	//if (ABS(left = right) > presum[N] - presum[cnt - 1]) return 0;

	// 해당 구슬을 올리지 않는 경우.
	if (DFS(cnt + 1, left, right) == 1) return 1;

	// 왼쪽에 구슬을 올리는 경우.
	if (DFS(cnt + 1, left + wei[cnt], right) == 1) return 1;

	// 오른쪽에 구슬을 올리는 경우.
	if (DFS(cnt + 1, left, right + wei[cnt]) == 1) return 1;

	return 0;
}

void InputData() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &wei[i]);
	}
	scanf("%d", &G);
	for (int i = 1; i <= G; i++) {
		scanf("%d", &goo[i]);
	}
}

int main()
{
	InputData();
	for (int ti = 1; ti <= G; ti++) {
		printf("%c ", msg[DFS(1, goo[ti], 0)]);
	}
}

#endif

/********************************************/
// 더하기2
/********************************************/

#if 0

#include <stdio.h>

int N, K, idx;
int num[12 + 10];
int sum[5000];		// 합을 저장할 배열의 크기 계산 : (1 << 12) + 10 -> 1을 12번 shift 해준다. 

void Sort() {
	int i, j;
	for (i = 0; i < idx - 1; i++) {
		for (j = i + 1; j < idx; j++) {
			if (sum[i] < sum[j]) {
				int temp = sum[i];
				sum[i] = sum[j];
				sum[j] = temp;
			}
			if (sum[i] == sum[j]) {
				sum[j] = 0;
			}
		}
	}
}

void DFS(int depth, int total) {
	if (depth >= N) {
		sum[idx++] = total;
		return;
	}

	DFS(depth + 1, total + num[depth]);
	DFS(depth + 1, total);
}

void InputData() {
	scanf("%d %d", &N, &K);
	for (int i = 0; i < N; i++) {
		scanf("%d", &num[i]);
	}
}

int main()
{
	int ans = -1, zero = 0;

	InputData();
	DFS(0, 0);

	Sort();
	for (int i = 0; i < idx; i++) {
		if (sum[i] == 0) zero++;
		if (sum[i] == K) {
			ans = i - zero + 1;
			break;
		}
	}
	printf("%d\n", ans);
}

#endif