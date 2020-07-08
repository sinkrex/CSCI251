/********************************************************************
* CSCI251 - Assignment 1
* Kazi Swad Abdullah - ksa255
* RAT.h - Contains the header file for customer order processing system
*********************************************************************/
#include <fstream>
#include <string>

 void ReadData(char*, char*, char*); // Function Prototype for ReadData()
 int CheckParts(int x, bool repeat);
 void CheckData(); // Function Prototype for CheckData()
 void WriteData(); // Function Prototype for WriteData()
 int Complexity (int x);
 int Variability(int v, std::string);
 int GenerateRandom (int a, int b);
 void WriteOrder(int i, int r,std::ofstream &Output);
 void WriteResult(int attempt, int number, int CX, bool i, std::ofstream &Output);
 void BuildOrder(char*); // Function Prototype for BuildOrder()


