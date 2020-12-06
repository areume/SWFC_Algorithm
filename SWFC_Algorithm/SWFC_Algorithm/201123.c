#pragma warning(disable: 4996)
#pragma warning(disable: 4477)
#pragma warning(disable: 4313)

/********************************************/
// 단순정렬
/********************************************/

#if 0

#include <stdio.h>

int N;
int arr[5000 + 10];

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}

	for (int i = 0; i < N - 1; i++) {
		for (int j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		printf("%d ", arr[i]);
	}
}

#endif

/********************************************/
// 작은 수 4개 찾기
/********************************************/

#if 0

#include <stdio.h>

int N;
int arr[30000 + 10];

void Simple_Sort_forth()
{
	for (int i = 0; i < 4; i++) {
		for (int j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	Simple_Sort_forth();

	for (int i = 0; i < 4; i++) {
		printf("%d ", arr[i]);
	}
}

#endif

/********************************************/
// 모범생
/********************************************/

#if 0

#include <stdio.h>

typedef struct _st {
	int id, score;
}SCORE;

int N;
SCORE arr[30000 + 10];

void Sorting_score()
{
	for (int i = 0; i < 3; i++) {
		for (int j = i + 1; j <= N; j++) {
			if (arr[i].score < arr[j].score) {		// 두 개 조건 한 줄에 입력가능하다.
				SCORE temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
			if (arr[i].score == arr[j].score) {
				if (arr[i].id > arr[j].id) {
					SCORE temp = arr[i];
					arr[i] = arr[j];
					arr[j] = temp;
				}
			}
		}
	}
}

int main()
{
	int num = 1;
	scanf("%d", &N);
	for (int i = 1; i <= N; i++) {
		scanf("%d", &arr[i].score);
		arr[i].id = num++;
	}
	Sorting_score();

	for (int i = 0; i < 3; i++) {
		printf("%d ", arr[i].id);
	}
}

#endif

/********************************************/
// 100만들기
/********************************************/

#if 0

#include <stdio.h>

int arr[10];
int x, y;

void Sort()
{
	for (int i = 0; i < 9 - 1; i++) {
		for (int j = i + 1; j < 9; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}


void Calc(int sum) {
	for (x = 0; x < 8; x++) {
		for (y = x + 1; y < 9; y++) {
			if ((arr[x] + arr[y]) == sum) return;
		}
	}
}

int main()
{
	int total = 0, sum = 0;

	for (int t = 0; t < 9; t++) {
		scanf("%d", &arr[t]);
		total += arr[t];
	}
	sum = total - 100;

	Sort();
	Calc(sum);
	for (int t = 0; t < 9; t++) {
		if (t == x || t == y) continue;
		printf("%d\n", arr[t]);
	}
}

#endif

/********************************************/
// 최소 비용으로 포장 다시 하기
/********************************************/

#if 0

#include <stdio.h>

int N;
int arr[5000 + 10];

void Sorting(int start)
{
	for (int i = start; i < start + 2; i++) {
		for (int j = i + 1; j < N; j++) {
			if (arr[i] > arr[j]) {
				int temp = arr[i];
				arr[i] = arr[j];
				arr[j] = temp;
			}
		}
	}
}

int Calc()
{
	int cost = 0;

	for (int i = 0; i < N - 1; i++) {
		Sorting(i);
		arr[i + 1] += arr[i];
		cost += arr[i + 1];
	}
	return cost;
}

int main()
{
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d", &arr[i]);
	}
	printf("%d\n", Calc());
}

#endif

/********************************************/
// 색종이(초)
/********************************************/

#if 0

#include <stdio.h>

int N;
int map[100 + 10][100 + 10];

int main()
{
	int W, H, cnt = 0;
	scanf("%d", &N);
	for (int t = 0; t < N; t++) {
		scanf("%d %d", &W, &H);

		for (int i = H; i < H + 10; i++) {
			for (int j = W; j < W + 10; j++) {
				map[i][j] = 1;
			}
		}
	}

	for (int i = 1; i <= 100; i++) {
		for (int j = 1; j <= 100; j++) {
			if (map[i][j] == 1) cnt++;
		}
	}
	printf("%d\n", cnt);
}

#endif

/********************************************/
// 색종이(중)
/********************************************/

#if 0

#include <stdio.h>

int N;
int area;
int x[100 + 10], y[100 + 10];
int map[100 + 10][100 + 10];

int Count_zero(int i, int j)
{
	int cnt = 0;
	int dr[] = { 1,-1,0,0 };
	int dc[] = { 0,0,-1,1 };

	for (int k = 0; k < 4; k++) {
		if (map[i + dr[k]][j + dc[k]] == 0) cnt++;
	}
	return cnt;
}

int main()
{
	// 입력받는 부분
	scanf("%d", &N);
	for (int i = 0; i < N; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}

	// 여기서부터 작성
	for (int k = 0; k < N; k++) {
		for (int i = y[k]; i < y[k] + 10; i++) {
			for (int j = x[k]; j < x[k] + 10; j++) {
				map[i][j] = 1;
			}
		}
	}

	for (int i = 1; i < 100; i++) {
		for (int j = 1; j < 100; j++) {
			if (map[i][j] == 1) area += Count_zero(i, j);
		}
	}
	printf("%d", area);
}

#endif

/********************************************/
// 같은 모양 찾기 simple
/********************************************/

#if 0

#include <stdio.h>

int M, P;
char map[100 + 10][100 + 10];
char pat[100 + 10][100 + 10];


int Judge(int x, int y)
{
	for (int i = 0; i < P; i++) {
		for (int j = 0; j < P; j++) {
			if (map[x + i][y + j] != pat[i][j]) return 0;
		}
	}
	return 1;
}

int Solve()
{
	int ret = 0;

	for (int i = 0; i <= M - P; i++) {
		for (int j = 0; j <= M - P; j++) {
			if (Judge(i, j) == 1) ret++;
		}
	}
	return ret;
}

int main()
{
	scanf("%d", &M);
	for (int i = 0; i < M; i++) {
		for (int j = 0; j < M; j++) {
			scanf("%1d", &map[i][j]);
		}
	}
	scanf("%d", &P);
	for (int i = 0; i < P; i++) {
		for (int j = 0; j < P; j++) {
			scanf("%1d", &pat[i][j]);
		}
	}

	printf("%d", Solve());
}

#endif

/********************************************/
// 가장 많은 알파벳은?
/********************************************/

#if 0

#include <stdio.h>

char word[35];
int alpha[26];

int main()
{
	int index, max_i;
	scanf("%s", &word);

	for (int i = 0; i < 35; i++) {
		if (word[i] == '\0') break;
		if (word[i] >= 'a' && word[i] <= 'z') {
			index = word[i] - 'a';
			alpha[index]++;
		}
	}

	// 최대값 찾기
	max_i = 0;
	for (int i = 1; i < 26; i++) {
		if (alpha[i] > alpha[max_i]) max_i = i;
	}

	printf("%c\n", max_i + 97);
}

#endif