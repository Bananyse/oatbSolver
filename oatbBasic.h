#ifndef OATBBASIC_H
#define OATBBASIC_H
#include <bits/stdc++.h>

#define forr(_I,_N) for(int _I=0;_I<(_N);_I++)

const int N = 16;
const int M = 6;

typedef std::pair<int,int> ABpair;
typedef std::array<int,M> arr;

char toChar(int x)
{
	if(x<0) return '-';
	if(x<10) return '0'+x;
	if(x<36) return 'A'+x-10;
	return '+';
}
	
ABpair oatb(arr X,arr Y)
{
	int A=0,B=0;
	int flag[N]={0};
	forr(i,M) if(X[i]>=0) flag[X[i]]=i+1;
	forr(i,M) if(Y[i]>=0)
	{
		int tmp=flag[Y[i]];
		if(tmp==i+1) A++;
		else if(tmp) B++;
	}
	return std::make_pair(A,B);
}
#endif
