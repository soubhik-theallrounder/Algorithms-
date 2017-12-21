#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

int main()
{	int M, N, R;
	cin >> M >> N >> R;
    
	int mat[M][N];
	for(int i=0; i<M; i++)
	{	for(int j=0; j<N; j++)
		{	cin >> mat[i][j];	}
	}
	
	int sti=0, stj=0;
	vector<int> temp;
	//cout << endl << endl;
	for(int x=M-1, y=N-1; x>0 && y>0; x-=2, y-=2,sti++,stj++)
	{	int rot = R%(2*(x+y));
		int sz = 2*(x+y);
		int i=sti, j=stj;
		//cout << "x,y : " << x << "," << y << "\trot : "<< rot << endl;
		//cout << "A : " ;
		for(int cnt=0; cnt<sz; cnt++)
		{	//cout << mat[i][j] << "  ";
			temp.push_back(mat[i][j]);
			if(j==sti && i<sti+x)
			{	i++;	}
			else if(i==sti+x && j<stj+y)
			{	j++;	}
			else if(j==stj+y && i>sti)
			{	i--;	}
			else if(i==sti && j>stj)
			{	j--;	}
		}
		
		i=sti, j=stj;
		int npos;
		//cout << "\nRotated : ";
		for(int cnt=0; cnt<sz; cnt++)
		{	npos = (cnt-rot)%sz;
			npos = (npos<0)? npos+sz : npos;
			mat[i][j] = temp[npos];
			//cout << mat[i][j] << "  ";
			if(j==sti && i<sti+x)
			{	i++;	}
			else if(i==sti+x && j<stj+y)
			{	j++;	}
			else if(j==stj+y && i>sti)
			{	i--;	}
			else if(i==sti && j>stj)
			{	j--;	}
		}
		temp.clear();
		//cout << endl;
	}
	
	for(int i=0; i<M; i++)
	{	for(int j=0; j<N; j++)
		{	cout << mat[i][j] << " ";	}
		cout << endl;
	}
    return 0;
}
