#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct disjoint_set {
    int *nodes;
    int *heights;

    disjoint_set(int size) {
        int cels = pow(size, 2);
        this->nodes = new int[cels];
        this->heights = new int[cels];

        for(int i = 0; i < cels; i++) {
            this->nodes[i] = i;
            this->heights[i] = 0;
        }
    }

    int find(int a) {
        if(nodes[a] == a) {
            return a;
        } else {
            nodes[a] = find(nodes[a]);
            return nodes[a];
        }
    }

    int union_set(int a, int b) {
        int r1 = find(a);
        int r2 = find(b);

        if(this->heights[r1] == this->heights[r2]) {
            nodes[r2] = r1;
            this->heights[r1]++;
            return r1;
        } else if(this->heights[r1] > this->heights[r2]) {
            this->nodes[r2] = r1;
            return r1;
        } else {
            this->nodes[r1] = r2;
            return r2;
        }
    }
};
typedef struct disjoint_set* dsPtr;

struct par {
    int a, b;

    par(int a, int b) {
        this->a = a;
        this->b = b;
    }
};

par* getNodes(int e, int n) {
    if(n > 2) {
        int r = e % (2*n - 1);
        int line = (e/(2*n-1))*n;

        if(r < n-1) {
            int a = line + r;
            int b = a + 1;

            par *resp = new par(a, b);
            return resp;
        } else {
            int a = line + r - (n-1);
            int b = a + n;

            par *resp = new par(a, b);
            return resp;
        }
    } else if(n == 2) {
        if(e == 0) {
            par *resp = new par(0, 1);
            return resp;
        } else if(e == 1) {
            par *resp = new par(0, 2);
            return resp;
        } else if(e == 2) {
            par *resp = new par(1, 3);
            return resp;
        } else {
            par *resp = new par(2, 3);
            return resp;
        }
    } else {
        par *resp = new par(1, 1);
        return resp;
    }
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int k;
    cin >> k;

    for(int i = 0; i < k; i++) {
        int n, m, q;
        cin >> n;
        cin >> m;
        cin >> q;

        disjoint_set *D = new disjoint_set(n);

        for(int j = 0; j < m; j++) {
            int w;
            cin >> w;
            par *p = getNodes(w, n);
            D->union_set(p->a, p->b);
        }

        for(int j = 0; j < q; j++) {
            int a, b;
            cin >> a;
            cin >> b;

            cout << i << "." << j << " ";
            if(D->find(a) == D->find(b)) {
                cout << 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }

        cout << endl;
    }

    cout << endl;

    return 0;
}
