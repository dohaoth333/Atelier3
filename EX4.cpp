#include <iostream>
#include <string>

// Classe Client
class Client {
private:
    int id;
    std::string nom;
    std::string prenom;

public:
    // Constructeur par défaut (client vide)
    Client() : id(0), nom(""), prenom("") {}

    // Constructeur avec valeurs initiales
    Client(int id, const std::string& nom, const std::string& prenom)
        : id(id), nom(nom), prenom(prenom) {}

    // Constructeur de copie (copie superficielle, car les attributs sont simples)
    Client(const Client& autre) : id(autre.id), nom(autre.nom), prenom(autre.prenom) {}

    // Destructeur (non indispensable ici car pas de ressources dynamiques, mais bon pratique)
    ~Client() {
        std::cout << "Destruction du client : " << nom << " " << prenom << std::endl;
    }

    // Méthode pour afficher les informations du client
    void afficher() const {
        std::cout << "Client ID: " << id << ", Nom: " << nom << ", Prenom: " << prenom << std::endl;
    }

    // Getters (pour accès depuis Compte)
    int getId() const { return id; }
    std::string getNom() const { return nom; }
    std::string getPrenom() const { return prenom; }
};

// Classe Compte
class Compte {
private:
    int numero;
    float solde;
    Client* client;  // Pointeur vers un client (possédé par le compte)
    static int nombreTotalComptes;  // Variable statique pour compter les comptes

public:
    // Constructeur par défaut
    Compte() : numero(0), solde(0.0f), client(nullptr) {
        nombreTotalComptes++;
    }

    // Constructeur avec paramètres
    Compte(int numero, float solde, Client* client)
        : numero(numero), solde(solde), client(client) {
        nombreTotalComptes++;
    }

    // Constructeur de copie (copie profonde pour le client)
    Compte(const Compte& autre)
        : numero(autre.numero), solde(autre.solde), client(new Client(*autre.client)) {
        nombreTotalComptes++;
    }

    // Destructeur : libère la mémoire du client associé
    ~Compte() {
        delete client;
        nombreTotalComptes--;
        std::cout << "Destruction du compte numero : " << numero << std::endl;
    }

    // Méthode pour afficher les informations du compte
    void afficher() const {
        std::cout << "Compte Numero: " << numero << ", Solde: " << solde;
        if (client) {
            std::cout << ", Client: ";
            client->afficher();
        } else {
            std::cout << ", Aucun client associe" << std::endl;
        }
    }

    // Méthode statique pour afficher le nombre total de comptes
    static void afficherNombreTotalComptes() {
        std::cout << "Nombre total de comptes existants : " << nombreTotalComptes << std::endl;
    }

    // Getter pour solde (pour calculInteret)
    float getSolde() const { return solde; }

    // Setter pour solde (après calcul d'intérêts)
    void setSolde(float nouveauSolde) { solde = nouveauSolde; }
};

// Initialisation de la variable statique
int Compte::nombreTotalComptes = 0;

// Fonction utilitaire calculInteret (inline car simple et potentiellement appelée plusieurs fois)
inline float calculInteret(float solde, float taux) {
    return solde * (1 + taux / 100.0f);
}

// Programme principal
int main() {
    std::cout << "=== Creation de clients et comptes ===" << std::endl;
    Client* client1 = new Client(1, "Dupont", "Jean");
    Client* client2 = new Client(2, "Martin", "Marie");

    Compte compte1(101, 1000.0f, client1);
    Compte compte2(102, 2000.0f, client2);
    Compte compte3(103, 1500.0f, new Client(3, "Durand", "Paul"));

    compte1.afficher();
    compte2.afficher();
    compte3.afficher();
    Compte::afficherNombreTotalComptes();  // Devrait afficher 3

    std::cout << "\n=== Copie de comptes ===" << std::endl;
    Compte compte1Copie = compte1;  // Test constructeur de copie
    Compte compte2Copie(compte2);   // Autre façon
    compte1Copie.afficher();
    compte2Copie.afficher();
    Compte::afficherNombreTotalComptes();  // Devrait afficher 5

    std::cout << "\n=== Suppression de comptes ===" << std::endl;
    {
        Compte compteTemp(104, 500.0f, new Client(4, "Test", "Temp"));
        Compte::afficherNombreTotalComptes();  // Devrait afficher 6
    }  // compteTemp est détruit ici, nombreTotalComptes décrémenté
    Compte::afficherNombreTotalComptes();  // Devrait afficher 5

    std::cout << "\n=== Application d'interets ===" << std::endl;
    float taux = 5.0f;  // 5%
    compte1.setSolde(calculInteret(compte1.getSolde(), taux));
    compte2.setSolde(calculInteret(compte2.getSolde(), taux));
    std::cout << "Apres interets :" << std::endl;
    compte1.afficher();
    compte2.afficher();

    std::cout << "\n=== Fin du programme ===" << std::endl;
    Compte::afficherNombreTotalComptes();  // Devrait afficher 5, puis décrémenter à 0 lors de la destruction

    return 0;
}