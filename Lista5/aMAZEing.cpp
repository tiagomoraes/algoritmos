#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct node {
    node *parent;
    int id, height;

    node(int id) {
        this->id = id;
        this->height = 0;
        this->parent = this;
    }
};

node* find(node *a) {
    if(a->parent->id == a->id) {
        return a;
    } else {
        a->parent = find(a->parent);
        return a->parent;
    }
}

node* union_set(node *a, node* b) {
    node *r1 = find(a);
    node *r2 = find(b);

    if(r1->height == r2->height) {
        r2->parent = r1;
        r1->height++;
        return r1;
    } else if(r1->height > r2->height) {
        r2->parent = r1;
        return r1;
    } else {
        r1->parent = r2;
        return r2;
    }
}

/* Pega a parede (a) e faz a mod 2n-1. Se for menor que n-1, é coluna; senão é linha
    se for menor que n-1, {
        union de (a mod 2n-1) e (a mod 2n-1) + 1
    }
    senão {
        union de (a mod 2n-1) - (n-1)
    }
*/
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    node *a = new node(1);
    node *b = new node(2);
    node *c = new node(3);
    node *cls = new node(4);

    //cout << find(a)->id;

    cls = union_set(b, a);

    cout << find(cls)->id;




    return 0;
}
