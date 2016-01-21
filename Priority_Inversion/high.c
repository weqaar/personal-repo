#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/resource.h>
#include <sched.h>
#include <sys/ipc.h>
#include <sys/shm.h>



#define PRIO_H -10
#define PRIO_L 10
#define PRIO_M 0
static int sem_id;
int who_locked;
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
int prio_inheritance=0;

	/*
	int shm_id=0;
	char *shm, *s;
	 FILE *f = fopen("shared_mem_info.txt","r");
        if (f == NULL)
        {
                printf("Error in opening file!!! \n");
                exit(1);
        }
	fscanf(f,"%d",&shm_id);
	fclose(f);
	printf("shared memory id = %d \n",shm_id);


	}
*/
/************************************* Process 1 (High Priority) *********************************/
	
	key_t key;
	int shm_id;
        char *shm, *s;
        char c;

        key = 5788; // name the shared memory
        shm_id= shmget(key,100, IPC_CREAT | 0666); // make a shared memory of 27 bytes
        if(shm_id < 0)
        {
                perror("shmget");
                exit(1);
        }
        // Now attach the shared memory to our data space
        if((shm = shmat(shm_id,NULL,0)) == (char *) -1)
        {
                perror("shmat");
                exit(1);
        }

        s = shm;  // Now we will write in the memory

        FILE *f = fopen("shared_mem_info.txt","w");
        if (f == NULL)
        {
                printf("Error in opening file!!! \n");
                exit(1);
        }
        fprintf(f,"%d\n",shm_id);
        fclose(f);

	sem_id = semget(key,1,0666 | IPC_CREAT);
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
	
		usleep(200);
		printf("High Prio task is now try to access the semaphore...\n");
		
	union semun sem_union;
	who_locked = semctl(sem_id,0,GETPID,sem_union);
//	if(who_locked != PID_H)
//	{
		if(who_locked > 0)
		{
			printf("The PID = %d has locked the Semaphore. . . \n",who_locked);	
			/*setpriority(PRIO_PROCESS,who_locked,PRIO_H);
			prio_inheritance = 1;
			printf("The PID = %d has inherited priority of High that is %d...\n",who_locked,PRIO_H);
			sched_yield();*/			
		} 
//	}

	
	sem_lock();	
	printf("High process has acquired the lock\n");
printf("Address = %d\n",shm);		
        for(c='a';c<='z';c++)
        {
                *s++ = c;
        }
	*s=NULL;
        printf("write succesfull...\n");
	
	while(*shm != '*')
	{
		sleep(1);
	}
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
	
	/*union semun sem_union;
	who_locked = semctl(sem_id,0,GETPID,sem_union);
	if(who_locked > 0)
	printf("The PID = %d has locked the Semaphore. . . \n",who_locked);
	*/
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
