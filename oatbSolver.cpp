#include <bits/stdc++.h>
#include "oatbBasic.h"
#include "oatbMath.h"

using namespace std;

typedef pair<int,int> ABpair;
typedef array<int,M> arr;
typedef pair<arr,ABpair> result;
typedef vector<result> record;
typedef long long lint;

class solver 
{
private:
	record guessHistory; //records the history of Y and oatb(X,Y)
	array<vector<int>,N> toHistory; //toHistory[i] records all guessHistory[j] that have i
	set<int> innerSpace; //contains numbers that can be found in guessHistory
	set<int> outerSpace; //contains untouched numbers
	
	void recur_gAG(set<int> curInner,record curRule,arr curArr,int availOuter,int progress);
	vector<arr> availGuess;
	
	facList<double> fac;
	combTable<double> comb;
	double F(arr Y);
	//This 'genNegComb()' thing is bullshit
	//I'll get rid of this stupid recursion ASAP
	void genNegComb(
		int sizX,int sizY,int negXY,int totSpace,
		int num,int depth,vector<int> &tmpArr,
		double table[M+1][M+1],int biasA,int biasB);
	
public:
	solver() {};
	virtual ~solver() {};
	
	void initialize();
	void addRecord(arr Y, ABpair ab);
	void genAvailGuess();
	
	double order(int n,int m) {return fac.get(n)/fac.get(n-m);}
	double disorder(int n)
	{
		if(!n) return 1;
		double tmp1 = (double)fac.get(n);
		lint tmp2 = (lint)(tmp1/exp(1)+0.5);
		return (double)tmp2;
	}
	double solve(arr &Y_min)
	{
		genAvailGuess();
		double SabY_min = DBL_MAX;
		for(auto &Y:availGuess)
		{
			double SabY=F(Y);
			if(SabY<SabY_min)
			{
				Y_min = Y;
				SabY_min = SabY;
			}
		}
		set<int> out = outerSpace;
		forr(i,M) if(Y_min[i]<0)
		{
			Y_min[i] = *out.begin();
			out.erase(Y_min[i]);
		}
		return SabY_min;
	}
	
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
	/*
	cout<<availGuess.size()<<endl;
	for(auto i:availGuess)
	{
		for(auto j:i) cout<<toChar(j);
		cout<<endl;
	}
	*/
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
		
		availGuess.push_back(curArr);
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

double solver::F(arr Y)
{
	double f = 0;
	double SabY[M+1][M+1] = {0};
	
	for(auto X:availGuess)
	{
		int biasA=0,biasB=0;
		int negXY=0,negX=0,negY=0;
		int flag[N]={0};
		forr(i,M)
		{
			if(X[i]>=0) flag[X[i]]=i+1;
			else if(Y[i]>=0) negX++;
			else negXY++;
		}
		forr(i,M)
		{
			if(Y[i]>=0)
			{
				int tmp=flag[Y[i]];
				if(tmp==i+1) biasA++;
				else if(tmp) biasB++;
			}
			else if(X[i]>=0) negY++;
		}
		int space=outerSpace.size()-negXY-negY;
		vector<int> tmpArr(negXY+negX);
		genNegComb(negXY+negX,negXY+negY,negXY,space+negXY+negY,0,0,tmpArr,SabY,biasA,biasB);
		//for(auto i:X) printf("%c",toChar(i));
		//printf(":[%d],[%d,%d],[%d]\n",negXY,negY,negX,space);
	}
	
	forr(i,M+1) forr(j,M+1-i)
	{
		double tmp=SabY[i][j];
		//printf("%dA%dB:%d\n",i,j,(int)tmp);
		if(tmp>0) f += tmp*log(tmp);
	}
	return f;
}

//******BULLSHIT DONT TOUCH******
void solver::genNegComb(
	int sizX,int sizY,int negXY,int totSpace,
	int num,int depth,vector<int> &tmpArr,
	double table[M+1][M+1],int biasA,int biasB)
{
	if(depth==sizX)
	{
		vector<int> tmp = tmpArr;
		do{
			int a=0,c=0;
			forr(i,sizX)
			{
				if(i<negXY && tmp[i]==i) a++;
				if(tmp[i]<sizY) c++;
			}
			table[a+biasA][c-a+biasB]++;
		}
		while(next_permutation(tmp.begin(),tmp.end()));
		return;
	}
	int target=totSpace-sizX+depth;
	for(int i=num;i<=target;i++)
	{
		tmpArr[depth]=i;
		genNegComb(sizX,sizY,negXY,totSpace,i+1,depth+1,tmpArr,table,biasA,biasB);
	}
	return;
}
//******BULLSHIT DONT TOUCH******

int main()
{
	Solver.initialize();
	Solver.addRecord({0,1,2,3,4,5},make_pair(0,0));
	//Solver.addRecord({6,7,8,9,10,11},make_pair(0,2));
	
	arr Y = {0};
	Solver.solve(Y);
	for(auto i:Y) cout<<toChar(i);
	
	return 0;
}
