#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int threadCount = 0;

//thread converts ptr to int, multiplies by 10 and returns it.
void *fib_thread( void *ptr ){

	int n = (int)ptr;
	
	if (n < 2) {
		printf("%d ", n);
		return (void *) n;
	}

	// n >= 2: fib(N) = fib(n-1) + fib(n-2)
	// create 2 threads
	pthread_t thread1, thread2;

	if (pthread_create(&thread1, NULL, fib_thread, (void *) (n-1)) != 0){
		fprintf(stderr, "Thread creation failed after %d threads.\n", threadCount);
		exit(1);
	}
	threadCount++;
	void *ptr1, *ptr2;
	pthread_join(thread1, &ptr1);	
	
	if (pthread_create(&thread2, NULL, fib_thread, (void *) (n-2)) != 0){
		fprintf(stderr, "Thread creation failed after %d threads.\n", threadCount);
		exit(1);
	}
	threadCount++;
	
	pthread_join(thread2, &ptr2);	
	int result = (int) ptr1 + (int) ptr2;
	printf("%d ", result);
	return (void *) result;
}

int main(int argc, char *argv[]){
	int n = atoi(argv[1]); //n to compute fib(n)
	
	pthread_t thread;
	
	if (pthread_create(&thread, NULL, fib_thread, (void *) n)){
		fprintf(stderr, "Thread creation failed.\n");
		exit(1);
	}
	threadCount++;

	void *ptr;
	pthread_join(thread, &ptr);
	printf("\nfibonacci(%d): %d\n", n, (int) ptr);
	printf("Total thread count: %d\n", threadCount);
	
	exit(0);
}
