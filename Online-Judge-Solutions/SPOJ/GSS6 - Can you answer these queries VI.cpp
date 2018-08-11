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


/*-------------------------Treap Start------------------------*/
struct node
{
    int prior,size;
    int val;//value stored in the array
    int sum;//whatever info you want to maintain in segtree for each node
    int leftbest;
    int rightbest;
    int ans;
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

//void lazy(pnode t)
//{
//    if(!t || !t->lazy)return;
//    t->val+=t->lazy;//operation of lazy
//    t->sum+=t->lazy*sz(t);
//    if(t->l)t->l->lazy+=t->lazy;//propagate lazy
//    if(t->r)t->r->lazy+=t->lazy;
//    t->lazy=0;
//}

void reset(pnode t)
{
    if(t)t->sum =t->leftbest=t->rightbest=t->ans=t->val;//no need to reset lazy coz when we call this lazy would itself be propagated
}

void combine(pnode& t,pnode l,pnode r) //combining two ranges of segtree
{
    if(!l || !r)return void(t = l?l:r);
    t->ans=max(l->rightbest+r->leftbest,max(l->ans,r->ans));
    t->leftbest=max(l->leftbest,l->sum+r->leftbest);
    t->rightbest=max(r->rightbest,r->sum+l->rightbest);
    t->sum = l->sum + r->sum;
}

void operation(pnode t) //operation of segtree
{
    if(!t)return;
    reset(t);//reset the value of current node assuming it now represents a single element of the array
//    lazy(t->l);
//    lazy(t->r);//imp:propagate lazy before combining t->l,t->r;
    combine(t,t->l,t);
    combine(t,t,t->r);
}

void split(pnode t,pnode &l,pnode &r,int pos,int add=0)
{
    if(!t)return void(l=r=NULL);
//    lazy(t);
    int curr_pos = add + sz(t->l);
    if(curr_pos<=pos)//element at pos goes to left subtree(l)
        split(t->r,t->r,r,pos,curr_pos+1),l=t;
    else
        split(t->l,l,t->l,pos,add),r=t;
    upd_sz(t);
    operation(t);
}

void merge(pnode &t,pnode l,pnode r)  //l->leftarray,r->rightarray,t->resulting array
{
//    lazy(l);
//    lazy(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
    else    merge(r->l,l,r->l),t=r;
    upd_sz(t);
    operation(t);
}

pnode init(int val)
{
    pnode ret = (pnode)malloc(sizeof(node));
    ret->prior=rand();
    ret->size=1;
    ret->val=val;
    ret->sum=val;
    ret->leftbest=val;
    ret->rightbest=val;
    ret->ans=val;
//    ret->lazy=0;
    return ret;
}

int range_query(pnode t,int l,int r) //[l,r]
{
    pnode L,mid,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);//note: r-l!!
    int ans = t->ans;
    merge(mid,L,t);
    merge(t,mid,R);
    return ans;
}

void range_update(pnode t,int l,int r,int val) //[l,r]
{
    pnode L,mid,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);//note: r-l!!
//    t->lazy+=val; //lazy_update
    merge(mid,L,t);
    merge(t,mid,R);
}

//void split(pnode t,pnode &l,pnode &r,int key)
//{
//    if(!t) l=r=NULL;
//    else if(t->val<=key) split(t->r,t->r,r,key),l=t; //elem=key comes in l
//    else split(t->l,l,t->l,key),r=t;
//    upd_sz(t);
//}
//
//void insert(pnode &t,pnode it)
//{
//    if(!t) t=it;
//    else if(it->prior>t->prior) split(t,it->l,it->r,it->val),t=it;
//    else insert(t->val<=it->val?t->r:t->l,it);
//    upd_sz(t);
//}
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


void output(pnode t)
{
    if(!t) return;
    output(t->l);
    printf("%d ",t->val);
    output(t->r);
}

/*-------------------------Treap End--------------------------*/



int main()
{
//    freopen("in.txt","r",stdin);
//	  freopen("out.txt","w",stdout);

    pnode root=NULL;
    int n;
    sf(n);
    for(int i=0;i<n;i++)
    {
        int a;
        sf(a);
        merge(root,root,init(a));
    }

    int q;
    sf(q);
    while(q--)
    {
        char ch;
        int x,y;
        scanf(" %c",&ch);
        if(ch=='I')
        {
            sff(x,y);
            x--;
            pnode l,r;
            split(root,l,r,x-1);
            merge(root,l,init(y));
            merge(root,root,r);
        }
        else if(ch=='D')
        {
            sf(x);
            x--;
            pnode l,r;
            split(root,l,r,x-1);
            split(r,r,root,0);
            merge(root,l,root);
        }
        else if(ch=='R')
        {
            sff(x,y);
            x--;
            pnode l,r;
            split(root,l,r,x-1);
            split(r,r,root,0);
            merge(l,l,init(y));
            merge(root,l,root);
        }
        else if(ch=='Q')
        {
            sff(x,y);
            x--,y--;
            printf("%d\n",range_query(root,x,y));
        }
    }

    return 0;
}
