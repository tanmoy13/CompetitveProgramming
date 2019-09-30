
int trie[1000005][26];
int isWord[1000005];

int root,total,valid_char=26;


///Always remember to call init() function at the beginging of trie

void init()
{
    root =0;
    total=0;
    for(int i=0;i<valid_char;i++)
        trie[root][i]=-1;
}

void insert(string str)
{
    int now=root;
    for(int i=0;i<SZ(str);i++)
    {
        int id=str[i]-'0';
        if(trie[now][id]==-1)
        {
            trie[now][id]=++total;
            ms(trie[total],-1);
        }
        now=trie[now][id];
    }
    isWord[now]++;
}

void del(string str)
{
    int now=root;
    for(int i=0;i<SZ(str);i++)
    {
        now=trie[now][str[i]-'0'];
    }
    isWord[now]--;
}

int query(string str)
{
   int now=root;
   int ans=0;
   for(int i=0;i<SZ(str);i++)
   {
        now=trie[now][str[i]-'0'];
   }
   return isWord[now];
}

