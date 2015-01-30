//2015 Evan Steele
//CS325 Oregon State University
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void unlock_locker(int arr[],int locker,int max){
   arr[locker-1] = 1;
   if(locker==1)arr[0]=1;
}

int main(int argc, char *argv[]){
   //////////////////////////////////////////////////////////////
   int data_array[]={67, 16, 14};
   int keys_owned[]={12, 53, 32, 18, 11, 48, 17, 63, 7, 54, 20, 4, 6, 8, 14, 56 };
   int tennis_balls[]={66, 32, 38, 16, 8,40, 19, 52, 53, 12, 21, 51, 22, 18 };
   /////////////////////////////////////////////////////////////////////////////
   int i,n,x=0;
   int val=0;
   int found=0;
   int curr_key_cost,this_key;
   int min_key = data_array[0];
   int solution_array[data_array[0]];//prevents the counting of duplicate key results
   int min_locker;
   int this_locker;
   int curr_locker_cost;
   int unlock_me;
   int this_ball;

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

   for(i=0;i<(sizeof(tennis_balls)/sizeof(int));i++){
      for(n=0;n<(sizeof(keys_owned)/sizeof(int));n++){
         curr_key_cost = abs(tennis_balls[i]-keys_owned[n]);
         if (curr_key_cost < min_key){
            min_key = curr_key_cost+1;
            this_key = keys_owned[n];
            this_ball = tennis_balls[i];
         }
      }
   }

   if(this_ball<this_key){
      for(x=this_key;x>=this_ball;x--){
         unlock_locker(solution_array,x,data_array[0]);
      }
   }else if(this_ball>this_key){
      for(x=this_key;x<=this_ball;x++){
         unlock_locker(solution_array,x,data_array[0]);
      }
   }else if(this_ball==this_key){
      unlock_locker(solution_array,this_key,data_array[0]);
   }

   /*
      for(x=0;x<(sizeof(solution_array)/sizeof(int));x++){
      printf("x-%i (LOCKER %i): %i\n",x,x+1,solution_array[x]);
      } //these lockers are actually OPEN, their keys retrieved
      */

   //We have retrieved one tennis ball with a key now, with the opened lockers stored in the solution array. Now each remaining tennis ball will be tested against the newly opened lockers and the keys still avaliable
   for(i=0;i<(sizeof(tennis_balls)/sizeof(int));i++){
      min_key = data_array[0];
      for(n=0;n<(sizeof(keys_owned)/sizeof(int));n++){
         curr_key_cost = abs(tennis_balls[i]-keys_owned[n]);
         if (curr_key_cost < min_key){
            min_key = curr_key_cost+1;
            this_key = keys_owned[n];
         }
      }
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

      if (solution_array[tennis_balls[i]]==1){
         found =0;
      }

      if (found==0){
         unlock_me = MIN(min_locker,min_key);
         if(min_locker<=min_key){
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
   }
/*

   for(x=0;x<(sizeof(solution_array)/sizeof(int));x++){
      printf("x-%i (LOCKER %i): %i\n",x,x+1,solution_array[x]);
   } //these lockers are actually OPEN, their keys retrieved
*/
   for(i = 0;i<( (sizeof(solution_array)/sizeof(int)));i++){
      if(solution_array[i]==1)val = val +1;
   }

   printf("You will need to open a minimum of %i lockers to collect all tennis balls\n",val);
   return 0;
}
