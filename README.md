# Jeu de la Vie - Conway's Game of Life

##  Description

Le **Jeu de la Vie** (Game of Life) est un automate cellulaire conçu par le mathématicien britannique **John Horton Conway** en 1970. Il s'agit d'un jeu à zéro joueur, ce qui signifie que son évolution est déterminée uniquement par son état initial, sans aucune intervention ultérieure.

### Concept

Le jeu se déroule sur une grille rectangulaire bidimensionnelle, théoriquement infinie, dont les cases (cellules) peuvent prendre deux états distincts : **vivante** ou **morte**. À chaque étape (génération), l'état de chaque cellule est déterminé par l'état de ses huit voisines selon des règles simples. Ces règles permettent l'émergence de comportements complexes et fascinants : structures stables, oscillateurs, vaisseaux spatiaux, etc.

### Historique et importance

Le Jeu de la Vie est un exemple classique de **système dynamique** et d'**émergence** : des règles simples produisent des comportements complexes et imprévisibles. Il est utilisé dans de nombreux domaines :
- Biologie : modélisation de populations
- Informatique théorique : universalité de Turing
- Mathématiques : étude des automates cellulaires
- Philosophie : réflexion sur la vie artificielle

---

##  Règles du jeu

Le jeu se déroule sur une grille rectangulaire où chaque cellule peut être dans l'un des trois états suivants :

### Types de cellules

| Type | Symbole fichier | Symbole console | Couleur graphique | Comportement |
|------|----------------|-----------------|-------------------|--------------|
| **Morte** | `0` | `0` | Gris foncé | Peut devenir vivante |
| **Vivante** | `1` | `1` | Vert | Peut mourir |
| **Obstacle** | `2` | `#` | Rouge | Immuable |

### Règles de Conway (cellules normales)

À chaque génération, l'état d'une cellule est déterminé par le nombre de ses **voisines vivantes** (maximum 8 voisines) :

1. **Naissance** : Une cellule morte avec exactement **3 voisines vivantes** devient vivante
   - Exemple : `0` entouré de 3 cellules `1` → devient `1`

2. **Survie** : Une cellule vivante avec **2 ou 3 voisines vivantes** reste vivante
   - Exemple : `1` entouré de 2 ou 3 cellules `1` → reste `1`

3. **Mort par isolement** : Une cellule vivante avec **moins de 2 voisines vivantes** meurt
   - Exemple : `1` entouré de 0 ou 1 cellule `1` → devient `0`

4. **Mort par surpopulation** : Une cellule vivante avec **plus de 3 voisines vivantes** meurt
   - Exemple : `1` entouré de 4, 5, 6, 7 ou 8 cellules `1` → devient `0`

### Règles spéciales (obstacles)

Les **obstacles** (`2`) ne changent jamais d'état, quelle que soit leur configuration de voisinage. Ils peuvent cependant influencer l'évolution des cellules voisines en étant comptés comme des cellules mortes dans le calcul des voisins.

### Voisinage

Chaque cellule possède **8 voisines** : les cellules adjacentes horizontalement, verticalement et en diagonale.
```
┌───┬───┬───┐
│ V │ V │ V │
├───┼───┼───┤
│ V │ C │ V │  C = Cellule centrale
├───┼───┼───┤  V = Voisines (8 au total)
│ V │ V │ V │
└───┴───┴───┘
```

### Configurations classiques

**Vie immobile (Still lifes)** :
- **Bloc** : carré 2×2 de cellules vivantes
- **Ruche** : hexagone de 6 cellules
- **Bateau** : forme en L de 5 cellules

**Oscillateurs** :
- **Clignotant** (période 2) : 3 cellules alignées
- **Crapaud** (période 2) : 6 cellules en forme de rectangle
- **Pulsar** (période 3) : structure symétrique de 48 cellules

**Vaisseaux spatiaux** :
- **Planeur** : se déplace en diagonale, période 4
- **LWSS** (Light Weight Spaceship) : se déplace horizontalement

---

##  Fonctionnalités

### Fonctionnalités principales

 **Simulation complète du Jeu de la Vie** selon les règles de Conway  
 **Double mode d'affichage** :
   - **Console** : Affichage textuel simple pour débogage et analyse
   - **Graphique** : Interface SFML colorée et intuitive

 **Chargement depuis fichier** : Import de configurations initiales personnalisées  
 **Détection automatique de stabilisation** : Arrêt intelligent quand la grille n'évolue plus  
 **Contrôle du nombre d'itérations** : Limitation configurable de la simulation  
 **Sauvegarde automatique** : Export de chaque génération dans un fichier

### Extensions implémentées (points bonus)

 **Grille torique** : Les bords de la grille sont connectés (effet "Pac-Man")
   - La cellule en position (0, y) est voisine de la cellule en position (largeur-1, y)
   - La cellule en position (x, 0) est voisine de la cellule en position (x, hauteur-1)
   - Permet aux motifs de "traverser" les bords de la grille

 **Cellules obstacles** : Cellules immuables qui ne changent jamais d'état
   - Symbolisées par `2` dans les fichiers et `#` en console
   - Affichées en rouge dans le mode graphique
   - Permettent de créer des labyrinthes et des barrières

 **Tests unitaires complets** : Suite de 10 tests automatisés validant :
   - Les configurations classiques (bloc, planeur, clignotant)
   - Les règles de Conway
   - Le mode torique
   - Les obstacles
   - Le chargement/sauvegarde de fichiers

### Fonctionnalités techniques

🔧 **Architecture orientée objet** respectant les principes SOLID  
🔧 **Séparation MVC** (Modèle-Vue-Contrôleur)  
🔧 **Polymorphisme** pour les cellules et les règles  
🔧 **Gestion mémoire sécurisée** avec destructeurs appropriés  
🔧 **Extensibilité** : Ajout facile de nouveaux types de cellules ou de règles


##  Utilisation

### Syntaxe de base
```bash
./main [fichier] [mode] [iterations]
```

### Paramètres détaillés

| Paramètre | Type | Valeur par défaut | Description |
|-----------|------|-------------------|-------------|
| `fichier` | String | `grille.txt` | Chemin vers le fichier de configuration initiale |
| `mode` | String | `graphique` | Mode d'affichage : `console` ou `graphique` |
| `iterations` | Integer | `100` | Nombre maximum de générations à simuler |

### Exemples d'utilisation

**1. Lancer avec les paramètres par défaut**
```bash
./main
```
→ Charge `grille.txt`, affiche en mode graphique, 100 itérations max

**2. Mode graphique avec fichier personnalisé**
```bash
./main grille_initiale.txt graphique 200
```
→ Simulation visuelle de 200 générations

**3. Mode console pour analyse rapide**
```bash
./main grille_test.txt console 50
```
→ Affichage textuel dans le terminal, 50 générations

**4. Simulation longue avec détection de stabilisation**
```bash
./main planeur.txt graphique 1000
```
→ S'arrête automatiquement si la grille se stabilise avant 1000 itérations

**5. Grille torique**
```bash
./main grille_torique.txt graphique 500
```
→ Les motifs peuvent traverser les bords de la grille

### Lancer les tests unitaires
```bash
./main test
```

Cette commande exécute la suite complète de 10 tests automatisés et affiche le résultat :
```
========================================
TESTS UNITAIRES - JEU DE LA VIE
========================================

[OK] Test 1: Bloc stable
[OK] Test 2: Extinction
[OK] Test 3: Planeur
[OK] Test 4: Clignotant
[OK] Test 5: Obstacles
[OK] Test 6: Mode torique
[OK] Test 7: Grille vide
[OK] Test 8: Regles Conway
[OK] Test 9: Chargement fichier
[OK] Test 10: Stabilisation

========================================
Tests reussis: 10
Tests echoues: 0
Total: 10
========================================

✓ Tous les tests ont réussi.
```

### Comportement du programme

**Conditions d'arrêt :**
1. **Nombre d'itérations atteint** : Le programme s'arrête après le nombre spécifié
2. **Stabilisation détectée** : La grille n'évolue plus (identique à la génération précédente)
3. **Fermeture manuelle** : L'utilisateur ferme la fenêtre (mode graphique uniquement)

**Sortie du programme :**
- Code retour `0` : Exécution réussie
- Code retour `1` : Erreur (fichier introuvable, format invalide, etc.)

---

##  Format du fichier de grille

### Structure générale

Le fichier d'entrée suit un format texte simple :
```
hauteur largeur [mode_torique]
valeur valeur valeur ...
valeur valeur valeur ...
...
```

### Spécifications détaillées

**Ligne 1 : En-tête**
```
hauteur largeur [T/F]
```
- `hauteur` : Nombre de lignes de la grille (entier positif)
- `largeur` : Nombre de colonnes de la grille (entier positif)
- `T` ou `F` : **Optionnel** - Mode torique activé (`T`) ou désactivé (`F`)
  - Si absent, mode non-torique par défaut

**Lignes suivantes : Matrice de cellules**

Chaque ligne contient `largeur` valeurs séparées par des espaces :
- `0` : Cellule morte
- `1` : Cellule vivante
- `2` : Obstacle (extension)

### Exemples de fichiers

**Exemple 1 : Planeur simple (5×5)**
```
5 5 F
0 0 0 0 0
0 0 1 0 0
0 0 0 1 0
0 1 1 1 0
0 0 0 0 0
```
→ Le motif "planeur" classique qui se déplace en diagonale

**Exemple 2 : Bloc stable (4×4)**
```
4 4
0 0 0 0
0 1 1 0
0 1 1 0
0 0 0 0
```
→ Un carré 2×2 qui ne bouge jamais (configuration stable)

**Exemple 3 : Clignotant (5×5)**
```
5 5 F
0 0 0 0 0
0 0 1 0 0
0 0 1 0 0
0 0 1 0 0
0 0 0 0 0
```
→ Oscille entre vertical et horizontal (période 2)

**Exemple 4 : Grille torique avec obstacles (10×10)**
```
10 10 T
0 0 0 0 0 0 0 0 0 2
0 0 0 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0 0
0 0 0 0 1 0 0 0 0 0
0 0 1 1 1 0 0 0 0 0
0 0 0 0 0 0 0 0 0 2
2 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0
```
→ Planeur dans une grille torique avec des obstacles rouges dans les coins

**Exemple 5 : Pulsar (17×17)**
```
17 17 F
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0
0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
0 0 1 0 0 0 0 1 0 1 0 0 0 0 1 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 1 1 1 0 0 0 1 1 1 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
```
→ Le pulsar, un oscillateur de période 3

### Règles de formatage

 **Espaces entre valeurs** : Obligatoires (séparateur)  
 **Lignes vides** : Ignorées  
 **Lignes commençant par `#`** : Commentaires ignorés  
 **Dimensions** : Doivent correspondre exactement à la matrice fournie  
 **Valeurs invalides** : Toute valeur autre que 0, 1, 2 est traitée comme 0

### Validation du fichier

Le programme vérifie automatiquement :
- Existence du fichier
- Format de l'en-tête (hauteur, largeur valides)
- Cohérence entre dimensions déclarées et contenu
- Valeurs de cellules valides

En cas d'erreur, un message explicite est affiché :
```
[ERREUR] Impossible d'ouvrir le fichier: grille.txt
[ERREUR] Dimensions invalides dans le fichier
[ERREUR] Nombre de lignes incorrect dans le fichier
```

---

## 📂 Structure du projet

### Organisation des fichiers
```
jeu-de-la-vie/
│
├── main.cpp                       # Point d'entrée du programme
├── Makefile                       # Script de compilation
├── README.md                      # Documentation complète
│
├── Modèle/ (NS_Modele)           # Logique métier du jeu
│   ├── Cellule.hpp                # Classe abstraite de base
│   ├── CelluleVivante.hpp         # Cellule vivante (état 1)
│   ├── CelluleVivante.cpp
│   ├── CelluleMorte.hpp           # Cellule morte (état 0)
│   ├── CelluleMorte.cpp
│   ├── CelluleObstacle.hpp        # Cellule obstacle (état 2)
│   ├── CelluleObstacle.cpp
│   ├── Grille.hpp                 # Gestion de la grille 2D
│   ├── Grille.cpp
│   ├── Regle.hpp                  # Interface des règles
│   ├── ReglesStandard.hpp         # Règles de Conway
│   ├── ReglesStandard.cpp
│   ├── Position.hpp               # Structure de position (x, y)
│   └── Position.cpp
│
├── Vue/ (NS_Vue)                  # Couche de présentation
│   ├── Affichage.hpp              # Interface d'affichage abstraite
│   ├── AffichageConsole.hpp       # Affichage textuel terminal
│   ├── AffichageConsole.cpp
│   ├── AffichageGraphique.hpp     # Affichage SFML
│   └── AffichageGraphique.cpp
│
├── Contrôleur/ (NS_Controleur)    # Logique de contrôle
│   ├── Jeu.hpp                    # Orchestration de la simulation
│   ├── Jeu.cpp
│   ├── GestionFichier.hpp         # Chargement/Sauvegarde
│   ├── GestionFichier.cpp
│   ├── FabriqueDeJeu.hpp          # Factory pattern
│   └── FabriqueDeJeu.cpp
│
├── TEST/ (NS_Test)                # Tests unitaires
│   ├── Test.hpp                   # Interface de test
│   └── Test.cpp                   # Implémentation des tests
│
├── Diagrammes UML/
│   ├── DiagrammeClasse.txt        # Diagramme de classes Mermaid
│   ├── DiagrammeActivité.txt      # Diagramme d'activité Mermaid
│   └── DiagrammeSequences.txt     # Diagramme de séquences Mermaid
│
├── Grilles/                       # Fichiers de configuration exemple
│   ├── grille.txt                 # Grille par défaut
│   ├── grille_initiale.txt        # Planeur torique avec obstacles
│   ├── grille_test_iteration.txt  # Planeur simple
│   └── test_planeur.txt           # Fichier de test
│
├── jeu_de_la_vie/                 # Dossier de sortie (généré automatiquement)
│   ├── iteration_0000.txt
│   ├── iteration_0001.txt
│   ├── iteration_0002.txt
│   └── ...
│
└── .vscode/                       # Configuration VS Code
    ├── launch.json                # Configuration de débogage
    ├── tasks.json                 # Tâches de compilation
    └── settings.json              # Paramètres projet
```

### Description des namespaces

**NS_Modele** : Contient toute la logique métier
- Représentation des cellules (hiérarchie polymorphe)
- Gestion de la grille et de ses opérations
- Définition et application des règles du jeu

**NS_Vue** : Gère l'affichage et l'interface utilisateur
- Abstraction de l'affichage (console ou graphique)
- Rendu SFML pour le mode graphique
- Affichage textuel pour le mode console

**NS_Controleur** : Orchestre le déroulement du jeu
- Boucle principale de simulation
- Chargement et sauvegarde de fichiers
- Création d'objets via le pattern Factory

**NS_Test** : Suite de tests automatisés
- Tests unitaires des règles
- Validation des configurations classiques
- Tests d'intégration

### Hiérarchie des classes principales
```
Cellule (abstract)
├── CelluleVivante
├── CelluleMorte
└── CelluleObstacle

Regle (abstract)
└── ReglesStandard

Affichage (abstract)
├── AffichageConsole
└── AffichageGraphique

Grille
├── contient → Cellule*
└── utilise → Regle*

Jeu
├── possède → Grille*
├── utilise → Regle*
├── utilise → Affichage*
└── historique → vector<Grille*>
```

---

## 🎮 Contrôles

### Mode console

Le mode console est entièrement automatisé :
- **Aucune interaction** : La simulation s'exécute automatiquement
- **Affichage séquentiel** : Chaque génération est affichée dans le terminal
- **Arrêt automatique** : Selon les conditions définies (itérations max ou stabilisation)

**Sortie console typique :**
```
Iteration 0 :
0 0 0 0 0
0 0 1 0 0
0 0 0 1 0
0 1 1 1 0
0 0 0 0 0

Iteration 1 :
0 0 0 0 0
0 1 0 1 0
0 0 1 1 0
0 0 1 0 0
0 0 0 0 0
```

### Mode graphique

Le mode graphique offre une visualisation interactive :

**Contrôles disponibles :**
- **Fermer la fenêtre (X)** : Arrête immédiatement la simulation
- **Observation passive** : Regardez l'évolution en temps réel

**Codes couleurs :**
-  **Vert** : Cellule vivante
-  **Gris foncé** : Cellule morte
-  **Rouge** : Obstacle (immuable)
-  **Noir** : Fond de grille

**Informations affichées :**
- **Titre de la fenêtre** : Affiche le numéro de l'itération courante
  - Exemple : `Jeu de la Vie - Iteration 42`
- **Grille adaptative** : Taille des cellules ajustée automatiquement selon les dimensions
- **Framerate limité** : 60 FPS pour fluidité optimale

### Conditions d'arrêt automatique

La simulation s'arrête automatiquement dans les cas suivants :

**1. Nombre maximum d'itérations atteint**
```
Limite d'iterations atteinte : 100
```

**2. Stabilisation détectée**
```
Grille stabilisee - Aucune evolution
```
→ La grille est identique à la génération précédente (configuration stable ou oscillateur de période 1)

**3. Fermeture de la fenêtre (mode graphique uniquement)**
```
[INFO] Fenêtre fermée par l'utilisateur
Arrêt demandé par l'utilisateur
```

### Paramètres d'affichage

**Mode console :**
- Pas de configuration nécessaire
- Affichage immédiat dans le terminal

**Mode graphique :**
- **Taille des cellules** : 50 pixels par défaut (ajustement automatique pour grandes grilles)
- **Délai entre itérations** : 0.2 seconde par défaut
- **Taille fenêtre** : Calculée automatiquement selon dimensions de la grille
  - Exemple : Grille 10×10 → Fenêtre 500×500 pixels

**Adaptation automatique :**
Si la grille est trop grande (> 50 000 pixels), le programme réduit automatiquement la taille des cellules :
```
[INFO] Taille de fenêtre réduite, nouvelle taille de cellule: 25px
```

---

##  Sauvegarde

### Système de sauvegarde automatique

À chaque génération, le programme enregistre automatiquement l'état de la grille dans un fichier texte.

### Organisation des fichiers de sortie

**Dossier de sauvegarde :**
```
jeu_de_la_vie/
├── iteration_0000.txt    # État initial
├── iteration_0001.txt    # Après 1 génération
├── iteration_0002.txt    # Après 2 générations
├── iteration_0003.txt
...
├── iteration_0099.txt
└── iteration_0100.txt    # Dernier état
```

Le dossier `jeu_de_la_vie/` est créé automatiquement dans le répertoire d'exécution.

### Format des fichiers de sauvegarde

Chaque fichier suit le même format que les fichiers d'entrée :
```
hauteur largeur
0 0 1 0 0
0 0 0 1 0
0 1 1 1 0
...
```

**Exemple de fichier généré :**
```
# Fichier: jeu_de_la_vie/iteration_0042.txt

5 5
0 0 0 0 0
0 0 0 1 0
0 0 0 0 1
0 0 1 1 1
0 0 0 0 0
```

### Nomenclature des fichiers

Les fichiers sont nommés avec un **format fixe à 4 chiffres** :
- `iteration_0000.txt` : 0ème génération (état initial)
- `iteration_0001.txt` : 1ère génération
- `iteration_0042.txt` : 42ème génération
- `iteration_1234.txt` : 1234ème génération

Ce format garantit un **tri alphabétique correct** et permet jusqu'à **9999 itérations**.

### Utilisation des fichiers sauvegardés

**1. Vérification visuelle de l'évolution**
```bash
cat jeu_de_la_vie/iteration_0010.txt
```

**2. Reprise d'une simulation**
```bash
./main jeu_de_la_vie/iteration_0050.txt graphique 100
```
→ Reprend la simulation à partir de la 50ème génération

**3. Comparaison de générations**
```bash
diff jeu_de_la_vie/iteration_0010.txt jeu_de_la_vie/iteration_0020.txt
```

**4. Animation externe**
Les fichiers peuvent être utilisés pour créer des animations ou analyses avec des outils externes (Python, MATLAB, etc.)

### Gestion de l'espace disque

**Taille typique par fichier :**
- Grille 10×10 : ~200 octets
- Grille 50×50 : ~5 Ko
- Grille 100×100 : ~20 Ko

**Exemple de calcul :**
- Simulation de 1000 itérations d'une grille 50×50
- Espace disque : ~5 Mo

**Nettoyage des fichiers :**
```bash
# Supprimer toutes les sauvegardes
rm -rf jeu_de_la_vie/

# Supprimer les sauvegardes anciennes uniquement
find jeu_