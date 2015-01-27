#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

int main(int argc, char *argv[]){

   int i,n,t,z=0,x=0,y;
   int val=0;
   int found=0;
   int curr_key_cost,this_key,tracker=0;
   int data_array[] = {14, 5, 6};
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

   for (i=0;i<(sizeof(tennis_balls)/sizeof(int));i++){
      //the greatest for loop shall check the distance for each tennis ball, we shall decide if it is best to use a key or a locker

      found = 0;
      min_locker = data_array[0];
      //we have reset our checker values, now we'll look through the array for open lockers

      for(n=0;n<(sizeof(solution_array)/sizeof(int));n++){
         //now,we're checking our solution array for lockers that have been opened,if none have been, we move on to the key algorithm. If one has been, we check the distance to the tennis ball

         printf("N IS %i\n",n);
         if(solution_array[n]!=0){  //we found an open locker!
            printf("We have an opened locker at %i, let's check it\n",solution_array[n]);
            found = 1;
            //we should note if we found any open lockers

            curr_locker = abs(tennis_balls[i]-solution_array[n]);
            //what's the distance from this open locker to the tennis ball we're testing?

            if(curr_locker < min_locker){
               min_locker = curr_locker;
               min_locker_location = solution_array[n];
               //we've got the smallest value, and the locker it's at
            }
         }
      }
      printf("The best locker location is at %i, with path %i\n",min_locker_location,min_locker);
      printf("Done checking existing array, now looking at keys\n");
      //we've finished and got the best possible path from the closest open locker. Now, we'll check the best route if we use a key

      //this here algroithm shall come up with the best possible path from the current tennis ball to a key.
      min_key = data_array[0];
      for(n=0;n<sizeof(keys_owned)/sizeof(int);n++){
         curr_key_cost = abs(tennis_balls[i]-keys_owned[n]);
         if (curr_key_cost < min_key) {
            min_key = curr_key_cost+1;
            this_key = keys_owned[n];
            if(tennis_balls[i] == 1){
               solution_array[0] == 1;
            }else if (tennis_balls[i] == data_array[0]){
               solution_array[(sizeof(solution_array)/sizeof(int))] = data_array[0];
            }else{
               solution_array[tennis_balls[i+1]] = tennis_balls[i+1];
               solution_array[tennis_balls[i-1]] = tennis_balls[i-1];
            }
         }
      }
      printf("The shortest route to tennis ball at locker %d is with path %d, using key %d\n",tennis_balls[i],min_key,this_key);
   }
   return 0;
}
