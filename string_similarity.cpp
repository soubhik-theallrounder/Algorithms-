/* Enter your code here. Read input from STDIN. Print output to STDOUT */
#include<string.h>
#include<stdlib.h>
#include<stdio.h>

int const N=100010;
char s[N];                          // N > 256
int n, sa[N], height[N], rank[N], tmp[N], top[N];
void makesa()                       // O(N * log N)
{
	int i, j, len, na;
	na = (n < 256 ? 256 : n);
	memset(top, 0, na * sizeof(int));
	for (i = 0; i < n ; i++) top[ rank[i] = s[i] & 0xff ]++;
	for (i = 1; i < na; i++) top[i] += top[i - 1];
	for (i = 0; i < n ; i++) sa[ --top[ rank[i] ] ] = i;
	for (len = 1; len < n; len <<= 1) {
		for (i = 0; i < n; i++) {
			j = sa[i] - len; if (j < 0) j += n;
			tmp[ top[ rank[j] ]++ ] = j;
		}
		sa[ tmp[ top[0] = 0 ] ] = j = 0;
		for (i = 1; i < n; i++) {
			if (rank[ tmp[i] ] != rank[ tmp[i-1] ] ||
				rank[ tmp[i]+len ]!=rank[ tmp[i-1]+len ])
				top[++j] = i;
			sa[ tmp[i] ] = j;
		}
		memcpy(rank, sa , n * sizeof(int));
		memcpy(sa  , tmp, n * sizeof(int));
		if (j >= n - 1) break;
	}
}
void lcp()                          // O(4 * N)
{
	int i, j, k;
	for (j = rank[height[i=k=0]=0]; i < n - 1; i++, k++)
		while (k >= 0 && s[i] != s[ sa[j-1] + k ])
			height[j] = (k--), j = rank[ sa[j] + 1 ];
}

void print(int i)
{
	for (;s[i];i++)
	{
		putchar(s[i]);
	}
	puts("");
}

int main()
{
	int i,Z;
	scanf("%d",&Z);
	while (Z--)
	{
		scanf("%s",s);
		n=strlen(s)+1;
		makesa(); 
		lcp();
		n--;
		for (i=1;i<=n;i++)
		{
			if (!sa[i])
				break;
		}
		int tmp,j;
		long long ans;
		ans=tmp=strlen(s);
		for (j=i-1;j&&tmp;j--)
		{
			if (height[j+1]<tmp)
			{
				tmp=height[j+1];
			}
			ans+=tmp;
		}
		tmp=strlen(s);
		for (j=i+1;j<=n&&tmp;j++)
		{
			if (height[j]<tmp)
			{
				tmp=height[j];
			}
			ans+=tmp;
		}
		printf("%lld\n",ans);
	}
}
