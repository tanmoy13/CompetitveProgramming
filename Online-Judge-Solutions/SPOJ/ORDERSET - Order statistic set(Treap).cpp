#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

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

struct node
{
    int val, prior, size;
    node *lft,*rgt;
};

typedef node* pnode;

int sz(pnode t)
{
    return t?t->size:0;
}

void upd_sz(pnode t)
{
    if(t) t->size=sz(t->lft)+1+sz(t->rgt);
}

void split(pnode t, pnode &l, pnode &r, int key)
{
    if(!t) l=r=NULL;
    else if(t->val<=key)
    {
        split(t->rgt,t->rgt,r,key);
        l=t;
    }
    else
    {
        split(t->lft,l,t->lft,key);
        r=t;
    }
    upd_sz(t);
}

void merge(pnode &t, pnode l, pnode r)
{
    if(!l || !r) t=l?l:r;
    else if(l->prior >r->prior)
    {
        merge(l->rgt,l->rgt,r);
        t=l;
    }
    else
    {
        merge(r->lft,l,r->lft);
        t=r;
    }
    upd_sz(t);
}

void insert(pnode &t, pnode it)
{
    if(!t) t=it;
    else if(it->prior>t->prior)
    {
        split(t,it->lft,it->rgt,it->val);
        t=it;
    }
    else
    {
        insert(t->val<=it->val?t->rgt:t->lft,it);
    }
    upd_sz(t);
}

void erase(pnode &t, int key)
{
    if(!t) return;
    else if(t->val==key)
    {
        pnode temp=t;
        merge(t,t->lft,t->rgt);
        free(temp);
    }
    else
    {
        erase(t->val<key?t->rgt:t->lft,key);
    }
    upd_sz(t);
}

pnode init(int val)
{
    pnode ret=(pnode) malloc(sizeof(node));
    ret->val=val;
    ret->size=1;
    ret->prior=rand();
    ret->lft=ret->rgt=NULL;
    return ret;
}

int find_kth(pnode t, int val)
{
    if(sz(t->lft)+1==val) return t->val;
    if(sz(t->lft)>=val) return find_kth(t->lft,val);
    else return find_kth(t->rgt,val-sz(t->lft)-1);
}

void print(pnode t)
{
    if(!t) return;
    print(t->lft);
    cout<<t->val<<" ";
    print(t->rgt);
}

int main()
{
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);
    pnode treap=NULL;
//    for(int i=5;i>=1;i--)
//    {
//        insert(treap,init(5+(i%2)));
//    }
//    print(treap);

    int n;
    sf(n);
    for(int i=0;i<n;i++)
    {
        char ch; int d;
        scanf(" %c %d",&ch,&d);
        if(ch=='I')
        {
            erase(treap,d);
            insert(treap,init(d));
        }
        else if(ch=='D')
            erase(treap,d);
        else if(ch=='K')
        {
            if(sz(treap)<d)
                printf("invalid\n");
            else
                printf("%d\n",find_kth(treap,d));
        }
        else if(ch=='C')
        {
            pnode l,r;
            split(treap,l,r,d-1);
            printf("%d\n",sz(l));
            merge(treap,l,r);
        }

    }

//    print(treap);


    return 0;
}
