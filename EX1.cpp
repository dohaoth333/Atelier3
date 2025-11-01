#include <iostream>
#include <vector>
#include <stdexcept>

class Pile {
private:
    std::vector<int> elements; 
public:
    // Constructeur par défaut : initialise une pile vide
    Pile() {}
    // Empiler un élément sur la pile
    void push(int value) {
        elements.push_back(value);
    }
    // Dépiler un élément de la pile
    // Retourne l'élément dépilé, lève une exception si la pile est vide
    int pop() {
        if (elements.empty()) {
            throw std::out_of_range("Erreur : tentative de dépiler une pile vide");
        }
        int topElement = elements.back();
        elements.pop_back();
        return topElement;
    }
    // Méthode optionnelle pour vérifier si la pile est vide (utile pour le test)
    bool isEmpty() const {
        return elements.empty();
    }
    // Méthode optionnelle pour obtenir la taille de la pile
    size_t size() const {
        return elements.size();
    }
};
int main() {
    // Création de deux piles p1 et p2
    Pile p1;
    Pile p2;
    // Empilage de valeurs sur p1
    std::cout << "Empilage sur p1 : 10, 20, 30" << std::endl;
    p1.push(10);
    p1.push(20);
    p1.push(30);
    // Empilage de valeurs sur p2
    std::cout << "Empilage sur p2 : 100, 200" << std::endl;
    p2.push(100);
    p2.push(200);
    // Dépilage et vérification pour p1
    std::cout << "Dépilage de p1 :" << std::endl;
    while (!p1.isEmpty()) {
        std::cout << "Dépilé : " << p1.pop() << std::endl;
    }
    // Dépilage et vérification pour p2
    std::cout << "Dépilage de p2 :" << std::endl;
    while (!p2.isEmpty()) {
        std::cout << "Dépilé : " << p2.pop() << std::endl;
    }
    // Test de dépilage sur une pile vide (pour vérifier la gestion d'erreur)
    try {
        std::cout << "Tentative de dépilage sur p1 vide : " << p1.pop() << std::endl;
    } catch (const std::out_of_range& e) {
        std::cout << e.what() << std::endl;
    }
    return 0;
}