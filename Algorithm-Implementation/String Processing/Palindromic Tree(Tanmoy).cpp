///***Note: String must be in 2 based indexing

/**
    len[idx] = length of the palindromic string which represent this idx node.
    link[idx] = node of the longest palindromic suffix string of palindromic string represent by node idx.
    idx = current node
    t = last processed node
*/

#define mx 100005

int tree[mx][26];
int len[mx],link[mx];
int idx,t;

///ms(tree,0) optimization
int cas;
int visi[mx][26];

char str[mx];

void init_tree()
{
    len[1]=-1,link[1]=1;
    len[2]= 0,link[2]=1;
    cas++;
    idx=t=2;
}

void insert(int p)
{
    while(str[p-len[t]-1]!=str[p]) t=link[t];
    int x=link[t];
    while(str[p-len[x]-1]!=str[p]) x=link[x];
    int c=str[p]-'a';
    if(visi[t][c]!=cas)
    {
        visi[t][c]=cas;
        tree[t][c]=++idx;
        len[idx]=len[t]+2;
        link[idx]=(len[idx]==1)?2:tree[x][c];
    }
    t=tree[t][c];
}

