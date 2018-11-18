
#define mx 50005

int SA[mx],tempSA[mx];
int RA[2*mx],tempRA[mx];
int c[mx];
int LCP[mx],PLCP[mx],Phi[mx];
int P[18][mx], step;
char str[mx];
char pattern[mx];
int n;

void counting_sort(int k) {
    int maxi=max(300,n);
    ms(c,0);
    for(int i=0; i<n; i++) {
        int a=i+k<n?RA[i+k]:0;
        c[a]++;
    }
    for(int i=0,sum=0; i<maxi; i++) {
        int x=c[i];
        c[i]=sum;
        sum+=x;
    }

    for(int i=0; i<n; i++) {
        int a=SA[i]+k<n?RA[SA[i]+k]:0;
        int b=c[a];
        c[a]++;
        tempSA[b]=SA[i];
    }

    for(int i=0; i<n; i++)
        SA[i]=tempSA[i];
}

void build_Suffix_Array() {
    step=0;
    for(int i=0; i<n; i++) {
        RA[i]=str[i];
        SA[i]=i;
        P[step][i]=RA[i];
    }
    step++;
    for(int k=1; k<n; k*=2) {
        counting_sort(k);
        counting_sort(0);
        int r=0;
        tempRA[SA[0]]=r=0;
        for(int i=1; i<n; i++) {
            if(RA[SA[i]]==RA[SA[i-1]] && RA[SA[i]+k]==RA[SA[i-1]+k])
                tempRA[SA[i]]=r;
            else
                tempRA[SA[i]]=++r;
        }
        for(int i=0; i<n; i++) {
            RA[i]=tempRA[i];
            P[step][i]=RA[i];
        }
        step++;
        if(RA[SA[n-1]]==n-1) break;
    }
    step--;
}

int find_lcp(int x, int y) {
    int ret=0;
    if(x==y) return n-x;
    for(int k=step; k>=0 && x<n && y<n; k--) {
        if(P[k][x]==P[k][y]) {
            x+=(1<<k);
            y+=(1<<k);
            ret+=(1<<k);
        }
    }
    return ret;
}

void build_LCP() {
    Phi[SA[0]]=-1;
    for(int i=1; i<n; i++)
        Phi[SA[i]]=SA[i-1];
    for(int i=0,L=0; i<n; i++) {
        if(Phi[i]==-1) {
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

int find_pattern(int len) {
    int lo=0,hi=n-1;
    while(lo<hi) {
        int mid=(lo+hi)/2;
        int res=strncmp(str+SA[mid],pattern,len);
        if(res>=0)
            hi=mid;
        else
            lo=mid+1;
    }
    ll ret=lo;
    if(strncmp(str+SA[ret],pattern,len)!=0) return 0;
    lo=0,hi=n-1;
    while(lo<hi) {
        int mid=(lo+hi)/2;
        int res=strncmp(str+SA[mid],pattern,len);
        if(res>0)
            hi=mid;
        else
            lo=mid+1;
    }

    if(strncmp(str+SA[hi],pattern,len)!=0) hi--;
    return hi-ret+1;
}


int main() {

//    freopen("in.txt","r",stdin);
//    freopen("out.txt","w",stdout);

    scanf(" %s",str);
    strcat(str,"$");
    n=strlen(str);
    build_Suffix_Array();

    cout<<"index : ";
    for(int i=0; i<n; i++)
        cout<<i<<" ";
    cout<<endl;
    cout<<"SA    : ";
    for(int i=0; i<n; i++)
        cout<<SA[i]<<" ";
    cout<<endl;

    string ss=str;

    for(int i=0; i<n; i++)
        cout<<ss.substr(SA[i])<<endl;

    return 0;
}

