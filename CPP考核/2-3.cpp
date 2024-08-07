#include<bits/stdc++.h>
using namespace std;
#include<cstdio>
    int main() {
        int n, i=0, j=0;
        scanf("%d", &n);
        while(n>j) {
            i++;
            j+=i;
        }
        if(i%2==1)
            printf("%d/%d",j-n+1,i+n-j);
        else
            printf("%d/%d",i+n-j,j-n+1);
        return 0;
}
