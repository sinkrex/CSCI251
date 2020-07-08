/********************************************************************
* CSCI251 - Assignment 1
* Kazi Swad Abdullah - ksa255
* RAT.cpp - Contains the function definitions for customer order processing system
*********************************************************************/

#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
#include <random>
#include <chrono>

using namespace std;

/** Constants **/

const int MaxCustomers = 100; // Maximum Number of Customers the array can hold
const int MaxParts = 50;      // Maximum Number of Parts the array can hold
const int MaxBuilders = 50;   // Maximum Number of Builders the array can hold.

/** User Defined Types **/

struct Customers{string name;string robot;string parts;int PrtNum[5] ={0};};   //Structure of Customers with elements name,robot, parts, PrtNum - which is the number of parts A to E
struct Parts{char partCode;string partName;int Min;int Max;int complexity;};   //Sructure of Parts with elements partCode, partName, Min, Max, complexity
struct Builders{string name;int ability;int variability;};                     //Structure of Parts with elements name,ability,variability

/** Global Data **/

 Customers C [MaxCustomers]; // Declaring an array of Customer C
 Builders B [MaxBuilders];   // Declaring an array of Buidlers B
 Parts P [MaxParts];         // Declaring an array of Parts P
 int NumCust = 0;            // Counts the number of customers
 int NumBld = 0;             // Counts the number of Builders
 int NumPrts = 0;            // Counts the number of Parts
 bool ValidData = true;      // If not true, then errors printed on screen and program aborted
 unsigned seed =  chrono::system_clock::now().time_since_epoch().count(); //Creates as seed for the random engine
 static default_random_engine randEng(seed);   // Declaring a static Random Engine

/** isNumber Function - returns true if s is a number else false**/

bool isNumber(string s)
{
    for (int i = 0; i < s.length(); i++)
        if (isdigit(s[i]) == false)
            return false;

    return true;
}

 /** ReadData Function - reads data from file and stores it in the array of structures**/

 void ReadData(char* file1, char* file2, char* file3)
{
 ifstream Customers;
 Customers.open(file1); // Creates a input file stream for the customers
 ifstream Parts;
 Parts.open(file2); // Creates a input file stream for the parts
 ifstream Builders;
 Builders.open(file3); // Creates a input file stream for the builders
 string line;
 int num = 0;
 int x = 1;
 string temp;

 if ((file1 == NULL) || (file2 == NULL) || (file3 == NULL)) // Checks whether the three input file have been entered, if not diplays error and aborts
 {
  cerr<<"\nOne or more files missing, Please enter three files containing the Customers, Parts and Builders\n"<<endl;
  exit(1);
 }
 else  //
 cout<<"\n\n Reading Orders............................................\n\n"<<endl; // Displays the current status of program

 // Checks whether file one containing the customers exists or not, if not an error message printed and the program is aborted
 if (!Customers)
 {
  cerr <<"\nFILE ERROR "<<x<<": The file " << file1 << " could not be opened or does not exist."<<endl;
  ValidData = false;
  x++;
 }

 // Checks whether file two containing the parts exists or not, if not an error message printed and the program is aborted
 if (!Parts)
 {
  cerr <<"\nFILE ERROR "<<x<<": The file " << file2 << " could not be opened or does not exist."<<endl;
  ValidData = false;
  x++;
 }

  // Checks whether file three containing the builders exists or not, if not an error message printed and the prorgam is aborted
 if (!Builders)
 {
  cerr <<"\nFILE ERROR "<<x<<": The file " << file3 << " could not be opened or does not exist."<<endl;
  ValidData = false;
  x++;
 }

 if (!ValidData) exit(1); // If ValidData is set to false for any of the previous cases the program aborts

 // Reads data from the customer file and stores it in the array of Customers C
 while(getline(Customers,line))
 {
  stringstream s(line);
  getline(s,C[NumCust].name,':');
  getline(s, C[NumCust].robot ,':');
  getline(s, C[NumCust].parts,'.');
  NumCust++;
 }

  // Reads data from the parts file and stores it in the array of Parts P
 while(getline(Parts,line))
 {
  stringstream s(line);
  getline(s,temp,':');
  P[NumPrts].partCode = temp[0];
  getline(s,P[NumPrts].partName,':');
  getline(s,temp,':');
  num = stoi(temp);
  P[NumPrts].Min = num;
  getline(s,temp,':');
  num = stoi(temp);
  P[NumPrts].Max = num;
  getline(s, temp,'.');
  num = stoi(temp);
  P[NumPrts].complexity = num;
  NumPrts++;
 }

  // Reads data from the builders file and stores it in the array of Builders B
 while(getline(Builders,line))
 {
  stringstream s(line);
  getline(s,B[NumBld].name,':');
  getline(s,temp,':');
  if (isNumber(temp)) // Checks whether value is a numeric or not, if not program aborts
  num = lround(stoi(temp));
  else
  {
   cerr <<"\nERROR: "<<temp<<" is not a numeric integer."<<endl;
   ValidData = false;
  }
  B[NumBld].ability = num;
  getline(s, temp,'.');
  if (isNumber(temp)) // Checks whether value is a numeric or not, if not program aborts
  num = lround(stoi(temp));
  else
  {
   cerr <<"\nERROR: "<<temp<<" is not a numeric integer."<<endl;
   ValidData = false;
  }
  B[NumBld].variability = num;
  NumBld++;
 }
 if (!ValidData) exit(1); // If ValidData is set to false for any of the previous cases the program aborts

 Customers.close(); // Closes Customer File
 Parts.close(); // Closes Parts File
 Builders.close(); // Closes Builders File
}

/** CheckParts Function - checks the validity of the parts the customer has provided **/

int CheckParts(int x, bool repeat)
{
 string c = C[x].parts; // sets string c with the parts entered by customer

 if (!repeat) // We only need this part to occur once every iteration so if repeat is false, this part does not occur
 {
  for (int i=0; i< c.length(); i++) //Checks whethers parts are between A and E, and then increments PrtNum with the number of letters A to E, if not return -1
  {
   if (c.at(i)=='A'||c.at(i)=='a') C[x].PrtNum[0]++;
   else if (c.at(i)=='B'||c.at(i)=='b') C[x].PrtNum[1]++;
   else if (c.at(i)=='C'||c.at(i)=='c') C[x].PrtNum[2]++;
   else if (c.at(i)=='D'||c.at(i)=='d') C[x].PrtNum[3]++;
   else if (c.at(i)=='E'||c.at(i)=='e') C[x].PrtNum[4]++;
   else return -1;
  }
 }
 else
 {
  //Checks whether parts are in the range is between 1<=A<=2,B<=6,C<=4,D<=4,E<=6, if not return -2
  if (C[x].PrtNum[0]<1||C[x].PrtNum[0]>2||C[x].PrtNum[1]>6||C[x].PrtNum[2]>4||C[x].PrtNum[3]>4||C[x].PrtNum[4]>6)
  {
   return -2;
  }
 }
}

 /** CheckData Function - checks validity of data that has been read  **/

void CheckData()
{
 int x = 1;
 bool repeat; // variable to keep track of repeat attempts to access a function

 if (NumCust>10) //Checks whether the number of customers is less than equal to 10, if not the program aborts
 {
  cerr <<"\nINPUT ERROR "<<x<<": There cant be more than 10 customer orders"<<endl;
  ValidData = false;
  x++;
 }

 if (NumBld>5) //Checks whether the number of builders is less than equal to 5, if not the program aborts
 {
  cerr <<"\nINPUT ERROR "<<x<<": There cant be more than 5 builders"<<endl;
  ValidData = false;
  x++;
 }

 for (int i=0; i< NumCust; i++) // Itertates through every customer
 {
  if (C[i].name.empty()) //Checks whether name of the customer is empty, if it is the program aborts
  {
   cerr <<"\nINPUT ERROR "<<x<<": For Customer Number "<<i+1<<": "<<"The customers name is empty."<< endl;
   ValidData = false;
   x++;
  }

  if (C[i].robot.empty()) //Checks whether name of the robot is empty, if it is the program aborts
  {
   cerr <<"\nINPUT ERROR "<<x<<": For Customer Number "<<i+1<<": "<<"The customers robot order is empty."<< endl;
   ValidData = false;
   x++;
  }

  if (C[i].parts.size() > 10) //Checks whether the number of parts is less than 10, if not it the program aborts
  {
   cerr <<"\nINPUT ERROR "<<x<<": For Customer Number "<<i+1<<": "<<"The order has more than 10 parts."<< endl;
   ValidData = false;
   x++;
  }

  repeat = false; // States that it is not repeat attempt to call the function
  if (CheckParts(i, repeat) == -1) //Checks whether the parts the customer inputed is between A to E
  {
   cerr <<"\nINPUT ERROR "<<x<<": For Customer Number "<<i+1<<": "<<"One or More of the letters in parts are not between A and E."<< endl;
   ValidData = false;
   x++;
  }

  repeat = true;// States that it is a repeat attempt to call the function
  if (CheckParts(i, repeat) == -2) //Checks whether parts are in the range 1<=A<=2, B<=6, C<=4, D<=4, E<=6
  {
   cerr <<"\nINPUT ERROR "<<x<<": For Customer Number "<<i+1<<": "<<"The number of parts are not in the range: 1<=A<=2, B<=6, C<=4, D<=4, E<=6."<< endl;
   ValidData = false;
   x++;
  }
 }

 for (int i=0; i< NumBld; i++) //Iterates through every builder
 {
  if (B[i].name.empty()) //Checks whether name of the builder is empty, if it is the program aborts
  {
   cerr <<"\nINPUT ERROR "<<x<<": For Builder Number "<<i+1<<": "<<"The Builders name is empty."<< endl;
   ValidData = false;
   x++;
  }

  if (B[i].ability <1 || B[i].ability >99) //Checks if the builders ability is between 1 and 99, if not program aborts
  {
   cerr <<"\nINPUT ERROR "<<x<<": For Builder umber "<<i+1<<": "<<"The ability of the builder is not between 1 and 99."<< endl;
   ValidData = false;
   x++;
  }

  if (B[i].variability<1 || B[i].variability>10) //Checks if the builders variability is between 1 and 10, if not the program aborts
  {
   cerr <<"\nINPUT ERROR "<<x<<": For builder number "<<i+1<<": "<<"The variability of the builder is not between 1 and 10."<< endl;
   ValidData = false;
   x++;
  }
 }

 if (!ValidData) exit(1); //if valid data is set to false for any of the previous cases, the program aborts
}

/** WriteData Function - writes the data that has been read to standard out **/

void WriteData()
{
 cout << "------------------Customers Information---------------\n"<< endl;
 for(int i = 0; i<NumCust; i++)
 {
   cout <<"\n";
   cout <<" Customer Name: "<< C[i].name << "\n" << " Customer Robot: " <<C[i].robot << "\n" << " Robot Parts: " << C[i].parts << endl;
 }
 cout << "\n";
 cout << "------------------Parts Information--------------------\n"<< endl;
 for(int i = 0; i<NumPrts; i++)
 {
  cout <<"\n";
  cout <<" Parts Code: "<< P[i].partCode <<"\n" << " Parts Name: : "<<P[i].partName << "\n" << " Minimum Parts: " << P[i].Min<< "\n" << " Maximum Parts: "<<P[i].Max <<"\n" << " Complexity: "<< P[i].complexity << endl;
 }
 cout << "\n";
 cout << "------------------Builders Information--------------------\n"<< endl;
 for(int i = 0; i<NumBld; i++)
 {
  cout <<"\n";
  cout <<" Builder Name: "<< B[i].name << "\n" << " Builder Ability: "<<B[i].ability << "\n" << " Builder Variability: "<< B[i].variability << endl;
 }
 cout << "\n";
}

/** Complexity Function - calculates the complexity of an order**/

int Complexity (int i)
{
 int CX = 20; // Set inital complexity to 20
 CX += C[i].PrtNum[0]*P[0].complexity + C[i].PrtNum[1]*P[1].complexity + C[i].PrtNum[2]*P[2].complexity+C[i].PrtNum[3]*P[3].complexity+C[i].PrtNum[4]*P[4].complexity; // Add to the complexity the number of each part multiplied by the complexity of teh part
 if (CX>100) CX=100; // If complexity is greater than 100 it is reset to 100
 return CX;
}

/** Variability Function - calculates the overall robot variability of an order**/

int Variability(int VBofB, string part)
{
 int VB = 5 + VBofB + part.length(); // The variability is equal to 5 + variability of the builder + the number of parts
 return VB;
}

/** GenerateRandom Function - generates a random from normal distribution **/

int GenerateRandom (int a, int b)
{
 static normal_distribution<> normal(a,b); //Creates a normal distribution from the mean a and standard deviation b
 int r = lround(normal(randEng)); // Generates a random number from the normal distribution created earlier
 return r;
}

/** WriteOrder Function - writes the order being processed to std out and to the output file**/

void WriteOrder(int i, int r,ofstream &Output)
{
  cout << "------------------Order Number: "<<i+1<<"--------------------------"<<endl;
  cout << " Customer Name: " << C[i].name <<"\n Robot being built: "<< C[i].robot <<"\n Builder Assigned: "<<B[r].name<<endl;
  cout << "\n";

  Output << "------------------Order Number: "<<i+1<<"--------------------------"<<endl;
  Output << " Customer Name: " << C[i].name <<"\n Robot being built: "<< C[i].robot <<"\n Builder Assigned: "<<B[r].name<<endl;
  Output << " Complexity: " << Complexity(i)<<"\n Variability: "<< Variability(B[r].variability,C[i].parts)<<endl;
  Output << "\n";
}

/** WriteOResult Function - writes the result of the order being processed to std out and to the output file**/

void WriteResult(int attempt, int number, int CX, bool failure, ofstream &Output)
{
 if (failure==false) //If failure is false the following executes
 {
  cout << " Attempt: "<<attempt+1<<", where the random value generated is "<< number<<", and the complexity is "<<CX<<", has been a success."<<endl;
  Output << " Attempt: "<<attempt+1<<", where the random value generated is "<< number<<", and the complexity is "<<CX<<", has been a success."<<endl;
 }
 else // If failure is true the following executes
 {
  cout << " Attempt: "<<attempt+1<<", where the random value generated is "<< number<<", and the complexity is "<<CX<<", has been a failure."<<endl;
  Output << " Attempt: "<<attempt+1<<", where the random value generated is "<< number<<", and the complexity is "<<CX<<", has been a failure."<<endl;
 }
 cout<<"\n";
 Output<<"\n";
}

/**  BuildOrder Function - assigns a builder to an order and attempts to build the robot*/

void BuildOrder (char* file4)
{
 if (file4 == NULL) // If the Output file is not entered the following error mesage executes and the program aborts
 {
  cerr<<"\nOutput File missing, Please enter the name of the output file.\n"<<endl;
  exit(1);
 }
 else
 cout<<"\n\n Processing Orders............................................\n\n"<<endl; //Displays the current status of the program

 ofstream Output;
 Output.open(file4); //Creates an output file stream for the output
 int i = 0;
 static uniform_int_distribution<int> uniform(0, (NumBld-1)); // Create an uniform distribution to choose a random builder, range equals to the number of builders

 while (i<NumCust) // Iterates for all the customers
 {
  int r = uniform(randEng);  //Generates a random number from the uniform distribution created earlier
  bool iterate = true;       //Check whether function should iterate or not
  int attempt = 0;           //Tracks the number of attempts
  int CX = Complexity(i); // Calculates the Complexity of the order
  int VB = Variability(B[r].variability,C[i].parts); // Calculates the overall robot complexity
  WriteOrder (i,r, Output); // Call to WriteOrder function

  while(iterate && attempt < 3) //Iterates as long as iterate is true i.e build unsuccessful or the number of attempts exceed 3
  {
   int number = GenerateRandom(B[r].ability,VB); //Call to Generate Random function, where mean is the ability of the builder assigned and standard deviation is teh overall variability of the robot
   if ((number+= 5*attempt) >= CX) // Occurs if number generated is greater than the overall complexity and the build is successfull
   {
    iterate = false;
    WriteResult(attempt,number,CX,iterate,Output); //Call to WriteResult function
   }
   else // Occurs if number generated is less than the overall complexity and the build is a failure
   {
    iterate = true;
    WriteResult(attempt,number,CX,iterate,Output); //Call to WriteResult function
    attempt++;
   }
  }
  i++;
 }
 Output.close(); //Closes the output file stream
}
