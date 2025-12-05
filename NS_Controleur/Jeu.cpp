#include "Jeu.hpp"
#include "Grille.hpp"
#include "Regle.hpp"
#include "Affichage.hpp"
#include "AffichageGraphique.hpp"
#include "GestionFichier.hpp"
#include <iostream>

namespace NS_Controleur { //Début du namespace 

    Jeu::Jeu(NS_Modele::Grille* g, NS_Modele::Regle* r, NS_Vue::Affichage* a, int nbIterations) 
        : grille(g), regle(r), affichage(a), iterationCourante(0), iterationsMax(nbIterations) {} //Constructeur : inialise la grille, la règle, l'affichage et le compteur d'itérations

    Jeu::~Jeu() { //Destructeur du jeu
        delete grille; //Libère la grille
        delete regle; //Libère la règle 
        delete affichage; //Libère l'affichage
        for (NS_Modele::Grille* g : grillesPrecedentes) { //Parcourt les anciennes grilles
            delete g; //Libère chaque copie sauvegardée
        }
    }

    void Jeu::initialiser() { //Initialise le jeu
        affichage->initialiser(); //Initialise l'affichage
        affichage->afficher(grille, 0); //Affiche la grille de départ (itération 0)
    }

    void Jeu::executer() { //Boucle principale du jeu
        while (!doitArreter()) { //Continue tant que le jeu ne doit pas s'arrêter
            etape(); //Effectue une étape de jeu
        }

        if (iterationCourante >= iterationsMax) { //Si la limite d'itérations est atteinte
            affichage->afficherMessage("Limite d'iterations atteinte : " + std::to_string(iterationsMax)); //Message correspondant
        } else if (estStable()) { //Si la grille ne change plus
            affichage->afficherMessage("Grille stabilisee - Aucune evolution"); //Message de stabilité
        }
        
        affichage->nettoyer(); //Nettoie / termine l'affichage
    }

    void Jeu::etape() { //Effectue une étape du jeu
        grillesPrecedentes.push_back(grille->clone()); //Sauvegarde un clone de la grille actuelle
        grille->mettreAJour(regle); //Met à jour la grille selon la règle
        iterationCourante++; //Incrémente le compteur d'itérations
        sauvegarderIterationCourante(); //Sauvegarde la grile dans un fichier
        affichage->afficher(grille, iterationCourante); //Affiche la nouvelle grille
    }

    bool Jeu::doitArreter() { //Vérifie si le jeu dois s'arrêter
        NS_Vue::AffichageGraphique* affichageGraph = 
            dynamic_cast<NS_Vue::AffichageGraphique*>(affichage); //Vérifier si l'affichage est graphique
        
        if (affichageGraph && affichageGraph->estFermee()) { //Si la fenêtre a été fermée par l'utilisateur
            std::cout << " Arrêt demandé par l'utilisateur" << std::endl; //Message
            return true; //Le jeu doit s'arrêter
        }
        
        if (iterationCourante >= iterationsMax) { //Si max d'itérations atteint
            return true; //Le jeu doit s'arrêter
        }
        
        if (estStable()) { //Si la grille est stable
            return true; //Arrêt
        }
        
        return false; //Sinon, continuer le jeu
    }

    bool Jeu::estStable() { //Vérifie si la grille est stable
        if (grillesPrecedentes.empty()) { //Si aucune grille précedente enregistrée
            return false; //Impossible de comparer
        }
        
        NS_Modele::Grille* derniere = grillesPrecedentes.back(); //Dernière grille actuelle
        return grille->estIdentique(derniere); //Retourne la valeur
    }

    int Jeu::getIteration() const { //Guetter de l'itération actuelle
        return iterationCourante; //Retourne la valeur
    }

    void Jeu::sauvegarderIterationCourante() { //Sauvegarde de l'itération 
        std::string dossier = "jeu_de_la_vie"; //Nom du dossier de sortie 
        GestionFichier::sauvegarderGrille(dossier, grille, iterationCourante); //Sauvegarde
    }

}