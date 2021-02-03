/// @tags: luogu; template; heap; STL
/// @info: 使用 STL。原版可看历史提交记录
#include <bits/stdc++.h>
using namespace std;

// std :: push_heap / pop_heap
// an alternative for priority_queue

int H[(int)1e6 + 155], sz = 0;

int main() {
    int n; scanf("%d", &n);
    while (n--) {
        int op, x; scanf("%d", &op);
        if (op == 1) {
            scanf("%d", &H[++sz]);
            push_heap(H + 1, H + 1+sz, greater<int>());
        } else {
            if (op == 2) printf("%d\n", H[1]);
            else pop_heap(H+1, H+1+sz--, greater<int>());
        }
    }
    return 0;
}
