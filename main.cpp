#include <iostream>
#include <math.h>
#include <limits>
using namespace std;
int board[4][4];
int iteration = 500000;
double denom =  500000.0;// same as iteration
int sum[500000];// same as iteration
double running_sum = 0.0;
int n,m, k, steps,i, j;
int a = 0;
int b = 0;
int dummya, dummyb;
typedef std::numeric_limits< double > dbl;


int make_board()
{
  cout.precision(13) ;
  k = 0;
  for ( n=0 ; n<4 ; ++n )
    {
      for ( m=0 ; m<4 ; ++m )
	{
	  board[n][m] = k;
	  k = k + 1; // putting in the values on the chessboard 
	}
    }
  return 0;
}

int jump()
{
  int r1 = rand()% 100-50;
  int r2 = rand()% 100-50;
  int r3 = rand()% 100-50;
  int step1;
  int step2;
  if (r1 > 0) //to decide which step is the long direction
    {
      step1 = 1;
      step2 = 2;
    }
  else
    {
      step1 = 2;
      step2 = 1;
    }
  if (r2 > 0)  //to step horizontally 
    {
      dummya = a+step1;
      if (dummya > 3) 
	{ a = a-step1;}
      else
	{ a = a+step1;}
    }
  else
    {
      dummya = a-step1;
      if (dummya < 0)
        { a = a+step1;}
      else
	{ a = a-step1;}
    }
  if (r3 > 0) //to step vertically
    { 
      dummyb = b+step2;
      if (dummyb > 3)
        { b = b-step2;}
      else
	{ b = b+step2;}
    }
  else
    {
      dummyb = b-step2;
      if (dummyb < 0)
        { b = b+step2;}
      else
        { b = b-step2;}
    }
  return 0;
}


int main() 
{
  srand (time(NULL));
  make_board();
  int totalsteps;
  int modnum;
  int prob_modnumA;
  int prob_modnumB;
  cout.precision(dbl::max_digits10);// forcing the print to full digits
  for (j =0; j<2; ++j)// stepping over each case
    {
      int S[512];
      double mean = 0.0;
      double variance = 0.0;
      double prob_sum = 0.0;
      double stdev = 0.0;
      if (j <1)
	{
	  totalsteps= 16;
	  modnum = 13;
	  prob_modnumA=5;
	  prob_modnumB=13;
	}
      else
	{
	  totalsteps= 512;
	  modnum = 311;
	  prob_modnumA=7;
	  prob_modnumB=43;
	}
      running_sum = 0.0;
      for (i = 0; i <iteration;++i) //stepping through the given number of steps
	{
	  for ( steps = 0; steps < totalsteps; ++steps ) 
	    {
	      jump();
	      S[steps]=board[a][b];
	      sum[i] = sum[i] + S[steps]; //composing the sum
	    }
	  running_sum = running_sum + sum[i];// to find the mean
	}
      mean = running_sum/denom;// running sum used here
      for (i = 0; i <iteration;++i) 
	{
	  variance = variance + (sum[i]-mean)*(sum[i]-mean);// to find the stdev
	  if ((sum[i] % prob_modnumA == 0) &&  (sum[i] % prob_modnumB == 0))//for the joint prob calc
	    {prob_sum = prob_sum+1.0;} 
	  sum[i]=0;
	}
      stdev = sqrt(variance/denom);// variance used here
      if (j == 0)// printing out results
        {
	  cout << "For 16 Steps:"<< endl;
	}
      else
	{
	  cout << "For 512 Steps:"<< endl;
	}
      cout << "Mean:        "<< mean<<"   Stdev: "<<stdev<<endl;
      int int_mean = (int) mean;
      int final_mod = int_mean % modnum;
      cout << "Mean mod:    "<< modnum << " :  " << final_mod << endl;
      cout << "Probability: "<< prob_sum/denom<<endl;
    }
  return 0;
}
