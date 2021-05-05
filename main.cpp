#include <iostream>
#include <fstream>
using namespace std;

//ifstream f("input.in");
ofstream g("output.out");

struct mon_struct{

    int cardinal;
    int lCount;
    long long value;
    mon_struct *stanga, *dreapta, *parinte;
};


void inserare(mon_struct *&rad , long long x){ // inserarea nodului in arbore
    mon_struct *newnod = new mon_struct;
    newnod -> value = x;
    newnod -> stanga = nullptr;
    newnod -> dreapta = nullptr;
    newnod -> parinte = nullptr;
    if(rad){

        rad->cardinal++;
        mon_struct *nod = rad, *xnod;
        bool fl;
        while(nod){
            xnod =  nod;
            fl = x < nod -> value;
            if(fl)
            {rad->lCount++;
                nod = nod ->stanga;}
            else
                nod = nod -> dreapta;
        }
        if(fl){
            newnod -> parinte = xnod;
            xnod -> stanga = newnod;
        }
        else {
            newnod -> parinte = xnod;
            xnod -> dreapta = newnod;
        }
    }
    else {
        rad = newnod;
        rad -> cardinal=1;
        rad -> lCount=0;
    }
}

void stergere(mon_struct *&rad, int x){
    mon_struct *xnod;
    mon_struct *nod = rad;
    while(nod -> value != x){// caut nodul in arbore
        if(x < nod -> value) {
            if(nod -> stanga == nullptr)
                break;
            nod = nod -> stanga;
        }
        else{
            if(nod -> dreapta == nullptr)
                break;
            nod = nod -> dreapta;
        }
    }
    if(nod -> value == x){
        rad->cardinal--;

        if(nod -> stanga && nod -> dreapta){// daca nodul are copii pe ambele parti, atunci il inlocuiesc cu cea mai
            xnod = nod -> stanga;// din dreapta valoare din subarborele stang
            while(xnod -> dreapta){
                xnod = xnod -> dreapta;
            }
            nod -> value = xnod -> value;
            if(xnod -> stanga){
                xnod -> value = (xnod -> stanga) -> value;
                xnod -> stanga = (xnod -> stanga) -> stanga;
                xnod -> dreapta = (xnod -> stanga) -> dreapta;
            }
            else{
                if(xnod -> parinte -> stanga == xnod)
                    xnod -> parinte -> stanga = nullptr;
                else
                    xnod -> parinte -> dreapta = nullptr;
            }
        }
        else{
            if(nod -> stanga){// daca am doar copil in stanga, inlocuiesc nodul cu copilul din stanga
                nod -> value = (nod -> stanga) -> value;
                nod -> stanga = (nod -> stanga) -> stanga;
                nod -> dreapta = (nod -> stanga) -> dreapta;
            }

            else{
                if(nod -> dreapta){//la fel ca pt stanga
                    nod -> value = (nod -> dreapta) -> value;
                    nod -> stanga = (nod -> dreapta) -> stanga;
                    nod -> dreapta = (nod -> dreapta) -> dreapta;
                }
                else{// daca nu are copii, nodul e sters
                    if(nod -> parinte == nullptr)
                        rad = nullptr;
                    else{
                        if(nod -> parinte -> stanga == nod)
                            nod -> parinte -> stanga = nullptr;
                        else
                            nod -> parinte -> dreapta = nullptr;
                    }
                }
            }
        }

    }
    else
        g << "Input incorect ";
}

long long min(mon_struct * nod){ // calculez minimul cautnd cea mai din stanga valoare a arboreului
    while(nod -> stanga != nullptr)
        nod = nod -> stanga;
    return nod -> value;
}

long long max(mon_struct * nod){ // calculez maximul cautand cea mai din dreapta valoare a arborelui
    while(nod -> dreapta != nullptr)
        nod = nod -> dreapta;
    return nod -> value;
}

long long predecesor(mon_struct *rad, long long x){
    mon_struct *nod = rad;
    while(nod -> value != x){ // caut nodul
        if(x < nod -> value) {
            if (nod->stanga == nullptr)
                break;
            nod = nod->stanga;
        }
        else{
            if(nod -> dreapta == nullptr)
                break;
            nod = nod -> dreapta;
        }
    }
    if(nod -> value != x) {
        cout << "Input incorect";
        return -1; // nu stiu ce ar trb sa returnez

    }
    else{
        if(nod -> stanga== nullptr) // daca nodul nu are copil in stanga atunci caut predecesor in nivelele superioare
            if(nod -> parinte == nullptr || nod -> parinte -> stanga == nod) {//verific daca predecesor este parintele
                if(nod -> parinte && nod -> parinte -> parinte && nod -> parinte -> parinte -> dreapta == nod -> parinte)
                    return nod -> parinte -> parinte -> value; // verific daca predecesorul este bunicul
                cout << "Nu exista valoare"<<' ';
                return -1; // same
            }
            else{
                return nod -> parinte -> value;
            }
        else{//daca nodul are copil in stanga, atunci caut cea mai din dreapta valoare din subarborele stang
            nod = nod -> stanga;
            while(nod -> dreapta)
                nod = nod -> dreapta;
            return nod -> value;
        }
    }

}

long long succesor(mon_struct *rad, long long x){ // la fel ca predecesor
    mon_struct *nod = rad;
    while(nod -> value != x){
        if(x < nod -> value) {
            if (nod->stanga == nullptr)
                break;
            nod = nod->stanga;
        }
        else{
            if(nod -> dreapta == nullptr)
                break;
            nod = nod -> dreapta;
        }
    }
    if(nod -> value != x) {
        cout << "Input incorect";
        return -1; // nu stiu ce ar trb sa returnez
    }
    else{
        while(nod -> dreapta != nullptr && nod -> value == nod -> dreapta -> value)
            nod = nod -> dreapta;
        if(nod -> dreapta == nullptr)
            if(nod -> parinte == nullptr || nod == nod -> parinte -> dreapta) {
                if(nod -> parinte && nod -> parinte -> parinte && nod -> parinte -> parinte -> stanga == nod -> parinte)
                    return nod -> parinte -> parinte -> value;
                cout<<"Nu exista valoare";
                return -1; // same
            }
            else{
                return nod -> parinte -> value;
            }
        else{
            nod = nod -> dreapta;
            while(nod -> stanga)
                nod = nod -> stanga;
            return nod -> value;
        }
    }

}

int este_in(mon_struct * rad, long long x){
    mon_struct *nod = rad;
    while(nod -> value != x){
        if(x < nod -> value) {
            if(nod -> stanga == nullptr)
                break;
            nod = nod->stanga;
        }
        else{
            if(nod -> dreapta == nullptr)
                break;
            nod = nod -> dreapta;
        }
    }
    if(nod -> value == x)
        return 1;
    return 0;
}

void parcurgere(mon_struct *nod){
    // Parcurge arborele de la stanga la dreapta, mereu outputul va fi in ordine crescatoare
    if(nod){
        parcurgere(nod -> stanga);
        g << nod -> value << ' ';
        parcurgere(nod -> dreapta);
    }
}


int Cardinal(mon_struct *nod){
    return nod->cardinal;
}


mon_struct* kleaElement(mon_struct* rad, int k)
{
  
    if (rad == nullptr)
        return nullptr;
 
    int count = rad->lCount + 1;
    if (count == k)
        return rad;
 
    if (count > k)
        return kleaElement(rad->stanga, k);
 

    return kleaElement(rad->dreapta, k - count);
}

int main() {

    ifstream f;
    string files[] = {"input.in", "in1.in", "in2.in", "in3.in", "in4.in", "in5.in", "in6.in", "in7.in"};
    int file_number = 7; // se deschide fisierul cu indicele respectiv
    f.open(files[file_number]);

    int x, N; //numarul de noduri
    f>>N;
    mon_struct *v = nullptr;
    //Input arbore
    while(N){
        f>>x;
        inserare(v,x);
        N--;

    }

    //Output arbore
    parcurgere(v);

    //Cardinal
    g <<"Cardinalul initial este: "<<Cardinal(v)<<"\n";

    //Stergere si parcurgere dupa stergerea elementului
    f >> x;
    stergere(v, x);
    parcurgere(v); g<<"\n";

    // Noul Cardinal
    g <<"Noul cardinal este: "<<Cardinal(v)<<"\n";

    // Al k-lea element
    f >> x;
    g <<"Al "<<x<<"-lea element este: "<<kleaElement(v, x) <<"\n";
    //parcurgere(v); g<<"\n";
    g <<'\n';

    // Un element se afla sau nu in arbore
    int y;
    f>>x>>y;
    g << este_in(v, x)<<' '<< este_in(v, y)<<'\n';

    // Predecesor
    int z;
    f>>x>>y>>z;
    g << predecesor(v, x)<< ' '<<predecesor(v, y)<<' '<<predecesor(v,z)<<'\n';

    // Succesor
    f>>x>>y>>z;
    g << succesor(v, x)<< ' '<< succesor(v, y)<<' '<< succesor(v, z)<<'\n';

    f.close();
    // Max - min
    g << max(v)<< ' '<< min(v)<<'\n';

    //parcurgere(v);

    g.close();

    return 0;
}