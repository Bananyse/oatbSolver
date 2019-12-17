#include <bits/stdc++.h>
#include "oatbBasic.h"

using namespace std;

typedef pair<int,int> ABpair;
typedef array<int,M> arr;
typedef pair<arr,ABpair> result;
typedef vector<result> record;

class solver 
{
private:
	record guessHistory; //records the history of Y and oatb(X,Y)
	array<vector<int>,N> toHistory; //toHistory[i] records all guessHistory[j] that have i
	set<int> innerSpace; //contains numbers that can be found in guessHistory
	set<int> outerSpace; //contains untouched numbers
	
	void recur_gAG(set<int> curInner,set<int> curOuter,arr curArr,int progress);
	set<arr> availGuess;
	
public:
	solver() {};
	virtual ~solver() {};
	
	void initialize();
	void addRecord(arr Y, ABpair ab);
	void genAvailGuess();
	
}glbCond;

void solver::initialize()
{
	guessHistory.clear();
	for(auto i:toHistory) i.clear();
	innerSpace.clear();
	outerSpace.clear();
	forr(i,N) outerSpace.insert(i);
	
	availGuess.clear();
	return;
}

void solver::addRecord(arr Y, ABpair ab)
{
	int tmp = guessHistory.size();
	guessHistory.push_back(make_pair(Y,ab));
	for(auto i:Y)
	{
		innerSpace.insert(i);
		outerSpace.erase(i);
		toHistory[i].push_back(tmp);
	}
	return;
}

void solver::genAvailGuess()
{
	availGuess.clear();
	arr tmpArr = {};
	recur_gAG(innerSpace,outerSpace,tmpArr,0);
	return;
}
void solver::recur_gAG(set<int> curInner,set<int> curOuter,arr curArr,int progress)
{
	if(progress==M)
	{
		for(auto i:curArr) cout<<i;
		cout<<endl;
		return;
	}
	for(auto i:curInner)
	{
		
	}
	return;
}

int main()
{
	glbCond.initialize();
	glbCond.addRecord({0,1,2,3,4,5},make_pair(3,2));
	return 0;
}
