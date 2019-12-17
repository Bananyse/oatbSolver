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
	
	void recur_gAG(set<int> curInner,record curRule,arr curArr,int availOuter,int progress);
	set<arr> availGuess;
	
public:
	solver() {};
	virtual ~solver() {};
	
	void initialize();
	void addRecord(arr Y, ABpair ab);
	void genAvailGuess();
	
}Solver;

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
	recur_gAG(innerSpace,guessHistory,tmpArr,outerSpace.size(),0);
	return;
}
void solver::recur_gAG(set<int> curInner,record curRule,arr curArr,int availOuter,int progress)
{
	if(progress==M)
	{
		bool flag = false;
		for(auto rule:curRule)
			if(rule.second.first||rule.second.second)
				{flag=true;break;}
		if(flag) return;
		for(auto i:curArr) cout<<toChar(i);
		cout<<endl;
		return;
	}
	
	for(auto i:curInner)
	{
		//Try picking i as Arr[progress]
		set<int> nxtInner = curInner;
		record nxtRule = curRule;
		arr nxtArr = curArr;
		bool flag = false;
		for(auto hID:toHistory[i])
		{
			bool isA = curRule[hID].first[progress]==i;
			bool noA = curRule[hID].second.first<1;
			bool noB = curRule[hID].second.second<1;
			if(isA)
			{
				if(noA) { flag=true; break; }
				nxtRule[hID].second.first--;
			}
			else //isB
			{
				if(noB) { flag=true; break; }
				nxtRule[hID].second.second--;
			}
		}
		if(flag) continue;
		nxtInner.erase(i);
		nxtArr[progress] = i;
		recur_gAG(nxtInner,nxtRule,nxtArr,availOuter,progress+1);
	}
	if(availOuter)
	{
		arr nxtArr = curArr;
		nxtArr[progress] = -1;
		recur_gAG(curInner,curRule,nxtArr,availOuter-1,progress+1);
	}
	return;
}

int main()
{
	Solver.initialize();
	Solver.addRecord({0,1,2,3,4,5},make_pair(3,0));
	Solver.addRecord({0,1,2,6,7,8},make_pair(3,0));
	Solver.genAvailGuess();
	return 0;
}
