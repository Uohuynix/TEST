#include<stdio.h>
int main()

{
int m,n,i,j,k;
int a[100][2],b[100][2],t[1000];
	scanf("%d %d",&m,&n);//输入m,n
	//开始输入数据 
	for(i=0;i<m;i++){
		scanf("%d %d",&a[i][1],&a[i][2]);
	t[i]=a[i][2]-a[i][1];
	
	}//输入线段所占坐标 
	for(j=0;j<n;j++){
		scanf("%d %d",&b[j][1],&b[j][2]);
	
	}//输入区间的坐标 
	//开始比较 
	int l,r,ans; 
	for(i=0;i<n;i++){
		for (j = 1; j <= n; j++)
        {
            if (a[j][2] <= l || a[j][1] >= r) continue;
            int cnt;
            if (a[j][1] < l && a[j][2] > l && a[j][2] < r) cnt = a[j][2] - l;
            else if (a[j][2] > r && a[j][1] < r && a[j][1] > l) cnt = r - a[j][1];
            else if (a[j][1] >= l && a[j][2] <= r) cnt = a[j][0];
            else cnt = r - l;
            if (cnt * 2 >= a[j][0]) ans++;// 如果重叠长度乘2大于该线段长度，答案+1。
        }
        printf("%d\n", ans);
		printf("%d\n",k);
		
	}
	
	
	
	return 0;
}
