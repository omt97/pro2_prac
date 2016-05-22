/** @file Textos.hh
    @brief Especificació de la classe Textos
*/

#ifndef TEXTOS_HH
#define TEXTOS_HH

#include "Cita.hh"
#include "Text.hh"

#ifndef NO_DIAGRAM
#include <vector>
#include <iostream>
#include <list>
#include <utility>
#include <string>
#endif

/** @class Textos

    @brief Classe principal. Representa un conjunt de textos ordenats per autor
    i titol. Es poden consultar i modificar els seus elements (de tipus Text) i
    tambe altres amb els quals es relaciona (com les cites).
    */
class Textos {

private:

  struct ultim{
      pair <vector<string>, Text> ult;
      vector<pair<int, string> > freq_v;
      bool esta = false;
  }
  map<vector<string>, list<Text> > textos;
  map<string, Cita> Cites;
  int nAutor;
  int nText;
  /*
    Invariant de la representacio:
      - ultim sempre conté un Text encara que sigui buit.
  */

	/** @brief Calcula la referencia que serà usada en una cita, per tal de poder-
                la identificar més fàcilment, la referencia estarà formada per
                les inicials de l'autor del text de la cita, i per un nombre natural.
      \pre cert
      \post el resultat es un string que fa de referencia per alguna cita, el
            qual esta format per les inicials de l'autor de la cita, i un nombre
            natural n, on n > 1, si ja existeix una referencia amb les mateixes
            inicials que aquesta i n = 1, si no existeix.
  */
	string calcular_ref(vector<string>& autor);

  /** @brief La funció transforma la taula de freqüencia del ultim text triat
              en un vector ordenat segons el segon element de la taula.
      \pre text es vàlid.
      \post La funció transforma la taula de freqüencia del ultim text triat
            en un vector ordenat segons el segon element de la taula.
  */
  void calc_vec_freq(Text& text);

  /** @brief La funció retorna un boolea que ens diu si els dos vectors itroduits
              són iguals o no.
      \pre t1 i t2 són valids.
      \post el resultat es un boolea que ens diu si els dos vectors son iguals
            o diferents.
  */
  bool son_iguals(vector<string>& t1, vector<string>& t2);

  /** @brief La funció retorna un 1 si alfabeticament t1 va abans de t2, contrariament
              treu un 2.
      \pre t1 i t2 són valids.
      \post el resultat es un 1 si alfabeticament t1 va abans de t2, contrariament
            treu un 2.
  */
  int ordre(vector<string>& t1, vector<string>& t2);

public:

  //Constructores

  /** @brief Creadora per defecte.
      S'executa automaticament al declarar Text t;
      \pre cert
      \post el resultat es un conjunt textos buit, un conjunt Cites buida, i ultim
            es buit, nAutors i nTextos son 0.
  */
  Textos();

    //Consultores

  /** @brief Consulta dins de textos, si existeix alguna element first igual a autor
            , retorna cert si hi es i fals contrariament.
      \pre autor ha de ser vàlid
      \post el resultat es un boolea, que diu si existeix alguna element de textos
            first igual a autor.
  */
	bool esta_autor(vector<string>& autor);

  /** @brief Consulta dins de textos, si existeix algun text que inclogui les
              paraules que hi ha en el vector paraules. En cas
              de que existeixi, el text es guarda dins de ultim.
      \pre paraules ha de ser vàlid, i ha d'existir un sol text que les contingui.
      \post la variable ultim guarda el text que inclou les paraules del vector paraules
  */
	void triar_text_par(vector<string>& paraules);

  /** @brief La funció retorna un vector que conté tots els textos de l'element
              first del map textos, que es igual a autor.
      \pre autor ha de ser vàlid
      \post el resultat és un vector que conté tots els textos de l'element
                  first del map textos, que es igual a autor.
  */
	list<Text> textos_autor(vector<string>& autor);

  /** @brief La funció retorna l'autor del text guardat dins de la variable
              ultim, que és l'últim test triat.
      \pre cert.
      \post el resultat es el nom de l'autor del text guardat dins de la variable
                  ultim, que és l'últim test triat.
  */
	vector<string> consulta_autor();

  /** @brief La funció retorna el numero de frases que conté l'últim text triat,
              guradat dins de la variable ultim.
      \pre cert.
      \post el resultat es el nombre de frases que conté l'últim text triat,
              guradat dins de la variable ultim.
  */
	int consulta_nFrases();

  /** @brief La funció retorna el numero de paraules que conté l'últim text triat,
              guradat dins de la variable ultim.
      \pre cert.
      \post el resultat es el nombre de paraules que conté l'últim text triat,
            guradat dins de la variable ultim.
  */
	int consulta_nParaules();

  /** @brief La funció retorna un vector que conté les frases que hi ha entre la x-essima frase (inclosa)
            i la y-essima frase (inclosa) de l'últim text triat, guardat dins de la variable ultim.
      \pre 'x' i 'y' són vàlids.
      \post el resultat es un vector que conté les frases que hi ha entre la x-essima i la y-essima frase de l'ultim
            text triat.
  */
	vector<Frase> obtenir_frases(int x, int y);

  /** @brief La funció retorna la taula de freqüencies de l'ultim text triat, on la taula de freqüencies és una
            taula que conté totes les paraules del text i el nombre d'aparicions que tenen, la taula està
            ordenada per ordre d'aparicions, (de més a menys).
      \pre cert.
      \post el resultat es la taula de freqüencies de l'ultim text triat.
  */
	vector<pair<int, string> > obtenir_freq();

  /** @brief La funció retorna un vector que conté les frases de l'ultim text triat, on apareixen les paraules
            del vector paraules.
      \pre paraules és valid.
      \post el resultat es una seqüencia de frases, de l'ultim text triat, que contenen les paraules del vector
            paraules.
  */
	vector<Frase> obtenir_frases_par(vector<string>& paraules);




    //Modificadors

  /** @brief Dins de textos, existeix un element first igual al vector autor cridat a la funció, llavors
            el text cridat a la funció s'introdueix com a element second d'aquest element
            , llavors l'element first té un Text més.

      \pre el text és vàlid, i textos conté un element first igual a l'autor cridat a la funció.
      \post la fitxa,l'elment first de textos, que té el mateix autor que el cridat per referencia,
            se li associa un nou Text, que es text, el nombre de paraules i frases de la Fitxa
            augmenten en funció de text.
   */
  void afegir_text(vector<string>& autor, Text& text);

  /** @brief s'elimina de textos el Text guradat dins de ultim.

      \pre cert
      \post el Text guardat dins de la variable ultim, es eliminat.
   */
  void eliminar_text();

  /** @brief En l'ultim text triat es canvien totes els paraules que siguin igual a p per la paraula q.

      \pre el parametre implicit conté la paraula p i q es una paraula vàlida
      \post totes les aparicions de p en el parametre implicit han pasat a ser q.
   */
  void cambiar_paraula(string p, string q);

    /** @brief Dins del map de cites guradem una nova cita, que esta formada per totes les frases que hi ha entre:
                la x-essima frase (inclosa) i la y-essima frase (inclosa) de l'ultim text triat, amb la funció calcular_ref
                també afegim una referencia asociada a la cita inclosa.

      \pre el valors 'x' i 'y' son vàlids
      \post el map de cites guradem una nova cita, que esta formada per totes les frases que hi ha entre:
                la x-essima frase (inclosa) i la y-essima frase (inclosa) de l'ultim text triat i se li associa una
                referencia amb l'ajuda de la funció calcular_ref.
   */
  void afegir_cita(int x, int y);

    /** @brief Dins del map de cites eliminaem la cita associada a la referencia cridada per la funció.

      \pre referencia és vàlida
      \post al map de cites se li esborra la cita associada a la referencia cridada per la funció
   */
  void eliminar_cita(string& referencia);



  // Lectura i escriptura

  /** @brief Operacio d'escriptura

    \pre cert
    \post s'han escrit pel canal estandard de sortida tots els títols dels textos
          i els seus autors ordenats alfabeticament
   */
  void escriure() const;

	/** @brief Operacio d'escriptura d'autors (vector<string>), el nombre de textos
            de cada autor, i el nombre de paraules i de frases de tots els textos.

		\pre cert
		\post s'han escrit pel canal estandard de sortida tots els autors, el nombre
          de textos, paraules i frases de cada autor que hi ha dins de textos.
	 */
	void escriure_autors();

  /** @brief Operacio d'escriptura de totes les cites que han estat extretes de
            l'ultim text triat, del seu autor i el titol, i el nombre de frases
            i paraules que conté.

    \pre cert
    \post s'han escrit pel canal estandard de sortida de l'ultim text, el seu
          autor, titol, el nombre de frases i el nombre de paraules que conté.
   */
  void escriure_info();

  /** @brief Operacio d'escriptura de totes les frases de l'utim text triat per
            ordre i numerades per posició.

    \pre cert
    \post s'han escrit pel canal estandard de sortida totes les frases, de l'útlim
          text triat, ordenades i numerades.
   */
  void escriure_contingut();

  /** @brief Operacio d'escriptura de totes les frases de la cita associada a la
            referencia cridada per la funció (ref), i escriptura de l'autor i titol
            , de l'obra d'on ha sigut extreta, i els valors de la frase inicial
            i final

    \pre dins de cites existeix alguna referencia igual a ref
    \post s'han escrit pel canal estandard de sortida totes les frases, de la cita
          associada a ref, dins de cites. I l'autor i titol, de l'obra d'on ha
          sigut extreta, i els valors de la frase inicial i final
   */
  void escriure_cita_ref(string& ref);

  /** @brief Operacio d'escriptura de totes les frases de les cites, tretes de
            textos on l'autor es el vector autor cridat per referencia, i
            escriptura del titol i la referencia de cada cita, ordenades segons
            la referencia.

    \pre existeix alguna cita treta d'un Text on l'autor es el cridat per referencia
    \post s'han escrit pel canal estandard de sortida totes les frases, de les
          cites tretes del textos on l'autor es igual al cridat per la funció, i
          el titol i referencia de cada una. L'escriptura s'ha ordenat en funció
          de la referencia.
   */
  void escriure_cita_autor(vector<string>& autor);

  /** @brief Operacio d'escriptura de totes les frases de les cites, obtingudes
              de l'ultim text triat. I escriptura de l'autor, titol i referencia
              de cada una, ordenades en funció de la referencia.

    \pre cert
    \post s'han escrit pel canal estandard de sortida totes les frases, de les
          cites tretes de l'últim text triat. I l'autor, el titol i la referencia
          de cada cita, ordenades en funció de la referencia.
   */
  void escriure_cites();

  /** @brief Operacio d'escriptura de totes les frases de les cites de la classe
            Textos, i l'autor, el titol i la referencia de cada una, ordenades en
            funció de la referencia.

    \pre cert
    \post s'han escrit pel canal estandard de sortida totes les frases, de totes les
          cites de la classe Textos, i l'autor, el titol i la referencia de
          cada una d'elles. L'escriptura s'ha ordenat en funció de la referencia.
   */
  void escriure_totes_cites();

};
#endif
