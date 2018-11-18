///Manachar's algorithm find longest palindromic substring centered in every position including gap

#define mx 100005

char s1[mx];
int p[2*mx];
int n;

string process(string &str)
{
    string ret;
    ret+='$';
    ret+='#';
    for(int i=0; i<SZ(str); i++)
    {
        ret+=str[i];
        ret+='#';
    }
    ret+='@';
    return ret;
}

void manacher(string s)
{
    string str=process(s);
    int c=0,r=0;
    for(int i=1; i<SZ(str)-1; i++)
    {
        int miror=c+c-i;
        if(i<r)
            p[i]=min(p[miror],r-i);
        while(str[i+1+p[i]]==str[i-1-p[i]])
            p[i]++;
        if(i+p[i]>r)
        {
            c=i;
            r=i+p[i];
        }
    }
    int ret=0;
    int pos=0;
    for(int i=0; i<SZ(str); i++)
    {
        if(p[i]>ret)
        {
            ret=p[i];
            pos=i;
        }
    }

    pos=(pos-ret-1)/2;

    printf("%d\n",ret);
    printf("%s\n",s.substr(pos,ret).c_str());
}



