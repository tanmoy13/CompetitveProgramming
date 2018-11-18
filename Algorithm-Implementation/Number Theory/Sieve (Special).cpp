#define mx 100000
 
bitset<mx/2> vis;
 
vector<int>prime;
 
void sive()
{
    int x=mx/2,y=sqrt(mx)/2;
 
    for(int i=1; i<y; i++)
    {
        if(vis[i]==0)
        {
            for(int j=i*(i+1)*2; j<x; j+=(2*i)+1)
                vis[j]=1;
        }
    }
 
    prime.pb(2);
    for(int i=3; i<mx; i+=2)
        if(vis[i/2]==0)
            prime.pb(i);
 
}
