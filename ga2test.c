#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void unlock_locker(int arr[],int locker,int max){
   arr[locker] = 1;
   if(locker==1)arr[0]=1;
}

int main(int argc, char *argv[]){

   int i,n,t,z=0,x=0,y;
   int val=0;
   int found=0;
   int curr_key_cost,this_key,tracker=0;
   int data_array[] = {139, 50, 56};
   int keys_owned[] = {8, 121, 112, 9, 28, 84, 82, 129, 31, 91, 138, 25, 59, 89, 52, 36, 33, 110, 54, 37, 79, 109, 55, 16, 96, 26, 93, 101, 76, 104, 113, 139, 118, 47, 63, 128, 123, 15, 136, 132, 44, 70, 49, 86, 11, 23, 22, 39, 69, 68};
   int tennis_balls[]={86, 33, 92, 19, 125, 41, 14, 60, 75, 135, 50, 61, 57, 28, 104, 43, 129, 128, 83, 48, 133, 65, 45, 114, 55, 11, 58, 97, 17, 42, 91, 138, 34, 127, 2,35, 103, 49, 18, 118, 111, 74, 101, 124, 113, 47, 70, 52, 5, 139, 69, 93, 13, 29, 40,12};
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
   int unlock_me;

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

   for(x=0;x<(sizeof(solution_array)/sizeof(int));x++){
      printf("x-%i (LOCKER %i): %i\n",x,x+1,solution_array[x]);
   } //these lockers are actually OPEN, their keys retrieved


   //We have retrieved one tennis ball with a key now, with the opened lockers stored in the solution array. Now each remaining tennis ball will be tested against the newly opened lockers and the keys still avaliable
   for(i=1;i<(sizeof(tennis_balls)/sizeof(int));i++){
      //curr_key_cost = data_array[0];
      min_key = data_array[0];
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
      found = 0;
      for(x=0;x<(sizeof(solution_array)/sizeof(int));x++){
         if(solution_array[x]!=0){
            curr_locker_cost = abs(tennis_balls[i]-x);
            if (curr_locker_cost < min_locker){
               min_locker = curr_locker_cost+1;
               this_locker = x;
            }
         }
      }
      printf("It appears that the best OPENED LOCKER path for tennis ball %i is using opened locker %i, with a path of %i\n",tennis_balls[i],this_locker+1,min_locker);
      if (solution_array[tennis_balls[i]]==1){
         printf("Alert! This locker is already open and accounted for.\n");
         found = 1;
      }

      if (found==0){
         unlock_me = MIN(min_locker,min_key);
         if(min_locker<=min_key){
            printf("The locker is closer\n");
            if(tennis_balls[i]<this_locker){
               for(unlock_me=this_locker;unlock_me>=tennis_balls[i];unlock_me--){
                  unlock_locker(solution_array,unlock_me,data_array[0]);
               }
            }else if(tennis_balls[i]>this_locker){
               for(unlock_me=this_locker;unlock_me<=tennis_balls[i];unlock_me++){
                  unlock_locker(solution_array,unlock_me,data_array[0]);
               }
            }else if(tennis_balls[i]==this_locker){

               unlock_locker(solution_array,tennis_balls[i],data_array[0]);
            }
         }else{
            printf("One of our given keys is closer\n");
            if(tennis_balls[i]<this_key){
               for(unlock_me=this_key;unlock_me>=tennis_balls[i];unlock_me--){
                  unlock_locker(solution_array,unlock_me,data_array[0]);
               }
            }else if(tennis_balls[i]>this_key){
               for(unlock_me=this_key;unlock_me<=tennis_balls[i];unlock_me++){
                  unlock_locker(solution_array,unlock_me,data_array[0]);
               }

            }else if(tennis_balls[i]==this_key){
               unlock_locker(solution_array,tennis_balls[i],data_array[0]);
            }
         }
      }
      printf("\n");
   }
   val = 0;
   for(i = 0;i<( (sizeof(solution_array)/sizeof(int)));i++){
      printf("Locker %i: %i\n",i+1,solution_array[i]);
      if(solution_array[i]==1)val++;
   }
   printf("VAL: %i\n",val);
   return 0;
}
