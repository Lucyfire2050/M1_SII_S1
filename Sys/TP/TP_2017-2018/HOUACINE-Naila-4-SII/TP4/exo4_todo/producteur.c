#include <stdio.h>
# include <unistd.h>
#include <sys/shm.h>
#include "semaphores2.h"
#include <pthread.h>

typedef struct data{
int indL;
int indR;
int tab[10];
}sdata;

int main()
{
//creation d'une clé 
key_t key = ftok("/home/izan/Desktop/Naila/Sys",'m');

	pthread_mutex_t myMutexP = PTHREAD_MUTEX_INITIALIZER;
	
	int shmid = shmget(key,sizeof(sdata), 0);
	if(shmid==-1){
		//la zone existe deja !
		shmid=shmget(key,sizeof(sdata),0); //recuperer son id
	}
	
	sdata *sd= NULL;
	sd = shmat(shmid,sd,0);
	
	int semid = semcreate(key,2);
	int val;

	while(1){
	
	val = rand()%20;
	
		P(semid,0);//vide

		pthread_mutex_lock(& myMutexP);

		printf("produire val = %d \n",val);
		sd->tab[sd->indR] = val;
		sd->indR = (sd->indR+1)%10;
		
		printf("tab = [ %d,%d,%d,%d,%d,%d,%d,%d,%d,%d ] \n\n",sd->tab[0] , sd->tab[1] , sd->tab[2] , sd->tab[3] , sd->tab[4] , sd->tab[5] , sd->tab[6] , sd->tab[7] , sd->tab[8] , sd->tab[9] );

		
		pthread_mutex_unlock(& myMutexP);

		V(semid,1);//plein
		
		sleep(5);
		
	}


return 0;
}
