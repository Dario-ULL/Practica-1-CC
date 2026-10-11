/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    8/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#pragma once

#include "Transicion.h"

#include <iostream>
#include <utility>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <iomanip>

class AutomataPilaVaciado {
  public:
    AutomataPilaVaciado() = default;
    AutomataPilaVaciado(const std::set<std::string> &conjuntoEstados,
                        const std::set<std::string> &conjuntoAlfabetoEntrada,
                        const std::set<std::string> &conjuntoAlfabetoPila,
                        std::string estadoInicial,
                        std::string simboloInicialPila,
                        std::multimap<std::string, Transicion> transiciones,
                        bool traza);
    ~AutomataPilaVaciado() = default;

    bool resolverCadena(std::string cadenaEntrada) const;
    void showAutomata() const;
    void activarTraza(bool activar);

    std::set<std::string> getConjuntoEstados() const { return conjuntoEstados_; }
    std::set<std::string> getConjuntoAlfabetoEntrada() const { return conjuntoAlfabetoEntrada_; }
    std::set<std::string> getConjuntoAlfabetoPila() const { return conjuntoAlfabetoPila_; }
    std::string getEstadoInicial() const { return estadoInicial_; }
    std::string getSimboloInicialPila() const { return simboloInicialPila_; }
    std::multimap<std::string, Transicion> getTransiciones() const { return transiciones_; }
  private:
    bool resolverCadenaRecursivo(std::string estadoActual, std::string cadenaEntrada, std::string pilaActual, 
                                 std::vector<Traza> &traza) const; 
    bool perteneceConjuntoAlfabetoCadena(const std::string &simbolo) const;
    std::set<std::string> conjuntoEstados_;
    std::set<std::string> conjuntoAlfabetoEntrada_;
    std::set<std::string> conjuntoAlfabetoPila_;
    std::string estadoInicial_;
    std::string simboloInicialPila_;
    std::multimap<std::string, Transicion> transiciones_;
    bool traza_;
};