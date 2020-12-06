#pragma warning(disable: 4996)
#pragma warning(disable: 4477)
#pragma warning(disable: 4313)

/********************************************/
// 스트라이크볼 - 아이디어
/********************************************/

#if 0

#include <stdio.h>

int N;
int A[5 + 5];
int S[5 + 5];
int B[5 + 5];

int sol;

int Check(int X, int A, int S, int B) {
	int x[5], a[5];
	int sp = 0, bp = 0;

	// 배열로 만들기, 일의 자리부터 채워진다.
	for (int i = 0; i < 5; i++) {
		x[i] = X % 10;
		a[i] = A % 10;

		X /= 10; A /= 10;
	}

	// 스트라이크 판정
	for (int i = 0; i < 5; i++) {
		if (a[i] == x[i]) {
			a[i] = x[i] = -1;
			sp++;
		}
	}
	if (sp != S) return 0;

	// 볼 판정
	for (int i = 0; i < 5; i++) {
		if (a[i] == -1) continue;
		for (int j = 0; j < 5; j++) {
			if (x[j] == -1) continue;
			if (a[i] == x[j] && i != j) {
				x[j] = -1;
				bp++;
				break;
			}
		}
	}
	if (bp != B) return 0;

	return 1;
}

void Solve() {
	int i, X;
	for (X = 10000; X < 100000; X++) {
		for (i = 1; i <= N; i++) {
			if (Check(X, A[i], S[i], B[i]) == 0) break;
		}
		if (i == N + 1) sol++;
	}
}

void InputData() {
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &A[i], &S[i], &B[i]);
	}
}

int main()
{
	InputData();
	Solve();
	printf("%d\n", sol);
	return 0;
}

#endif


/********************************************/
// 색상혼합 - DFS
/********************************************/

#if 0

#include <stdio.h>

int N;
int SR, SG, SB;
int R[15 + 10];
int G[15 + 10];
int B[15 + 10];

int sol = 0x7fffffff;


int DFS(int pos, int cnt, int sum_r, int sum_g, int sum_b) {
	if (cnt >= sol) return;

	if (pos > N) {
		if (cnt > 0) {
			if (sum_r / cnt == SR && sum_g / cnt == SG && sum_b / cnt == SB) {
				if (cnt < sol) {
					sol = cnt;
				}
			}
		}
		return;
	}

	DFS(pos + 1, cnt + 1, sum_r + R[pos], sum_g + G[pos], sum_b + B[pos]);
	DFS(pos + 1, cnt, sum_r, sum_g, sum_b);
}

void InputData() {
	scanf("%d %d %d", &SR, &SG, &SB);
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d %d %d", &R[i], &G[i], &B[i]);
	}
}

int main()
{
	InputData();
	DFS(1, 0, 0, 0, 0);	// 1번 색부터 시작

	if (sol == 0x7fffffff) printf("-1");
	else printf("%d\n", sol);

	return 0;
}

#endif