#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

using namespace std;
class Filiere;
class Etudiant {
private:
    string nom;
    string cin;
    double note1, note2, note3;
    Filiere* filiere; 

public:
    Etudiant() : nom("Inconnu"), cin("000000000000000"), note1(0), note2(0), note3(0), filiere(nullptr) {}

    Etudiant(string n, string c, double n1, double n2, double n3) 
        : nom(n), cin(c), note1(n1), note2(n2), note3(n3), filiere(nullptr) {}

    string getNom() const { return nom; }
    string getCin() const { return cin; }
    double getNote1() const { return note1; }
    double getNote2() const { return note2; }
    double getNote3() const { return note3; }
    Filiere* getFiliere() const { return filiere; }

    void setNom(string n) { nom = n; }
    void setCin(string c) { cin = c; }
    
    void setNote1(double n) {
        if (n >= 0 && n <= 20) note1 = n;
        else cout << "Erreur: Note 1 invalide !" << endl;
    }
    void setNote2(double n) {
        if (n >= 0 && n <= 20) note2 = n;
        else cout << "Erreur: Note 2 invalide !" << endl;
    }
    void setNote3(double n) {
        if (n >= 0 && n <= 20) note3 = n;
        else cout << "Erreur: Note 3 invalide !" << endl;
    }

    void setFiliere(Filiere* f) {
        filiere = f;
    }

    double calculerMoyenne() const {
        return (note1 + note2 + note3) / 3.0;
    }

    void changerDeFiliere(Filiere* nouvelleFiliere);
};

class Filiere {
private:
    string nomFiliere;
    vector<Etudiant*> etudiants;

public:
    Filiere(string nom) : nomFiliere(nom) {}
    ~Filiere() {
        for (auto e : etudiants) {
            delete e;
        }
        etudiants.clear();
    }

    string getNomFiliere() const {
        return nomFiliere;
    }

    void inscrireEtudiant(Etudiant* e) {
        if (e == nullptr) {
            throw invalid_argument("Erreur: Impossible d'inscrire un etudiant nul !");
        }
        for (const auto et : etudiants) {
            if (et == e) {
                throw runtime_error("Erreur: Cet etudiant est deja inscrit dans cette filiere !");
            }
        }
        if (e->getFiliere() != nullptr && e->getFiliere() != this) {
            throw runtime_error("Erreur: Cet etudiant appartient deja a une autre filiere !");
        }

        etudiants.push_back(e);
        e->setFiliere(this);
    }

    void retirerEtudiant(Etudiant* e) {
        auto it = find(etudiants.begin(), etudiants.end(), e);
        if (it != etudiants.end()) {
            (*it)->setFiliere(nullptr);
            etudiants.erase(it);
        }
    }

    int getNombreEtudiants() const {
        return etudiants.size();
    }
    void afficherTous() const {
        cout << "Etudiants de la filiere " << nomFiliere << " :" << endl;
        if (etudiants.empty()) {
            cout << "  (Aucun etudiant inscrit)" << endl;
        } else {
            for (const auto e : etudiants) {
                cout << "  - " << e->getNom() << " (Moyenne: " << e->calculerMoyenne() << ")" << endl;
            }
        }
    }
};

void Etudiant::changerDeFiliere(Filiere* nouvelleFiliere) {
    if (nouvelleFiliere == nullptr) {
        cerr << "Erreur: Nouvelle filiere invalide." << endl;
        return;
    }

    if (filiere != nullptr) {
        filiere->retirerEtudiant(this);
    }

    nouvelleFiliere->inscrireEtudiant(this);
    
    filiere = nouvelleFiliere;
    
    cout << ">> " << nom << " a change de filiere avec succes." << endl;
}

int main() {
    cout << "TEST DES ASSOCIATIONS ET GESTION DES EXCEPTIONS" << endl << endl;

    try {
        Filiere* f1 = new Filiere("Informatique");
        Filiere* f2 = new Filiere("Mathematiques");

        Etudiant* e1 = new Etudiant("Alice", "123", 15.0, 16.0, 17.0);
        Etudiant* e2 = new Etudiant("Bob", "456", 10.0, 12.0, 14.0);
        Etudiant* e3 = new Etudiant("Charlie", "789", 18.0, 19.0, 20.0);

        f1->inscrireEtudiant(e1);
        f1->inscrireEtudiant(e2);
        f1->inscrireEtudiant(e3);

        f1->afficherTous();
        cout << "Nombre d'etudiants dans f1 : " << f1->getNombreEtudiants() << endl << endl;

        cout << "Test de changement de filiere pour Alice" << endl;
        e1->changerDeFiliere(f2);
        
        cout << "\nApres le changement :" << endl;
        f1->afficherTous();
        cout << endl;
        f2->afficherTous();
        cout << endl;

        cout << "Test d'exception" << endl;
        f1->inscrireEtudiant(e2); 

        delete f1;
        delete f2;

    } catch (const exception& ex) {
        cerr << "\n[EXCEPTION ATTRAPPEE] : " << ex.what() << endl;
    }

    return 0;
}