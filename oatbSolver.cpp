#include <bits/stdc++.h>
#include "oatbBasic.h"

using namespace std;

typedef pair<int,int> ABpair;
typedef array<int,M> arr;
typedef vector<arr> pool;

class condition
{
public:
	vector<pair<arr,ABpair>> record;
	
	struct numTable
	{
		// (Y1,oatb(X,Y1)), (Y2,oatb(X,Y2)),...
		array<set<int>,N> numToSet;
		// number[0,N) -> numSets[number] has this number inside
		vector<set<int>> numSets; 
		vector<int> needCount;
		// count needed for each set
		set<int> outerSpace;
	}nT;
	
	set<arr> availGuess;
	
	void forge(numTable cur_nT,arr X,int progress=0);
	
public:
	condition() {};
	virtual ~condition() {};
	void initialize(); 
	void addRecord(arr Y, ABpair ab);
	
}glbCond;

void condition::initialize()
{
	record.clear();
	
	for(auto i:nT.numToSet) i.clear();
	nT.numSets.clear();
	nT.needCount.clear();
	nT.outerSpace.clear();
	forr(i,N) nT.outerSpace.insert(i);
	
	return;
}

void condition::addRecord(arr Y, ABpair ab)
{
	record.push_back(make_pair(Y,ab));
	set<int> tmp; nT.numSets.push_back(tmp);
	nT.needCount.push_back(ABtot(ab));
	for(auto i:Y)
	{
		nT.outerSpace.erase(i); nT.numSets.back().insert(i);
		//outerSpace --i--> that set
		nT.numToSet[i].insert(nT.numSets.size()-1);
		//link i to that set
	}
	return;
}

void condition::forge(numTable cur_nT,arr X,int progress)
{
	if(progress==M)
	{
		availGuess.insert(X);
		return;
	}
	arr nxt_X = X;
	for(auto i:cur_nT.numSets)
	if(!i.empty()) for(auto j:i)
	{
		numTable nxt_nT = cur_nT;
		
		for(auto k:nxt_nT.numToSet[j])
			nxt_nT.numSets[k].erase(j);
		
		forge(nxt_nT,nxt_X,progress);
		
		bool flag = false;
		for(auto k:nxt_nT.numToSet[j])
			if(nxt_nT.needCount[k]<1) flag=true;
		if(flag) continue;
		
		for(auto k:nxt_nT.numToSet[j])
			nxt_nT.needCount[k]--;
		
		nxt_X[progress] = j;
		forge(nxt_nT,nxt_X,progress+1);
	}
	
	for(auto i:cur_nT.needCount) if(i) return;
	for(auto i:cur_nT.outerSpace)
	{
		X[progress++] = i;
		if(progress==M) break;
	}
	if(progress==M)
	{
		availGuess.insert(X);
		return;
	}
	return;
}

double F(arr Y,condition Cond)
{
	
}

double solve(arr &Y_min,condition Cond)
{
	
}

int main()
{
	glbCond.initialize();
	arr Y = {0,1,2,3,4,5};
	glbCond.addRecord(Y,make_pair(3,2));
	
	arr X = {0};
	glbCond.availGuess.clear();
	glbCond.forge(glbCond.nT,X);
	
	for(auto i:glbCond.availGuess)
	{
		for(auto j:i) printf("%d",j);
		printf("\n");
	}
	return 0;
}
