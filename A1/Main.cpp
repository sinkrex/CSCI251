/********************************************************************
* CSCI251 - Assignment 1
* Kazi Swad Abdullah - ksa255
* Main.cpp - Contains the driver function for customer order processing system
*********************************************************************/
#include "RAT.h"

int main(int argc, char *argv[])
{
 ReadData(argv[1],argv[2],argv[3]); // Function call to Read()
 CheckData(); // Function call to CheckData()
 WriteData(); // Function call to WriteData()
 BuildOrder(argv[4]); // Fucntion call to BuildOrder()

 return 0;
}
