#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/resource.h>

#define PRIO_H -10
#define PRIO_L 10
#define PRIO_M 0
static int sem_id;
union semun {
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};
/************************************ Initiallize the semaphore **********************************/
static int set_semvalue(void);
static int del_sem(void);
static int sem_lock(void);
static int sem_unlock(void);

/**************************************************************************************************/


int main()
{
int i;
/************************************* Process 1 (High Priority) *********************************/
	
	
		sem_id = semget((key_t)1234,1,0666 | IPC_CREAT);
		if(!set_semvalue())
		{
			fprintf(stderr,"Failed to initiaalize the semaphore \n");
			exit(EXIT_FAILURE);
		}

	// It is the parent process. I have schedule it as high priority process.
	int PID_H = getpid();
	int PR_H = getpriority(PRIO_PROCESS,PID_H);
	printf("The Priority of High Process %d = %d\n", PID_H,PR_H);
	setpriority(PRIO_PROCESS,PID_H,PRIO_H);
	printf("The Priority of High Process %d changes = %d\n", PID_H,PRIO_H);
	
	
	int pid,pid_2;
	pid = fork();
	pid_2 = fork();


/************************************ Process 2 (Low Priority) **********************************/
	if(pid == 0)				// 0 shows it is child process
	{
		
	int PID_L = getpid();
	int PR_L = getpriority(PRIO_PROCESS,PID_L);
	printf("The Priority of LOW Process %d = %d\n", PID_L,PR_L);
	setpriority(PRIO_PROCESS,PID_L,PRIO_L);
	printf("The Priority of LOW Process %d changes = %d\n", PID_L,PRIO_L);

	/*Low Priority Task tries to acquire to lock the semaphore*/
		sem_lock();
		printf("Low Priority Process locks semaphore\n");
		for(i=0;i<50;i++)
		printf("Low Prio task is running...\n");
		sem_unlock();
		printf("Low Priority task is completed...\n");
		
					 	
	}
/*********************************** Process 3 (Medium Priority)*********************************/
	if(pid_2 == 0)
	{
		
	int PID_M = getpid();
	int PR_M = getpriority(PRIO_PROCESS,PID_M);
	printf("The Priority of Medium Process %d = %d\n", PID_M,PR_M);
	setpriority(PRIO_PROCESS,PID_M,PRIO_M);
	printf("The Priority of Medium Process %d changes = %d\n", PID_M,PRIO_M);
		for(i=0;i<20;i++)
		printf("Medium Prio task is running...\n");
	printf("Medium Priority Task is Completed\n");

	}
		usleep(50);	
		//for(i=0;i<20;i++)
		printf("High Prio task is now try to access the semaphore...\n");
	sem_lock();
	printf("High process has acquired the lock\n");

	
		for(i=0;i<40;i++)
		printf("High Prio task is running...\n");
	sem_unlock();
	printf("High process has unlock the semaphore... \n");
	return 0;

}

/************************************ Initiallize the semaphore **********************************/
static int set_semvalue(void)
{
	union semun sem_union;
	sem_union.val = 1;
	if(semctl(sem_id,0,SETVAL,sem_union) == -1)
	{
		return(0);
	}
	return (1);
}
static int del_sem(void)
{
	union semun sem_union;
	if(semctl(sem_id,0,IPC_RMID,sem_union) == -1)
	{
		fprintf(stderr,"Failed to delete semaphore.\n");
	}
}
static int sem_lock(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = -1;
	sem_b.sem_flg = SEM_UNDO;
	
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		fprintf(stderr,"Semaphore did't lockecd = failed \n");
		return (0);
	}
	return (1);
}

static int sem_unlock(void)
{
	struct sembuf sem_b;
	sem_b.sem_num = 0;
	sem_b.sem_op = 1;
	sem_b.sem_flg = SEM_UNDO;
	
	if(semop(sem_id, &sem_b, 1) == -1)
	{
		fprintf(stderr,"Semaphore did't release (unlockecd) = failed \n");
		return (0);
	}
	return (1);
}

/**************************************************************************************************/
