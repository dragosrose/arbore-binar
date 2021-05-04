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


void inserare(mon_struct *&rad , long long x){
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
    while(nod -> value != x){
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

        if(nod -> stanga && nod -> dreapta){
             xnod = nod -> stanga;
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
            if(nod -> stanga){
                nod -> value = (nod -> stanga) -> value;
                nod -> stanga = (nod -> stanga) -> stanga;
                nod -> dreapta = (nod -> stanga) -> dreapta;
            }

            else{
                if(nod -> dreapta){
                    nod -> value = (nod -> dreapta) -> value;
                    nod -> stanga = (nod -> dreapta) -> stanga;
                    nod -> dreapta = (nod -> dreapta) -> dreapta;
                }
                else{
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

long long min(mon_struct * nod){
    while(nod -> stanga != nullptr)
        nod = nod -> stanga;
    return nod -> value;
}

long long max(mon_struct * nod){
    while(nod -> dreapta != nullptr)
        nod = nod -> dreapta;
    return nod -> value;
}

long long predecesor(mon_struct *rad, long long x){
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
        g << "Input incorect";
        return -1; // nu stiu ce ar trb sa returnez

    }
    else{
        if(nod -> stanga== nullptr)
           if(nod -> parinte == nullptr || nod -> parinte -> stanga == nod) {
               g << "Nu exista valoare"<<' ';
               return -1; // same
           }
           else{
               return nod -> parinte -> value;
           }
        else{
            nod = nod -> stanga;
            while(nod -> dreapta)
                nod = nod -> dreapta;
            return nod -> value;
        }
    }

}

long long succesor(mon_struct *rad, long long x){
    mon_struct *nod = rad;
    // In functie de valoarea curenta a nodului raportata la x se parcurge arborele spre stanga sau dreapta
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
        g << "Input incorect";
        return -1; // nu stiu ce ar trb sa returnez
    }
    else{
        while(nod -> dreapta != nullptr && nod -> value == nod -> dreapta -> value)
            nod = nod -> dreapta;
        if(nod -> dreapta == nullptr)
           if(nod -> parinte == nullptr || nod == nod -> parinte -> dreapta) {
               g<<"Nu exista valoare";
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


int kLeaElement(mon_struct* rad, int k)
{
    // base case
    if (rad == NULL)
        return NULL;

    int ccount = rad->lCount + 1;
    if (ccount == k)
        return rad->value;

    if (ccount > k)
        return kLeaElement(rad->stanga, k);

    // else search in right subtree
    return kLeaElement(rad->dreapta, k - ccount);
}

int main() {
    
    ifstream f;
    string files[] = {"input.in", "in1.in", "in2.in", "in3.in", "in4.in", "in5.in", "in6.in"};
    int file_number = 6; // se deschide fisierul cu indicele respectiv
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
    g <<"Al "<<x<<"-lea element este: "<<kLeaElement(v, x) <<"\n";
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