/*-------------------------Treap Start------------------------*/
struct node
{
    int prior,size;
    int val;//value stored in the array
    int sum;//whatever info you want to maintain in segtree for each node
    int lazy;//whatever lazy update you want to do
    struct node *l,*r;
};

typedef node* pnode;

int sz(pnode t) /// Return size of the current subtree
{
    return t?t->size:0;
}

void upd_sz(pnode t) /// Update size of current subtree
{
    if(t)t->size=sz(t->l)+1+sz(t->r);
}

void lazy(pnode t) ///Propagate the lazy value
{
    if(!t || !t->lazy)return;
    t->val+=t->lazy;//operation of lazy
    t->sum+=t->lazy*sz(t);
    if(t->l)t->l->lazy+=t->lazy;//propagate lazy
    if(t->r)t->r->lazy+=t->lazy;
    t->lazy=0;
}

void reset(pnode t)
{
    if(t)t->sum = t->val;//no need to reset lazy coz when we call this lazy would itself be propagated
}

void combine(pnode& t,pnode l,pnode r) ///combining two ranges of segment tree
{
    if(!l || !r)return void(t = l?l:r);
    t->sum = l->sum + r->sum;
}

void operation(pnode t) //operation of segtree
{
    if(!t)return;
    reset(t);//reset the value of current node assuming it now represents a single element of the array
    lazy(t->l);
    lazy(t->r);//imp:propagate lazy before combining t->l,t->r;
    combine(t,t->l,t);
    combine(t,t,t->r);
}

/**
split : Splits the array A[1..n] into two parts : L[1..pos] , R[pos+1..n] , about "pos". Note that A[pos] comes in the left part.
merge : merges L[1..n1] , R[1..n2] to form A[1..n1,n1+1,...n2] . Note that the condition for merge in treap
        (i.e. greatest element in l <= smallest element in r) is satisified here since the keys are array indices and we are
        assuming that mergin L and R would result in A such that first n1 elements of A come from L and next n2 from R.

**/

void split(pnode t,pnode &l,pnode &r,int pos,int add=0) ///Split node by position
{
    if(!t)return void(l=r=NULL);
    lazy(t);
    int curr_pos = add + sz(t->l);
    if(curr_pos<=pos)//element at pos goes to left subtree(l)
        split(t->r,t->r,r,pos,curr_pos+1),l=t;
    else
        split(t->l,l,t->l,pos,add),r=t;
    upd_sz(t);
    operation(t);
}

void merge(pnode &t,pnode l,pnode r) /// Merge 2 child node
{
    //l->leftarray,r->rightarray,t->resulting array
    lazy(l);
    lazy(r);
    if(!l || !r) t = l?l:r;
    else if(l->prior>r->prior)merge(l->r,l->r,r),t=l;
    else    merge(r->l,l,r->l),t=r;
    upd_sz(t);
    operation(t);
}

pnode init(int val) ///Initialize a node
{
    pnode ret = (pnode)malloc(sizeof(node));
    ret->prior=rand();
    ret->size=1;
    ret->val=val;
    ret->sum=val;
    ret->lazy=0;
    return ret;
}

int range_query(pnode t,int l,int r) ///Query over range [l,r] where t is root
{
    pnode L,mid,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);//note: r-l!!
    int ans = t->sum;
    merge(mid,L,t);
    merge(t,mid,R);
    return ans;
}

void range_update(pnode t,int l,int r,int val) /// Range update over range [l,r] whare t is root
{
    pnode L,mid,R;
    split(t,L,mid,l-1);
    split(mid,t,R,r-l);//note: r-l!!
    t->lazy+=val; //lazy_update
    merge(mid,L,t);
    merge(t,mid,R);
}

/**

//split(T,X) :  It splits a given treap T into two different treaps L and R such that L contains all the nodes with
//              Bk<=X and R contains all the nodes with Bk>X . The original treap T is destroyed/doesn't exist anymore
//              after the split operation. (The equality can be put on either side depending on your choice wlg.
//              I prefer equality on the left side and so shall be used further in the blog)
//
//
//merge(L,R) : The merge operation merges two given treaps L and R into a single treap T and L and R are destroyed after
//             the operation. A very important assumption of the merge operation is that the largest value of L is less
//             than the smallest value of R (where value refers to the Bk values of the particular node).


void split(pnode t,pnode &l,pnode &r,int key)
{
    if(!t) l=r=NULL;
    else if(t->val<=key) split(t->r,t->r,r,key),l=t; //elem=key comes in l
    else split(t->l,l,t->l,key),r=t;
    upd_sz(t);
}

void insert(pnode &t,pnode it) ///Insert a single element in treap. It always keep unique elements.
{
    if(!t) t=it;
    else if(it->prior>t->prior) split(t,it->l,it->r,it->val),t=it;
    else insert(t->val<=it->val?t->r:t->l,it);
    upd_sz(t);
}

void erase(pnode &t,int key) ///Erase an signle element where element is key from treap.
{
    if(!t)return;
    else if(t->val==key)
    {
        pnode temp=t;
        merge(t,t->l,t->r);
        free(temp);
    }
    else erase(t->val<key?t->r:t->l,key);
    upd_sz(t);
}

void merge(pnode &t,pnode l,pnode r)
{
    if(!l || !r) t=l?l:r;
    else if(l->prior > r->prior)merge(l->r,l->r,r),t=l;
    else merge(r->l,l,r->l),t=r;
    upd_sz(t);
}
*/

void output(pnode t)
{
    lazy(t);
    if(!t)
    {
        cerr<<"{}";
        return;
    }
    cerr<<" { ";
//    cerr<<"("<<t->val.ff<<" "<<t->val.ss<<")"<<" ";
    cout<<t->val<<" ";
    output(t->l);
//    printf("%d ",t->val);
    output(t->r);
    cerr<<" } ";
}

void print_Treap(pnode t)
{
    cerr<<"--------------------"<<endl;
    output(t);
    cerr<<endl<<"--------------------"<<endl;

/*-------------------------Treap End--------------------------*/

