#include<stdio.h>
int main()
{
    int i,a[7],b[7],c[7],max=0,n;
    for(i=0;i<7;i++)
    {
        scanf("%d %d\n",&a[i],&b[i]);
        c[i]=a[i]+b[i];  
    }
        for(i=6;i>=0;i--)
        {
            if(max>c[i])
			max=max; 
            else if(max<=c[i])
			max=c[i];
        }
    for(i=6;i>=0;i--)
    {
            if(max>=8&&max==c[i])
			n=i;
            if(max<8&&max!=c[i])
			printf("%d\n",0);
    }
        printf("%d\n",n+1); 
        return 0;
}
