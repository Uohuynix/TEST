#include<stdio.h>
int main()
{
	long a[11];
	int n,t,s;
	int i,j;
        for(i=0;i<10;i++)
        scanf("%lld",&a[i]);
        scanf("%d",&n); 
        t=n+30;
        for(j=0;j<10;j++)
        {if(t>=a[j])
            s++;
        }
        printf("%lld",s);
		return 0;
}
