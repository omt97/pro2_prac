#include "Textos_v2.0.hh"

string Textos::calcular_ref(vector<string>& autor){
    string ref;
    for (int i = 0; i < autor.size(); ++i){
        ref += autor[i][0];
    }
    map<string, Cita>::const_iterator it;
    for (it = Cites.begin(); it != Cites.end(); ++it){
        string ref2 = it->first;
        int i = 0;
        string rref;
        while (ref2[i] >= 'Z' and ref2[i] <= 'A'){
            rref.push_back(ref2[i]);
            ++i;
        }                                                            //no acabada
        int mida = ref2.size() - rref.size();                        //no acabada
        if (ref == rref){                                           //no acabada
            int mida2 = ref2.size();                                //no acabada
            string num;
            for (int j = mida; j < mida2; ++j){
                num.push_back(ref2[j]);
            }
            ref.push_back(num);
        }
        else ref.push_back('1');
    }
}

Textos::Textos(){
    nAutor = 0;
    nText = 0;
}

bool Textos::esta_autor(vector<string>& autor){
    map<vector<string>, list<Text> >::const_iterator it = textos.begin();
    bool esta = false;
    while (not esta and it != textos.begin()){
        if (autor = it->first) esta = true;
    }
    return esta;
}

void Textos::triar_text_par(vector<string>& paraules){
    map<vector<string>, list<Text> >::const_iterator it = textos.begin();
    bool trobat = false;
    while (not trobat and it != textos.end()){
        list<Text> tex;
        list<Text>::const_iterator t_it;
        while (not trobat and t_it != tex.end()){
            trobat = t_it*.te_paraules(paraules);
        }
        if (trobat) utlim = *t_it;
    }
}

vector<Text> Textos::textos_autor(vector<string>& autor){
    vector<Text> tex;
    map<>
}
