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


	key = 5688; // name the shared memory
	shm_id= shmget(key,27, IPC_CREAT | 0666); // make a shared memory of 27 bytes
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
	for(c='a';c<='z';c++)
	{
		*s++ = c;
	}
	printf("Waiting for client to response");
	*s = NULL;	

	while(*shm != '*')
	{
		sleep (1);
	}
	

exit (0);

}
