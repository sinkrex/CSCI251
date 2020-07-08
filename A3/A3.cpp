/********************************************************************
* CSCI251 - Assignment 3
* Kazi Swad Abdullah - ksa255
* A3.cpp - Contains the function and class definitions for the
           knapsack resource allocation program
*********************************************************************/

#include <iostream>
#include <stdio.h>
#include <string>
#include <vector>
#include "collect.h"
#include <bits/stdc++.h>

using namespace std;

// Knapsack class which accepts objects of the class A to G, and adds them as they arrive,
// if they fit. An instance of this class stores the size and name of the object as they
// arrive.
class Knapsack
{
 private:
     int initialSize; // initialSize of knapsack as defined by user input.
     int remainingSize; // remainingSize of knapsack, which is decremented as objects are inserted.
     vector<int>size1; // stores the sizes of the objects as they are added.
     vector<char>object; // stores the name of the objects as they are added.
 public:
     Knapsack(int Size); // prototype of the knapsack constructor
     template<typename T> bool addIt(T& n); // prototype of the template function
     void report1(); // prototype for report1
     void report2(); // protype for report2
};

// Knapsack constructor which takes the input from user for the size
// of the knapsack and sets the size for the inital and remining size
// accordingly.
Knapsack::Knapsack(int Size)
{
 remainingSize = Size; // Set remainingSize to Size
 initialSize = Size; // Set initialSize to Size
}

// Template function that takes an object of a class and adds it to
// the knapsack if it fits. If it fits the remaingSize is decremented
// by the size of the object. Furthermore, its size and name are stored in the size
// and name vector respectively.
template<class T> bool Knapsack::addIt(T& n)
{
 int x = remainingSize-sizeof(n); // set x to the remaining size of the knapsack - the size of object

 if (x>=0) // condition occurs if x is greater than 0
 {
  remainingSize = x; // decrement remaining size of the by the size of the object
  size1.push_back(sizeof(n)); //add the size of the object added to vector size1
  char c = n.getName(); // get the name of the object
  object.push_back(c); // add the name of the obejct to vector object
  return true; // set return value to true
 }
 else {return false;} // if x is not greater than 0, the return value is set to false
}

// Report 1, reports on the knapsacks initial size, the size of the added objects, and
// the object types in the order they are added.
void Knapsack::report1()
{
 cout<<"\nKnapsack size: "<<initialSize<<"\n"<<endl; // Prints the initial size of the knapsack
 cout<<"Added object size: "<<initialSize-remainingSize<<"\n"<<endl; // Prints the size of the combined size of the objects added
 for (int i = 0; i < object.size(); i++) // Iterates for all the elements stored in the object vector
 {
  cout << object[i]; // Prints the object type stored in index i
 }
 cout<<"\n"<<endl;
}

// Report 2, reports on the list of object types in alphabetical order with the size of
// each type and the number of each included.
void Knapsack::report2()
{
 sort(object.begin(), object.end()); // Sort object by alpahbetical order
 sort(size1.begin(), size1.end()); // Sort size1 by numeric order
 int counter = 0; // Set counter to 0
 for (int i = 0; i < object.size(); i++) //Iterate for all the elembers in the vector
 {
  if (object[i] == object[i+1]) counter++; //Increment counter if first element in object is the same as the next element in the vector.
  else
  {
   counter++; //Increment counter
   cout << object[i] <<": "<<size1.at(i)<<", "<<counter<<endl ; // Prints and object type, its size and the number of objects the knapsack contains
   counter = 0; //Set counter to 0
  }
 }
 cout<<"\n"<<endl;
}

// The checkInput function checks the input to see if it is only two inputs and if the
// the inputs added are positive integers.
void checkInput(int argc, char* argv[])
{
  if (argc!=3) // Returns error message and aborts if number of arguments is more or less than 2
  {
   cerr <<"\nERROR: There should be only two values as input"<<endl;
   exit(1);
  }

  for (int i = 1; i < argc; i++) // Returns error message and aborts if the user inputs are not positive numeric integer
  {
    string s(argv[i]);
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]) == false)
        {
            cerr <<"\nERROR: "<<s<<" is not a numeric positive integer."<<endl;
            exit(1);
        }
    }
  }

  string s1(argv[1]);
  int Size = stoi(s1); // Set Size to the first user input
  string s2(argv[2]);
  int seed = stoi(s2); // Set seed to the second user input

  if (Size<=0) //Returns error message and aborts if Size is not positive
  {
   cerr <<"\nERROR: "<<s1<<" is not a numeric positive integer"<<endl;
   exit(1);
  }

  if (seed<=0) //Returns error message and aborts if seed is not positive
  {
   cerr <<"\nERROR: "<<s2<<" seed is not a numeric positive integer"<<endl;
   exit(1);
  }
}

// Drive function which demonstrates the functionlaity of the Knapsack class
int main(int argc, char *argv[])
{
 checkInput(argc,argv); // Function call to checkInput, which checks the user input to command line
 bool iterate = true; // Set iterate to true
 Knapsack KAP(stoi(argv[1])); // Creates an object of the Knapsack class and sets its inital size to the first user input

 while(iterate) //Loops as long as iterate is true
 {
  char c = generate(stoi(argv[2])); // the generate function, generates a character between A to G and sets it character c
  if (c=='A') // if c is A, it creates an object of class A and adds it to the knapsack object
  {
   A a;
   iterate = KAP.addIt<A>(a);
  }
  else if (c=='B') // if c is B, it creates an object of class B and adds it to the knapsack object
  {
   B b;
   iterate = KAP.addIt<B>(b);
  }
  else if (c=='C') // if c is C, it creates an object of class C and adds it to the knapsack object
  {
   C c;
   iterate = KAP.addIt<C>(c);
  }
  else if (c=='D') // if c is D, it creates an object of class D and adds it to the knapsack object
  {
   D d;
   iterate = KAP.addIt<D>(d);
  }
  else if (c=='E') // if c is E, it creates an object of class E and adds it to the knapsack object
  {
   E e;
   iterate = KAP.addIt<E>(e);
  }
  else if (c=='F') // if c is F, it creates an object of class F and adds it to the knapsack object
  {
   F f;
   iterate = KAP.addIt<F>(f);
  }
  else if (c=='G') // if c is G, it creates an object of class G and adds it to the knapsack object
  {
   G g;
   iterate = KAP.addIt<G>(g);
  }
  else // if c is not between A to G, reports error to cerr and exits
  {
   cerr<<"The character generated in not withing the range A to G, the program will therfore abort, please try with a different seed."<<endl;
   exit(1);
  }
 }

 KAP.report1(); // Call to report1 function of the Knapsack object created.
 KAP.report2(); // Call to report2 function of the Knapsack object created.

 return 0;
}


