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
	struct shmid_ds *buffer;

	key = 5678; // name the shared memory
	shm_id= shmget(key,27, 0666); // make a shared memory of 27 bytes
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
	// Here we will read what server has written
	for(s=shm; *s !=NULL; s++)
	{
		putchar(*s);
	}
	putchar('\n');
	
/*	int rtn = shmctl(shm_id, SHM_UNLOCK, buffer);

        if(rtn == -1)
        {
                perror("UNLock Failed");
                exit(1);
        }

*/
int i;
char *ss = shm;
for(i=1;i<=10;i++)
{	
	*ss++ = '*';
}

*shm = '*';
	exit(0);

}
