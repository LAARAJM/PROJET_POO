# Compilateur et flags
CXX = clang++
CXXFLAGS = -g -Wmost -Werror -std=c++17
LDFLAGS = -lsfml-graphics -lsfml-window -lsfml-audio -lsfml-network -lsfml-system

# Répertoires
MODELE_DIR = NS_Modele
VUE_DIR = NS_Vue
CONTROLEUR_DIR = NS_Controleur
TEST_DIR = TEST

# Includes
INCLUDES = -I$(MODELE_DIR) -I$(VUE_DIR) -I$(CONTROLEUR_DIR) -I$(TEST_DIR)

# Sources par namespace
MODELE_SRCS = $(wildcard $(MODELE_DIR)/*.cpp)
VUE_SRCS = $(wildcard $(VUE_DIR)/*.cpp)
CONTROLEUR_SRCS = $(wildcard $(CONTROLEUR_DIR)/*.cpp)
TEST_SRCS = $(wildcard $(TEST_DIR)/*.cpp)

# Toutes les sources
SRCS = main.cpp $(MODELE_SRCS) $(VUE_SRCS) $(CONTROLEUR_SRCS) $(TEST_SRCS)

# Objets
OBJS = $(SRCS:.cpp=.o)

# Exécutable
TARGET = main

# Règle par défaut
all: $(TARGET)

# Compilation de l'exécutable
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

# Compilation des fichiers objets
%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

# Version debug
main-debug: CXXFLAGS += -U_FORTIFY_SOURCE -O0
main-debug: $(TARGET)

# Nettoyage
clean:
	rm -f $(TARGET) main-debug $(OBJS)
	rm -rf jeu_de_la_vie/

# Nettoyage complet
cleanall: clean
	rm -rf jeu_de_la_vie/

# Aide
help:
	@echo "Commandes disponibles:"
	@echo "  make          - Compile le projet"
	@echo "  make clean    - Supprime les fichiers compilés"
	@echo "  make cleanall - Supprime tout (compilés + sauvegardes)"
	@echo "  make help     - Affiche cette aide"

.PHONY: all clean cleanall help main-debug