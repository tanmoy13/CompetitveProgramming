#define MH 600006

#define Base1 10000019
#define Base2 10000079

#define MOD1 1000000007
#define MOD2 1000000009

ll B1[MH],B2[MH];

void init_hash()
{
    B1[0]=B2[0]=1;
    for(int i=1; i<MH; i++)
    {
        B1[i]=(B1[i-1]*Base1)%MOD1;
        B2[i]=(B2[i-1]*Base2)%MOD2;
    }
}

struct Hash
{
    pll H[MH];
    int digit[MH];
    int len;

    Hash()
    {
        len=0;
        H[0]=pll(0,0);
    }

    void clear()
    {
        len=0;
        H[0]=pll(0,0);
    }

    void insert(char ch)
    {
        len++;
        digit[len]=ch-'a'+1;
        H[len].ff=(((H[len-1].ff*Base1)%MOD1)+digit[len])%MOD1;
        H[len].ss=(((H[len-1].ss*Base2)%MOD2)+digit[len])%MOD2;
    }

    pll substr(int l, int r)
    {
        if(l>len || r<1 || r<l) return pll(0,0);
        int sub_len=r-l+1;
        pll ans;
        ans.ff=(H[r].ff-((H[l-1].ff*B1[sub_len])%MOD1)+MOD1)%MOD1;
        ans.ss=(H[r].ss-((H[l-1].ss*B2[sub_len])%MOD2)+MOD2)%MOD2;
        return ans;
    }

    pll concate(pll h, int l, int r)
    {
        pll x=substr(l,r);
        int sub_len=r-l+1;
        h.ff=(((h.ff*B1[sub_len])%MOD1)+x.ff)%MOD1;
        h.ss=(((h.ss*B2[sub_len])%MOD2)+x.ss)%MOD2;
        return h;
    }


    bool operator==(const Hash& p) const
    {
        return len==p.len && H[len]==p.H[len];
    }

    pll & operator[](int index)
    {
        return H[index];
    }
};

Hash h1,h2;

int lcp(int id1, int id2, int l)
{
    int lo=1,hi=l;
    while(lo<=hi)
    {
        int mid=(lo+hi)/2;
        if(h1.substr(id1,id1+mid)==h2.substr(id2,id2+mid))
            lo=mid+1;
        else
            hi=mid-1;
    }
    return hi;
}

