# Práctica 1: Simulador de Autómata con Pila

## Información general
* **Asignatura:** Complejidad Computacional
* **Curso:** 2026/2027
* **Lenguaje:** C++ (Estándar C++17)
* **Tipo de autómata implementado:** **Autómata con Pila por Vaciado de Pila (APv)**

---

## Descripción del proyecto
Este simulador permite cargar y ejecutar autómatas a pila mediante programación orientada a objetos en C++. 
El modelo implementado acepta cadenas exclusivamente si existe al menos una secuencia de transiciones que consuma la totalidad de la cadena de entrada 
y deje la pila completamente vacía (reconocimiento por vaciado de pila mediante búsqueda y backtracking).

---

## Ejecución del programa

Tras compilar con `make`, el ejecutable `simulador` se genera en la raíz del proyecto. El programa se ejecuta desde la consola pasando las opciones de configuración y traza requeridas:

```bash
./simulador -config <fichero_apv> -trace <y|n>

```

---

## Estructura del proyecto

```text
.
├── Makefile
├── README.md
├── simulador              # Ejecutable
├── simulador.cc           # Archivo main del programa
├── data/                  # Ficheros de definición (.txt)
├── includes/              # Archivos de cabecera (.h)
│   ├── AutomataPilaVaciado.h
│   ├── LectorDeArchivo.h
│   └── Transicion.h
├── src/                   # Código fuente (.cc)
│   ├── AutomataPilaVaciado.cc
│   ├── LectorDeArchivo.cc
│   ├── Transicion.cc
│   └── main.cc
└── builds/                # Archivos objeto (.o)
```
