#include <iostream>

// Structure pour représenter un élément de la liste
struct Element {
    int valeur;          
    Element* suivant;  

    // Constructeur pour initialiser un élément
    Element(int val) : valeur(val), suivant(nullptr) {}
};

// Classe pour la liste simplement chaînée
class Liste {
private:
    Element* tete; 

public:
    // Constructeur : initialise une liste vide
    Liste() : tete(nullptr) {}

    // Destructeur : libère la mémoire de tous les éléments pour éviter les fuites
    ~Liste() {
        while (tete != nullptr) {
            Element* temp = tete;
            tete = tete->suivant;
            delete temp;
        }
    }

    // Méthode pour ajouter un élément au début de la liste
    void ajouterAuDebut(int valeur) {
        Element* nouvelElement = new Element(valeur);
        nouvelElement->suivant = tete;
        tete = nouvelElement;
    }

    // Méthode pour supprimer un élément au début de la liste
    // Retourne true si suppression réussie, false si la liste est vide
    bool supprimerAuDebut() {
        if (tete == nullptr) {
            return false; 
        }
        Element* temp = tete;
        tete = tete->suivant;
        delete temp;
        return true;
    }

    // Méthode pour afficher la liste entière
    void afficher() const {
        Element* courant = tete;
        std::cout << "Liste : ";
        while (courant != nullptr) {
            std::cout << courant->valeur << " -> ";
            courant = courant->suivant;
        }
        std::cout << "nullptr" << std::endl;
    }
};

// Programme principal pour tester la classe Liste
int main() {
    Liste maListe;

    // Ajout d'éléments au début
    std::cout << "Ajout de 10, 20, 30 au début :" << std::endl;
    maListe.ajouterAuDebut(10);
    maListe.afficher();
    maListe.ajouterAuDebut(20);
    maListe.afficher();
    maListe.ajouterAuDebut(30);
    maListe.afficher();

    // Suppression d'éléments au début
    std::cout << "\nSuppression au début :" << std::endl;
    if (maListe.supprimerAuDebut()) {
        maListe.afficher();
    }
    if (maListe.supprimerAuDebut()) {
        maListe.afficher();
    }

    // Test de suppression sur une liste vide
    std::cout << "\nTentative de suppression sur liste vide :" << std::endl;
    if (!maListe.supprimerAuDebut()) {
        std::cout << "Liste vide, rien à supprimer." << std::endl;
    }
    maListe.afficher();

    return 0;
}