/*
        Author: Tanmoy Datta

        Solution Idea:
            - When the Y value is positive then it is a straight forward problem which can be
              handled in many ways including treap.
            - But when Y value is negative then the order of treap will not be preserved. Here
              comes an interesting observation. In constraints we can see that the transition from
              negative to positive or vice versa can occur at most N times. So in such case we can
              perform insert operation. Which will happen in at most N times.
*/

#include <bits/stdc++.h>
// #include <ext/pb_ds/assoc_container.hpp>
// #include <ext/pb_ds/tree_policy.hpp>

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
#define VI               vector <int>
#define MOD              1000000007
#define fast_cin         ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define SZ(a)            (int)a.size()
#define sf(a)            scanf("%d",&a)
#define sfl(a)           scanf("%lld",&a)
#define sff(a,b)         scanf("%d %d",&a,&b)
#define sffl(a,b)        scanf("%lld %lld",&a,&b)
#define sfff(a,b,c)      scanf("%d %d %d",&a,&b,&c)
#define sfffl(a,b,c)     scanf("%lld %lld %lld",&a,&b,&c)
#define stlloop(v)       for(__typeof(v.begin()) it=v.begin();it!=v.end();it++)
#define UNIQUE(v)        (v).erase(unique((v).begin(),(v).end()),(v).end())
#define POPCOUNT         __builtin_popcountll
#define RIGHTMOST        __builtin_ctzll
#define LEFTMOST(x)      (63-__builtin_clzll((x)))
#define NUMDIGIT(x,y)    (((vlong)(log10((x))/log10((y))))+1)
#define NORM(x)          if(x>=mod) x-=mod;if(x<0) x+=mod;
#define ODD(x)           (((x)&1)==0?(0):(1))
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
#define D(x)        	 cerr << __LINE__ << ": " << #x << " = " << (x) << '\n'
#define DD(x,y)          cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << '\n'
#define DDD(x,y,z)       cerr << __LINE__ << ": " << #x << " = " << x << "   " << #y << " = " << y << "   " << #z << " = " << z << '\n'
#define DBG              cerr << __LINE__ << ": Hi" << '\n'

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

/*-------------------------Treap Start------------------------*/
struct node
{
    ll prior,size;
    ll val;//value stored in the array
    ll sum;//whatever info you want to maintain in segtree for each node
    ll lazy;//whatever lazy update you want to do
    int idx;
    struct node *l,*r;
};

typedef node* pnode;

int sz(pnode t)
{
    return t?t->size:0;
}

void upd_sz(pnode t)
{
    if(t)t->size=sz(t->l)+1+sz(t->r);
}

//void reset(pnode t)
//{
//    if(t)t->sum = t->val;//no need to reset lazy coz when we call this lazy would itself be propagated
//}

//void combine(pnode& t,pnode l,pnode r) //combining two ranges of segtree
//{
//    if(!l || !r)return void(t = l?l:r);
//    t->sum = l->sum + r->sum;
//}

//void operation(pnode t) //operation of segtree
//{
//    if(!t)return;
//    reset(t);//reset the value of current node assuming it now represents a single element of the array
//    lazy(t->l);
//    lazy(t->r);//imp:propagate lazy before combining t->l,t->r;
//    combine(t,t->l,t);
//    combine(t,t,t->r);
//}

//void split(pnode t,pnode &l,pnode &r,int pos,int add=0)
//{
//    if(!t)return void(l=r=NULL);
//    lazy(t);
//    int curr_pos = add + sz(t->l);
//    if(curr_pos<=pos)//element at pos goes to left subtree(l)
//        split(t->r,t->r,r,pos,curr_pos+1),l=t;
//    else
//        split(t->l,l,t->l,pos,add),r=t;
//    upd_sz(t);
//    operation(t);
//}

void lazy(pnode t)
{
    if(!t || !t->lazy)return;
    t->val+=t->lazy;//operation of lazy
//    t->sum+=t->lazy*sz(t);
    if(t->l)t->l->lazy+=t->lazy;//propagate lazy
    if(t->r)t->r->lazy+=t->lazy;
    t->lazy=0;
}

void merge(pnode &t,pnode l,pnode r)  //l->leftarray,r->rightarray,t->resulting array
{
    lazy(l);
    lazy(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
    else    merge(r->l,l,r->l),t=r;
//    upd_sz(t);
//    operation(t);
}

pnode init(ll val, int id)
{
    pnode ret = (pnode)malloc(sizeof(node));
    ret->prior=rand();
    ret->size=1;
    ret->idx=id;
    ret->val=val;
//    ret->sum=val;
    ret->lazy=0;
    ret->l=NULL;
    ret->r=NULL;
    return ret;
}

//int range_query(pnode t,int l,int r) //[l,r]
//{
//    pnode L,mid,R;
//    split(t,L,mid,l-1);
//    split(mid,t,R,r-l);//note: r-l!!
//    int ans = t->sum;
//    merge(mid,L,t);
//    merge(t,mid,R);
//    return ans;
//}

//void range_update(pnode t,int l,int r,int val) //[l,r]
//{
//    pnode L,mid,R;
//    split(t,L,mid,l-1);
//    split(mid,t,R,r-l);//note: r-l!!
//    t->lazy+=val; //lazy_update
//    merge(mid,L,t);
//    merge(t,mid,R);
//}




void split(pnode t,pnode &l,pnode &r,ll key)
{
    lazy(t);
    if(!t) l=r=NULL;
    else if(t->val<=key) split(t->r,t->r,r,key),l=t; //elem=key comes in l
    else split(t->l,l,t->l,key),r=t;
//    upd_sz(t);
}

void insert(pnode &t,pnode it)
{
    lazy(t);
    if(!t) t=it;
    else if(it->prior>t->prior) split(t,it->l,it->r,it->val),t=it;
    else insert(t->val<=it->val?t->r:t->l,it);
//    upd_sz(t);
}

void output2(pnode &t)
{
    if(!t) return;
    lazy(t);
    output2(t->l);
    printf("%lld ",t->val);
    output2(t->r);
}


void output1(pnode t, vector<pll> &v)
{
    if(!t) return;
    lazy(t);
    v.pb(pll(t->val,t->idx));
    output1(t->l,v);
    output1(t->r,v);
}



//
//void erase(pnode &t,int key)
//{
//    if(!t)return;
//    else if(t->val==key)
//    {
//        pnode temp=t;
//        merge(t,t->l,t->r);
//        free(temp);
//    }
//    else erase(t->val<key?t->r:t->l,key);
//    upd_sz(t);
//}


ll ans[500005];

void output(pnode &t)
{
    if(!t) return;
    lazy(t);
    output(t->l);
    ans[t->idx]=t->val;
    output(t->r);
}

/*-------------------------Treap End--------------------------*/

void del(pnode &t)
{
    if(!t) return;
    del(t->l);
    del(t->r);
    delete t;
    t=NULL;
}


int main()
{
//#ifndef ONLINE_JUDGE
//    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int t;
    sf(t);
    TEST_CASE(t)
    {

        pnode root=NULL;
        int n,q;
        sff(n,q);
//        ms(ans,0);
        for(int i=0; i<n; i++)
        {
            ll a;
            sfl(a);
            insert(root,init(a,i));
        }

//        output(root);

        while(q--)
        {
            ll a,x,y;
            sfffl(a,x,y);
            if(a==1)
            {
                pnode l,r;
                split(root,l,r,x);
                if(y>=0)
                {
                    if(l)
                        l->lazy-=y;
                    merge(root,l,r);
                }
                else
                {
                    vector<pll>v;
                    output1(l,v);
                    for(int i=0; i<SZ(v); i++)
                    {
                        insert(r,init(v[i].ff-y,v[i].ss));
                    }
                    merge(root,NULL,r);
                }
            }
            else if(a==2)
            {
                pnode l,r;
                split(root,l,r,x-1);
                if(y>=0)
                {
                    if(r)
                        r->lazy+=y;
                    merge(root,l,r);
                }
                else
                {
//                    cout<<"------------------------"<<endl;
//                    output2(root);
//                    cout<<endl<<"-----------------------"<<endl;
                    vector<pll>v;
                    output1(r,v);
                    for(int i=0; i<SZ(v); i++)
                    {
                        insert(l,init(v[i].ff+y,v[i].ss));
                    }
                    merge(root,l,NULL);
                }
            }
        }


//        D("\n-----------------\n");
//        output2(root);
//        D("\n-----------------\n");

//        cout<<"------------------------"<<endl;
//        output2(root);
//        cout<<endl<<"-----------------------"<<endl;

        output(root);

        for(int i=0; i<n; i++)
        {
            printf("%lld",ans[i]);
            if(i+1!=n)
                printf(" ");
        }
        printf("\n");
        del(root);

    }

    return 0;
}
