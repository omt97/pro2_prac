#include "Textos_v2.0.hh"
#include <stack>

string Textos::calcular_ref(vector<string>& autor){
    string ref;
    for (int i = 0; i < autor.size(); ++i){
        ref += autor[i][0];
    }
    map<string, Cita>::const_iterator it;
    int num = 0;
    for (it = Cites.begin(); it != Cites.end(); ++it){
        string ref2 = it->first;
        int i = 0;
        string rref;
        while (ref2[i] >= 'Z' and ref2[i] <= 'A'){
            rref.push_back(ref2[i]);
            ++i;
        }
        int mida = ref2.size() - rref.size();
        if (ref == rref){
            ++num;
        }
    }
    string num2;
    int i = 0;
    stack<char> p;
    while (num >= 1){
        num = num/(i*10);
        int n = num%10;
        p.push(n);
        ++i;
    }
    while (not p.empty()){
        ref.push_back(p.top());
        p.pop();
    }
    return ref;
}

void Textos::calc_vec_freq(Text& text){
    map<string, int> freq = text.obtenir_freq();
    map<string, int>::iterator it;
    while (not freq.empty()){
        int i = 0;
        map<string, int>::iterator it2;
        for (it = freq.begin(); it != freq.end(); ++it){
            if (it->second > i){
                i = it->second;
                it2 = it;
            }
            else if (it->second == i){
                if (it->first < it2->first){
                    it2 = it;
                }
            }
        }
        ultim.freq_v.push_back(make_pair(it2->second, it2->first));
        freq.erase(it2);
    }
}

bool Textos::son_iguals(vector<string>& t1, vector<string>& t2){
    if (t1.size() != t2.size()) return false;
    else{
        int size = t1.size();
        for (int i = 0; i < size; ++i){
            if (t1[i] != t2[i]) return false;
        }
        return true;
    }
}

int Textos::ordre(vector<string>& t1, vector<string>& t2){
    int size1 = t1.size();
    int size2 = t2.size();
    int i = 0;
    while (i < size1 and i < size2){
        if (t1[i] > t2[i]) return 2;
        else if (t1[i] < t2[i]) return 1;
        else{
            ++i;
        }
    }
    if (i == size1) return 1;
    else if (i == size1) return 2;
}

Textos::Textos(){
    nAutor = 0;
    nText = 0;
}

bool Textos::esta_autor(vector<string>& autor){
    map<vector<string>, list<Text> >::const_iterator it = textos.begin();
    bool esta = false;
    while (not esta and it != textos.begin()){
        if (son_iguals (autor, it->first)) esta = true;
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
        if (trobat){
            utlim.ult = make_pair(it->first, *t_it);
            calc_vec_freq(*t_it);
            ultim.esta = true;
        }
    }
}

list<Text> Textos::textos_autor(vector<string>& autor){
    map<vector<string>, list<Text> >::const_iterator it = textos.begin();
    bool trobat = false;
    while (not trobat and it != textos.end()){
        if (son_iguals (it->first, autor)){
            trobat = true;
        }
        else ++it;
    }
    return it->second;
}

vector<string> Textos::consulta_autor(){
    if (not ultim.esta) cout << "error" << endl;
    else{
        pair<vector<string>, Text> par;
        par = ultim.ult;
        return par.first;
    }
}

int Textos::consulta_nFrases(){
    return nFrases;
}

int Textos::consulta_nParaules(){
    return nParaules;
}

vector<Frase> Textos::obtenir_frases(int x, int y){
    if (not ultim.esta) cout << "error" << endl;
    else{
        vector<Frase> fra (y - x);
        pair <vector<string>, Text> par;
        par = utlim.ult;
        Text tex;
        tex = par.second;
        fra = tex.obtenir_frases(x, y);                       //las carpetas son de aqui
        return fra;
    }
}

vector<pair<int, string> > Textos::obtenir_freq(){
    if (not utlim.esta) cout << "error" << endl;
    else{
        return utlim.freq_v;
    }
}

vector<Frase> obtenir_frases_par(vector<string>& paraules){
    if (not utlim.esta) cout << "error" << endl;
    else{
        pair<vector<string>, Text> par;
        par = ultim.ult;
        Text tex;
        tex = par.second;
        return tex.obtenir_frases_par(paraules);
    }
}

void afegir_text(vector<string>& autor, Text& text){
    map<vector<string>, list<Text> >::iterator it;
    it = textos.find(autor);
    if (it != textos.end()){
        list<Text>::iteratos it2 = it->second.begin();
        vector<string> titol = text.consultar_titol();
        bool fi = false;
        bool mes_gran = true;
        while (not fi and it2 != it->second.end()){
            int comp = ordre(text.consultar_titol, it->second.consultar_titol());
            if (int == 1) it->second.insert(it2, text);
            else ++it2;
        }
        ++nText;
    }
    else{
        textos.insert(make_pair(autor, text));
        ++nText;
        ++nAutor;
    }
}

void Textos::eliminar_text(){
    if (not utlim.esta) cout << "error" << endl;
    else{
        vector<string> autor = ultim.ult.first;
        Text tex = ultim.ult.second;
        vector<string> tit = tex.consultar_titol();
        map<>::iterator it_m;
        it_m = textos.find(autor);
        list<Text>::iterador it_l = it_m->second.begin();
        bool borrat = false;
        while (not borrat and it_l != it_m->second.end()){
            vector<string> tit2 = *it_l.consultar_titol();
            if (son_iguals(tit, tit2)){
                it_l = it_m->second.erase(it_l);
                borrat = true;
            }
        }
        --nText;
        if (it_m->second.empty()){
            textos.erase(it_m);
            --nAutor;
        }
  }
}

void Textos::cambiar_paraula(string p, string q){
    if (not utlim.esta) cout << "error" << endl;
    else{
        ultim.ult.second.cambiar_paraula(p, q);
        vector<string> autor = ultim.ult.first;
        Text tex = ultim.ult.second;
        vector<string> tit = tex.consultar_titol();
        map<>::iterator it_m;
        it_m = textos.find(autor);
        list<Text>::iterador it_l = it_m->second.begin();
        bool cambiat = false;
        while (not cambiat and it_l != it_m->second.end()){
            vector<string> tit2 = *it_l.consultar_titol();
            if (son_iguals(tit, tit2)){
                *it_l.cambiar_paraula(p, q);
            }
        }
        cambiar_freq_v(p, q);
    }
}

void Textos::afegir_cita(int x, int y){
    vector<Frase> v_fra = ultim.ult.second.obtenir_frases(x, y);
    vector<string> autor = ultim.ult.first;
    string ref = calcula_ref(autor);
    map<string, Cita>::iterator it = Cites.begin();
    bool trobat = false;
    while (not trobat and it != Cites.begin()){
        vector<string> tit = it->second.consultar_Titol();
        vector<string> aut = it->second.consulta_Autor();
        if (son_iguals(tit == ultim.ult.second.consultar_titol()) and son_iguals(aut == ultim.ult.second.consulta_autor())){
            int x1 = it->second.consultar_fra_in();
            int y1 = it->second.consultar_fra_fi();
            if (x1 == x  and y1 == y) trobat true;
        }
    }
    if (not trobat){
      Cita cita;
      cita.afegir_frases(v_fra, x, y);
      cita.afegir_tit_aut(ultim.ult.second.consultar_titol(), autor);
    }
    else cout << "error, la cita ja existeix"
}

void Textos::eliminar_cita(string& referencia){
    map<string, Cita>::iterator it;
    it = Cites.find(referencia);
    Cites.erase(it);
}

void Textos::escriure(){
    map<vector<string>, list<Text> >::const_iterator it;
    for (it = textos.begin(); it != textos.end(); ++it){
        vector<string> aut = it->first;
        bool first = true;
        for (int i = 0; i < aut.size; ++i){
            if (first){
                cout << aut[i];
                first = false;
            }
            else cout << ' ' << aut[i];
        }
        cout << endl;
        vector<string> tit = it->first.consultar_titol();
        bool first2 = true;
        for (int j = 0; j < tit.size; ++j){
            if (first2){
                cout << '"' << tit[j];
                first2 = false;
            }
            else cout << ' ' << aut[i];
        }
        cout << '"' << endl;
    }
}

void Textos::escriure_autors(){
    map<vector<string>, list<Text> >::const_iterator it;
    for (it = textos.begin(); it != textos.end(); ++it){
        vector<string> aut = it->first;
        bool first = true;
        for (int i = 0; i < aut.size(); ++i){
            if (first){
                cout << aut[i];
                first = false;
            }
            else cout << ' ' << aut[i];
        }
        cout << endl;
        cout << "nombre de textos: " << it->second.size() << endl;
        int nPar = 0;
        int nFra = 0;
        list<Text>::const_iterator it2;
        for (it2 = it->second.begin(); it2 != it->second.end(); ++it2){
            nPar += *it2.consultar_nParaules();
            nFra += *it2.consultar_nFrases();
        }
        cout << "nombre de paraules: " << nPar << endl;
        cout << "nombre de frases: " << nFra << endl;
    }
}

void Textos::escriure_info(){
  vector<string> aut = ultim.ult.first;
  vector<string> tit = ultim.ult.second.consultar_titol();
  bool first = true;
  for (int i = 0; i < aut.size(); ++i){
      if (first){
          cout << "autor: " << aut[i];
          first = false;
      }
      else cout << ' ' << aut[i];
  }
  first = true;
  for (int i = 0; i < tit.size(); ++i){
      if (first){
          cout << "titol: " << tit[i];
          first = false;
      }
      else cout << ' ' << tit[i];
  }
  cout << "nombre de paraules: " << ultim.ult.second.consultar_nParaules();
  cout << "nombre de frases: " << ultim.ult.second.consultar_nFrases();
  map<string, Cita>::const_iterator it;
  cout << "cites: " << endl;
  for (it = Cites.begin(); it != Cites.end(); ++it){
      if (son_iguals(it->second.consultar_Autor(), aut)){
          if (son_iguals(it->second.consultar_Titol(), tit)){
              vector<Frase> frases = it->second.consultar_cita();
              for (int i = 0; i < frases.size(); ++i){
                  frases[i].escriure();
                  nParaules += frases[i].consultar_nParaules();
              }
          }
      }
  }
}


void Textos::escriure_contingut(){
    ultim.ult.second.escriure();
}

void Textos::escriure_cita_ref(string& ref){
    map<string, Cita>::const_iterator it;
    it = Cites.find(ref);
    vector<string> aut = it->second.consultar_Autor();
    vector<string> tit = it->second.consultar_Titol();
    vector<Frase> frases = it->second.consultar_cita();
    for (int i = 0; i < frases.size(); ++i){
        frases[i].escriure();
    }
    bool first = true;
    for (int i = 0; i < aut.size(); ++i){
        if (first){
            cout << "autor: " << aut[i];
            first = false;
        }
        else cout << ' ' << aut[i];
    }
    first = true;
    for (int i = 0; i < tit.size(); ++i){
        if (first){
            cout << "titol: " << tit[i];
            first = false;
        }
        else cout << ' ' << tit[i];
    }
    cout << "valor frase inicial: " << it->second.consultar_fra_in() << endl;
    cout << "valor frase final: " << it->second.consultar_fra_fi() << endl;
}

void Textos::escriure_cita_autor(vector<string>& autor){
    map<string, Cita>::const_iterator it;
    for (it = Cites.begin(); it != Cites.end(); ++it){
        if (son_iguals(autor, it->second.consultar_Autor()){
            cout << "referencia: " << it->first << endl;
            vector<string> tit = it->second.consultar_Titol();
            cout << "titol: ";
            for (int i = 0; i < tit.size(); ++i){
                if (first){
                    cout << tit[i];
                    first = false;
                }
                else cout << ' ' << tit[i];
            }
            cout << endl;
            cout << "cita: ";
            vector<Cita> cita = it->second.consultar_cita();
            for (int i = 0; i < cita.size(); ++i){
                cita[i].escriure();
            }
        }
    }
}

void escriure_cites(){
  vector<string> aut = ultim.ult.first;
  vector<string> tit = ultim.ult.second.consultar_titol();
  map<string, Cita>::const_iterator it;
  for (it = Cites.begin(); it != Cites.end(); ++it){
      if (son_iguals(it->second.consultar_Autor(), aut)){
          if (son_iguals(it->second.consultar_Titol(), tit)){
              vector<Frase> frases = it->second.consultar_cita();
              for (int i = 0; i < frases.size(); ++i){
                  frases[i].escriure();
              }
              bool first = true;
              for (int i = 0; i < aut.size(); ++i){
                  if (first){
                      cout << "autor: " << aut[i];
                      first = false;
                  }
                  else cout << ' ' << aut[i];
              }
              first = true;
              for (int i = 0; i < tit.size(); ++i){
                  if (first){
                      cout << "titol: " << tit[i];
                      first = false;
                  }
                  else cout << ' ' << tit[i];
              }
          }
      }
  }
}


void Textos::escriure_totes_cites(){
    map<string, Cita>::const_iterator it;
    for (it = Cites.begin(); it != Cites.end(); ++it){
        vector<Cites> cita = it->second.consultar_cita();
        vector<string> tit = it->second.consultar_Titol();
        vector<string> aut = it->second.consultar_Autor();
        cout << "referencia: " << it->first << endl;
        cout << "titol: ";
        bool first = true;
        for (int i = 0; i < tit.size(); ++i){
            if (first){
                cout << tit[i];
                first = false;
            }
            else cout << ' ' << tit[i];
        }
        first = true;
        for (int i = 0; i < aut.size(); ++i){
            if (first){
                cout << aut[i];
                first = false;
            }
            else cout << ' ' << aut[i];
        }
        for (int i = 0; i < cita.size(); ++i){
            cita[i].escriure();
        }
    }
}
