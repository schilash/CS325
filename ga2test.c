#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void unlock_locker(int arr[],int locker,int max){
   if(locker==0){
      arr[0] = 1;
      arr[1] = 1;
   }else if(locker==max){
      arr[max] = 1;
      arr[max-1] = 1;
   }else{
      arr[locker]=1;
      arr[locker-1]=1;
      arr[locker+1]=1;
   }
}

int main(int argc, char *argv[]){

   int i,n,t,z=0,x=0,y;
   int val=0;
   int found=0;
   int curr_key_cost,this_key,tracker=0;
   int data_array[] = {13, 5, 6};
   int keys_owned[] = {6,4,2,7,5};
   int tennis_balls[]={13,1,6,9,4,2};
   int min_key = data_array[0];
   int lockers_opened[data_array[0]];
   int solution_array[data_array[0]];//prevents the counting of duplicate key results
   int unlocked=0;
   int curr_locker;
   int chosen_path;
   int min_locker_cost;
   int curr_locker_first,curr_locker_last;
   int min_locker;
   int min_locker_location;
   int this_locker;
   int curr_locker_cost;

   memset(solution_array,0,(sizeof(solution_array)/sizeof(int)));
   for(i=0;i<(sizeof(solution_array)/sizeof(int));i++){
      solution_array[i]=0;
   }

   printf("We have %d lockers, %d keys at the start, and %d tennis balls\n",data_array[0],data_array[1],data_array[2]);

   printf("We are given the keys to lockers:");
   for(i=0;i<(sizeof(keys_owned)/sizeof(int));i++){
      printf(" %d ",keys_owned[i]);
   }
   printf("\n");

   printf("There are tennis balls in lockers:");
   for(i=0;i<(sizeof(tennis_balls)/sizeof(int));i++){
      printf(" %d ",tennis_balls[i]);
   }
   printf("\n");

   i = 0;
   min_key = data_array[0];
   for(n=0;n<(sizeof(keys_owned)/sizeof(int));n++){
      curr_key_cost = abs(tennis_balls[i]-keys_owned[n]);
      if (curr_key_cost < min_key){
         min_key = curr_key_cost+1;
         this_key = keys_owned[n];
      }
   }
   printf("We have arbitrarily chosen tennis ball at locker %d to be unlocked opening %d lockers, using key %d\n",tennis_balls[i],min_key,this_key);

   val = min_key;
   for(x=this_key-1;(abs(x-tennis_balls[i]))!=0;x++){
      unlock_locker(solution_array,x,data_array[0]);
   }

   /*
   for(x=0;x<(sizeof(solution_array)/sizeof(int));x++){
      printf("x-%i (LOCKER %i): %i\n",x,x+1,solution_array[x]);
   }
   */


   //We have retrieved one tennis ball with a key now, with the opened lockers stored in the solution array. Now each remaining tennis ball will be tested against the newly opened lockers and the keys still avaliable
   for(i=1;i<(sizeof(tennis_balls)/sizeof(int));i++){
      curr_key_cost = data_array[0];
      for(n=0;n<(sizeof(keys_owned)/sizeof(int));n++){
         curr_key_cost = abs(tennis_balls[i]-keys_owned[n]);
         if (curr_key_cost < min_key){
            min_key = curr_key_cost+1;
            this_key = keys_owned[n];
         }
      }
      printf("It appears that the best KEY path for tennis ball %i is using key %i, with a path of %i\n",tennis_balls[i],this_key,min_key);
      //Let's see how it compares with our opened lockers....

      min_locker = data_array[0];
      for(x=0;x<(sizeof(solution_array)/sizeof(int));x++){
         if(solution_array[x]!=0){
            curr_locker_cost = abs(tennis_balls[i]-solution_array[x]);
            if (curr_locker_cost < min_locker){
               min_locker = curr_locker_cost+1;
               this_locker = x;
            }
         }
      }
      printf("It appears that the best OPENED LOCKER path for tennis ball %i is using opened locker %i, with a path of %i\n",tennis_balls[i],this_locker,min_locker);
      printf("\n");
   }

   return 0;
}
