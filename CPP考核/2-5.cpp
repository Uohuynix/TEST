#include<stdio.h>
#include<algorithm>
using namespace std;
int n;
struct student
{
    int number;
    int ch;
    int ma;
    int en;
    int total;
};student a[10000];
int cmp(const student & a,const student & b)
{
    if(a.total>b.total) return 1;
    if(a.total<b.total) return 0;
    if(a.ch>b.ch) return 1;
    if(a.ch<b.ch) return 0;
    if(a.number<b.number) return 1;
    return 0;
}
int main()
{
     scanf("%d",&n);
    for(int i=1;i<=n;i++)
        scanf("%d%d%d",&a[i].ch,&a[i].ma,&a[i].en);
    for(int i=1;i<=n;i++)
    {
        a[i].number=i;
        a[i].total=a[i].ch+a[i].ma+a[i].en;
    }
    sort(a+1,a+n+1,cmp);
    for(int i=1;i<=5;i++)
       printf("%d %d\n",a[i].number,a[i].total);
}
