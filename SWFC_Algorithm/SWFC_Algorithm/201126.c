#pragma warning(disable: 4996)
#pragma warning(disable: 4477)
#pragma warning(disable: 4313)

/********************************************/
// �׷��� ĥ�ϱ�
/********************************************/

#if 0

#include <stdio.h>

int N, M;
int connect[12 + 5][12 + 5];
int noColor[12 + 5];

int Check(int node, int color) {
	for (int i = 1; i < node; i++) {			// node�� ����� �ٸ� ������ ��� �˻��ؼ�
		if (connect[node][i] == 1) {			// ����Ǿ��ִµ�
			if (noColor[i] == color) return 0;	// ���� ���̸� �ش� ���� �ش� ��忡 ��ĥ �Ұ���.
		}
	}
	return 1;
}

int DFS(int node) {
	if (node > N) return 1;					// node��ȣ�� N���� ũ�� ������ ���� ĥ�� �� -> ����.

	for (int i = 1; i <= M; i++) {			// i�� ĥ�� ������ ��ȣ�� �ǹ��Ѵ�.
		if (Check(node, i) == 0) continue;	// �ش� ��忡 �ش� ���� ĥ�� �� �ִ��� Ȯ���Ѵ�.

		noColor[node] = i;
		if (DFS(node + 1) == 1) return 1;		// DFS�� ���ϰ��� ������ if���� ������ش�.
		noColor[node] = 0;
	}
	return 0;								// DFS�� ������ Ž������ ���� ����.
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
// �ع��� ��ȯȸ��
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
		if (vist[i] == 1) continue;					// �̹� �湮�� ���� �湮�� �� ����.
		if (cost[city][i] == 0) continue;			// ����� 0�� ���� �湮�� �� ����.
		if (total + cost[city][i] > Min) continue;	// �̹� �ּҰ��� �Ѿ�� ���̻� Ž������ �ʾƵ� �ȴ�.

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
// ������ - ���̵�� ����
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
			if (numb[i] < numb[j]) {		// �������� ����
				int temp = numb[i];
				numb[i] = numb[j];
				numb[j] = temp;
			}
			if (numb[i] == numb[j]) {		// �ߺ� ����
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
	for (int turn = 0; turn < len; turn++) {					// turn�� ȸ�� ��.
		for (int i = turn; i < turn + N; i += len) {			// i�� �� ���ڿ��� ���� ��ġ.
			num = 0;
			for (int j = 0; j < len; j++) {				// j�� �� ���ڿ��� ���� ����.
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
// ������ - BFS
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
// �������� - DFS
/********************************************/

#if 0

#include <stdio.h>

int N, G;			// ���� ����, ������ ����.
int wei[12 + 10];	// ���� ���Ը� ������ �迭.
int goo[7 + 10];	// ������ ���Ը� ������ �迭.

char msg[] = { 'N','Y' };

int DFS(int cnt, int left, int right) {

	if (left == right) return 1;
	if (cnt > N)  return 0;

	//if (ABS(left = right) > presum[N] - presum[cnt - 1]) return 0;

	// �ش� ������ �ø��� �ʴ� ���.
	if (DFS(cnt + 1, left, right) == 1) return 1;

	// ���ʿ� ������ �ø��� ���.
	if (DFS(cnt + 1, left + wei[cnt], right) == 1) return 1;

	// �����ʿ� ������ �ø��� ���.
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
// ���ϱ�2
/********************************************/

#if 0

#include <stdio.h>

int N, K, idx;
int num[12 + 10];
int sum[5000];		// ���� ������ �迭�� ũ�� ��� : (1 << 12) + 10 -> 1�� 12�� shift ���ش�. 

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