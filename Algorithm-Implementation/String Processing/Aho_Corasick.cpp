/*
    - Always remember to execute trie[nodeCnt].clear(); in multiple test case problem
      In insertTrie function
    - Function call order in main function
            insertTrie(str,i);
            calcFailFunction();
            match_text(text);
            push_up();
*/

const int Size = 1000006; /// Maximum Text Length
const int NODE = 250005; /// Maximum Nodes
const int MXQ = 1005; /// Maximum Patterns
const int MXL = 1005; /// Maximum Length Of Pattern
const int MXCHR = 52; /// Maximum Characters

struct node
{
    int val;
    bool endmark;
    int next[MXCHR];
    int endCnt; /// Number of times the prefix match with text
    vector<int>endsList; /// List of patterns ends here
    void clear()
    {
        endmark=0;
        endCnt=0;
        ms(next,0);
        endsList.clear();
    }
} trie[NODE];

int get_name(char ch)
{
    if(ch>='a' && ch<='z')
        return ch-'a';
    if(ch>='A' && ch<='Z')
        return 26+(ch-'A');
}

int root=0,nodeCnt=0; ///Root node and total node count of the trie tree

void insertTrie(string &str, int id)
{
    /// Add string str to the trie in general way
    int cur=root;
    for(int i=0; i<SZ(str); i++)
    {
        int a=get_name(str[i]);
        if(trie[cur].next[a]==0)
        {
            nodeCnt++;
            trie[cur].next[a]=nodeCnt;
            trie[nodeCnt].clear();
            trie[nodeCnt].val=a;
        }
        cur=trie[cur].next[a];
    }
    trie[cur].endmark=1;
    trie[cur].endsList.pb(id);
}

vector<int>lvlnode; /// List of nodes sorted by level


char ss[Size];
int fail[NODE],par[NODE],level[NODE];


int go_to(int u, int name) ///Return the appropriate position for the char name
{
    while(u!=0 && trie[u].next[name]==0)
        u=fail[u];
    return trie[u].next[name];
}

void calcFailFunction() ///This bfs calculates failure function on trie tree
{
    queue<int>Q;
    Q.push(root);
    par[root]=root;
    level[root]=0;
    fail[root]=root;
    while(!Q.empty())
    {
        int u=Q.front();
        lvlnode.pb(u);
        Q.pop();
        /// Add all the child to the queue:
        for(int i=0; i<MXCHR; i++)
        {
            int v=trie[u].next[i];
            if(v==0) continue;
            par[v]=u;
            level[v]=level[u]+1;

            /// Find fall back of s:
            fail[v]=go_to(fail[u],i);
            if(fail[v]==v) /// Self fall back not allowed
                fail[v]=0;
            if(level[v]==1) /// fail of first level nodes is always root
                fail[v]=0;
            Q.push(v);
        }

    }
}

ll ans[MXQ]; /// How many times i'th pattern matched

void match_text(string &str) /// Iterate through the whole text and find all the matchings
{
    int cur=root;
    for(int i=0; i<SZ(str); i++)
    {
        int a=get_name(str[i]);
        if(trie[cur].next[a]!=0)
            cur=trie[cur].next[a];
        else
            cur=go_to(fail[cur],a);
        trie[cur].endCnt+=1;
    }
}

bool cmp(int a, int b)
{
    return level[a]<level[b];
}

void push_up()
{

    /// The prefix of my fall back node matches with my suffix
    /// So every time i match with text, my fall back node also match

    for(int i=SZ(lvlnode)-1; i>=0; i--)
    {
        int u=lvlnode[i];
        if(trie[u].endCnt)
            trie[fail[u]].endCnt+=trie[u].endCnt;
        for(int j=0; j<SZ(trie[u].endsList); j++)
        {
            int v=trie[u].endsList[j];
            ans[v]+=trie[u].endCnt;
        }
    }
}

