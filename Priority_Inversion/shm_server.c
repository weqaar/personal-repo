#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h> 
#include <stdlib.h>

int main()
{
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
		for(c='a';c<='z';c++)
	{
		*s++ = c;
	}

	FILE *f = fopen("shared_mem_info.txt","w");
	if (f == NULL)
	{
		printf("Error in opening file!!! \n");
		exit(1);
	}
	fprintf(f,"%d\n",shm_id);
	fclose(f);
	
	for(c='a'; c<='z';c++)
        {
                *s++ =c;
        }
	*s = NULL;
        printf("write succesfull...\n");

/*	
	printf("Waiting for client to response");
	*s = NULL;	

	while(*shm != '*')
	{
		sleep (1);
	}
	
*/
exit (0);

}
