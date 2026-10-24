#include <iostream>
#include <string>

using namespace std;

class Etudiant {
private:
    string nom;
    string cin;
    double note1;
    double note2;
    double note3;

public:
    Etudiant() {
        nom = "Inconnu";
        cin = "000000000000000";
        note1 = 0.0;
        note2 = 0.0;
        note3 = 0.0;
    }

    
    Etudiant(string n, string c, double n1, double n2, double n3) {
        nom = n;
        cin = c;
        note1 = n1;
        note2 = n2;
        note3 = n3;
    }

    string getNom() {
        return nom;
    }

    string getCin() {
        return cin;
    }

    double getNote1() {
        return note1;
    }

    double getNote2() {
        return note2;
    }

    double getNote3() {
        return note3;
    }

    void setNom(string n) {
        nom = n;
    }

    void setCin(string c) {
        cin = c;
    }

    void setNote1(double n) {
        if (n >= 0 && n <= 20) {
            note1 = n;
        } else {
            cout << "Erreur: Note 1 invalide (" << n << ").Elle doit etre entre 0 et 20." << endl;
        }
    }

    void setNote2(double n) {
        if (n >= 0 && n <= 20) {
            note2 = n;
        } else {
            cout << "Erreur: Note 2 invalide (" << n << ").Elle doit etre entre 0 et 20." << endl;
        }
    }

    void setNote3(double n) {
        if (n >= 0 && n <= 20) {
            note3 = n;
        } else {
            cout << "Erreur: Note 3 invalide (" << n << ") ! Elle doit etre entre 0 et 20." << endl;
        }
    }

    double calculerMoyenne() {
        double moyenne = (note1 + note2 + note3) / 3.0;
        return moyenne;
    }
};

int main() {
    cout << "TEST DE LA CLASSE ETUDIANT" << endl << endl;

    Etudiant e1;
    e1.setNom("Alice Dupont");
    e1.setCin("123456789012345");
    e1.setNote1(15.5);
    e1.setNote2(12.0);
    e1.setNote3(18.5);

    cout << "Étudiant 1 : " << e1.getNom() << endl;
    cout << "CIN : " << e1.getCin() << endl;
    cout << "Moyenne : " << e1.calculerMoyenne() << endl << endl;

    cout << "Test de securite (Mise a 25.0 de la Note 1)" << endl;
    e1.setNote1(25.0);
    cout << "Note 1 apres la tentative : " << e1.getNote1() << endl << endl;

    Etudiant e2("Bob Martin", "987654321098765", 10.0, 14.0, 16.0);

    cout << "Étudiant 2 : " << e2.getNom() << endl;
    cout << "CIN : " << e2.getCin() << endl;
    cout << "Moyenne : " << e2.calculerMoyenne() << endl;

    return 0;
}