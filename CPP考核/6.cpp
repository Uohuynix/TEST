#include<stdio.h>
int n,t[1001],i,s;
int main(){
    scanf("%d",&n);
    for(i=1;i<=n;i++){
        scanf("%d",&s);
        t[s]=1;
    }
    s=0;
    for(i=1;i<=1000;i++)
        if(t[i])
            s++;
    printf("%d\n",s);
    for(i=1;i<=1000;i++)
        if(t[i])
            printf("%d ",i);
    return 0;
}
