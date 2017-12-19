#include<stdio.h>
#include<Windows.h>
#include<time.h>


int memo[100];
int fibo(int n){
	if(n <= 2) return 1;
	if(memo[n] != 0) return memo[n];
	return memo[n] = fibo(n-2) + fibo(n-1);
}

//Bottom-up
int fiboIter(int n){
	int prevPrev = 1;
	int prev = 1;
	int curr;
	for(int i=0;i<n-2;i++){
		curr = prevPrev + prev;
		prevPrev = prev;
		prev = curr;
	}
	return curr;
}

int main(){
	int start = time(NULL);
	printf("%d\n", fibo(200) );
	int finish = time(NULL);
	printf("%d\n", finish - start);
	system("PAUSE");
	return 0;
}