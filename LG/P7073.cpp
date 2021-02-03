#include <bits/stdc++.h>
using namespace std;

const int T_OPT = 1, T_VAL = 0, V_OR = 0, V_AND = 1, V_NOT = 2, N = 1000005;
int n, nNum = 0, eNum = 0, bufLoc = 0, rLen = 0;
int va[N], v[N], hed[N], S[N];
bool flag[N]; char rdBuff[N], bufF[10005];
struct edge {int to, nxt; } edges[N * 2];
struct myPair { bool first; int second; } sList[N];

inline bool readNext(bool& tNode, int& vNode) {
    if (bufLoc >= rLen) return false;
    sscanf(rdBuff + bufLoc, "%s", bufF);
    bufLoc += strlen(bufF) + 1;
    
    if (bufF[0] != 'x') {
        tNode = T_OPT;
        switch(bufF[0]) {case '|':return vNode=V_OR,1;case '&':return vNode=V_AND,1;case '!':return vNode=V_NOT,1;}
    }
    tNode = T_VAL; sscanf(bufF + 1, "%d", &vNode); return 1;
}
inline void addedge(int x, int y) { // x -> y
    edges[++eNum] = (edge){y, hed[x]};
    hed[x] = eNum;
}
void makeTree() {
    int top = 0;
    int id = -1; for (int id=0; id<=nNum; ++id) { myPair& i = S[id];
        if (i.first && i.second == V_NOT) {
            addedge(id, S[top--]);
        } else if (i.first) {
            addedge(id, S[top--]);
            addedge(id, S[top--]);
        }
        S[++top] = id;
    }
}
bool calcTree(int x) {
    if (sList[x].first) {
        bool vt, v[2]; int in=0;
        for (int e=hed[x]; e; e=edges[e].nxt) {
            int y = edges[e].to;
            v[in++] = calcTree(y);
        }
        if (sList[x].second == V_NOT) vt = !v[0];
        else if (sList[x].second == V_AND) vt = v[0] & v[1];
        else vt = v[0] | v[1];
        return va[x] = vt;
    } else return va[x] = v[sList[x].second];
}
void flagTree(int x, bool isL = 0) {
    if (sList[x].first) {
        bool vt = va[x], v1,v2;
        int e = hed[x];
        if (e) {
            v1 = va[edges[e].to];
            if (e = edges[e].nxt) v2 = va[edges[e].to];
        }

        for (e=hed[x]; e; e=edges[e].nxt) {
            int y=edges[e].to;
            bool bo = e == hed[x] ? v2 : v1;
            if (isL) flagTree(y, 1);
            else if (sList[x].second == V_NOT) flagTree(y, 0);
            else if (sList[x].second == V_AND) flagTree(y, vt ? 0 : !bo);
            else flagTree(y, !vt ? 0 : bo);
        }
    } else {
        flag[sList[x].second] = isL;
    }
}

int main() {
    nNum = 0; gets(rdBuff); rLen = strlen(rdBuff);
    while (readNext(sList[nNum].first, sList[nNum].second)) ++nNum; --nNum;
    makeTree();

    scanf("%d", &n);  for (int i=1; i<=n; i++) scanf("%d", &v[i]);
    calcTree(nNum);
    flagTree(nNum);
    int vv = calcTree(nNum), q, I; scanf("%d", &q); while (q--) {
        scanf("%d", &I); printf("%d\n", !(vv ^ flag[I]));
    }
    return 0;
}
