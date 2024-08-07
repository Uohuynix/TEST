#include <stdio.h>
int main(){
    int a,b,j=0;
    scanf("%d %d",&a,&b);
    for(int i=1;i<=a;i++){
        int d=i;
        while(d>0){
            int c=d%10;
            d=d/10;
            if(c==b){
                j++;
            }
        }
    }
    printf("%d",j);
    return 0;
}
 
