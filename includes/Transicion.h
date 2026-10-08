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

#include <string>
#include <iostream>

struct Transicion {
  std::string simboloEntrada_;
  std::string simboloPila_;
  std::string estadoDestino_;
  std::string simboloPilaNuevo_;

  Transicion() = default;
  Transicion(std::string simboloEntrada, std::string simboloPila, std::string estadoDestino, std::string simboloPilaNuevo): simboloEntrada_(simboloEntrada),
                                                                                                                    simboloPila_(simboloPila),
                                                                                                                    estadoDestino_(estadoDestino),
                                                                                                                    simboloPilaNuevo_(simboloPilaNuevo) {}
  bool esEpsilonEntrada() const { return simboloEntrada_ == "."; }
  bool esEpsilonPila() const { return simboloPilaNuevo_ == "."; }
  void showTransicion() const {
    std::cout << "Transición: (" << simboloEntrada_ << ", " << simboloPila_ << ") --> " << estadoDestino_ << " [Push: " << simboloPilaNuevo_ << "]" << std::endl;
  }
};

struct Traza {
  std::string estadoActual_;
  std::string cadenaActual_;
  std::string pilaActual_;
  Transicion transicionAplicada_;

  void cadenaVacia() {
    cadenaActual_ = ".";
  }
  void pilaVacia() {
    pilaActual_ = ".";
  }
};