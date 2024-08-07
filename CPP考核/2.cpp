#include <stdio.h>
int main()
{
    int l=0,r=0,t=0,sum=0,p=0;
    scanf("%d %d",&l,&r);
    for(int i=l;i<=r;i++)
    {
        p=i;
        while(p!=0)
        {
            t=p%10;
            p/=10;
            if(t==2)
            {
                sum++;
            }
        }
    }
    printf("%d",sum);
    return 0;
}
