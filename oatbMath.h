#ifndef OATBMATH_H
#define OATBMATH_H
#include <bits/stdc++.h>
#include "oatbBasic.h"

template <class type>
class facList
{
private:
	std::vector<type> List;
	int size;
public:
	facList(int n=N)
	{
		List.push_back(1);
		List.push_back(1);
		size = 2;
		get(n-1);
	}
	type get(int n)
	{
		while(size<=n)
		{
			type tmp=List.back();
			List.push_back(tmp*size);
			size++;
		}
		return List[n];
	}
};

template <class type>
class combTable
{
private:
	type C[N+1][N+1];
public:
	combTable()
	{
		for(int i=0;i<=N;i++)
		{
			C[0][i] = 0;
			C[i][0] = 1;
		}
		for(int i=1;i<=N;i++)
			for(int j=1;j<=i;j++)
				C[i][j] = C[i-1][j] + C[i-1][j-1];
	}
	type getC(int n,int m)
	{
		return C[n][m];
	}
};
#endif
