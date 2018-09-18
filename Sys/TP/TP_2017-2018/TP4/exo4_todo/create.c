#include <stdio.h>
# include <unistd.h>
#include <sys/shm.h>
#include "semaphores2.h"


typedef struct data{
int indL;
int indR;
int tab[10];
}sdata;

int main(void)
{
//creation d'une clé 
key_t key = ftok("/home/izan/Desktop/Naila/Sys",'m');

//recupérer la key du semaphore qui cré la memoire patagé
int shmid = shmget(key,sizeof(sdata), IPC_CREAT | IPC_EXCL | 0666);
if(shmid==-1){
//la zone existe deja !
shmid=shmget(key,sizeof(sdata),0); //recuperer son id
}

//attacher le processus a la zone de mémoire partagée
sdata *sd= NULL;
sd = shmat(shmid,sd,0);

//initialiser les tetes de lecture et ecriture
sd->indL = 0;
sd->indR = 0;

//creation d'un groupe de 2 sémaphores binaires
int semid = semcreate(key,2);

//initialiser les sémaphores
seminit(semid , 0 , 10);
seminit(semid , 1 , 0);



return 0;
}
