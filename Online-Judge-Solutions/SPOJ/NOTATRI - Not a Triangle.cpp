#include <bits/stdc++.h>

using namespace std;
typedef long long lli;

bool islucky(int n)
{
    bool check=0;
    while(n)
    {
        int x=n%10;
        if(x!=4 && x!=7)
            return false;
        n/=10;
    }
    return true;
}

int main()
{
    int n;
    while(scanf("%d",&n) && n)
    {
        vector<int>v;
        for(int i=0;i<n;i++)
        {
            int a;
            scanf("%d",&a);
            v.push_back(a);
        }
        sort(v.begin(),v.end());
        long long ans=0;
        for(int i=0;i<v.size();i++)
        {
            for(int j=i+1;j<v.size();j++)
            {
                ans+=v.end()-upper_bound(v.begin(),v.end(),v[i]+v[j]);
            }
        }
        printf("%lld\n",ans);
    }

    return 0;
}
