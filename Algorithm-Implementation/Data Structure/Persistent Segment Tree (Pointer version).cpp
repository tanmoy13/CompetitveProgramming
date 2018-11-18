#define mx 100005

struct node
{
    int val;
    node *l,*r;
    node(int a=0,node *b=NULL, node *c=NULL):val(a),l(b),r(c) {}
};

node *root[mx];

//node *init(int b, int e)
//{
//    if(b==e)
//    {
//        node *p = new node;
//        return p;
//    }
//    node *ret = new node;
//    int mid=(b+e)/2;
//    ret->l=init(b,mid);
//    ret->r=init(mid+1,e);
//    ret->val=ret->l->val+ret->r->val;
//    return ret;
//}


///Update operation create a new segment tree for this new version
///In a update operation at most log N new nodes are created
///This operation return a new root which contains all the previous records and the new one as well
node *update(node *cur, int b, int e, int i)
{
    if(b>i || e<i) return cur; //for out of range returning the old tree
    if(b==e && b==i)
    {
        node *p = new node(1);
        return p;
    }
    node *ret=new node; //creating a new tree for this current version
    int mid=(b+e)/2;
    ret->l=update(cur?cur->l:NULL,b,mid,i);
    ret->r=update(cur?cur->r:NULL,mid+1,e,i);
    if(ret->l) //this check is necessary to avoid runtime error.
        ret->val+=ret->l->val;
    if(ret->r)
        ret->val+=ret->r->val;
    return ret;
}

///This query function take two version as it input and calculate difference like cumulative sum.
///Depending on the difference value and K it's decide where to go left or right subtree.
int query(node *cur, node *prev, int b, int e, int k)
{
    if(k==1 && b==e)
    {
        return b;
    }
    int mid=(b+e)/2;

    int temp=0;
    if(cur && cur->l) temp=cur->l->val; //This two checks are necessary for avoiding runtime error.
    if(cur!=prev && prev && prev->l) temp-=prev->l->val;

    if(temp>=k)
        return query(cur->l,prev?prev->l:NULL,b,mid,k);
    else
        return query(cur->r,prev?prev->r:NULL,mid+1,e,k-temp);
}

int main()
{
//#ifndef ONLINE_JUDGE
////    freopen("in.txt","r",stdin);
////	  freopen("out.txt","w",stdout);
//#endif

    int n,m;
    sff(n,m);
    const int mx_node=1000000009;
//    root[0]=init(1,mx_node);

    map<int,int>mp1,mp2;
    int cnt=0;
    vector<int>v,v1;
    for(int i=0; i<n; i++)
    {
        int a;
        sf(a);
        v.pb(a);
        v1.pb(a);
    }
    sort(all(v));
    for(int i=0; i<SZ(v); i++) //Compressing the array.
    {
        int a=v[i];
        if(mp1[a]==0)
        {
            mp1[a]=++cnt;
            mp2[cnt]=a;
        }
    }

    for(int i=1; i<=n; i++)
    {
        int val=mp1[v1[i-1]];
        root[i]=update(root[i-1],1,cnt,val); //Creating a new tree for every version and storing the root
    }

    while(m--)
    {
        int a,b,k;
        sfff(a,b,k);
        int ans=query(root[b],root[a-1],1,cnt,k); //Calculating answers using two versions of tree.
        ans=mp2[ans];
        printf("%d\n",ans);
    }


    return 0;
}

