"# GenetisAlgorithm을 이용한 회귀"


# 유전 알고리즘
BookAlgorithm을 기준으로 설명

## 동작 방식
1. 초기 염색체의 집합 생성
2. 초기 염색체들에 대한 적합도 계산
3. 현재 염색체들로 부터 자손 생성  
   자손-> 염색체들을 교차 및 돌연변이 연산
4. 생성된 자손들의 적합도 계산
5. 종료 조건 판별  
   (요기서는 회전 횟수) 
6. 종료 조건이 거짓인 경우 다시 1번으로

## 변수
cnadidates[]: 염색체들  
cross_x, cross_y: 2개의 염색체를 교차 연산한 2진수 배열
fitness[]: 염색체들을 함수에 넣을때 나오는 값 (f(x))  
roulette[]: f(x)에 대해 교차연산에서 뽑힐 확률  
n: 종료 조건 (회전 횟수로 n==1까지 연산)  
arg: 유사값으로 BookAlgorithm에서는 평균값으로 유사값을 구함  
final_fitness[]: 순서별로 적합도를 저장해둔 배열로 마지막에 정렬을 통해 적합도가 가장 큰 적합도를 찾기 위해 마듦 


## 실행별 함수
* 교차 연산  
binary(int x, int y): 10진수 x, y를 2진수로 바꾸고 특정 n번째 자리수(2^n의 자리수)부터 x, y를 바꿔줌
* 돌연변이 연산  
mutate(int arr[]): 2진수로 표현되어 있는 수를 n번째 자리(arr[n-1])의 수를 0을 1로 1을 0으로 바꿔줌
* 최적값 연산   
fitness_funct(int x): x값을 집어 넣은 일반식의 값을 출력  
-> 지금부터 f(x)로 표현  
Tfitness(int arr[]): arr는 염색체들의 배열로 f(x)에 대입하여 평균값을 구함. 이 평균값은 최적값.  
최적값이 가장 큰 염색체들을 가지고 유사값 구함.  
* 염색체 뽑기  
selection(double arr[], int arr2[]): arr[]는 염색체들의 확률이 정장되어 있고, arr2[]는 확률별로 나올 염색체가 저장됨. 출력은 arr2[]

## 유전 알고리즘 순서도
![순서도](data:image/png;base64,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)




# 시간대 별 총 범죄 발생 수
## 그래프 설명
![시간-범죄수 그래프]()
* 그래프의 x축  (독립 변수)
1-> 00시 00분 부터 02시 59분  
2-> 03시 00분 부터 05시 59분  
3-> 06시 00분 부터 08시 59분  
4-> 09시 00분 부터 11시 59분  
5-> 12시 00분 부터 14시 59분  
6-> 15시 00분 부터 27시 59분  
7-> 18시 00분 부터 20시 59분  
8-> 21시 00분 부터 23시 59분  

* 그래프의 y축 (종속 변수)  
범죄 발생 수

## 0~2 돌연변이 그림
(출력은 제대로 되나 염색체 뽑을때 랜덤 수가 너무 적었음)  
돌연변이를 0~2로 다르게 출력 했음.  
* 0돌연변이 연산: 유사값으로 2번째 회전의 값이 나왔음  
* 1돌연변이 연산: 유사값으로 3번째 회전의 값이 나왔음  
* 2돌연변이 연산: 유사값으로 3번째 회전의 값이 나왔음   
-> 어느 돌연변이 연산이 더 효율적인지 알 수 없음


#### BookAlgorithm이랑 CrimAlgorithm의 다른 점
* 유사값(모수값)을 평균 -> 최댓값 으로 변경
* fitness_funct[arr] -> fitness_funct[x,arr]: 유사값 말고도 오류값을 계산할 x를 추가함.  
* insertSort(int arr[], int n) 추가: 선택 정렬로 모수값과 모수값을 구하기 위한 가장 높은 최적값을 구하기 위해 추가
* 에러값을 줄이기 위해 염색체의 수를 32->32767로 변경
* 그래프에 대한 값들을 불러오기 위해 txt파일을 불러옴
* 불러온 파일을 구조체 배열에 저장




# 아쉬운 점
노트북에 과부하가 와서 많은 회전을 시키지 못한 점

