#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
using namespace std;

struct Deposit
{
	unsigned int ID;
	unsigned int value;
	unsigned int loss;
};

//subset method. brute force
vector<Deposit*> gDeposits;

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Usage: LeastLossFD input.csv" << endl;
		return -1;	
	}
	cout << "Given a list of fixed deposits, some of which have to be closed prematurely to make a given sum,"
		<< " this program gives out the list of deposits to be closed for minimal loss" << endl;
	//read FDs from a csv
	ifstream infile("input.csv");
	if(!infile.is_open())
	{
		cout << "Couldn't open file" << endl; 
		return -1;
	}	
	string line;
	while(std::getline(infile, line))
	{
		cout << line;	
	}
	
	return 0;
}
