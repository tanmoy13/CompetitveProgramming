
/**
    In suffix automata if we visit all path from initial node and make string using transition characters,
    then we will get all the distinct suffixes of the string.

    len: Length of the string from starting node to this node.
    link: link[cur] means that string[t0 to link_node] is the longest suffix of the string[t0 to cur].
          such that string[t0 to link] and string [t0 to cur] are endpos equivalent.

    next: next['a'] holds the node number of transition node from current node using edge 'a'.

*/
struct state
{
    int len,link;
    map<char,int>next;
};

///Note that size of st array is 2*MAXLEN
const int MAXLEN = 100005;
state st[MAXLEN*2];
int sz,last;

void sa_init(int l)
{
    sz=last=0;
    st[0].len=0;
    st[0].link=-1;
    ++sz;
    l=2*l ///there can be at most 2*l state node in the sa machine.
    for(int i=0;i<l;i++)
        st[i].next.clear();

}

void sa_extend(char c)
{
    int cur=sz++;
    st[cur].len=st[last].len+1;
    int p;
    for(p=last; p!=-1 && !st[p].next.count(c); p=st[p].link)
        st[p].next[c]=cur;
    if(p==-1)
        st[cur].link=0;
    else
    {
        int q=st[p].next[c];
        if(st[p].len+1==st[q].len)
            st[cur].link=q;
        else
        {
            int clone=sz++;
            st[clone].len=st[p].len+1;
            st[clone].next=st[q].next;
            st[clone].link=st[q].link;
            for( ; p!=-1 && st[p].next[c]==q; p=st[p].link)
                st[p].next[c]=clone;
            st[q].link=st[cur].link=clone;
        }
    }
    last=cur;
}

void print_sa(int idx, string str)
{
    if(st[idx].next.empty())
    {
        cout<<str<<endl;
        return;
    }
    for(char ch='a'; ch<='z'; ch++)
    {
        if(st[idx].next.count(ch))
            print_sa(st[idx].next[ch],str+ch);
    }
}

