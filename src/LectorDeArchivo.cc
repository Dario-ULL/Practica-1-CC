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
  while (std::getline(archivo, linea)) {
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
  automata_ = AutomataPilaVaciado(conjuntoEstados, conjuntoAlfabetoEntrada, conjuntoAlfabetoPila, estadoInicial, simboloInicialPila, transiciones, "n");
  archivo.close();
}



void
LectorDeArchivo::leerArchivo(std::string nombreArchivo) {
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

  while (std::getline(archivo, linea)) {
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
  automata_ = AutomataPilaVaciado(conjuntoEstados, conjuntoAlfabetoEntrada, conjuntoAlfabetoPila, estadoInicial, simboloInicialPila, transiciones, "n");
  archivo.close();
}