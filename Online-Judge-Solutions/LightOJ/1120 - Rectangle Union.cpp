#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
//#include <ext/pb_ds/tree_policy.hpp>

#define pii              pair <int,int>
#define pll              pair <long long,long long>
#define sc               scanf
#define pf               printf
#define Pi               2*acos(0.0)
#define ms(a,b)          memset(a, b, sizeof(a))
#define pb(a)            push_back(a)
#define MP               make_pair
#define db               double
#define ll               long long
#define EPS              10E-10
#define ff               first
#define ss               second
#define sqr(x)           (x)*(x)
#define D(x)             cerr<<#x " = "<<(x)<<endl
#define VI               vector <int>
#define DBG              pf("Hi\n")
#define MOD              1000000007
#define CIN              ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define loop(i,n)        for(int i=0;i<n;i++)
#define loop1(i,n)       for(int i=1;i<=n;i++)
#define REP(i,a,b)       for(int i=a;i<b;i++)
#define RREP(i,a,b)      for(int i=a;i>=b;i--)
#define TEST_CASE(t)     for(int z=1;z<=t;z++)
#define PRINT_CASE       printf("Case %d: ",z)
#define LINE_PRINT_CASE  printf("Case %d:\n",z)
#define CASE_PRINT       cout<<"Case "<<z<<": "
#define all(a)           a.begin(),a.end()
#define intlim           2147483648
#define infinity         (1<<28)
#define ull              unsigned long long
#define gcd(a, b)        __gcd(a, b)
#define lcm(a, b)        ((a)*((b)/gcd(a,b)))

using namespace std;

//using namespace __gnu_pbds;
//typedef tree<int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update> ordered_set;


/*----------------------Graph Moves----------------*/
//const int fx[]={+1,-1,+0,+0};
//const int fy[]={+0,+0,+1,-1};
//const int fx[]={+0,+0,+1,-1,-1,+1,-1,+1};   // Kings Move
//const int fy[]={-1,+1,+0,+0,+1,+1,-1,-1};  // Kings Move
//const int fx[]={-2, -2, -1, -1,  1,  1,  2,  2};  // Knights Move
//const int fy[]={-1,  1, -2,  2, -2,  2, -1,  1}; // Knights Move
/*------------------------------------------------*/

/*-----------------------Bitmask------------------*/
//int Set(int N,int pos){return N=N | (1<<pos);}
//int reset(int N,int pos){return N= N & ~(1<<pos);}
//bool check(int N,int pos){return (bool)(N & (1<<pos));}
/*------------------------------------------------*/

#define mx 1000000009

struct node
{
    int b,e,cnt,sum;
    bool valid;
    node *lft,*rgt;
    node()
    {
        b=e=cnt=sum=valid=0;
        lft=rgt=NULL;
    }
    node(int bb, int ee)
    {
        b=bb;
        e=ee;
        cnt=0;
        sum=0;
        valid=0;
        lft=rgt=NULL;
    }
};

struct data
{
    int x,y1,y2,type;
    data(int a, int b, int c, int d)
    {
        x=a,y1=b,y2=c,type=d;
    }
};

vector<data>v;

void update(node *seg, int st, int ed, int type)
{
    if(seg->b>=st && seg->e<=ed)
    {
        if(type==0)
        {
            seg->cnt++;
            seg->sum=(seg->e - seg->b+1);
        }
        else
        {
            seg->cnt--;
            if(seg->cnt==0)
            {
                seg->sum=0;
                int xx=0,yy=0;
                if(seg->lft!=NULL)
                    xx=seg->lft->sum;
                if(seg->rgt!=NULL)
                    yy=seg->rgt->sum;
                seg->sum=max(seg->sum,xx+yy);
            }
        }
        return;
    }
    int mid=(seg->b + seg->e)/2;
    if(ed<=mid)
    {
        if(seg->lft==NULL)
            seg->lft=new node(seg->b,mid);
        update(seg->lft,st,ed,type);
    }
    else if(st>mid)
    {
        if(seg->rgt==NULL)
            seg->rgt=new node(mid+1,seg->e);
        update(seg->rgt,st,ed,type);
    }
    else
    {
        if(seg->lft==NULL)
            seg->lft=new node(seg->b,mid);
        update(seg->lft,st,ed,type);
        if(seg->rgt==NULL)
            seg->rgt=new node(mid+1,seg->e);
        update(seg->rgt,st,ed,type);
    }
    int x=0,y=0;
    if(seg->lft!=NULL)
        x=seg->lft->sum;
    if(seg->rgt!=NULL)
        y=seg->rgt->sum;
    if(seg->cnt==0)
        seg->sum=x+y;
}

void del(node *ob)
{
    if(ob->lft) del(ob->lft);
    if(ob->rgt) del(ob->rgt);
    delete(ob);
}

bool cmp(data a, data b)
{
    if(a.x<b.x) return true;
    if(a.x==b.x) return a.type<b.type;
    return false;
}

int main()
{

//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        int n;
        sf(n);
        for(int i=0; i<n; i++)
        {
            int a,b,c,d;
            sff(a,b);
            sff(c,d);
            v.pb(data(a,b,d,0));
            v.pb(data(c,b,d,1));
        }
        sort(all(v),cmp);

        node *root = new node(1,mx);

        ll ans=0;
        ll last=v[0].x;
        update(root,v[0].y1+1,v[0].y2,0);
        for(int i=1; i<SZ(v); i++)
        {
            if(v[i].type==0)
            {
                ans+=(v[i].x-last)*(ll)root->sum;
                update(root,v[i].y1+1,v[i].y2,0);
                last=v[i].x;
            }
            else
            {
                ans+=(v[i].x-last)*(ll)root->sum;
                update(root,v[i].y1+1,v[i].y2,1);
                last=v[i].x;
            }
        }

        PRINT_CASE;
        printf("%lld\n",ans);
        del(root);
        v.clear();
    }


    return 0;
}
