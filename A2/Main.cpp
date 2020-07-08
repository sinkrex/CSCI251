/********************************************************************
* CSCI251 - Assignment 2
* Kazi Swad Abdullah - ksa255
* Main.cpp - Contains the driver function for the politcal election simulation system
*********************************************************************/
#include "APE.h"

using namespace std;

int main(int argc, char *argv[])
{
 checkInput(argc,argv); // Function call to checkInput

 int Electorates = atoi(argv[1]);

 nationalParty Labour(Electorates, "Labour"); //creates an object of class nationalParty
 nationalParty Liberal(Electorates, "Liberal"); //creates an object of class nationalParty
 nationalParty Greens(Electorates, "Greens"); //creates an object of class nationalParty
 Nation Australia(Electorates, "Australia"); //creates an object of class Nation

 Report(Labour,Liberal,Greens,Australia); // Function call to Report

 NationalEvent N; //Creates an object of the class NationalEvent
 ElectoralEvent E[Electorates]; //Creates an array of objects of the class ElectoralEvent
 Campaign(Labour,Liberal,Greens,N,E); // Function call to Campaign

 Report(Labour,Liberal,Greens,Australia); // Function call to Report

 Election (Labour,Liberal,Greens,Australia); // Function call to Election

 return 0;
}
