#include "Cita.hh"

Cita::Cita() {
    fra_in = 0;
    fra_fi = 0;
}

void Cita::afegir_frases(vector<Frase>& frase, int x, int y){
    int size_f = frase.size();
    for (int i = 0; i < size_f; ++i){
        cita.push_back(frase[i]);
    }
    fra_in = x;
    fra_fi = y;
}

void Cita::afegir_tit_aut(vector<string>& titol, vector<string>& autor){
    int size_tit = titol.size();
    for (int i = 0; i < size_tit; ++i){
        Titol.push_back(titol[i]);
    }
    int size_aut = autor.size();
    for (int i = 0; i < size_aut; ++i){
        Autor.push_back(autor[i]);
    }
}

vector<string> Cita::consultar_Titol(){
    return Titol;
}

vector<string> Cita::consultar_Autor(){
    return Autor;
}

int Cita::consultar_fra_in(){
    return fra_in;
}

int Cita::consultar_fra_fi(){
    return fra_fi;
}

vector<Frase> Cita::consultar_cita(){
    return cita;
}
