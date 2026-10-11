/**
 * Universidad de La Laguna
 * Escuela Superior de Ingenieria y Tecnologia
 * Complejidad Computacional
 * 
 * @author  Dario Dominguez Gonzalez
 * @date    8/10/2026
 * @brief   Programar un simulador de un autómata con pila
*/

#include "../includes/AutomataPilaVaciado.h"

AutomataPilaVaciado::AutomataPilaVaciado(const std::set<std::string> &conjuntoEstados,
                                         const std::set<std::string> &conjuntoAlfabetoEntrada,
                                         const std::set<std::string> &conjuntoAlfabetoPila,
                                         std::string estadoInicial,
                                         std::string simboloInicialPila,
                                         std::multimap<std::string, Transicion> transiciones,
                                         bool traza) : 
    conjuntoEstados_(conjuntoEstados),
    conjuntoAlfabetoEntrada_(conjuntoAlfabetoEntrada),
    conjuntoAlfabetoPila_(conjuntoAlfabetoPila),
    estadoInicial_(std::move(estadoInicial)),
    simboloInicialPila_(std::move(simboloInicialPila)),
    transiciones_(std::move(transiciones)),
    traza_(traza) {}

void
AutomataPilaVaciado::showAutomata() const {
  std::cout << "Conjunto de Estados: ";
  for (const auto& estado : conjuntoEstados_) {
    std::cout << estado << " ";
  }
  std::cout << std::endl;

  std::cout << "Conjunto de Alfabeto de Entrada: ";
  for (const auto& simbolo : conjuntoAlfabetoEntrada_) {
    std::cout << simbolo << " ";
  }
  std::cout << std::endl;

  std::cout << "Conjunto de Alfabeto de Pila: ";
  for (const auto& simbolo : conjuntoAlfabetoPila_) {
    std::cout << simbolo << " ";
  }
  std::cout << std::endl;

  std::cout << "Estado Inicial: " << estadoInicial_ << std::endl;
  std::cout << "Símbolo Inicial de Pila: " << simboloInicialPila_ << std::endl;

  std::cout << "Transiciones:" << std::endl;
  for (const auto& [estado, transicion] : transiciones_) {
    std::cout << estado << " --(" 
              << transicion.simboloEntrada_ << ", "
              << transicion.simboloPila_ << ")--> "
              << transicion.estadoDestino_ 
              << " [Push: " 
              << transicion.simboloPilaNuevo_ 
              << "]" 
              << std::endl;
  }
}



void
AutomataPilaVaciado::activarTraza(bool activar) {
  if (activar) {
    traza_ = true;
  } else {
    traza_ = false;
  }
}


bool
AutomataPilaVaciado::resolverCadena(std::string cadenaEntrada) const {
  std::string estadoActual = estadoInicial_;
  std::string pilaActual = simboloInicialPila_;
  std::vector<Traza> traza;

  for (const char& aux : cadenaEntrada) {
    std::string simbolo(1, aux);
    if (!perteneceConjuntoAlfabetoCadena(simbolo)) {
      throw std::runtime_error("Error: El símbolo '" + simbolo + "' no pertenece al conjunto de alfabeto de entrada.");
    }
  }
  bool resultado = resolverCadenaRecursivo(estadoActual, cadenaEntrada, pilaActual, traza);
  if (traza_ == true) {
  std::cout << "Traza de la resolución de la cadena:\n";
    int anchoEstado = 6;
    int anchoCadena = static_cast<int>(std::max<size_t>(cadenaEntrada.length() + 2, 8));
    int anchoPila   = 8;
    for (const auto& paso : traza) {
      anchoPila = std::max(anchoPila, static_cast<int>(paso.pilaActual_.length() + 2));
    }
    auto valorOEpsilon = [](const std::string& str) -> std::string {
      return str.empty() ? "." : str;
    };
    std::cout << std::left
              << std::setw(anchoEstado) << estadoInicial_ << " | "
              << std::setw(anchoCadena) << valorOEpsilon(cadenaEntrada) << " | "
              << std::setw(anchoPila)   << valorOEpsilon(simboloInicialPila_) << " | \n";
    for (const auto& paso : traza) {
      std::cout << std::left
                << std::setw(anchoEstado) << paso.estadoActual_ << " | "
                << std::setw(anchoCadena) << valorOEpsilon(paso.cadenaActual_) << " | "
                << std::setw(anchoPila)   << valorOEpsilon(paso.pilaActual_) << " | ";
      paso.transicionAplicada_.showTransicion();
    }
  }
  return resultado;
}



bool
AutomataPilaVaciado::resolverCadenaRecursivo(std::string estadoActual, std::string cadenaEntrada, std::string pilaActual, 
                                             std::vector<Traza> &traza) const {
  if (cadenaEntrada.empty() && pilaActual.empty()) {
    return true;
  } else if (pilaActual.empty() && !cadenaEntrada.empty()) {
    return false;
  }
  auto rango = transiciones_.equal_range(estadoActual);
  if (rango.first == rango.second) {
    return false;
  }
  std::string cimaPila = pilaActual.substr(0, 1);
  std::string simboloActual = cadenaEntrada.empty() ? "" : cadenaEntrada.substr(0, 1);
  for (auto it = rango.first; it != rango.second; ++it) {
    const Transicion& transicion = it->second;
    if (transicion.simboloPila_ != cimaPila) {
      continue;
    }
    bool consumeEntrada = false;
    if (!cadenaEntrada.empty() && transicion.simboloEntrada_ == simboloActual) {
      consumeEntrada = true;
    } else if (transicion.esEpsilonEntrada()) {
      consumeEntrada = false;
    } else {
      continue;
    }
    std::string nuevaCadena = consumeEntrada ? cadenaEntrada.substr(1) : cadenaEntrada;
    std::string nuevaPila = pilaActual.substr(1);
    if (!transicion.esEpsilonPila()) {
      nuevaPila = transicion.simboloPilaNuevo_ + nuevaPila;
    }
    traza.push_back({estadoActual, nuevaCadena, nuevaPila, transicion});
    if (resolverCadenaRecursivo(transicion.estadoDestino_, nuevaCadena, nuevaPila, traza)) {
      return true;
    }
  }
  return false;
}


bool
AutomataPilaVaciado::perteneceConjuntoAlfabetoCadena(const std::string &simbolo) const {
  return conjuntoAlfabetoEntrada_.find(simbolo) != conjuntoAlfabetoEntrada_.end();
}