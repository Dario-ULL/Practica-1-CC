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
#include "AutomataPilaVaciado.h"

#include <iostream>
#include <string>
#include <fstream>
#include <filesystem>
#include <vector>
#include <map>
#include <set>

class LectorDeArchivo {
  public:
    LectorDeArchivo(std::string nombreArchivo);
    ~LectorDeArchivo() = default;

    AutomataPilaVaciado getAutomataPilaVaciado() const { return automata_; }
  private:
    bool validarAutomata() const; 
    AutomataPilaVaciado automata_;
};