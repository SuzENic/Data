#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <fstream>
#include <stdio.h>      /* printf, fgets */
#include <stdlib.h>     /* atoi */
#include <math.h>


int main()
{
  using namespace std;

  ifstream in_acc("Stats19_Data_2005-2014/Accidents0514.csv");
  string line_acc, field_acc;
  vector< vector<string> > accident_string;  // the 2D array
  //  vector< vector<float> > accident;  // the 2D array
  vector<string> acc;                // array of values for one line only
  
  while ( getline(in_acc,line_acc) )    // get next line in file
    {
      acc.clear();
      stringstream ss(line_acc);
        while (getline(ss,field_acc,','))  // break line into comma delimitted fields
        {
	  acc.push_back(field_acc);  // add each field to the 1D array
        }
        accident_string.push_back(acc);  // add the 1D array to the 2D array
    }
  
  ifstream in_cas("Stats19_Data_2005-2014/Casualties0514.csv");

  string line_cas, field_cas;
  vector< vector<string> > casual_string;  // the 2D array
  //vector< vector<float> > caasual;  // the 2D array
  vector<string> cas;                // array of values for one line only
  
  while ( getline(in_cas,line_cas) )    // get next line in file
    {
      cas.clear();
      stringstream ss(line_cas);
      
      while (getline(ss,field_cas,','))  // break line into comma delimitted fields
        {
	  cas.push_back(field_cas);  // add each field to the 1D array
        }
      
      casual_string.push_back(cas);  // add the 1D array to the 2D array
    }

  ifstream in_V("Stats19_Data_2005-2014/Vehicles0514.csv");

  string line_V, field_V;
  vector< vector<string> > vehicle_string;  // the 2D array                                                                                                                                       
  vector< vector<int> > vehicle;  // the 2D array                                                                                                                               
  vector<string> V;                // array of values for one line only                                                                                                                          
  
  while ( getline(in_V,line_V) )    // get next line in file                                                                                                                                           
    {
      V.clear();
      stringstream ss(line_V);

      while (getline(ss,field_V,','))  // break line into comma delimitted fields                                                                                                                    
        {
          V.push_back(field_V);  // add each field to the 1D array                                                                                                                                
	}
      vehicle_string.push_back(V);  // add the 1D array to the 2D array                                                                                                           
    }
  // print out what was read in
  
  for (size_t i=vehicle_string.size()-35; i<vehicle_string.size(); ++i)//i<array.size()
    {
      //      for (size_t j=0; j<vehicle_string[i].size(); ++j)
      //  {
      //	  cout << accident_string[i][j] << "|"; // (separate fields by |)
	  //cout << casual_string[i][j] << "|"; // (separate fields by |)
	  //cout << vehicle_string[i][15] << "|"; // (separate fields by |)
	  //	  vehicle[i][j] = atoi(vehicle_string[i][j]);
	  //	}
      //  cout << "\n";
    }

  double urban = 0.0;
  std::string zero ("0");  
  std::string one ("1");  
  std::string two ("2");  
  std::string three ("3");  
  std::string four ("4");  
  std::string five ("5");  
  std::string six ("6");  
  std::string seven ("7");  
  std::string eight ("8");  
  std::string nine ("9");  
  std::string ten ("10");  
  std::string eleven ("11");  
  std::string neg ("-1");  
  int year[100];
  double hour[24];
  double hour_fatal[24];
  double X_size[99];
  double Y_size[99];
  double ratio;
  int size_calc;
  double Xsize_calc;
  double Ysize_calc;
  int acc_date[]={0,0,0,0};
  int acc_time[]={0,0,0};
  int transition;
  vector<double> X; 
  vector<double> Y; 
  cout.precision(10) ; 
  
  for (size_t i=0; i<accident_string.size(); ++i)
    {
      if (accident_string[i][29] == one) //urban or not
      	{
      	  urban = urban +1;
	}
      std::string date = accident_string[i][9];
      std::istringstream iss(date);
      char cD = '/';
      for (int j=1;j<4;++j)
	{
	  iss >>cD >>acc_date[j];
	} 
      year[acc_date[3]-2000]=year[acc_date[3]-2000]+1;
      std::string time = accident_string[i][11];
      std::istringstream issT(time);
      //issT >> acc_time[0];
      std::replace(time.begin(), time.end(), ':', ' ');
      for (int j=1;j<3;++j)
	{
	  issT  >>acc_time[j];
	} 
      /*      if (i <35) 
	{
	  cout <<"date "<<accident_string[i][9]<< " vs. " <<acc_date[1]<< "/"<<acc_date[2]<< "/"<<acc_date[3];;
	  cout <<"time "<<accident_string[i][11]<< " vs. " <<acc_time[1]<< ":"<<acc_time[2]<<endl;
	  }*/
      hour[acc_time[1]]=hour[acc_time[1]]+1.0;
      istringstream (accident_string[i][6] )>> transition;
      if (transition == 3)
	{
	  hour_fatal[acc_time[1]]=hour_fatal[acc_time[1]]+1.0;
	}
    }
  for (int j=1;j<99;++j)
    {
      for (size_t i=0; i<accident_string.size(); ++i)
	{
	  istringstream (accident_string[i][5])>>size_calc;
       	  if (j == size_calc) 
	    {
	      stringstream(accident_string[i][3])>>Xsize_calc;
	      stringstream(accident_string[i][4])>>Ysize_calc;	      
	      //std::string::size_type sz; 
	      //Xsize_calc = std::stod(accident_string[i][3]);
	      //Ysize_calc = std::stod(accident_string[i][4]);
	      X.push_back(Xsize_calc);
	      Y.push_back(Ysize_calc);
	      //if (j == 55)
	      //{
	      //	  cout <<accident_string[i][3]<< " "<<Xsize_calc<<" "<<accident_string[i][4]<<" "<<Ysize_calc<<endl;
	      //}
	    }
	}
      double sumX = 0;
      double sumY = 0;
      for (size_t i=0; i<X.size(); ++i)
	{
	  sumX = sumX +X[i];
	  sumY = sumY +Y[i];
	}
      double meanX = sumX/X.size();
      double meanY = sumY/Y.size();
      double varX = 0;
      double varY = 0;
      for (size_t i=0; i<X.size(); ++i)
	{
	  varX = varX+(X[i]-meanX)*(X[i]-meanX);
	  varY = varY+(Y[i]-meanY)*(Y[i]-meanY);
	}      
      X_size[j] = sqrt(varX/X.size());
      Y_size[j] = sqrt(varY/Y.size());
      cout << "District: "<<j<< " Area: "<<3.1415926535897*X_size[j]*Y_size[j]<<endl;
    }
    
  cout << "by year"<< endl;
  for (int j= 5;j<15; ++j)
    {
      cout <<"Year: "<<2000+j<< " Number: "<<year[j]<< endl;
    }
  cout << "by hour"<< endl;
  for (int j= 0;j<24; ++j)
    {
      ratio = hour_fatal[j]/hour[j];
      cout <<"Hour: "<<j << " Ratio: " <<ratio << endl;
    }

  int age[100];
  int convert;
  for (size_t i=0; i<vehicle_string.size(); ++i)
    {
      istringstream (vehicle_string[i][15] )>>convert;
      if (convert >16) //age brackets
      	{
	     	  age[convert]= age[convert] +1;
      	}
    }
  cout << "Ages"<< endl;
  for (int j= 16;j<99; ++j)
    {
      cout << "Ages:"<<j <<" Number: "<<age[j]<< endl;
    }

  double males[]={0.0,0.0};
  double females[]={0.0,0.0};
  double jack_knife[]={0.0,0.0};
   for (size_t i=0; i<vehicle_string.size(); ++i)
    {
      for (size_t j=0; j<accident_string.size(); ++j)
	{
	  if (accident_string[j][0] == vehicle_string[i][0])
	    {
	      if (vehicle_string[i][14] == one) //males
		{
		  if (accident_string[j][2] == one)
		    {
		      males[0] = males[0] +1;
		    } 
		  males[1] = males[1] +1;
		}
	      if (vehicle_string[i][14] == two) //females
		{
		  if (accident_string[j][2] == one)
                    {
		      females[0] = females[0] +1;
                    }
                  females[1] = females[1] +1;
		}
	      if ((vehicle_string[i][14] != zero) && (vehicle_string[i][14] != neg)) //skidding
		{
		  if (accident_string[j][25] == one)//weather
		    {
		      ++jack_knife[1];
		    }
		  if ((accident_string[j][25] == two) || (accident_string[j][25] == three) || (accident_string[j][25] == five) || (accident_string[j][25] == six))//weather 
                    {
		      ++jack_knife[0];
		    }
		}
	    }
	}
	}
  cout << "Fraction in Urban areas: " << urban/accident_string.size()<<endl;
  cout << "Number of times more likely to skid in bad weather" << jack_knife[0]/jack_knife[1]<<endl;
  cout << "Ratio of male driver fatalities to female driver fatalities"<<males[0]*females[1]/(males[1]*females[0])<<endl;
  return 0;
}

