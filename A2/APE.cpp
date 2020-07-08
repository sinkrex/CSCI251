/********************************************************************
* CSCI251 - Assignment 2
* Kazi Swad Abdullah - ksa255
* APE.cpp - Contains the class implentation and function definitions for the politcal election simulation
*********************************************************************/

#include <iostream>
#include <stdio.h>
#include <string>
#include <time.h>
#include <random>
#include <chrono>
#include <vector>
#include <cstdlib>
#include "APE.h"

using namespace std;

/** Global Data **/
static int electorates;
static int campaignDays;
static int LabourEventImpact;
static int LiberalEventImpact;
static int GreensEventImpact;
unsigned seed =  chrono::system_clock::now().time_since_epoch().count();
static default_random_engine randEng(seed);

// Constructor for the stance class which assigns a random number to significance and approach
stance::stance()
{
 significance  = randEng()%9 + 1;
 approach =  randEng()%9 + 1;
}

// Reports the significance and approach of stace object to stdout
void stance::report()
{
 cout<<"(Significance, Approach) : ("<<significance<<","<<approach<<")"<<endl;
}

// Getter fucntion for the combined significance and approach of the stace object
int stance::getValue()
{
 return(significance + approach);
}

// Reports the significance and approach of all the issues in the issues object to stdout
void issue::report()
{
 for(int i=0;i<5;i++)
 {
  cout <<stances[i]<<" stance: ";
  position[i].report();
 }
 cout<<endl;
}

// Getter fucntion for the combined significance and approach of all the issues (stace objects) in the issues object
int issue::getValue()
{
 int x = climateChange.getValue() + Jobs.getValue() + Defence.getValue() + Exports.getValue() + Crime.getValue();
 return x;
}

// Constructor for the stance class which assigns a random number to popularity and experince
member::member()
{
 popularity = randEng() % 100 + 1;
 experience = randEng() % 100 + 1;
}

// Reports the popularity and experience of the member and all their stance positon to stdout
void member::report()
{
 cout<<"Popularity: "<<popularity<<endl;
 cout<<"Experience: "<<experience<<endl;
 cout<<endl;
 position.report();
}

// Getter fucntion for the combined significance and approach of all the member stance
int member::getValue()
{
 return position.getValue();
}

// Constructor for the electoralParty class which assigns a random number to electoral campaign manager
electoralParty::electoralParty()
{
 electorateCampaignManager = randEng()% 9 + 1;
}

// Reports the the relevant information of the electoral party to stdout
void electoralParty::report()
{
 cout<<"-----Electoral Candidate-----\n"<<endl;
 Candidate.report();
 cout<<"Electoral Campaign Manager Value: "<<electorateCampaignManager<<endl;
}

// Constructor for the nationalParty class which assigns a random number to national campaign manager and national finanace manager, sets initial funding,
// sets the name of the party and the number of electorates it serves. The initial funding is a random number between 1000 to 10000. Its also creates an
// array of object of the electoralPart class that are to be represented by the national party. Detials of the electoral party are given below.

nationalParty::nationalParty(int electorates, string name)
{
 nationalCampaignManager = randEng() %9 + 1;
 nationalFinanceManager = randEng() %9 + 1;
 initial = randEng() % 9000 + 1000;
 Name = name;
 NoOfElectorates = electorates;
 for (int i=0; i<electorates; i++)
 {
  electoralParty temp;
  parties[i] = temp;
 }
}

// Reports the the relevant information of the national party to stdout
void nationalParty::report()
{
 cout << "Party Name: "<<Name<<endl;
 cout <<endl;
 cout << "National Parties stances on issue of concern are shown below: \n"<<endl;
 position.report();
 cout<<"National Party Leaders popularity,experience and stance on issues shown below: \n"<<endl;
 Leader.report();
 cout << "National Party Campaign Manager Value: "<<nationalCampaignManager<<endl;
 cout << "National Party Finance Manager Value: "<<nationalFinanceManager<<endl;
 cout << "National Party Initial Funding: $"<<initial<<endl;
 cout<<endl;

 for (int i = 0; i<NoOfElectorates; i++)
 {
  cout<< "For electorate "<<i+1<<": "<<"Electoral Candidate popularity,experience and stance on issues shown below: \n"<<endl;
  parties[i].Candidate.report();
  cout<<endl;
  cout<< "For electorate "<<i+1<<": "<<"Electoral Campaign Manager Value: "<<parties[i].electorateCampaignManager<<endl;
  cout<<endl;
 }
 cout<<endl;
}

// Constructor for the Electorates class
Electorates::Electorates()
{
 vOfExp = randEng() %9 + 1;
 NoofVoters = randEng() % 9000 + 1000;
}
int Electorates::getValue()
{
 return position.getValue();
}

Nation::Nation(int electorates, string name)
{
 Name = name;
 NOofelectorates = electorates;
 for (int i=0; i<electorates; i++)
 {
  Electorates temp;
  areas[i] = temp;
  sum += temp.NoofVoters;
 }
}
void Nation::report()
{
 cout << "Nation Name: "<<Name<<endl;
 cout << "Nation Number of Voters: "<<sum<<endl;
 cout<<endl;
 for (int i=0; i<NOofelectorates; i++)
 {
  cout<< "For electorate "<<i+1<<": "<<"Electorates value for expereince: "<<areas[i].vOfExp<<endl;
  cout<< "For electorate "<<i+1<<": "<<"Number of Voters: "<<sum/NOofelectorates<<endl;
  cout<<endl;
  cout<< "For electorate "<<i+1<<": "<<"Electorates stance values shown below: \n"<<endl;
  areas[i].position.report();
 }
}
int random(vector<int> const &input, vector<int> const &probability)
{
	int n = input.size();
	if (n != probability.size())
		return -1;

	vector<int> prob_sum(n, 0);

	prob_sum.at(0) = probability.at(0);
	for (int i = 1; i < n; i++)
		prob_sum.at(i) = prob_sum.at(i-1) + probability.at(i);

	int r = (randEng() % 100) + 1;

	if (r <= prob_sum.at(0))
		return input.at(0);

	for (int i = 1; i < n; i++)
	{
		if (r > prob_sum.at(i-1) && r <= prob_sum.at(i))
			return input.at(i);
	}
}

void Event::setval(vector<int>val)
{
 for (int i=0; i<val.size(); i++)
  value.push_back(val[i]);
}

NationalEvent::NationalEvent()
{
 for (int i = 0; i < campaignDays; i++)
 {
  if (random(likelyhood, probability2)==1)
  {
   val.push_back(random(event, probability1));
  }
  else
  {
   val.push_back(0);
  }
 }
 setval(val);
}

ElectoralEvent::ElectoralEvent()
{
 for (int i = 0; i < campaignDays; i++)
 {
  if (random(likelyhood, probability2)==1)
  {
   val.push_back(random(event, probability1));
  }
  else
  {
   val.push_back(0);
  }
 }
 setval(val);
}
void checkInput(int argc, char* argv[])
{
  if (argc!=3)
  {
   cerr <<"\nERROR: There should be only two values as input"<<endl;
   exit(1);
  }

  for (int i = 1; i < argc; i++)
  {
    string s(argv[i]);
    for (int i = 0; i < s.length(); i++)
    {
        if (isdigit(s[i]) == false)
        {
            cerr <<"\nERROR: "<<s<<" is not a numeric integer."<<endl;
            exit(1);
        }
    }
  }

  string s1(argv[1]);
  electorates = stoi(s1);
  string s2(argv[2]);
  campaignDays = stoi(s2);

  if (electorates>10 || electorates<1)
  {
   cerr <<"\nERROR:  number of electorates should be in the range 1 to 10 inclusive"<<endl;
   exit(1);
  }

  if (campaignDays>30 || campaignDays<1)
  {
   cerr <<"\nERROR:  number of campaign days should be in the range 1 to 30 inclusive"<<endl;
   exit(1);
  }
}

void Report(nationalParty Labour, nationalParty Liberal, nationalParty Greens, Nation Australia)
{
 cout << "------------------Party Report---------------\n"<< endl;
 Labour.report();
 cout << endl;
 Liberal.report();
 cout << endl;
 Greens.report();
 cout << endl;
 cout << "------------------Nation Report---------------\n"<< endl;
 Australia.report();
}
// The campaign function calculates the money spent and money earned each election day for each party
// and prints out the results
void Campaign(nationalParty Labour, nationalParty Liberal, nationalParty Greens, NationalEvent N, ElectoralEvent E[])
{
 string nationalevents[] = {"Leaders Debate","Leader Event 1","Leader Event 2","National Issue Impact Event 1","National Issue Impact Event 2"};
 string electoralevents[] = {"Local Deabte","Candidate Event 1","Candidate Event 2","Local Issue Impact Event 1","Local Issue Impact Event 2"};

 cout <<"------------------Campaign Report---------------\n"<< endl;
 for(int i=0; i<campaignDays; i++)
 {
  cout << "For Campaign Day "<<(i+1)<<": "<<Labour.Name<<" initially had: $"<<Labour.initial<<", gained : $"<<Labour.nationalFinanceManager*100<<", spent : $"<<Labour.initial/Labour.nationalCampaignManager;
  Labour.initial -= Labour.initial/Labour.nationalCampaignManager;
  Labour.initial += Labour.nationalFinanceManager*100;
  cout <<" and finally had : $"<<Labour.initial<< endl;

  cout << "For Campaign Day "<<(i+1)<<": "<<Liberal.Name<<" initially had: $"<<Liberal.initial<<", gained : $"<<Liberal.nationalFinanceManager*100<<", spent : $"<<Liberal.initial/Liberal.nationalCampaignManager;
  Liberal.initial -= Liberal.initial/Liberal.nationalCampaignManager;
  Liberal.initial += Liberal.nationalFinanceManager*100;
  cout <<" and finally had : $"<<Liberal.initial<< endl;

  cout << "For Campaign Day "<<(i+1)<<": "<<Greens.Name<<" initially had: $"<<Greens.initial<<", gained : $"<<Greens.nationalFinanceManager*100<<", spent : $"<<Greens.initial/Greens.nationalCampaignManager;
  Greens.initial -= Greens.initial/Greens.nationalCampaignManager;
  Greens.initial += Greens.nationalFinanceManager*100;
  cout <<" and finally had : $"<<Greens.initial<< endl;

  if(N.value[i] != 0)
  {
   cout << "For Campaign Day "<<(i+1)<<": " << "National Event --"<<nationalevents[(N.value[i]-1)]<<"--took place."<<endl;
  }

  for(int x =0; x<electorates; x++)
  {
   if(E[x].value[i] != 0)
   {
    cout << "For Campaign Day "<<(i+1)<<": " <<"In Electorate :"<<(x+1)<<" Electoral Event --"<<electoralevents[(E[x].value[i]-1)]<<"--took place."<<endl;
   }
  }
  cout<<endl;
 }
}

// Election Function calculates the votes that each part got in each electorate and then prints out the results
// It also declares the winner of the elelction campaign
void Election(nationalParty Labour, nationalParty Liberal, nationalParty Greens,Nation Australia)
{
 int LabourElectorates = 0;
 int LiberalElectorates = 0;
 int GreensElectorates = 0;
 cout <<"------------------Election Report---------------\n"<< endl;
 for (int i = 0; i<electorates; i++)
 {
  double x = (Labour.parties[i].Candidate.popularity) - abs((Australia.areas[i].getValue())-(Labour.parties[i].Candidate.getValue()));
  double y = (Liberal.parties[i].Candidate.popularity) - abs((Australia.areas[i].getValue())-(Liberal.parties[i].Candidate.getValue()));
  double z = (Greens.parties[i].Candidate.popularity) - abs((Australia.areas[i].getValue())-(Greens.parties[i].Candidate.getValue()));
  if (x<0) x=0;
  if (y<0) y=0;
  if (z<0) z=0;
  double total = x+y+z;
  cout<<"Labour recieved "<<lround((x/total)*Australia.areas[i].NoofVoters)<<" votes for electorate :"<<(i+1)<<endl;
  cout<<"Liberal recieved "<<lround((y/total)*Australia.areas[i].NoofVoters)<<" votes for electorate :"<<(i+1)<<endl;
  cout<<"Greens recieved "<<lround((z/total)*Australia.areas[i].NoofVoters)<<" votes for electorate :"<<(i+1)<<endl;
  if (x>=y && x>=z)
  {
   cout<<"Labour won electorate :"<<(i+1)<<endl;
   LabourElectorates +=1;
  }

  if (y>=x && y>=z)
  {
   cout<<"Liberal won electorate :"<<(i+1)<<endl;
   LiberalElectorates +=1;
  }

  if (z>=x && z>=y)
  {
   cout<<"Greens won electorate :"<<(i+1)<<endl;
   GreensElectorates +=1;
  }
  cout<<endl;
 }
 cout<<"Number of Electorates Labour Won: "<<LabourElectorates<<endl;
 cout<<"Number of Electorates Liberal Won: "<<LiberalElectorates<<endl;
 cout<<"Number of Electorates Greens Won: "<<GreensElectorates<<endl;
 cout<<endl;
 if (LabourElectorates>(electorates/2)) cout<< "Labour rules over Australia"<<endl;
 else if (LiberalElectorates>(electorates/2)) cout<< "Liberal rules over Australia"<<endl;
 else if (GreensElectorates>(electorates/2)) cout<< "Greens rules over Australia"<<endl;
 else cout<< "Hung Parliment"<<endl;
}
