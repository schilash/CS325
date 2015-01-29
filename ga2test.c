#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))

void unlock_locker(int arr[],int locker,int max){
   arr[locker-1] = 1;
   if(locker==1)arr[0]=1;
}

int main(int argc, char *argv[]){

   int i,n,t,z=0,x=0,y;
   int val=0;
   int found=0;
   int curr_key_cost,this_key,tracker=0;

    int data_array[] = {9,3,4};
     int keys_owned[] = {1,3,8};
     int tennis_balls[]={2,5,6,9};

  // int data_array[] = {201, 184, 74};
 //  int keys_owned[] = {131, 94, 181, 99, 138, 193, 17, 145, 161, 165, 25, 107, 36, 142, 171, 110, 188, 97, 154, 28, 173, 60, 183, 53, 71, 13, 43, 184, 5,168, 73, 139, 106, 91, 18, 93, 192, 163, 29, 120, 62, 21, 96, 78, 149, 87, 81, 84, 47, 80, 167, 31, 14, 124, 151, 178, 162, 147, 101, 105, 123, 30, 113, 41, 121, 38, 72, 12, 68, 117, 129, 130, 46, 166, 35, 104, 74, 116, 108, 158, 44, 180, 100, 122, 182, 66, 136, 52, 55, 23, 194, 2, 42, 102, 160, 172, 50, 156, 51, 103, 195, 48, 8, 10, 137, 152, 98, 15, 143, 127, 176, 75, 89, 24, 70, 189, 144, 135, 76, 115, 77, 32, 164, 170, 153, 82, 196, 86, 20, 33, 85, 169, 83, 159, 57, 199, 174, 64,134,109, 95, 140, 191, 79, 67, 179, 197, 150, 37, 58, 119, 186, 27, 88, 111, 59, 4, 146, 1, 26, 34, 22, 201, 7, 16, 114, 65, 177, 63, 9, 19, 69, 157, 45, 49, 190, 112, 148, 118, 132, 133, 56, 61, 187 };
//   int tennis_balls[]={201, 146, 116, 189, 159, 71, 10, 21, 41, 35, 38, 106, 95, 7,43, 135, 193, 175, 117, 186, 185, 93, 194, 191, 3, 176, 196, 5, 148, 177, 45, 11, 144, 152, 72, 187, 147, 182, 14, 51, 138, 94, 183, 114, 64, 47, 76, 198, 174, 49, 123, 20, 179, 118, 97, 34, 86, 2, 105, 75, 98, 134, 178, 190, 80, 92, 81, 112, 9, 110, 87, 107, 17, 160 };

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

   if(tennis_balls[i]<this_key){
      for(x=this_key;x>=tennis_balls[i];x--){
         unlock_locker(solution_array,x,data_array[0]);
      }
   }else if(tennis_balls[i]>this_key){
      for(x=this_key;x<=tennis_balls[i];x++){
         unlock_locker(solution_array,x,data_array[0]);
      }
   }else if(tennis_balls[i]==this_key){
      unlock_locker(solution_array,this_key,data_array[0]);
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
         found =0;
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
   for(i = 0;i<( (sizeof(solution_array)/sizeof(int)));i++){
      printf("Locker %i: %i\n",i+1,solution_array[i]);
      if(solution_array[i]==1)val = val +1;
   }
   printf("VAL: %i\n",val);
   return 0;
}
