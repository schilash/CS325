#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <iostream>
//Sample 1
/*
#define NUM_LOCKERS 3
#define NUM_KEYS 1
#define NUM_BALLS 1
int keys[] = {1};
int locker_ball[] = {3};
*/

//Sample 2
/*
#define NUM_LOCKERS 4
#define NUM_KEYS 2
#define NUM_BALLS 2
int keys[] = {2,3};
int locker_ball[] = {1,4};
*/

//Sample 3
/*
#define NUM_LOCKERS 8
#define NUM_KEYS 2
#define NUM_BALLS 2
int keys[] = {1,8};
int locker_ball[] = {5,4};
*/

//Sample 4
/*
#define NUM_LOCKERS 13
#define NUM_KEYS 5
#define NUM_BALLS 6
int keys[] = {6,4,2,7,5};
int locker_ball[] = {13,1,6,9,4,2};
*/

//Sample 5
/*
#define NUM_LOCKERS 67
#define NUM_KEYS 16
#define NUM_BALLS 14
int keys[] = {12,53,32,18,11,48,17,63,7,54,20,4,6,8,14,56};
int locker_ball[] = {66,32,38,16,8,40,19,52,53,12,21,51,22,18};
*/

//Sample 6

#define NUM_LOCKERS 139
#define NUM_KEYS 50
#define NUM_BALLS 56
int keys[] = {8,121,112,9,28,84,82,129,31,91,138,25,59,89,52,36,33,110,54,37,79,109,55,16,96,26,93,101,76,104,113,139,118,47,63,128,123,15,136,132,44,70,49,86,11,23,22,39,69,68};
int locker_ball[] = {86,33,92,19,125,41,14,60,75,135,50,61,57,28,104,43,129,128,83,48,133,65,45,114,55,11,58,97,17,42,91,138,34,127,2,35,103,49,18,118,111,74,101,124,113,47,70,52,5,139,69,93,13,29,40,12};

//Sample 7
/*
#define NUM_LOCKERS 201
#define NUM_KEYS 184
#define NUM_BALLS 74
int keys[] = {};
int locker_ball[] = {};
*/

//Sample 8
/*
#define NUM_LOCKERS 399
#define NUM_KEYS 197
#define NUM_BALLS 90
int keys[]={};
int locker_ball[]={};
*/

int last_init_key_path_value;
int min_lockers = 0;
int max_obtained_key;
int last_init_key_loc = 0;
int last_ball_loc = 0;
int i,j,k,x;
int starting_balls = 0;
int ball_first=0;

bool check_array(int value, int*array, int length){
	for ( k = 0; k< length; k++){
	//printf("%d\n",array[k]);
		if (array[k] == value){
			return true;
		}
	}
	return false; 
}

int find(int*array, int length, int value){
	for (int h= 0; h < length; h++){
		if (array[h] == value) return h;		
	}
}

int optimizer(int z){
	int smallest = -1;
	int small_temp;
	//for( x = last_init_key_loc; x <= z; x++){
	x = find(locker_ball, sizeof(locker_ball)/sizeof(int), last_ball_loc);
	while((locker_ball[x] >= last_init_key_loc) && (locker_ball[x] <= z)){
	//printf("%d:%d:%d:%d\n",locker_ball[x],last_init_key_loc,z,x);
			if(locker_ball[x]-last_init_key_loc+1<z-locker_ball[x]+1){
				if (locker_ball[x+1] > z){
					small_temp = (locker_ball[x]-last_init_key_loc+1);
				}
				else if (locker_ball[x+1] == z){
					small_temp = (locker_ball[x]-last_init_key_loc+1);
				}
				else/* (locker_ball[x+1] < z)*/{
					small_temp = (locker_ball[x] -last_init_key_loc+1) + (z-locker_ball[x+1]);
				}
			}
			else{
				if (locker_ball[x-1] > last_init_key_loc){
					small_temp = (z-locker_ball[x]+1)+(locker_ball[x-1] - last_init_key_loc+1);
					max_obtained_key=j+1;
				}
				else if (locker_ball[x-1] = last_init_key_loc){
					small_temp = (z-locker_ball[x]+1);
					max_obtained_key=j+1;
				}
				else /* (locker_ball[x-1] < last_init_key_loc)*/{
					small_temp = (z-locker_ball[x])+1;
					max_obtained_key=j+1;
				}
			}
			if (small_temp < smallest || smallest ==-1){
				smallest = small_temp;
			}
		x-=1;
	}
	if (smallest == -1) return 900000;
	else return smallest;
}


int cmpfunc (const void  *a, const void  *b)
{
  if (*(int*)a < *(int*)b) return -1;
  if (*(int*)a == *(int*)b) return 0;
  if (*(int*)a > *(int*)b) return 1;
}

using namespace std;

int main(){
/*
   int keys[NUM_KEYS];
   int locker_ball[NUM_BALLS];
   for(int a = 1; a <= NUM_KEYS; a++)
      cin >> keys[a];
   for(int v = 1; v <= NUM_BALLS; v++)
      cin >> locker_ball[v];
*/
	qsort(keys,NUM_KEYS,(sizeof (int)),cmpfunc);
	qsort(locker_ball,NUM_BALLS,(sizeof(int)),cmpfunc);
	for (int h = 0; h<(sizeof(keys)/sizeof(int));h++){
		printf("%d,",keys[h]);
	}
	printf("\n");
	for (int h = 0; h<(sizeof(locker_ball)/sizeof(int));h++){
		printf("%d,",locker_ball[h]);
	}
	for ( j = 1; j <= NUM_LOCKERS; j++){
	//printf("%d\n",j);
	//printf("%d\n",last_init_key_loc);
	//printf("%d\n",last_init_key_path_value);
		if ( ball_first == 1){
			starting_balls +=1;
		}
		//checks if the next locker has a ball in it and not a key, while also making sure atleast one key is present before j
		if (check_array(j,locker_ball,sizeof(locker_ball)/sizeof(int))&& (!check_array(j,keys,sizeof(keys)/sizeof(int))) && (keys[0]<j)){
			min_lockers = j-max_obtained_key + min_lockers+1;
			max_obtained_key = j+1;
			last_ball_loc = j;
			
		}
		//checks for starting balls
		else if (check_array(j,locker_ball,sizeof(locker_ball)/sizeof(int))&& (!check_array(j,keys,sizeof(keys)/sizeof(int))) && (keys[0]>j)){
			ball_first = 1;
			last_ball_loc = j;
		}
		//base case if first one is a key to set last key value to current key
		else if (!check_array(j,locker_ball,sizeof(locker_ball)/sizeof(int)) && (check_array(j,keys,sizeof(keys)/sizeof(int))) && (locker_ball[0]>j)){
				max_obtained_key = j;
		}
		//checks if the next locker has a key in it and not a ball, wihle also making sure atleast one ball is present.
		else if (!check_array(j,locker_ball,sizeof(locker_ball)/sizeof(int)) && (check_array(j,keys,sizeof(keys)/sizeof(int))) && (locker_ball[0]<j)){
			last_init_key_path_value = min_lockers;
			max_obtained_key = j;
			if (min_lockers == 0){
				min_lockers = starting_balls+1 ;//
				starting_balls = 0;
				ball_first = 0;
				last_init_key_path_value = min_lockers;
				max_obtained_key = j+1;
				printf("Times through: %d : %d\n",j,min_lockers);	
				continue;
			}
			if (min_lockers >= last_init_key_path_value + optimizer(j)){
				min_lockers = last_init_key_path_value + optimizer(j);
				max_obtained_key = j+1;
				
				
			}
			last_init_key_loc= j;
			
		}
		//if ball and a key are added
		else if (check_array(j,locker_ball,sizeof(locker_ball)/sizeof(int)) && (check_array(j,keys,sizeof(keys)/sizeof(int)))){
			max_obtained_key = j;
			last_ball_loc = j;
			if(min_lockers == 0){
				min_lockers = starting_balls+1;
				starting_balls = 0;
				ball_first = 0;
			}
			// if new ball and key added makes a more optimal path for less lockers
			else if (min_lockers + 1 > last_init_key_path_value + optimizer(j)){
				min_lockers = last_init_key_path_value + optimizer(j);
				max_obtained_key = j+1;
				last_init_key_path_value = min_lockers;
			}
			// if it doesn't still adds one for the new ball + key combo
			else{
			min_lockers = min_lockers + 1;
			max_obtained_key = j+1;
			}
			last_init_key_loc = j;
			last_init_key_path_value = min_lockers;
		}
	printf("Times through: %d : %d\n",j,min_lockers);	
	}
	printf("%d\n",min_lockers);
	return 1;
}
