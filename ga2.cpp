#include<iostream>
#include<cmath>
#include<string>
#include<vector>
#include<cstdlib>
#include <boost/dynamic_bitset.hpp>

using namespace std;

int main()
{
   //store input
   int N, M, T;
   cin >> N;
   cin >> M;
   cin >> T;
   
   int MLocs[M+1];
   int TLocs[T+1];
   for(int i = 1; i <= M; i++)
      cin >> MLocs[i];
   for(int i = 1; i <= T; i++)
      cin >> TLocs[i];
   MLocs[M+1] = 1201;
   TLocs[T+1] = 1201;
   for(int i = 1; i <= T+1; i++)
   {
      cout<<TLocs[i]<<" ";
   }
   cout<<endl;
   sort(MLocs, MLocs + sizeof MLocs / sizeof MLocs[0]);
   sort(TLocs, TLocs + sizeof TLocs / sizeof TLocs[0]);
   for(int i = 1; i <= T+1; i++)
   {
      cout<<TLocs[i]<<" ";
   }
   cout<<endl;

   //generate all possible key combinations as binary strings
   string key_combos[(int)pow(2,M)];
   vector<int> TMins(T, -1);
   int min_total_trues = 601;
   for(int i = 1; i < pow(2,M); i++)
   {
      boost::dynamic_bitset<> bs(600,i);
      to_string(bs,key_combos[i]);
      reverse(key_combos[i].begin(), key_combos[i].end());
      key_combos[i].append("11");
      cout<<key_combos[i].substr(0,M)<<endl;

      //determine best solution for each guess
      vector<bool> isOpen(N, false);
      //vector<int> Tmins(T, -1)
      int k = 1;
      int l = 1;
      int p = 1;
      int closest_behind = 1201;
      int closest_front = 1201;
      bool opening = false;
      int total_trues = 0;
      for(int j = 1; j <= N; j++)
      {
         //if locker has initial key, open the locker
	 //cout<<"blah! k: "<<k<<" key_combos[i].at(p-1): "<<key_combos[i].at(p-1)<<" j: "<<j<<" MLocs[k]: "<<MLocs[k]<<endl;
	 if(key_combos[i].at(k-1) == '1' && j == MLocs[k])
	 {
	    cout<<"locker has initial key, "<<key_combos[i].at(k-1)<<", "<<MLocs[k]<<endl;
            isOpen[j] = true;
	    total_trues++;
	    k++;
	 }
	 else if(key_combos[i].at(k-1) == '0' && j == MLocs[k])
	 {
            k++;
	    p++;
	 }
	 else
	 {
            p++;
	 }
	 //if locker is open, move to next locker
         if(isOpen[j])
	 {
	    cout<<"locker "<<j<<" is open\n"<<endl;
	    opening = false;
	    closest_behind = j;
	    //if locker has a ball
	    if(TLocs[l] == j)
	    {
               l++;
	    }
	 }

	 //if locker has a ball and is not open
         else if(isOpen[j] == false && TLocs[l] == j)
	 {
	    cout<<"locker "<<j<<" is not open and has a ball, "<<TLocs[l+1]<<", MLocs[k]: "<<MLocs[k]<<endl;
	    l++;
	    //if closest open locker is behind it
	    closest_front = k;
	    while(key_combos[i].at(closest_front-1) != '1')
	       closest_front++;

	    cout<<"j: "<<j<<" closest_behind: "<<closest_behind<<endl;
	    cout<<"closest_front: "<<closest_front<<" MLocs[cf]: "<<MLocs[closest_front]<<endl;
	    if((closest_front > M) || ((j-closest_behind) < (min(TLocs[l],MLocs[closest_front]))-j) && (closest_behind != 1201))
	    {
	       cout<<"   closest open locker is behind it, j: "<<j<<", closest_behind: "<<closest_behind<<", TLocs[l]: ";
	       cout<<TLocs[l]<<", MLocs[closest_front]: "<<MLocs[closest_front]<<endl;
	       int n = j;
               do
	       {
                  isOpen[n] = true;
		  total_trues++;
		  n--;
	       } while (!isOpen[n]);
	    }
	    //if closest open locker is in front of it or no lockers are open yet
	    else
	    {
	       cout<<"closest open locker is in front\n";
               opening = true;
	    }
	 }

	 if(opening == true)
	 {
	    cout<<"opening is true\n";
            isOpen[j] = true;
	    total_trues++;
	 }
	 cout<<endl;
      }
      cout<<"TOTAL_TRUES: "<<total_trues<<endl;
      if(min_total_trues > total_trues)
         min_total_trues = total_trues;
   }
   cout<<min_total_trues<<endl;

   return 0;
}
