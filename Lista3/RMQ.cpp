#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

struct segment_tree {
    int l, r, m;
    segment_tree *left, *right;

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
            this->m = min(this->left->m, this->right->m);
        }
    }

    void destroyRecursive() {
        if(this) {
            this->left->destroyRecursive();
            this->right->destroyRecursive();
            delete this;
        }
    }

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
};

typedef struct segment_tree* stPtr;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numSensores;
    cin >> numSensores;

    int sensores[numSensores];

    for(int i = 0; i < numSensores; i++) {
        cin >> sensores[i];
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
            st = new segment_tree(sensores, 0, numSensores-1);
        } else if(command == "RMQ") {
            int l, r;
            cin >> l;
            cin >> r;
            cout << st->RMQ(l, r) << endl;
        } else if(command == "END"){
            end = true;
        }
    }

    return 0;
}
