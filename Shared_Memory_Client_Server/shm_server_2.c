#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h> 

int main()
{
	key_t key;
	int shm_id;
	char *shm, *s;
	char c;
	struct shmid_ds *buffer; //shared memory data struct to hold results

	key = 5678; // name the shared memory
	shm_id= shmget(key,27, IPC_CREAT | 0666); // make a shared memory of 27 bytes
	printf("Hello\n");
	if(shm_id < 0)

	{
		perror("shmget");
		exit(1);
	}
	printf("shmget successfull\n");
	// Now attach the shared memory to our data space
	if((shm = shmat(shm_id,NULL,0)) == (char *) -1)
	{	
		perror("shmat");
		exit(1);
	}

	printf("shmat successfull\n");	

	int rtn = shmctl(shm_id, SHM_LOCK, buffer);
	printf("Return value from lock = %d\n",rtn);	
	if(rtn == -1)
	{
		perror("Lock Failed");
		exit(1);
	}
	printf("lock has been aquired");
	
	s = shm;  // Now we will write in the memory
	for(c='a';c<='z';c++)
	{
		*s++ = 'l';
	}
	*s = NULL;
	printf("Write Succesfull\n");
	
/*	 rtn = shmctl(shm_id, SHM_UNLOCK, buffer);
	if(rtn == -1)
	{
		perror("UNLock Failed");
		exit(1);
	}
	
	printf("lock has been unlocked");
*/
	printf("Waiting for client to response");
	while(*shm != '*')
	{
		sleep (1);
	}
exit (0);

}
