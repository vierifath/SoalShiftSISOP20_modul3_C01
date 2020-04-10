#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);
pthread_t thread1;

void *factorial();
unsigned long long output[4][5];


void main()
{
    key_t key = 1234;
    int (*C)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    C = shmat(shmid, 0, 0);

	// menampilkan matrix
    int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	
	int newthread;
	newthread = pthread_create(&thread1, NULL, factorial, NULL);
	pthread_join(thread1,NULL);
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%llu\t", output[i][j]);
		}
		printf("\n");
	}

	exit (EXIT_SUCCESS);
}

void *factorial()
{
    key_t key = 1234;
    int (*C)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    C = shmat(shmid, 0, 0);

	int i,j,k;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			unsigned long long f=1;
			for(k=1;k<=C[i][j];k++)
			{
				f= f+k;
				output[i][j] = f-1;
			}
		}
	}
}
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>
#include <pthread.h>

void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread, void **rval_ptr);
pthread_t thread1;

void *factorial();
unsigned long long output[4][5];


void main()
{
    key_t key = 1234;
    int (*C)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    C = shmat(shmid, 0, 0);

	// menampilkan matrix
    int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%d\t", C[i][j]);
		}
		printf("\n");
	}

	printf("\n");
	
	int newthread;
	newthread = pthread_create(&thread1, NULL, factorial, NULL);
	pthread_join(thread1,NULL);
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			printf("%llu\t", output[i][j]);
		}
		printf("\n");
	}

	exit (EXIT_SUCCESS);
}

void *factorial()
{
    key_t key = 1234;
    int (*C)[10];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    C = shmat(shmid, 0, 0);

	int i,j,k;
	for(i=0;i<4;i++)
	{
		for(j=0;j<5;j++)
		{
			unsigned long long f=1;
			for(k=1;k<=C[i][j];k++)
			{
				f= f+k;
				output[i][j] = f-1;
			}
		}
	}
}


