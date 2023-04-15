#include <iostream>
#include <bitset>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

pair<int,int> idxtoxy[16] = {{0,0},{1,0},{3,0},{2,0},{0,1},{1,1},{3,1},{2,1},{0,3},{1,3},{3,3},{2,3},{0,2},{1,2},{3,2},{2,2}};
int xytoidx[4][4] = {{0,4,12,8},{1,5,13,9},{3,7,15,11},{2,6,14,10}};
int init_m[4][4] = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
vector<int> nearsqridx;
int chk[16] = {0,}, chksize;
vector<vector<int>> epi;
vector<pair<int,int>> atleastsize;

// ascending order (vector's size)
bool cmp(pair<int,int> a, pair<int,int> b) {
    return a.second < b.second;
}

// find near square's index
void nearsqr(int idx) {
    int xoring = 1,tmp;
    for (int i=0; i<4; i++) {
        tmp = idx ^ xoring;
        if (init_m[idxtoxy[tmp].first][idxtoxy[tmp].second]==1) nearsqridx.push_back(tmp) ;
        xoring = (xoring << 1);
    }
}

// if (chk[idx]==1) skip vector storing
void minussize(int idx) {
    int xoring = 1,tmp;
    vector<int> trash;
    for (int i=0; i<4; i++) {
        tmp = idx ^ xoring;
        if (init_m[idxtoxy[tmp].first][idxtoxy[tmp].second]==1) {
            if (chk[tmp]==1) trash.push_back(tmp);
            else nearsqridx.push_back(tmp);
        }
        xoring = (xoring << 1);
    }
    if (nearsqridx.empty()) nearsqridx.push_back(trash[0]);
}

// find prime implicant & check covered index
void p_i_spect(int idx, int size) {
    auto [x,y] = idxtoxy[idx];
    vector<int> pi;
    if (size==4) return;
    else if (size==3) {
        if (init_m[x][(y+1)%4]&&init_m[x][(y+2)%4]&&init_m[x][(y+3)%4]&&init_m[(x+1)%4][y]&&init_m[(x+1)%4][(y+1)%4]&&init_m[(x+1)%4][(y+2)%4]&&init_m[(x+1)%4][(y+3)%4]) {
            chk[xytoidx[x][(y+1)%4]]=1; pi.push_back(xytoidx[x][(y+1)%4]);
            chk[xytoidx[x][(y+2)%4]]=1; pi.push_back(xytoidx[x][(y+2)%4]);
            chk[xytoidx[x][(y+3)%4]]=1; pi.push_back(xytoidx[x][(y+3)%4]);
            chk[xytoidx[(x+1)%4][y]]=1; pi.push_back(xytoidx[(x+1)%4][y]);
            chk[xytoidx[(x+1)%4][(y+1)%4]]=1; pi.push_back(xytoidx[(x+1)%4][(y+1)%4]);
            chk[xytoidx[(x+1)%4][(y+2)%4]]=1; pi.push_back(xytoidx[(x+1)%4][(y+2)%4]);
            chk[xytoidx[(x+1)%4][(y+3)%4]]=1; pi.push_back(xytoidx[(x+1)%4][(y+3)%4]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[x][(y+1)%4]&&init_m[x][(y+2)%4]&&init_m[x][(y+3)%4]&&init_m[(x+3)%4][y]&&init_m[(x+3)%4][(y+1)%4]&&init_m[(x+3)%4][(y+2)%4]&&init_m[(x+3)%4][(y+3)%4]) {
            chk[xytoidx[x][(y+1)%4]]=1; pi.push_back(xytoidx[x][(y+1)%4]);
            chk[xytoidx[x][(y+2)%4]]=1; pi.push_back(xytoidx[x][(y+2)%4]);
            chk[xytoidx[x][(y+3)%4]]=1; pi.push_back(xytoidx[x][(y+3)%4]);
            chk[xytoidx[(x+3)%4][y]]=1; pi.push_back(xytoidx[(x+3)%4][y]);
            chk[xytoidx[(x+3)%4][(y+1)%4]]=1; pi.push_back(xytoidx[(x+3)%4][(y+1)%4]);
            chk[xytoidx[(x+3)%4][(y+2)%4]]=1; pi.push_back(xytoidx[(x+3)%4][(y+2)%4]);
            chk[xytoidx[(x+3)%4][(y+3)%4]]=1; pi.push_back(xytoidx[(x+3)%4][(y+3)%4]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[(x+1)%4][y]&&init_m[(x+2)%4][y]&&init_m[(x+3)%4][y]&&init_m[x][(y+1)%4]&&init_m[(x+1)%4][(y+1)%4]&&init_m[(x+2)%4][(y+1)%4]&&init_m[(x+3)%4][(y+1)%4]) {
            chk[xytoidx[(x+1)%4][y]]=1; pi.push_back(xytoidx[(x+1)%4][y]);
            chk[xytoidx[(x+2)%4][y]]=1; pi.push_back(xytoidx[(x+2)%4][y]);
            chk[xytoidx[(x+3)%4][y]]=1; pi.push_back(xytoidx[(x+3)%4][y]);
            chk[xytoidx[x][(y+1)%4]]=1; pi.push_back(xytoidx[x][(y+1)%4]);
            chk[xytoidx[(x+1)%4][(y+1)%4]]=1; pi.push_back(xytoidx[(x+1)%4][(y+1)%4]);
            chk[xytoidx[(x+2)%4][(y+1)%4]]=1; pi.push_back(xytoidx[(x+2)%4][(y+1)%4]);
            chk[xytoidx[(x+3)%4][(y+1)%4]]=1; pi.push_back(xytoidx[(x+3)%4][(y+1)%4]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[(x+1)%4][y]&&init_m[(x+2)%4][y]&&init_m[(x+3)%4][y]&&init_m[x][(y+3)%4]&&init_m[(x+1)%4][(y+3)%4]&&init_m[(x+2)%4][(y+3)%4]&&init_m[(x+3)%4][(y+3)%4]) {
            chk[xytoidx[(x+1)%4][y]]=1; pi.push_back(xytoidx[(x+1)%4][y]);
            chk[xytoidx[(x+2)%4][y]]=1; pi.push_back(xytoidx[(x+2)%4][y]);
            chk[xytoidx[(x+3)%4][y]]=1; pi.push_back(xytoidx[(x+3)%4][y]);
            chk[xytoidx[x][(y+3)%4]]=1; pi.push_back(xytoidx[x][(y+3)%4]);
            chk[xytoidx[(x+1)%4][(y+3)%4]]=1; pi.push_back(xytoidx[(x+1)%4][(y+3)%4]);
            chk[xytoidx[(x+2)%4][(y+3)%4]]=1; pi.push_back(xytoidx[(x+2)%4][(y+3)%4]);
            chk[xytoidx[(x+3)%4][(y+3)%4]]=1; pi.push_back(xytoidx[(x+3)%4][(y+3)%4]);
            chk[idx]=1; pi.push_back(idx);
        }
    }
    else if (size==2) {
        if (init_m[x][(y+1)%4]&&init_m[x][(y+2)%4]&&init_m[x][(y+3)%4]) {
            chk[xytoidx[x][(y+1)%4]]=1; pi.push_back(xytoidx[x][(y+1)%4]);
            chk[xytoidx[x][(y+2)%4]]=1; pi.push_back(xytoidx[x][(y+2)%4]);
            chk[xytoidx[x][(y+3)%4]]=1; pi.push_back(xytoidx[x][(y+3)%4]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[(x+1)%4][y]&&init_m[(x+2)%4][y]&&init_m[(x+3)%4][y]) {
            chk[xytoidx[(x+1)%4][y]]=1; pi.push_back(xytoidx[(x+1)%4][y]);
            chk[xytoidx[(x+2)%4][y]]=1; pi.push_back(xytoidx[(x+2)%4][y]);
            chk[xytoidx[(x+3)%4][y]]=1; pi.push_back(xytoidx[(x+3)%4][y]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[(x+3)%4][y]&&init_m[(x+3)%4][(y+1)%4]&&init_m[x][(y+1)%4]) {
            chk[xytoidx[(x+3)%4][y]]=1; pi.push_back(xytoidx[(x+3)%4][y]);
            chk[xytoidx[(x+3)%4][(y+1)%4]]=1; pi.push_back(xytoidx[(x+3)%4][(y+1)%4]);
            chk[xytoidx[x][(y+1)%4]]=1; pi.push_back(xytoidx[x][(y+1)%4]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[x][(y+1)%4]&&init_m[(x+1)%4][(y+1)%4]&&init_m[(x+1)%4][y]) {
            chk[xytoidx[x][(y+1)%4]]=1; pi.push_back(xytoidx[x][(y+1)%4]);
            chk[xytoidx[(x+1)%4][(y+1)%4]]=1; pi.push_back(xytoidx[(x+1)%4][(y+1)%4]);
            chk[xytoidx[(x+1)%4][y]]=1; pi.push_back(xytoidx[(x+1)%4][y]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[x][(y+3)%4]&&init_m[(x+1)%4][(y+3)%4]&&init_m[(x+1)%4][y]) {
            chk[xytoidx[x][(y+3)%4]]=1; pi.push_back(xytoidx[x][(y+3)%4]);
            chk[xytoidx[(x+1)%4][(y+3)%4]]=1; pi.push_back(xytoidx[(x+1)%4][(y+3)%4]);
            chk[xytoidx[(x+1)%4][y]]=1; pi.push_back(xytoidx[(x+1)%4][y]);
            chk[idx]=1; pi.push_back(idx);
        }
        else if (init_m[x][(y+3)%4]&&init_m[(x+3)%4][(y+3)%4]&&init_m[(x+3)%4][y]) {
            chk[xytoidx[x][(y+3)%4]]=1; pi.push_back(xytoidx[x][(y+3)%4]);
            chk[xytoidx[(x+3)%4][(y+3)%4]]=1; pi.push_back(xytoidx[(x+3)%4][(y+3)%4]);
            chk[xytoidx[(x+3)%4][y]]=1; pi.push_back(xytoidx[(x+3)%4][y]);
            chk[idx]=1; pi.push_back(idx);
        }
    }
    else if (size==1) {
        chk[nearsqridx[0]]=1; pi.push_back(nearsqridx[0]);
        chk[idx]=1; pi.push_back(idx);
    }
    else {
        chk[idx]=1; pi.push_back(idx);
    }
    if (!pi.empty()) epi.push_back(pi);
}

int main() {
    ios::sync_with_stdio(0);

    cout << "[4 variable K-map implementation]" << '\n';
    int mintermcnt;
    cout << "Enter numbers of minterms: ";
    cin >> mintermcnt;
    chksize = mintermcnt;
    if (mintermcnt==16) {
        cout << 1; return;
    }
    else if (mintermcnt==0) {
        cout << 0; return;
    }

    int n;
    cout << "Enter indexs of minterms: ";
    for (int i=0; i<mintermcnt; i++) {
        cin >> n;
        init_m[idxtoxy[n].first][idxtoxy[n].second] = 1;
        chk[n]=-1;
    }
    
    int size;
    for (int i=0; i<16; i++) {
        if (chk[i]==-1) {
            nearsqridx.clear();
            nearsqr(i);
            size = nearsqridx.size();
            p_i_spect(i,size);
        }
    }

    for (int i=0; i<16; i++) {
        if (chk[i]==-1) {
            nearsqridx.clear();
            minussize(i);
            size = nearsqridx.size();
            vector<int> tmp_pi;
            if (size==1) {
                chk[i]=1; tmp_pi.push_back(i);
                chk[nearsqridx[0]]=1; tmp_pi.push_back(nearsqridx[0]);
                epi.push_back(tmp_pi);
            } 
            else atleastsize.push_back({i,size});
        }
    }
    int atleast = atleastsize.size();
    sort(atleastsize.begin(),atleastsize.end(),cmp);
    for (int i=0; i<atleast; i++) {
        if (chk[atleastsize[i].first]==-1) p_i_spect(atleastsize[i].first,atleastsize[i].second);
    }

    int epi_size = epi.size();
    vector<string> minterms;
    int shift=1;
    for (int a=0; a<epi_size; a++) {
        int epi_i_size = epi[a].size();
        int positive = 15, negative = 15;
        for (int j=0; j<epi_i_size; j++) {
            positive &= epi[a][j];
            negative &= ~epi[a][j];
        }
        char abcd_pi[9]={'z','z','z','z','z','z','z','z'};
        if (positive & shift) abcd_pi[7]='D';
        if (positive & shift<<1) abcd_pi[5] = 'C';
        if (positive & shift<<2) abcd_pi[3] = 'B';
        if (positive & shift<<3) abcd_pi[1] = 'A';
        if (negative & shift) {
            abcd_pi[7] = 'D'; abcd_pi[6] = '!';
        }
        if (negative & shift<<1) {
            abcd_pi[5] = 'C'; abcd_pi[4] = '!';
        }
        if (negative & shift<<2) {
            abcd_pi[3] = 'B'; abcd_pi[2] = '!';
        }
        if (negative & shift<<3) {
            abcd_pi[1] = 'A'; abcd_pi[0] = '!';
        }
        string abcd(abcd_pi);
        abcd.erase(remove(abcd.begin(),abcd.end(),'z'), abcd.end());
        minterms.push_back(abcd);
    }
    cout << "Product terms : ";
    for (int i=0; i<epi_size; i++) cout << minterms[i] << ' ';
}
