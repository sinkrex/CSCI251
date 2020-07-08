/********************************************************************
* CSCI251 - Assignment 2
* Kazi Swad Abdullah - ksa255
* APE.h - Contains the header file for the politcal election simulation
*********************************************************************/
#include <fstream>
#include <string>
#include <vector>

class stance
{
 private:
  int significance;
  int approach;
 public:
 stance();
 void report();
 int getValue();
};

class issue
{
 private:
  stance climateChange;
  stance Jobs;
  stance Defence;
  stance Exports;
  stance Crime;
  std::string stances[5] = {"Climate Change","Jobs","Defence","Exports","Crime"};
  stance position[5] = {climateChange,Jobs,Defence,Exports,Crime};

 public:
  void report();
  int getValue();
};

class member
{
 public:
  int popularity;
  int experience;
  issue position;
  member();
  void report();
  int getValue();
};

class electoralParty
{
 public:
  int electorateCampaignManager;
  member Candidate;
  electoralParty();
  void report();
};

class nationalParty
{
 public:
  int nationalCampaignManager;
  int nationalFinanceManager;
  member Leader;
  int NoOfElectorates;
  issue position;
  std::string Name;
  int initial;
  int funding[30];
  int spending[30];
  electoralParty parties[10];
  nationalParty(int electorates, std::string name);
  void report();
};

class Electorates
{
 public:
  int vOfExp;
  issue position;
  int NoofVoters;
  Electorates();
  int getValue();
};

class Nation
{
 public:
  Electorates areas[10];
  std::string Name;
  int sum = 0;
  int NOofelectorates = 0;
  Nation(int electorates, std::string name);
  void report();
};

class Event
{
 public:
  std::vector<int>value;
  void setval(std::vector<int>val);
};

class NationalEvent: public Event
{
 private:
  std::vector<int> event = {1,2,3,4,5};
  std::vector<int> probability1 = {10,15,15,30,30};
  std::vector<int> likelyhood = {0,1};
  std::vector<int> probability2 = {70,30};

 public:
  std::vector<int>val;
  NationalEvent();
 };

 class ElectoralEvent: public Event
{
 private:
  std::vector<int> event = {1,2,3,4,5};
  std::vector<int> probability1 = {10,15,15,30,30};
  std::vector<int> likelyhood = {0,1};
  std::vector<int> probability2 = {80,20};

 public:
  std::vector<int>val;
  ElectoralEvent();
};

void checkInput(int argc, char* argv[]);
void Report(nationalParty Labour, nationalParty Liberal, nationalParty Greens, Nation Australia);
void Campaign(nationalParty Labour, nationalParty Liberal, nationalParty Greens, NationalEvent N, ElectoralEvent E[]);
void Election(nationalParty Labour, nationalParty Liberal, nationalParty Greens,Nation Australia);
