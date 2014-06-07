#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cstdlib>
#include <set>
#include <climits>
using namespace std;

struct Deposit
{
	string ID;
	unsigned int value;
	unsigned int loss;
};

unsigned int sum = 0;

//subset method. brute force
vector<Deposit*> gDeposits;

void PrintDeposits()
{
    cout << "Deposits read" << endl;
    unsigned int size = gDeposits.size();
    for(unsigned int i = 0 ; i < size ; ++i)
    {
        Deposit *d = gDeposits[i];
        cout << "(" << d->ID << "," << d->value << "," << d->loss << ")" << endl;
    }
}

void ReadDepositsFile(string fileName)
{
	//read FDs from a csv
	ifstream infile(fileName.c_str());
	if(!infile.is_open())
	{
		cout << "Couldn't open file" << endl; 
		exit(0);
	}

    string line;
    //get the sum
    std::getline(infile, line);
    sum = atoi(line.c_str());
    cout << "Sum : " << sum << endl;

	while(std::getline(infile, line))
	{
        if(line.find("#") == 0)
            continue;
        stringstream ss(line);
        string token;
        int tokenID = 0;
        Deposit* d = new Deposit();
        while(std::getline(ss, token, ','))
        {
             switch(tokenID)
             {
                 case 0: 
                     d->ID = token;
                     break;
                 case 1:
                     d->value = atoi(token.c_str());
                     break;
                 case 2:
                     d->loss = atoi(token.c_str());
                     break;
                 default:
                     cout << "Unknown token!" << endl;
                     exit(1);
             }

             ++tokenID;
        }
        gDeposits.push_back(d);
	}
    PrintDeposits();
}

void PrintSubsets(set< set<unsigned int> >& subsets)
{
    set< set<unsigned int> >::iterator tempSubsetIter = subsets.begin();
    for(; tempSubsetIter != subsets.end() ; ++tempSubsetIter)
    {
        cout << "{";

        set<unsigned int>::iterator innerSetIter = (*tempSubsetIter).begin();
        for(; innerSetIter != (*tempSubsetIter).end() ; ++innerSetIter)
        {
            cout << *innerSetIter << ",";
        }

        cout << "}" << endl;
    }
}

void GetLeastLossSubset(set< set<unsigned int> >& subsets)
{
    set< set<unsigned int> >::iterator tempSubsetIter = subsets.begin();
    set<unsigned int> minimalLossSubset;
    unsigned int minimalLoss = UINT_MAX;
    unsigned int minimalSum = 0;
    for(; tempSubsetIter != subsets.end() ; ++tempSubsetIter)
    {
        unsigned int loss = 0;
        unsigned int valueSum = 0;
        set<unsigned int>::iterator innerSetIter = (*tempSubsetIter).begin();
        for(; innerSetIter != (*tempSubsetIter).end() ; ++innerSetIter)
        {
            Deposit *d = gDeposits[*innerSetIter];
            loss += d->loss;
            valueSum += d->value;
        }
        cout << loss << "," << valueSum << endl;
        if(valueSum >= sum)
        {
            if(loss < minimalLoss)
            {
                minimalLossSubset = *tempSubsetIter;
                minimalLoss = loss;
                minimalSum = valueSum;
            }
        }
    }
    cout << "Minimal Sum : " << minimalSum << ", minimal loss : " << minimalLoss << endl;
    set<unsigned int>::iterator setIter = minimalLossSubset.begin();
    for(; setIter != minimalLossSubset.end() ; ++setIter)
    {
        Deposit *d = gDeposits[*setIter];
        cout << d->ID << "," << d->value << "," << d->loss << endl;
    }

}

void RetrieveBestDepositsSubsetMethod()
{
    //construct subsets, compute loss and sum for each subset
    //and choose the subset closest to sum(above the sum) with lowest loss
    
    set< set<unsigned int> > subsets;
    unsigned int numDeposits = gDeposits.size();

    if(numDeposits <= 0)
    {
        cout << "Nothing to do here." << endl;
        return;
    }


    subsets.insert(*new set<unsigned int>());

        
    for(unsigned int i = 0 ; i < numDeposits ; ++i)
    {

        set< set<unsigned int> > tempSubset;
        set< set<unsigned int> >::iterator tempSubsetIter = subsets.begin(); //make a copy
        for(; tempSubsetIter != subsets.end() ; ++tempSubsetIter)
        {
            set<unsigned int> x = *tempSubsetIter;
            x.insert(i);
            tempSubset.insert(x);
        }
        subsets.insert(tempSubset.begin(), tempSubset.end());
    }
    cout << "Total number of subsets : " << subsets.size() << endl;
    //PrintSubsets(subsets);
    GetLeastLossSubset(subsets);
}

int main(int argc, char* argv[])
{
	if(argc < 2)
	{
		cout << "Usage: LeastLossFD input.csv" << endl;
		return -1;	
	}

	cout << "Given a list of fixed deposits, some of which have to be closed prematurely to make a given sum,"
		<< " this program gives out the list of deposits to be closed for minimal loss" << endl;

    ReadDepositsFile(argv[1]);

    RetrieveBestDepositsSubsetMethod();

	return 0;
}
