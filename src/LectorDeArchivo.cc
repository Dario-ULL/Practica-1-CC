/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    8/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#include "../includes/LectorDeArchivo.h"

namespace fs = std::filesystem;

LectorDeArchivo::LectorDeArchivo(std::string nombreArchivo) {
  if (nombreArchivo.rfind("data/", 0) != 0) {
    nombreArchivo = "data/" + nombreArchivo;
  }
  std::ifstream archivo(nombreArchivo);
  if (!archivo.is_open()) {
    throw std::runtime_error("No se pudo abrir el archivo: " + nombreArchivo);
  }

  std::set<std::string> conjuntoEstados;
  std::set<std::string> conjuntoAlfabetoEntrada;
  std::set<std::string> conjuntoAlfabetoPila;
  std::string estadoInicial;
  std::string simboloInicialPila;
  std::multimap<std::string, Transicion> transiciones;

  std::string linea;
  while (std::getline(archivo, linea)) {
    if (linea.empty() || linea[0] == '#') {
      continue;
    } else {
      break;
    }
  }

  std::string aux;
  std::istringstream iss(linea);
  while (iss >> aux) {
    conjuntoEstados.insert(aux);
  }

  std::getline(archivo, linea);
  iss.clear();
  iss.str(linea);
  while (iss >> aux) {
    conjuntoAlfabetoEntrada.insert(aux);
  }

  std::getline(archivo, linea);
  iss.clear();
  iss.str(linea);
  while (iss >> aux) {
    conjuntoAlfabetoPila.insert(aux);
  }

  std::getline(archivo, estadoInicial);
  std::getline(archivo, simboloInicialPila);

  bool comprobarEstadosFinales = true;

  while (std::getline(archivo, linea)) {
    if (comprobarEstadosFinales == true) {
      std::istringstream issEstadoFinal(linea);
      while (issEstadoFinal >> aux) {
        for (const auto& estado : conjuntoEstados) {
          if (aux == estado) {
            comprobarEstadosFinales = true;
            break;
          } else {
            comprobarEstadosFinales = false;
          }
        }
      }
      if (comprobarEstadosFinales == true) {
        throw std::runtime_error("Error: Se encontraron estados finales en la línea: " + linea);
      }
    }
    if (!linea.empty() && linea.back() == '\r') {
      linea.pop_back();
    }

    if (linea.empty() || linea[0] == '#') {
      continue;
    }
    std::istringstream issTransicion(linea);

    std::string estadoActual;
    std::string simboloEntrada;
    std::string simboloPila;
    std::string estadoSiguiente;
    std::string simboloPilaSiguiente;

    if (!(issTransicion >> estadoActual 
                        >> simboloEntrada 
                        >> simboloPila 
                        >> estadoSiguiente 
                        >> simboloPilaSiguiente)) {
      throw std::runtime_error("Formato de transición inválido: " + linea);
    }

    transiciones.emplace(estadoActual, Transicion(simboloEntrada, simboloPila, estadoSiguiente, simboloPilaSiguiente));
  }
  automata_ = AutomataPilaVaciado(conjuntoEstados, conjuntoAlfabetoEntrada, conjuntoAlfabetoPila, estadoInicial, simboloInicialPila, transiciones, false);
  archivo.close();
  validarAutomata();
}


bool 
LectorDeArchivo::validarAutomata() const {
  // 1. Validar estado inicial
  if (!automata_.getConjuntoEstados().count(automata_.getEstadoInicial())) {
    throw std::runtime_error("Error: El estado inicial '" + automata_.getEstadoInicial() + "' no pertenece al conjunto de estados.");
  }

  // 2. Validar símbolo inicial de pila
  if (!automata_.getConjuntoAlfabetoPila().count(automata_.getSimboloInicialPila())) {
    throw std::runtime_error("Error: El símbolo inicial de pila '" + automata_.getSimboloInicialPila() + "' no pertenece al conjunto de alfabeto de pila.");
  }

  // 3. Validar cada transición
  for (const auto& [origen, t] : automata_.getTransiciones()) {
    if (!automata_.getConjuntoEstados().count(origen)) {
      throw std::runtime_error("Error: Estado origen '" + origen + "' no definido.");
    }
    if (!automata_.getConjuntoEstados().count(t.estadoDestino_)) {
      throw std::runtime_error("Error: Estado destino '" + t.estadoDestino_ + "' no definido.");
    }
    if (!t.esEpsilonEntrada() && !automata_.getConjuntoAlfabetoEntrada().count(t.simboloEntrada_)) {
      throw std::runtime_error("Error: Símbolo de entrada '" + t.simboloEntrada_ + "' no está en el alfabeto de entrada.");
    }
    if (!automata_.getConjuntoAlfabetoPila().count(t.simboloPila_)) {
      throw std::runtime_error("Error: Símbolo a desapilar '" + t.simboloPila_ + "' no está en el alfabeto de la pila.");
    }
    if (!t.esEpsilonPila()) {
      for (char c : t.simboloPilaNuevo_) {
        std::string s(1, c);
        if (!automata_.getConjuntoAlfabetoPila().count(s)) {
          throw std::runtime_error("Error: Símbolo a apilar '" + s + "' en '" + t.simboloPilaNuevo_ + "' no está en el alfabeto de la pila.");
        }
      }
    }
  }
  return true;
}