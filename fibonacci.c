#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int threadCount = 0; // Counter for tracking the number of threads created

// Thread function that calculates the Fibonacci sequence
void *fib_thread(void *ptr) {
	int n = (int)ptr; // Convert the parameter to an integer
	
	// Base case: n < 2
	if (n < 2) {
		printf("%d ", n); // Print the Fibonacci number
		return (void *) n; // Return the result
	}

	// Recursive case: n >= 2
	pthread_t thread1, thread2; // Thread variables for the two subproblems
	
	// Create thread1 to calculate fib(n-1)
	if (pthread_create(&thread1, NULL, fib_thread, (void *)(n - 1)) != 0) {
		fprintf(stderr, "Thread creation failed after %d threads.\n", threadCount);
		exit(1);
	}
	threadCount++; // Increment the thread count
	void *ptr1, *ptr2;
	pthread_join(thread1, &ptr1); // Wait for thread1 to finish
	
	// Create thread2 to calculate fib(n-2)
	if (pthread_create(&thread2, NULL, fib_thread, (void *)(n - 2)) != 0) {
		fprintf(stderr, "Thread creation failed after %d threads.\n", threadCount);
		exit(1);
	}
	threadCount++; // Increment the thread count
	
	pthread_join(thread2, &ptr2); // Wait for thread2 to finish
	int result = (int)ptr1 + (int)ptr2; // Calculate the Fibonacci result
	printf("%d ", result); // Print the result
	return (void *)result; // Return the result
}

int main(int argc, char *argv[]) {
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <n>\n", argv[0]);
		exit(1);
	}
	
	int n = atoi(argv[1]); // Convert the input argument to an integer
	
	pthread_t thread;
	
	// Create the main thread to calculate fib(n)
	if (pthread_create(&thread, NULL, fib_thread, (void *)n) != 0) {
		fprintf(stderr, "Thread creation failed.\n");
		exit(1);
	}
	threadCount++; // Increment the thread count
	
	void *ptr;
	pthread_join(thread, &ptr); // Wait for the main thread to finish
	
	// Print the Fibonacci result and the total thread count
	printf("\nfibonacci(%d): %d\n", n, (int)ptr);
	printf("Total thread count: %d\n", threadCount);
	
	exit(0);
}
