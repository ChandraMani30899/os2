#include<stdio.h>
#include<unistd.h>
#include<semaphore.h>
#include<pthread.h>


int NumCats,NumBowl,NumMice,total_cats,total_Bowl,total_Mice;

sem_t EatingArea;

void *CatsEating()
{     if(NumCats<=total_cats && NumBowl<=total_Bowl && NumBowl > 0 && NumCats>0)
      {	
	  sem_wait(&EatingArea);
	   NumBowl--;
	   NumCats--;
	   printf("\n\nCat %d has eaten the  bowl %d ",total_cats-NumCats,total_Bowl-NumBowl);
	    sem_post(&EatingArea);
	   
      }
     else return 0;
}
void *MiceEating()
{
          if(NumMice<=total_Mice && NumBowl<=total_Bowl && NumBowl>0 && NumMice>0)
	  {
	   sem_wait(&EatingArea);
	   NumBowl--;
	   NumMice--;
	   printf("\n\nMice %d has eaten the  bowl %d ",total_Mice-NumMice,total_Bowl-NumBowl);
	  
	   sem_post(&EatingArea);
           }
  else return 0;
}
int main()
{    pthread_t th,th1;
	 printf("\n Enter the number of cats :");
 	 scanf("%d",&NumCats);
	printf("\n Enter the number of Mice :");
	scanf("%d",&NumMice);
	printf("\n Enter the number of Bowl of food :");
	scanf("%d",&NumBowl);
        printf("\n ==========================================================================================\n");
	total_cats=NumCats;
        total_Bowl=NumBowl;
	total_Mice=NumMice;
	sem_init(&EatingArea,0,1);
	while((NumBowl>0 ) && (NumCats>0 || NumMice>0))
	{    
	    pthread_create(&th,NULL,CatsEating,NULL);
	    pthread_create(&th1,NULL,MiceEating,NULL); 
        }
       while((NumBowl>0 ) && (NumCats>0 || NumMice > 0))
        {
            pthread_join(th,NULL);
            pthread_join(th1,NULL); 
        }
      printf("\n\n ==========================================================================================\n");

	return 0;
}
