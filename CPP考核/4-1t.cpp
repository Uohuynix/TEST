#include <iostream>
#include <cstdio>
#include <cstring>// ��ΪҪ��memset����Ҫ��������
using namespace std;

int a[1005][3];

int main()
{
    int n, m;
    scanf("%d%d", &n, &m);
    memset(a, 0, sizeof(a));
    for (int i = 1; i <= n; ++i)
    {
        scanf("%d%d", &a[i][1], &a[i][2]);
        a[i][0] = a[i][2] - a[i][1];// ��Ҫ��1�������߶γ��Ȳ��Ƕϵ������
    }
    for (int i = 1; i <= m; ++i)
    {
        int l, r, ans = 0;
        scanf("%d%d", &l, &r);
        for (int j = 1; j <= n; ++j)
        {
            if (a[j][2] <= l || a[j][1] >= r) continue;
            int cnt;
            if (a[j][1] < l && a[j][2] > l && a[j][2] < r) cnt = a[j][2] - l;
            else if (a[j][2] > r && a[j][1] < r && a[j][1] > l) cnt = r - a[j][1];
            else if (a[j][1] >= l && a[j][2] <= r) cnt = a[j][0];
            else cnt = r - l;
            if (cnt * 2 >= a[j][0]) ans++;// ����ص����ȳ�2���ڸ��߶γ��ȣ���+1��
        }
        printf("%d\n", ans);
    }
    return 0;
}
