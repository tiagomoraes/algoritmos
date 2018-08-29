#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

//PROCESSO STRUCT
struct processo {
    int magistradoPref, tempo, empresa, pos;

    // constructor for struct processo
    processo(int magistradoPref, int tempo, int empresa, int pos) {
        this->magistradoPref = magistradoPref;
        this->tempo = tempo;
        this->empresa = empresa;
        this->pos = pos;
    }
};

//NODE STRUCT
struct node {
    processo *val;
    node *prev;
    node *next;

    node(processo *val) {
        this->val = val;
        this->prev = nullptr;
        this->next = nullptr;
    }
};

// defines a node* as nodePtr for easy use
typedef struct node* nodePtr;

// PILHA STRUCT
struct Pilha {
    int size;

    nodePtr head;
    nodePtr tail;
    nodePtr cur;

    // constructor for the class
    Pilha() {
        head = nullptr;
        tail = nullptr;
        cur = nullptr;
        size = 0;
    }

    // inserts new node on the head
    void insert_head(processo *val) {
        nodePtr n;
        n = new node(val);

        // check if list is empty
        if(this->head == nullptr) {
            this->tail = n;
        } else {
            this->head->prev = n;
            n->next = this->head;
        }
        this->head = n;

        this->size++;
    }

    processo* remove_head() {
        if(this->head != nullptr) {
            processo *p = this->head->val;
            if(this->head->next != nullptr) {
                this->head->next->prev = nullptr;
            }
            this->head = this->head->next;
            this->size--;
            return p;
        } else {
            return nullptr;
        }
    }

    void print() {
        nodePtr cur;
        cur = this->head;
        nodePtr aux;
        while(cur != nullptr) {
            cout << "Processo" << endl;
            cout << "M:" << cur->val->magistradoPref << endl;
            cout << "T:" << cur->val->tempo << endl;
            cur = cur->next;
        }
    }

    int length() {
        return this->size;
    }
};

// FILA STRUCT
struct Fila {
    int size;

    nodePtr head;
    nodePtr tail;
    nodePtr cur;

    // constructor for the class
    Fila() {
        head = nullptr;
        tail = nullptr;
        cur = nullptr;
        size = 0;
    }

    // inserts new node on the tail
    void insert_tail(processo *val) {
        nodePtr n;
        n = new node(val);

        // check if list is empty
        if(this->tail == nullptr) {
            this->head = n;
        } else {
            this->tail->next = n;
            n->prev = this->tail;
        }
        this->tail = n;

        this->size++;
    }

    processo* remove_head() {
        if(this->head != nullptr) {
            processo *p = this->head->val;
            if(this->head->next != nullptr) {
                this->head->next->prev = nullptr;
            }
            this->head = this->head->next;
            this->size--;
            return p;
        } else {
            return nullptr;
        }
    }

    void print() {
        nodePtr cur;
        cur = this->head;
       nodePtr aux;
        while(cur != nullptr) {
            cout << "M:" << cur->val->magistradoPref << endl;
            cout << "T:" << cur->val->tempo << endl;
            cur = cur->next;
        }
    }

    int length() {
        return this->size;
    }
};

//MAGISTRADO STRUCT
struct magistrado {
    Pilha *pilha;
    int horasDia, horasRestantes;

    magistrado(int horasDia) {
        this->horasDia = horasDia;
        this->horasRestantes = horasDia;
        this->pilha = new Pilha();
    }
};

void concat(Pilha *baixo, Pilha *cima) {
    if(cima->length() > 0 && baixo->length() > 0) {
        baixo->head->prev = cima->tail;
        cima->tail->next = baixo->head;
        baixo->head = cima->head;
    } else if(cima->length() > 0) {
        baixo->head = cima->head;
        baixo->tail = cima->tail;
    }
}

// MAIN
int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int numEmpresas;
    cin >> numEmpresas;

    Fila *arrFilas[numEmpresas];

    int numProcessos;

    for(int i = 0; i < numEmpresas; i++) {
        arrFilas[i] = new Fila();

        cin >> numProcessos;

        for(int j = 0; j < numProcessos; j++) {
            int magistradoPref, tempoNec;
            cin >> magistradoPref;
            cin >> tempoNec;

            processo *p = new processo(magistradoPref, tempoNec, i, j);

            arrFilas[i]->insert_tail(p);
        }
    }

    int m;
    cin >> m;

    // array of int containing the magistrados(i) and hours
    magistrado *arrMagistrados[m];
    for(int i = 0; i < m; i++) {
        int horasDia;
        cin >> horasDia;
        arrMagistrados[i] = new magistrado(horasDia);
    }

    int totalProcessos = 0;
    for(int i = 0; i < numEmpresas; i++) {
        totalProcessos += arrFilas[i]->length();
    }


    int cont1 = 0;
    int cont2 = 0;
    // loop for distributing the processos between the magistrados
    for(int i = 0; i < totalProcessos; i++) {
        while(arrFilas[cont1]->length() <= 0) {
            if(cont1 == numEmpresas-1) {
                cont1 = 0;
            } else {
                cont1++;
            }
        }
        processo *p = arrFilas[cont1]->remove_head();
        arrMagistrados[cont2]->pilha->insert_head(p);

        if(cont1 == numEmpresas-1) {
            cont1 = 0;
        } else {
            cont1++;
        }

        if(cont2 == m-1) {
            cont2 = 0;
        } else {
            cont2++;
        }
    }

    // assistentes get their bosses processos
    for(int i = 0; i < m; i++) {
        for(int j = 0; j < m; j++) {
            if(i != j) {
                Pilha *assPilhaCerta = new Pilha();
                Pilha *assPilhaOutro = new Pilha();
                while(arrMagistrados[i]->pilha->head != nullptr) {
                    processo *p = arrMagistrados[i]->pilha->remove_head();
                    if(p->magistradoPref == j) {
                        assPilhaCerta->insert_head(p);
                    } else {
                        assPilhaOutro->insert_head(p);
                    }
                }
                arrMagistrados[i]->pilha = assPilhaOutro;
                concat(arrMagistrados[j]->pilha, assPilhaCerta);
            }
        }
    }

    // change the -1s
    for(int i = 0; i < m; i++) {
        nodePtr cur = arrMagistrados[i]->pilha->head;
        while (cur != nullptr) {
            cur->val->magistradoPref = i;
            cur = cur->next;
        }
    }
    int i = totalProcessos;

    while(i > 0) {
        for(int j = 0; j < 24; j++) {
            for(int k = 0; k < m; k++) {
                if(arrMagistrados[k]->pilha->head != nullptr) {
                    if(arrMagistrados[k]->horasRestantes > 0) {
                        arrMagistrados[k]->horasRestantes--;
                        arrMagistrados[k]->pilha->head->val->tempo--;

                        if(arrMagistrados[k]->pilha->head->val->tempo <= 0) {
                            cout << arrMagistrados[k]->pilha->head->val->magistradoPref << " ";
                            cout << arrMagistrados[k]->pilha->head->val->empresa << " ";
                            cout << arrMagistrados[k]->pilha->head->val->pos << endl;
                            arrMagistrados[k]->pilha->remove_head();
                            i--;
                        }
                    }
                }
            }
        }
        for(int j = 0; j < m; j++) {
            arrMagistrados[j]->horasRestantes = arrMagistrados[j]->horasDia;
        }
    }
    return 0;
}
