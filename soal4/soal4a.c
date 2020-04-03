//Referensi ada di bawah
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define M 4
#define K 2
#define N 5
#define NUM_THREADS M * N

/* Global variables for threads to share */
int A[M][K] = {{1, 1}, {1, 1}, {1, 1}, {1, 1}};
int B[K][N] = {{2, 2, 2, 2, 2}, {2, 2, 2, 2, 2}};
int C[M][N];

/* Structure for passing data to threads */
struct v
{
	int i; /* row */
	int j; /* column */
};

void *runner(void *ptr); /* the thread */

int main(int argc, char **argv)
{
	int i, j;
	int thread_counter = 0;
	
	pthread_t workers[NUM_THREADS];
	
	/* We have to create M * N worker threads */
	for (i = 0; i < M; i++)
	{
		for (j = 0; j < N; j++) 
		{
			struct v *data = (struct v *) malloc(sizeof(struct v));
			data->i = i;
			data->j = j;
			/* Now we will create the thread passing it data as a paramater*/
			pthread_create(&workers[thread_counter], NULL, runner, data);
			pthread_join(workers[thread_counter], NULL);
			thread_counter++;
		}
	}
	
	/* Waiting for threads to complete */
	for (i = 0; i < NUM_THREADS; i++)
	{
	    pthread_join(workers[i], NULL);
	}
	
	for(i = 0; i < M; i++)
	{ 
		for(j = 0; j < N; j++)
		{ 
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}
	return 0;
}

void *runner(void *ptr)
{	
	/* Casting paramater to struct v pointer */
	struct v *data = ptr;
	int i, sum = 0;
	
	for(i = 0; i < K; i++)
	{	
		sum += A[data->i][i] * B[i][data->j];
	}
	
	C[data->i][data->j] = sum;
	pthread_exit(0);
}

/*REFERENCES : 
https://gist.github.com/ozanyildiz/1863593
https://www.geeksforgeeks.org/multiplication-of-matrix-using-threads/
https://github.com/VYPRATAMA009/sisop-modul-3#26-shared-memory */
