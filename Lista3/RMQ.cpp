#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct segment_tree {
    int l, r, m, numLeaves;
    segment_tree *left, *right, *father;

    segment_tree(int arr[], int l, int r) {
        this->l = l;
        this->r = r;

        if(r <= l) { // caso base
            this->left = nullptr;
            this->right = nullptr;
            this->m = arr[r];
        } else { // caso resursivo
            int h = floor((l+r)/2);

            this->left = new segment_tree(arr, l, h);
            this->right = new segment_tree(arr, h+1, r);
            this->left->father = this;
            this->right->father = this;
            this->m = min(this->left->m, this->right->m);
        }
    }

    /*
    void destroyRecursive() {
        if(this) {
            this->left->destroyRecursive();
            this->right->destroyRecursive();
            delete this;
        } else {
            delete this;
        }
    }
    */

    int RMQ(int a, int b) {
        if(a > b || a > this->r || b < this->l) {
            return INT_MAX;
        } else if(a == this->l && b == this->r) {
            return this->m;
        } else {
            int h = floor((this->l+this->r)/2);
            return min(this->left->RMQ(max(a,this->l), min(b,h)), this->right->RMQ(max(a,h+1), min(b,this->r)));
        }
    }

    void print(int a, int b) {
        // percorrer a árvore toda em pós ordem e printar apenas os valores que tiverem algu valor do meu intervalo
        if(this == nullptr) {
            return;
        }

        if(this->left != nullptr) {
            this->left->print(a, b);
        }

        if(this->right != nullptr) {
            this->right->print(a, b);
        }

        if(a <= this->r && b >= this->l) {
            if(this->father == nullptr) {
                cout << this->m;
            } else {
                cout << this->m << " ";
            }
        }
    }

    void updateParents() {
        segment_tree* cur;
        cur = this;
        int min = this->m;
        while(cur->father != nullptr) {
            if(cur->father->left != nullptr) {
                cur->father->m = min(min, )
            }
        }
    }
};

typedef struct segment_tree* stPtr;

vector<stPtr> leaves;

void fillLeaves(stPtr st) {
    if(st->left == nullptr && st->right == nullptr) {
        ::leaves.push_back(st);
    }

    if(st->left != nullptr) {
        fillLeaves(st->left);
    }

    if(st->right != nullptr) {
        fillLeaves(st->right);
    }
}

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numSensores;
    cin >> numSensores;

    int sensores[numSensores];

    for(int i = 0; i < numSensores; i++) {
        int aux;
        cin >> aux;
        sensores[i] = aux;
    }

    stPtr st = new segment_tree(sensores, 0, numSensores-1);


    bool end = false;
    string command;

    while(!end) {
        cin >> command;
        if(command == "UPD") {
            int i, x;
            cin >> i;
            cin >> x;
            sensores[i] = x;
            stPtr aux = st;
            st = new segment_tree(sensores, 0, numSensores-1);
        } else if(command == "RMQ") {
            int l, r;
            cin >> l;
            cin >> r;
            cout << st->RMQ(l, r) << endl;
        } else if(command == "PRT"){
            int a, b;
            cin >> a;
            cin >> b;
            st->print(a, b);
            cout << endl;
        } else {
            end = true;
        }
    }

    fillLeaves(st);

    for(int i = 0; i < numSensores; i++) {
        cout << ::leaves[i]->father->l << "|" << ::leaves[i]->father->r << endl;
    }


    return 0;
}
