#include<stdio.h>
int i,j,k,m,n,s;
int main(){
    scanf("%d %d",&n,&k);
    s+=n;
    while(n>=k){
        m=n%k;
        n/=k;
        s+=n;
        n+=m;
    }
    printf("%d",s);
    return 0;
}
