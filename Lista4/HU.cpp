#include <bits/stdc++.h>
#define endl '\n'

using namespace std;

//Implementing a max_heap

struct paciente {
    int urgencia, idade, chegada;
    paciente(int urgencia, int idade, int chegada) {
        this->urgencia = urgencia;
        this->idade = idade;
        this->chegada = chegada;
    }
};

typedef struct paciente* pacientePtr;

struct heap {

    paciente **H;
    int size, heapSize;

    heap(int size) {
        this->H = new paciente*[size];
        this->size = size;
        this->heapSize = 0;

        for(int i = 0; i < size; i++) {
            H[i] = nullptr;
        }
    }

    void double_size() {
        paciente** arr_aux;
        arr_aux = this->H;
        this->H = new paciente*[2*this->size];

        for(int  i = 0; i < this->size; i++) {
            this->H[i] = arr_aux[i];
        }

        delete arr_aux;

        this->size = 2*this->size;
    }

    void bubble_up(int i) {
        while(i > 0 && this->H[i]->urgencia >= this->H[(i-1)/2]->urgencia) {
            if((this->H[i]->urgencia == this->H[(i-1)/2]->urgencia) && (this->H[i]->idade < this->H[(i-1)/2]->idade)) {
                break;
            } else if((this->H[i]->urgencia == this->H[(i-1)/2]->urgencia) && (this->H[i]->idade == this->H[(i-1)/2]->idade) && (this->H[i]->chegada > this->H[(i-1)/2]->chegada)) {
                break;
            }

            int iFather = floor((i-1)/2);
            pacientePtr aux;
            aux = this->H[i];
            this->H[i] = H[iFather];
            this->H[iFather] = aux;
            i = iFather;
        }
    }

    void heap_insert(pacientePtr p) {
        if(this->heapSize == this->size) {
            this->double_size();
        }
        H[this->heapSize] = p;
        this->heapSize++;
        this->bubble_up(this->heapSize - 1);
    }

    void heapify(int i) {
        int m = i;
        int l = 2*i + 1;
        int r = 2*i + 2;

        if((l < this->heapSize) && (this->H[l]->urgencia >= this->H[m]->urgencia)) {
            if(this->H[l]->urgencia == this->H[m]->urgencia) {
                if(this->H[l]->idade > this->H[m]->idade) {
                    m = l;
                } else if(this->H[l]->idade == this->H[m]->idade) {
                    if(this->H[l]->chegada < this->H[m]->chegada) {
                        m = l;
                    }
                }
            } else {
                m = l;
            }
        }

        if((r < this->heapSize) && (this->H[r]->urgencia >= this->H[m]->urgencia)) {
            if(this->H[r]->urgencia == this->H[m]->urgencia) {
                if(this->H[r]->idade > this->H[m]->idade) {
                    m = r;
                } else if(this->H[r]->idade == this->H[m]->idade) {
                    if(this->H[r]->chegada < this->H[m]->chegada) {
                        m = r;
                    }
                }
            } else {
                m = r;
            }
        }

        if(m != i) {
            pacientePtr aux = this->H[i];
            this->H[i] = this->H[m];
            this->H[m] = aux;
            this->heapify(m);
        }
    }

    pacientePtr heap_extract() {
        pacientePtr r = this->H[0];

        this->H[0] = this->H[this->heapSize - 1];
        this->H[this->heapSize - 1] = nullptr;

        this->heapSize--;
        this->heapify(0);

        return r;
    }

};

typedef struct heap* heapPtr;

int main(int argc, char *argv[]) {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int s;
    cin >> s;

    heap *servicos[s];

    for(int i = 0; i < s; i++) {
        servicos[i] = new heap(3);
    }

    string command;
    bool end = false;

    int chegada = 0;

    while(!end) {

        cin >> command;
        if(command == "CIN") { //inserir um paciente paciente
            int i, u, a;
            cin >> i;
            cin >> u;
            cin >> a;

            pacientePtr p = new paciente(u, i, chegada);
            chegada++;

            servicos[a]->heap_insert(p);

        } else if(command == "NXT") { //atendimento convencional no serviço a
            int a;
            cin >> a;

            if(servicos[a]->H[0]) {
                pacientePtr p = servicos[a]->heap_extract();
                cout << a << " " << p->idade << " " << p->urgencia << endl;
            } else {
                cout << "-1 -1 -1" << endl;
            }

        } else if(command == "STD"){ //atendimento do estudante

            int i, pos;
            i = 0;
            pos = 0;

            pacientePtr min = new paciente(INT_MAX, INT_MAX, INT_MAX);
            while(i < s) {
                if(servicos[i]->H[0]) {
                    if(servicos[i]->H[0]->urgencia < min->urgencia) {
                        min = servicos[i]->H[0];
                        pos = i;
                    }else if((servicos[i]->H[0]->urgencia == min->urgencia) && (servicos[i]->H[0]->idade < min->idade)) {
                        min = servicos[i]->H[0];
                        pos = i;
                    }else if((servicos[i]->H[0]->urgencia == min->urgencia) && (servicos[i]->H[0]->idade == min->idade) && (servicos[i]->H[0]->chegada < min->chegada)) {
                        min = servicos[i]->H[0];
                        pos = i;
                    }
                }

                i++;
            }

            if(servicos[pos]->H[0]) {
                pacientePtr p = servicos[pos]->heap_extract();
                cout << pos << " " << p->idade << " " << p->urgencia << endl;
            } else {
                cout << "-1 -1 -1" << endl;
            }

            i = 0;

        } else {
            end = true;
        }
    }

    return 0;
}
