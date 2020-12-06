#pragma warning(disable: 4996)
#pragma warning(disable: 4477)
#pragma warning(disable: 4313)

/********************************************/
// �̼����� ��ȸ
/********************************************/

#if 0

#include <stdio.h>

int N, normCnt, specCnt;
char map[100 + 10][100 + 10];
char cpy[100 + 10][100 + 10];

typedef struct _st {
	int r, c;
}POS;

POS queue[100 * 100 + 10];
int wp, rp;

int dr[] = { -1,1,0,0 };
int dc[] = { 0,0,-1,1 };

void Enqueue(int r, int c) {
	queue[wp].r = r; queue[wp].c = c; wp++;
}

POS Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

void BFS(int i, int j, char color) {
	Enqueue(i, j);
	cpy[i][j] = '-';

	while (!Empty()) {
		POS cur = Dequeue();

		for (int i = 0; i < 4; i++) {
			int nr = cur.r + dr[i];
			int nc = cur.c + dc[i];

			if (nr < 0 || nr >= N || nc < 0 || nc >= N) continue;
			if (cpy[nr][nc] == '-') continue;

			if (cpy[nr][nc] == color) {
				Enqueue(nr, nc);
				cpy[nr][nc] = '-';
			}
		}
	}
}

void InputData() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%s", &map[i][0]);
	}
}

void Copy(int flag) {
	if (flag == 0) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				cpy[i][j] = map[i][j];
			}
		}
	}
	if (flag == 1) {
		for (int i = 0; i < N; i++) {
			for (int j = 0; j < N; j++) {
				if (map[i][j] == 'G') {
					cpy[i][j] = 'R';
					continue;
				}
				cpy[i][j] = map[i][j];
			}
		}
	}
}

int main()
{
	InputData();

	// �Ϲ�
	Copy(0);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (cpy[i][j] != '-') {
				wp = rp = 0;
				BFS(i, j, cpy[i][j]);
				normCnt++;
			}
		}
	}

	// ���ϻ���
	Copy(1);
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (cpy[i][j] != '-') {
				wp = rp = 0;
				BFS(i, j, cpy[i][j]);
				specCnt++;
			}
		}
	}
	printf("%d %d", normCnt, specCnt);
}

#endif

/********************************************/
// ö���ձ�
/********************************************/

#if 0

#include <stdio.h>

int N, M, K;				// ���� ��, ö���� ��, �߰� ���� ö�� ��.
int map[50 + 10][50 + 10];	// ���� ���θ� ǥ���� �迭.
int vis[50 + 10];			// �湮 ���θ� ǥ���� �迭.

int group[50 + 10];
int idx;

int sol;

struct _st {
	int station;
};

struct _st queue[50 * 50 + 10];
int rp, wp;

void Enqueue(int station) {
	queue[wp++].station = station;
}

struct _st Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

int BFS(int row) {
	int cnt = 0;
	rp = wp = 0;

	Enqueue(row);
	vis[row] = 1;
	cnt++;

	while (!Empty()) {
		struct _st cur = Dequeue();

		for (int k = 1; k <= N; k++) {
			if (map[cur.station][k] == 0) continue;	// ������ �ȵǾ� ������ �н�.
			if (vis[k] == 1) continue;				// �̹� �湮�� ���̸� �н�.

			Enqueue(k);
			vis[k] = 1;
			cnt++;
		}
	}
	return cnt;
}

void Sort() {
	for (int i = 0; i <= K; i++) {
		for (int j = i + 1; j < idx; j++) {
			if (group[i] < group[j]) {
				int temp = group[i];
				group[i] = group[j];
				group[j] = temp;
			}
		}
	}
}

void InputData() {
	int r, c;
	scanf("%d %d %d", &N, &M, &K);
	for (int t = 0; t < M; t++) {
		scanf("%d %d", &r, &c);
		map[r][c] = map[c][r] = 1;
	}
}

int main()
{
	InputData();
	for (int i = 1; i <= N; i++) {
		if (vis[i] != 1) {
			group[idx++] = BFS(i);
		}
	}

	Sort();
	for (int j = 0; j <= K; j++) {
		sol += group[j];
	}
	printf("%d", sol);
	return 0;
}

#endif

/********************************************/
// 1~n������ ��
/********************************************/

// ���� �����÷ο찡 �߻��ϴ� ���
// ������Ʈ �Ӽ� > ��Ŀ > �ý��� > ���� ���� ũ�⸦ [10,000,000]���� ����.
// ����� ��忡�� ����İ� ȣ�� ���� â�� Ȱ���Ѵ�.
// ȣ�� ���� ��Ŭ���ؼ� �Ű����� �� ������� �������ش�.

#if 0

#include <stdio.h>

int N, sol;

int add(int num) {
	int result = 0;
	if (num == 1) return 1;
	result = add(num - 1);
	return num + result;
}

int main()
{
	scanf("%d", &N);
	sol = add(N);
	printf("%d", sol);
}

#endif

// memoization

#if 0

#include <stdio.h>

int N, sol;

int sum[10000 + 10];

int add(int num) {
	int result = 0;

	if (num == 1) return 1;
	if (sum[num] != 0) return sum[num];

	result = num + add(num - 1);
	sum[num] = result;

	return result;
}

int main()
{
	scanf("%d", &N);
	sol = add(N);
	printf("%d", sol);
}

#endif

/********************************************/
// �Ǻ���ġ ����
/********************************************/

#if 0

#include <stdio.h>

int N, sol;

int Fibo(int num) {
	if (num <= 2) return 1;

	return Fibo(num - 1) + Fibo(num - 2);
}

int main()
{
	scanf("%d", &N);
	sol = Fibo(N);
	printf("%d", sol);
}

#endif

// memoization

#if 0

#include <stdio.h>

int N, sol;
int arr[50];

int Fibo(int num) {
	int result = 0;

	if (arr[num] != 0) return arr[num];
	result = Fibo(num - 1) + Fibo(num - 2);
	arr[num] = result;

	return result;
}

int main()
{
	arr[1] = arr[2] = 1;

	scanf("%d", &N);
	sol = Fibo(N);
	printf("%d", sol);
}

#endif

/********************************************/
// ���ϱ�
/********************************************/

// �� �ڵ� - codexpert���� Runtime Error

#if 0

#include <stdio.h>

int N, K;
int number[20 + 10];
char *answer[] = { "NO","YES" };

int DFS(int index, int sum) {

	if (sum == 0) return 1;
	if (sum < 0) return 0;
	if (index > K) return 0;

	if (DFS(index + 1, sum - number[index]) == 1) return 1;		// ���			
	if (DFS(index + 1, sum) == 1) return 1;						// �̻��

	return 0;
}

int main()
{
	int ti, T;
	scanf("%d", &T);
	for (ti = 0; ti < T; ti++) {
		scanf("%d %d", &N, &K);
		for (int i = 0; i < N; i++) {
			scanf("%d", &number[i]);
		}
		printf("%s\n", answer[DFS(0, K)]);
	}
	return 0;
}

#endif

// ����� �ڵ�

#if 0

#include <stdio.h>

int N, K;
int number[20 + 10];
int presum[20 + 10];

int DFS(int index, int sum)
{
	if (sum > presum[N] - presum[index - 1]) return 0; // ���� ��� ��� ���ص� �ȵ�, ����
	if (sum == 0) return 1;		// ����
	if (sum < 0) return 0;		// ����
	if (index > N) return 0;	// ��� ��� �� �������, ����

	if (DFS(index + 1, sum - number[index]) == 1) return 1; // n��° ��� ���
	if (DFS(index + 1, sum) == 1) return 1;					// n��° ��� �̻��

	return 0; // ����
}

int solve(void) {
	int ans;
	for (int i = 1; i <= N; i++) {
		presum[i] = presum[i - 1] + number[i];
	}
	ans = DFS(1, K);
	return ans;
}

void InputData(void) {
	scanf("%d %d", &N, &K);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &number[i]);
	}
}

char *msg[] = { "NO", "YES" };

int main(void)
{
	int T, i, sol;

	scanf("%d", &T);
	for (i = 1; i <= T; i++) {
		InputData();
		sol = solve();
		printf("%s\n", msg[sol]);
	}
	return 0;
}

#endif

/********************************************/
// å����
/********************************************/

#if 0

#include <stdio.h>

int N, B;				// ���� ��, å������ ����,
int height[20 + 10];	// ���� Ű�� ������ �迭.
int presum[20 + 10];	// ���� ���� ������ �迭.

int ans = 100000000;		// �ּҰ��̿��� �ϹǷ� �ſ� ū ������ �ʱ�ȭ.

void DFS(int index, int sum) {

	if (presum[N] - presum[index - 1] + sum < B) return;	// ���� �� �� ���ص� B �ȳ����� return.

	if (index > N) {							// ��� ��츦 Ž���� ���, ans ���� ����. -> ����.
		if (sum >= B) {							// �հ谡 �� ���� ��쿡�� ����.
			if (ans > sum - B) ans = sum - B;	// ans �� ����.
		}
		return;									// �������ǿ����� �������� �ݵ�� return.
	}

	// �� ���� ���� ���� �� ���ٰ� �ǴܵǴ� ���. ���� �ּҰ��� B�� ���� sum�� index ���� ���� Ű �պ��� ũ�� ��� ȣ��.
	if (sum + height[index] < B + ans) DFS(index + 1, sum + height[index]);
	DFS(index + 1, sum);
}

void InputData() {
	scanf("%d %d", &N, &B);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &height[i]);
	}

	presum[1] = height[1];
	for (int i = 2; i <= N; i++) {
		presum[i] = height[i] + presum[i - 1];
	}
}

int main()
{
	int ti, T;
	scanf("%d", &T);
	for (ti = 1; ti <= T; ti++) {
		InputData();
		ans = 100000000;
		DFS(1, 0);
		printf("%d\n", ans);
	}
}

#endif

/********************************************/
// �ǹ������(BASIC2)
/********************************************/

#if 0

#include <stdio.h>

int N;						// �ǹ��� ��
int cost[10 + 5][10 + 5];	// ����� ������ �迭
int visited[10 + 5];		// ��� �湮 ���θ� ������ ����

int ans = 9999;

void DFS(int cnt, int total) {

	if (total > ans) return;			// total�� �̹� �ּ� ����� ���� ��� return 
	if (cnt > N) {						// cnt�� 4���� ũ�� ans ����
		if (total < ans) ans = total;
		return;
	}

	for (int i = 1; i <= N; i++) {
		if (visited[i] == 1) continue;	// �ǹ��� �̹� ������ ��ġ�̸� ����ġ��.

		visited[i] = 1;
		DFS(cnt + 1, total + cost[cnt][i]);
		visited[i] = 0;
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
	DFS(1, 0);
	printf("%d\n", ans);
}

#endif