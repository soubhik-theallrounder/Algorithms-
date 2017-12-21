#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>
#include <deque>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <algorithm>
#include <functional>
#include <utility>
#include <bitset>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <cstdio>

using namespace std;

#define REP(i,n) for((i)=0;(i)<(int)(n);(i)++)
#define snuke(c,itr) for(__typeof((c).begin()) itr=(c).begin();itr!=(c).end();itr++)

int N,K;
int a[100010];

void main2(void){
	int i,j;
	
	cin >> N >> K;
	
	if(K == 0){
		REP(i,N) a[i] = i;
	} else {
	
	REP(i,K){
		int cnt = 0;
		for(j=i;j<N;j+=K){
			if(cnt == 0) a[j] = j + K; else a[j] = j - K;
			cnt ^= 1;
		}
		if(cnt != 0){
			cout << -1 << endl;
			return;
		}
	}
	
	}
	
	REP(i,N){
		printf("%d", a[i] + 1);
		if(i == N-1) printf("\n"); else printf(" ");
	}
}

int main(void){
	int T,t;
	
	cin >> T;
	REP(t,T){
	//	cin >> N >> K;
		main2();
	}
	
	return 0;
}
