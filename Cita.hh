/** @file Cita.hh
    @brief Especificació de la classe Cita
*/

#ifndef CITA_HH
#define CITA_HH

#include "Frase.hh"
#include "Text.hh"

#ifndef NO_DIAGRAM
#include <iostream>
#include <string>
#include <vector>
#endif

class Cita {

  // Tipus de modul: dades


  /** @class  Cita
      @brief Representa una cita d'un text, formada per diverses
      frases del text.
      Les frases d'entrada han de ser valides
      */

private:
  vector<Frase> cita;
  int fra_in;
  int fra_fi;
  vector<string> Autor;
  vector <string> Titol;

  /*
    Invariant de la representació:
    - cita minim 1 frase
    - 0 <= fra_in <= fra_fi
    - autor sempre ha de tenir nom i cognom com a minim
    - titol minim 1 string
    - referencia valida
  */
public:
  //Constructores

  /** @brief Creadora per defecte.
      S'executa automáticament al declarar Cita c.
      \pre cert
      \post el resultat es una cita buida amb fra_in = fra_fi = 0, autor i titol
       no tenen valor.
  */
  Cita();

  //Modificadores

  /** @brief Afegeix les frases que formen la cita, i fra_in = x, i fra_fi = y.
      \pre la cita es buida, i frase, x i y son vàlids
      \post cita es converteix en el vector frase, i fra_in = x i fra_fi = y.
  */
  void afegir_frases(vector<Frase>& frase, int x, int y);

  /** @brief el vector Titol obté el valor del vector cridat per referencia, titol
            i el vector Autor obté el valor del vector cridat per referencia, autor.
      \pre els vectors autor i titol són buits.
      \post el vector Titol és igual al vector cridat per referencia, anomenat titol
            i el vector Autor és igual al vector cridat per referencia, anomenat autor.
  */
  void afegir_tit_aut(vector<string>& titol, vector<string>& autor);


  //Consultores

  /** @brief Consulta el Titol del parametre implicit
      \pre cert
      \post el resultat es el Titol del parametre implicit
   */
  vector<string> consultar_Titol();

  /** @brief Consulta l'Autor del parametre implicit
      \pre cert
      \post el resultat es l'Autor del parametre implicit
   */
  vector<string> consultar_Autor();

    /** @brief Consulta el numero de la frase inicial del parametre implicit
      \pre cert
      \post el resultat es el numero de la frase incial del parametre implicit
   */
  int consultar_fra_in();

    /** @brief Consulta el numero de la frase final del parametre implicit
      \pre cert
      \post el resultat es el numero de la frase final del parametre implicit
   */
  int consultar_fra_fi();

  /** @brief Retorna el contingut del parametre implicit
      \pre cert
      \post el resultat es un vector que conté totes les frases que formen la cita.
   */
  vector<Frase> consultar_cita();


  // Lectura i escriptura

};
#endif
