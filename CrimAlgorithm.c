#define _CRT_SECURE_NO_WARNINGS
#define SIZE 15
#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>


typedef struct graph {
	//graph* next;
	int time;
	int crim;
}graph;

graph col[8];
int cross_x[SIZE];
int cross_y[SIZE];
int candidates[4];
int fitness[4];
double sum;
double roulette[4];
int n;
double arg;
int aSum = 1;
int a[4];
int r;


void insertSort(double arr[], int n) {
    double key;
    int j;
    for (int i = 0; i < n; i++) {
        key = arr[i];
        for (j = i - 1; j >= 0 && arr[j] > key; j--)
            arr[j + 1] = arr[j];
        arr[j + 1] = key;
    }
    
}


int fitness_funct(int a, int x) {
	int result;
	result = (col[x].crim - (x * a + 75000)) * (col[x].crim - (x * a + 75000)); //유사해 a
	return result;
}

int selection(double arr[], int arr2[]) {
	int a = rand() % 100 + 1;
	if ((0 < a) && (a <= arr[0])) {
		return arr2[0];
	}
	else if ((arr[0] < a) && (a <= arr[0] + arr[1])) {
		return arr2[1];
	}
	else if ((arr[0] + arr[1] < a) && (a <= arr[0] + arr[1] + arr[2])) {
		return arr2[2];
	}
	else if ((arr[0] + arr[1] + arr[2] < a) && (a <= arr[0] + arr[1] + arr[2] + arr[3])) {
		return arr2[3];
	}
}

void binary(int x, int y) {
    int p = 0; int q = 0;
    int binary_x[SIZE]; int binary_y[SIZE];

    //2진수 변환
    while (x)
    {
        binary_x[p++] = x % 2;
        x /= 2;
    }
    while (y)
    {
        binary_y[q++] = y % 2;
        y /= 2;
    }
    

    //교차 연산
    for (int i = 0; i < SIZE; i++) {
        if (i > 6) {
            cross_x[i] = binary_x[i];
            cross_y[i] = binary_y[i];
        }
        else if (i <= 6) {
            cross_x[i] = binary_y[i];
            cross_y[i] = binary_x[i];
        }
    }
}


void mutate(int arr[]) {  //돌연변이 연산
    if (arr[8] == 0)arr[8] = 1;
    else if (arr[8] == 1)arr[8] = 0;
}

double Tfitness(int candidates[]) {
    double sum = 0;
    int x;
    for (int i = 0; i < 4; i++) {
        x = rand() % 8 + 1;
        fitness[i] = fitness_funct(r,x);
        sum += fitness_funct(r,x);
    }
    
    arg = sum / 4;
    printf("\n최적값: %0.2lf\n", arg); //마무리
    printf("유사해: %d", r);

    if (n == 1) return 0;


    for (int i = 0; i < 4; i++) {
        roulette[i] = round(fitness[i] / sum * 100);
    }

    return arg;
}

int decimal(int arr[]) { //2진수 -> 10진수 변환
    int dsum = 0;
    for (int i = 0; i < SIZE; i++) {
        if (arr[i] == 1) dsum += pow(2, i);
    }
    return dsum;
}

int main() {

	FILE* fp = fopen("crim.txt", "r");

	if (fp == NULL) {
		printf("에러");
		return 0;
	}

	for (int i = 0; i < 8; i++)
		fscanf(fp, "%d %d", &col[i].time, &col[i].crim);
	fclose(fp);

	for (int i = 0; i < 8; i++) {
		printf("%d-%d  ", col[i].time, col[i].crim);
	}
    //여기까지 파일 불러오기
    printf("\n");

    int count = 0; //회전 숫자
    double total_fitness[1000];


    sum = 0;
    srand(time(NULL));

    printf("회전 횟수 : ");
    scanf_s("%d", &n);
    for (int i = 0; i < 4; i++) {
        candidates[i] = rand() % 32767;
    }

    int temp = n;
    double* final_fitness =(double*) malloc(sizeof(double) * temp);

    while (n > 0) {

        printf("\n\n%d 번째\n", count + 1);

        for (int i = 0; i < 4; i++) {
            printf("후보해[%d]: %d ", i + 1, candidates[i]);
        }

        
        for (int i = 0; i < 4; i++) {
            a[i] = candidates[i];
        }
        insertSort(a, 4);
        r = a[3];
        

        Tfitness(candidates);
        final_fitness[count] = arg;

        if (n == 1) {
            printf("\n\nfinal_fitness: ");
            for (int i = 0; i < temp; i++)
                printf("[%d]-%.02lf  ", i, final_fitness[i]);
            break;
        }


        int x[4];
        for (int i = 0; i < 4; i++) {
            x[i] = selection(roulette, candidates);
        }


        int result[4];
        binary(x[0], x[1]);
        mutate(cross_x);
        mutate(cross_y);
        result[0] = decimal(cross_x);
        result[1] = decimal(cross_y);

        binary(x[2], x[3]);
        mutate(cross_x);
        mutate(cross_y);
        result[2] = decimal(cross_x);
        result[3] = decimal(cross_y);

        n--;
        count++;

        for (int i = 0; i < 4; i++) {
            candidates[i] = result[i];
            
        }
    }

    double arr[1000];
    for (int i = 0; i < temp; i++) {
        arr[i] = final_fitness[i];
    }

    printf("\n");
    insertSort(final_fitness, temp);
    
    for (int i = 0; i < temp; i++) {
        if (arr[i] == final_fitness[temp - 1]) {
            printf("%d번째 유사해", i + 1);
            return 0;
        }
            
    }

    return 0;
}