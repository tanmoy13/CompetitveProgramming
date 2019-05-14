/**
    If you have a set of lines Yi = Ai * X + Bi, then this code is for finding the smallest or largest 
    Yi for a given X.

    Time Complexity:
    Each Query: O(logN)
    Build: O(N)
*/

vector<long long>m,b;

bool bad(int f1, int f2, int f3, int id)
{
    ///mi > mi+1, and all queries are for minimum.
    if(id==1)
        return ((b[f3]-b[f1])*(m[f1]-m[f2]))<=((m[f1]-m[f3])*(b[f2]-b[f1]));

    ///mi > mi+1, and all queries are for maximum.
    if(id==2)
        return ((b[f3]-b[f1])*(m[f1]-m[f2]))>=((m[f1]-m[f3])*(b[f2]-b[f1]));

    ///mi < mi+1, and all queries are for minimum.
    if(id==3)
        return ((b[f3]-b[f1])*(m[f1]-m[f2]))>=((m[f1]-m[f3])*(b[f2]-b[f1]));

    ///mi < mi+1, and all queries are for maximum.
    if(id==4)
        return ((b[f3]-b[f1])*(m[f1]-m[f2]))<=((m[f1]-m[f3])*(b[f2]-b[f1]));

}

void add(long long new_m, long long new_b, int id)
{
    m.push_back(new_m);
    b.push_back(new_b);

    int sz=m.size();

    while(sz>=3 && bad(sz-3,sz-2, sz-1, id))
    {
        m.erase(m.end()-2);
        b.erase(b.end()-2);
        sz--;
    }
}

ll f(int i, ll x)
{
    return  m[i]*x+b[i];
}


///(mi > mi+1) or (mi < mi+1) and all queries are for minimum.
ll query1(ll x)
{
    int lo=0,hi=m.size()-1;
    ll ans=1e18;
    while(lo+3<=hi)
    {
        int mid1=(lo+lo+hi)/3;
        int mid2=(lo+hi+hi)/3;
        ll y1=f(mid1,x);
        ll y2=f(mid2,x);
        if(y1<=y2)
        {
            ans=min(ans,y1);
            hi=mid2-1;
        }
        else
        {
            ans=min(ans,y2);
            lo=mid1+1;
        }
    }

    for(int i=lo; i<=hi; i++)
        ans=min(ans,f(i,x));

    return ans;
}

///(mi > mi+1) or (mi < mi+1) and all queries are for maximum.
ll query2(ll x)
{
    int lo=0,hi=m.size()-1;
    ll ans=-1e18;
    while(lo+3<=hi)
    {
        int mid1=(lo+lo+hi)/3;
        int mid2=(lo+hi+hi)/3;
        ll y1=f(mid1,x);
        ll y2=f(mid2,x);
        if(y1>=y2)
        {
            ans=max(y1,ans);
            hi=mid2-1;
        }
        else
        {
            ans=max(y2,ans);
            lo=mid1+1;
        }
    }
    for(int i=lo; i<=hi; i++)
        ans=max(ans,f(i,x));
    return ans;
}
