#include <bits/stdc++.h>

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
#define D(x)             cout<<#x " = "<<(x)<<endl
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


#define mx 100005

int SA[mx],tempSA[mx];
int RA[mx],tempRA[mx];
int c[mx];
int LCP[mx],PLCP[mx],Phi[mx];
//int P[18][mx],stp;
string str,patern;
int P[mx],lps[mx],right_pos[mx];
char sss[mx];
int n;

void counting_sort(int k)
{
    int maxi=max(300,n);
    ms(c,0);
    for(int i=0; i<n; i++)
    {
        int a=i+k<n?RA[i+k]:0;
        c[a]++;
    }
    for(int i=0,sum=0; i<maxi; i++)
    {
        int x=c[i];
        c[i]=sum;
        sum+=x;
    }

    for(int i=0; i<n; i++)
    {
        int a=SA[i]+k<n?RA[SA[i]+k]:0;
        int b=c[a];
        c[a]++;
        tempSA[b]=SA[i];
    }

    for(int i=0; i<n; i++)
        SA[i]=tempSA[i];
}

void build_Suffix_Array()
{
    for(int i=0; i<n; i++)
    {
        RA[i]=str[i];
        SA[i]=i;
    }

    for(int k=1; k<n; k*=2)
    {
        counting_sort(k);
        counting_sort(0);
        int r=0;
        tempRA[SA[0]]=r=0;
        for(int i=1; i<n; i++)
        {
            if(RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])
                tempRA[SA[i]]=r;
            else
                tempRA[SA[i]]=++r;
        }
        for(int i=0; i<n; i++)
        {
            RA[i]=tempRA[i];
        }
        if(RA[SA[n-1]]==n-1) break;
    }
}

void build_LCP()
{
    Phi[SA[0]]=-1;
    for(int i=1; i<n; i++)
        Phi[SA[i]]=SA[i-1];
    for(int i=0,L=0; i<n; i++)
    {
        if(Phi[i]==-1)
        {
            PLCP[i]=0;
            continue;
        }
        while(str[i+L]==str[Phi[i]+L]) L++;
        PLCP[i]=L;
        L=max(L-1,0);
    }

    for(int i=0; i<n; i++)
        LCP[i]=PLCP[SA[i]];
}


void KMP_Preprocess(string &s)
{
    ms(lps,0);
    int k=0;
    lps[0]=0;
    for(int i=1;i<SZ(s);i++)
    {
        while(k>0 && s[i]!=s[k]) k=lps[k-1];
        if(s[i]==s[k]) k++;
        lps[i]=k;
    }
}

void KMP(string &s, string &pat)
{
    KMP_Preprocess(pat);
    int k=lps[0];
    ms(P,-1);

    for(int i=0;i<SZ(s);i++)
    {
        while(k>0 && s[i]!=pat[k]) k=lps[k-1];
        if(s[i]==pat[k]) k++;
        if(k==SZ(pat))
        {
            P[i-k+1]=i-k+1;
            k=lps[k-1];
        }
    }
    int last=SZ(s);
    int len=SZ(pat)-1;
    for(int i=SZ(s)-1;i>=0;i--)
    {
        if(P[i]==-1)
            P[i]=last;
        else
        {
            P[i]+=len;
            last=P[i];
        }
    }
}



int main()
{

//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    int t;
    sf(t);
    TEST_CASE(t)
    {
        scanf("%s",sss);
        str=sss;
        scanf("%s",sss);
        patern=sss;
        KMP(str,patern);
//        D(str);
//        for(int i=0;i<SZ(str);i++)
//            cout<<P[i]<<" ";
//        cout<<endl;
        str+="$";
        n=SZ(str);
        build_Suffix_Array();
        build_LCP();

//        for(int i=0;i<n;i++)
//            cout<<SA[i]<<" ";
//        cout<<endl;
//        for(int i=0;i<n;i++)
//            cout<<str.substr(SA[i])<<endl;

        int ans=0;

        for(int i=1;i<n;i++)
        {
            int a=SA[i];
            int temp=P[a]-a-LCP[i];
            temp=max(temp,0);
            ans+=temp;
        }
        PRINT_CASE;
        pf("%d\n",ans);

    }

    return 0;
}



/*
Algorithm: KMP, Suffix Array 
A nice tutorial on KMP: http://www.iti.fh-flensburg.de/lang/algorithmen/pattern/kmpen.htm
Tutorial on Suffix Array: http://www.stanford.edu/class/cs97si/suffix-array.pdf
First you need to know how to find the number of distinct substrings of a string using suffix
array. The idea has been described on the solution of problem 4 in the tutorial link I've given. 
In code, you can do this in:
sum = 0;
for(i = 0; i < len; i++)
{
    k = (len - B[i]) - LCP[i];
    if(k > 0) sum += k;
}
(Skip the next section if you already know how to find the number of distinct substrings)
------------------------------------------------------------------------------------------------
B[i] deontes the starting index of the i-th suffix in sorted order. For example, for the string
abaab:
B[0] = 2 aab
B[1] = 3 ab
B[2] = 0 abaab
B[3] = 4 b
B[4] = 1 baab
so len - B[i] = length of the i-th suffix in sorted order
len - B[0] = 3 aab
len - B[1] = 2 ab
len - B[2] = 5 abaab
len - B[3] = 1 b
len - B[4] = 4 baab
LCP[i] deontes the longest common prefix of the i-th and (i-1)th suffix in sorted order.
LCP[0] = 0	aab		distinct substrings: aab aa a, no common prefix
			null	k = (len - B[i]) - LCP[i] = 3 - 0 = 3
			
LCP[1] = 1 	ab		distinct substrings: ab, common prefix: a; so a not counted
			aab		k = (len - B[i]) - LCP[i] = 2 - 1 = 1
			
LCP[2] = 2	abaab	distinct substrings: abaab abaa aba, common prefix: ab; so ab, a not counted
			ab		k = (len - B[i]) - LCP[i] = 5 - 2 = 3
			
LCP[3] = 0	b		distinct substrings: b, no common prefix
			abaab	k = (len - B[i]) - LCP[i] = 1 - 0 = 1
			
LCP[4] = 1	baab	distinct substrings: baab baa ba, common prefix: b; so b not counted
			b		k = (len - B[i]) - LCP[i] = 4 - 1 = 3
			
So total distinct substrings = 3+1+3+1+3 = 11.
Our problem is harder, we have to find the distinct substrings of string A and remove those
substrings which contains B as a substring.
------------------------------------------------------------------------------------------------
The first test case:
ababa
ba
Using KMP, we can find out in which positions in A, B is found as a substring.
ababa
-ba--	position 1
---ba	position 3
q[i] denotes the nearest position on the right of A[i] where B is found as a substring
A[i]	ababa
q[i]	11335
Now, look, whe we are considering the suffix ababa, previously we are considering 5 substrings
ababa, abab, aba, ab, a
and deleting the duplicates from these substrings using LCP. But now we know ababa, abab, aba
can't be the part of the ans, as they contains ba. So we have to delete them too. q[B[i]]+len2-1
denotes the position where we have to stop deletion. All the substrings before this position
contains B as a substring, so they need to be deleted. So the code becomes:
for(i = 0; i < len1; i++)
{
	k = min(len1, q[B[i]]+len2-1) - B[i] - LCP[i];
	if(k > 0) sum += k;
}
*/

