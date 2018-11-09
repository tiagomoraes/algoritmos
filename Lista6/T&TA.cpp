#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct aresta {
    int v;
    double w;

    aresta(int v, double w) {
        this->v = v;
        this->w = w;
    }
};

struct destino {
    int v;
    double w;

    destino(int v, double w) {
        this->v = v;
        this->w = w;
    }
};

struct min_heap {
    destino **H;
    int size, heapSize;
    int *positions;

    min_heap(int size) {
        this->H = new destino*[size];
        this->positions = new int[size];
        this->size = size;
        this->heapSize = 0;

        for(int i = 0; i < size; i++) {
            this->H[i] = nullptr;
            this->positions[i] = -1;
        }
    }

    void double_size() {
        destino** arr_aux;
        arr_aux = this->H;
        this->H = new destino*[2*this->size];

        for(int  i = 0; i < this->size; i++) {
            this->H[i] = arr_aux[i];
        }

        delete arr_aux;

        this->size = 2*this->size;
    }

    void bubble_up(int i) {
        while(i > 0 && this->H[i]->w <= this->H[(i-1)/2]->w) {
            int iFather = floor((i-1)/2);
            destino *aux;
            aux = this->H[i];
            this->H[i] = this->H[iFather];
            this->H[iFather] = aux;
            this->positions[this->H[iFather]->v] = iFather;
            this->positions[this->H[i]->v] = i;
            i = iFather;
        }
    }

    void heap_insert(destino *d) {
        if(this->heapSize == this->size) {
            this->double_size();
        }
        this->H[this->heapSize] = d;
        this->positions[d->v] = this->heapSize;
        this->heapSize++;
        this->bubble_up(this->heapSize - 1);
    }

    void heapify(int i) {
        int m = i;
        int l = 2*i + 1;
        int r = 2*i + 2;

        if((l < this->heapSize) && (this->H[l]->w >= this->H[m]->w)) {
            m = l;
        }

        if((r < this->heapSize) && (this->H[r]->w >= this->H[m]->w)) {
            m = r;
        }

        if(m != i) {
            destino *aux = this->H[i];
            this->H[i] = this->H[m];
            this->H[m] = aux;

            this->positions[this->H[i]->v] = m;
            this->positions[this->H[m]->v] = i;

            this->heapify(m);
        }
    }

    void heap_update(destino *d) {
        //finds element and thad does bubble_up on it
        if(this->positions[d->v] != -1) {
            this->H[this->positions[d->v]] = d;
            this->bubble_up(this->positions[d->v]);
        } else {
            this->heap_insert(d);
        }
    }

    destino* heap_extract() {
        destino *r = this->H[0];

        this->H[0] = this->H[this->heapSize - 1];
        this->H[this->heapSize - 1] = nullptr;

        this->heapSize--;
        this->heapify(0);

        return r;
    }

};

struct node {
    aresta *val;
    node *prev;
    node *next;

    node(aresta *val) {
        this->val = val;
        this->next = nullptr;
    }
};

typedef struct node* nodePtr;

struct linked_list {
    int size;

    nodePtr head;
    nodePtr tail;

    // constructor for the Lista
    linked_list() {
        head = nullptr;
        tail = nullptr;
        size = 0;
    }

    // inserts new node on the tail
    void insert_tail(aresta *val) {
        nodePtr n;
        n = new node(val);

        // check if list is empty
        if(this->tail == nullptr) {
            this->head = n;
        } else {
            this->tail->next = n;
        }
        this->tail = n;

        this->size++;
    }
};

struct grafo {
    //declare array of veectors here
    linked_list **G;
    int size;

    grafo(int size) {
        //array of list for edges
        this->G = new linked_list*[size];
        this->size = size;

        for(int i = 0; i < this->size; i++) {
            G[i] = new linked_list();
        }
    }

    void insert(int a, int b, double w) {
        aresta *e1 = new aresta(b, w);
        this->G[a]->insert_tail(e1);

        aresta *e2 = new aresta(a, w);
        this->G[b]->insert_tail(e2);

    }

    string caminho(int s, int final) { //Dijkstra
        double D[this->size];
        int F[this->size];

        for(int i = 0; i < this->size; i++) {
            D[i] = DBL_MAX;
            F[i] = -1;
        }

        D[s] = 0;

        min_heap *H = new min_heap(this->size);
        destino *temp = new destino(s, D[s]);
        H->heap_insert(temp);

        while(H->heapSize > 0) {
            destino *dest = H->heap_extract();
            int u = dest->v;
            double d = dest->w;

            if(d > D[u]) {
                continue;
            }

            nodePtr e = this->G[u]->head;

            while (e != nullptr) {
                if(d + e->val->w < D[e->val->v]) {
                    D[e->val->v] = d + e->val->w;
                    F[e->val->v] = u;
                    destino *aux = new destino(e->val->v, D[e->val->v]);
                    H->heap_update(aux);
                }
                e = e->next;
            }
        }

        // string do caminho de s------>final
        int predTemp = final;
        string resp = "" + to_string(predTemp);

        if(predTemp != s) {
            resp = " " + resp;
        }

        while (predTemp != s) {
            predTemp = F[predTemp];

            if(predTemp == s) {
                resp = to_string(predTemp) + resp;
            } else {
                resp = " " + to_string(predTemp) + resp;
            }
        }
        return resp;
    }
};

double calcWeight(double p, int b, int c) {
    double w;
    w = (((p*b + (1-p)*c))/(b+c));
    return w;
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    double p;
    cin >> p;

    int n, m;
    cin >> n;
    cin >> m;

    grafo *G = new grafo(n);

    for(int i = 0; i < m; i++) {
        int x, y, b, c;
        cin >> x >> y >> b >> c;

        double w = calcWeight(p, b, c);
        G->insert(x, y, w);
    }

    int s, t;
    while (cin >> s >> t) {
        cout << G->caminho(s, t) << endl;
    }

    return 0;
}
