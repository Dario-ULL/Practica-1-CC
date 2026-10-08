# Compilador y flags
CXX      := g++
CXXFLAGS := -Wall -Wextra -std=c++17 -Iincludes

# Nombre del ejecutable final
TARGET   := simulador

# Directorios
SRC_DIR   := src
INC_DIR   := includes
BUILD_DIR := builds

# Archivos fuente (.cc)
# Incluye todos los .cc de 'src/' más 'Simulador.cc' que está en la raíz
SRCS := Simulador.cc $(wildcard $(SRC_DIR)/*.cc)

# Archivos objeto (.o) que se guardarán en 'builds/'
OBJS := $(patsubst %.cc, $(BUILD_DIR)/%.o, $(notdir $(SRCS)))

# Regla por defecto
all: $(BUILD_DIR) $(TARGET)

# Crear el directorio builds/ si no existe
$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

# Enlazado final del ejecutable
$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# Regla para compilar Simulador.cc (raíz) -> builds/Simulador.o
$(BUILD_DIR)/Simulador.o: Simulador.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para compilar cualquier archivo src/%.cc -> builds/%.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cc | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados (.o y binario)
clean:
	rm -rf $(BUILD_DIR)/*.o $(TARGET)

# Recompilar desde cero
re: clean all

.PHONY: all clean re