#pragma warning(disable: 4996)
#pragma warning(disable: 4477)
#pragma warning(disable: 4313)

/***************************************************/
// 1번 - 지능형 기차 - 아이디어
/***************************************************/

#if 0

#include <stdio.h>

int in[4 + 10];
int out[4 + 10];

void InputData() {
	for (int i = 1; i <= 4; i++) {
		scanf("%d %d", &out[i], &in[i]);
	}
}

int main() {
	int Max = 0;
	int tot = 0;

	InputData();
	for (int i = 1; i <= 4; i++) {
		tot = tot + in[i] - out[i];

		if (tot > Max) Max = tot;
	}
	printf("%d\n", Max);

	return 0;
}

#endif

/***************************************************/
// 2번 - 배열 정리 - 아이디어
/***************************************************/

#if 0

#include <stdio.h>

int X, Y;
int arr[1000 + 10][1000 + 10];
int brr[1000 + 10][1000 + 10];

void Solve(int i, int j, int cnt) {
	int ccnt = cnt;
	for (int k = j + 1; k < X; k++) {
		if (arr[i][k] == 0) break;
		if (arr[i][k] == 1) {
			arr[i][k] = ++ccnt;
		}
	}
}

void InputData() {
	scanf("%d %d", &Y, &X);
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			scanf("%d", &arr[i][j]);
		}
	}
}

int main() {

	InputData();
	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			if (arr[i][j] == 1) {
				Solve(i, j, 1);
			}
		}
	}

	for (int i = 0; i < Y; i++) {
		for (int j = 0; j < X; j++) {
			printf("%d ", arr[i][j]);
		}
		printf("\n");
	}
	return 0;
}

#endif

/***************************************************/
// 3번 - 도약 - 아이디어
/***************************************************/

#if 0

#include <stdio.h>

int N;
int leaf[1000 + 10];

int sol;

void InputData() {
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &leaf[i]);
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (leaf[i] > leaf[j]) {
				int temp = leaf[i];
				leaf[i] = leaf[j];
				leaf[j] = temp;
			}
		}
	}
}

int main() {

	InputData();

	for (int i = 0; i < N - 2; i++) {
		for (int j = i + 1; j < N - 1; j++) {
			for (int k = j + 1; k < N; k++) {
				int one = leaf[j] - leaf[i];
				int two = leaf[k] - leaf[j];

				if (one <= two && (2 * one) >= two) sol++;
			}
		}
	}
	printf("%d\n", sol);
	return 0;
}

#endif

/***************************************************/
// 4번 - 연결된 세포 - Flood Fill
/***************************************************/

#if 0

#include <stdio.h>

int M, N;
int map[10 + 10][10 + 10];

int cnt, MAX;

typedef struct _st {
	int r, c, cnt;
}Element;

Element queue[10 * 10 + 10];
int rp, wp;

int dr[] = { -1,-1,-1,0,1,1,1,0 };
int dc[] = { -1,0,1,1,1,0,-1,-1 };

void Enqueue(int r, int c) {
	queue[wp].r = r; queue[wp].c = c;
	wp++;
}

Element Dequeue() {
	return queue[rp++];
}

int Empty() {
	return rp == wp;
}

int BFS(int r, int c) {
	Element cur;

	Enqueue(r, c);
	map[r][c] = -1;
	cnt++;

	while (!Empty()) {
		cur = Dequeue();

		for (int k = 0; k < 8; k++) {
			int nr = cur.r + dr[k];
			int nc = cur.c + dc[k];

			if (nr<1 || nr>M || nc<1 || nc>N) continue;
			if (map[nr][nc] == 1) {

				Enqueue(nr, nc);
				map[nr][nc] = -1;
				cnt++;
			}
		}
	}
	return cnt;
}

void InputData() {
	scanf("%d", &M);
	scanf("%d", &N);
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			scanf("%d", &map[i][j]);
		}
	}
}

int main() {
	int ans = -1;

	InputData();
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= N; j++) {
			if (map[i][j] == 1) {
				cnt = 0;
				ans = BFS(i, j);

				if (ans > MAX) MAX = ans;
			}
		}
	}
	printf("%d\n", MAX);
	return 0;
}

#endif

/***************************************************/
// 5번 - 농장탈출 - DFS - ★못 풀어따★
/***************************************************/

#if 0

#include <stdio.h>

int N, MAX = -1;
int weight[20 + 10];

int Check(long long total, int add) {
	for (;;) {
		if (total == 0 || add == 0) return 1;
		int hap = (total % 10) + (add % 10);
		if (hap >= 10) return 0;
		total /= 10; add /= 10;
	}
	return 1;
}

void DFS(int index, int count, long long total) {
	int ans;
	if (index > N) {
		if (count > MAX) MAX = count;
		return;
	}

	// 소를 더했을 때 자리올림 발생하면 더하지 않고 진행.
	ans = Check(total, weight[index]);
	if (ans == 0) DFS(index + 1, count, total);
	if (ans == 1) DFS(index + 1, count + 1, total + weight[index]);
}

void InputData() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &weight[i]);
	}
}

int main() {
	InputData();
	DFS(1, 0, 0);
	printf("%d\n", MAX);
	return 0;
}

#endif

// 정식 코드

#if 0

#include <iostream>
using namespace std;

int N, W[20 + 10], max_num = 0;

int check(int a, int b) {
	int i = 0;
	for (;;) {
		if (a == 0 && b == 0) break;
		if (a % 10 + b % 10 >= 10)
			return 1;   //자리올림 발생
		a /= 10;
		b /= 10;
	}
	return 0;   //자리올림 없이 끝까지 가면 0 리턴
}

void DFS(int n, int num, int sum)   //n번째 index 체크, 현재까지 탑승한 num마리 소, 현재까지 합산한 체중 합계 sum
{
	if (n == N) {
		if (max_num < num) max_num = num;
		//cout << sum << endl;
		return;
	}

	if (check(sum, W[n]) == 0)
		DFS(n + 1, num + 1, sum + W[n]);    //n번째 탑승 시킴

	DFS(n + 1, num, sum);           //n번째 탑승 안시킴

	return;
}

int main() {
	cin >> N;
	for (int i = 0; i < N; i++)
		cin >> W[i];

	DFS(0, 0, 0);

	cout << max_num << endl;

	return 0;
}


#endif