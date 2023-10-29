#include <iostream>
#include <string.h>
#include <cstring>
using namespace std;

// am ales domeniul MeDical cu obiectele medicamente, pacienti, aparatura medicala

class Medicament{
private:
    string nume;
    float pretCutie; 
    const int id; // atribut constant
    static int contor; // atribut static, contor al medicamentelor administrate per total
    int nrIngrediente;
    string* ingredientePrincipale;

public:
    // declaratia de prietenie a functiei globale de modificare a pretului
    friend void modificaPretMedicament(Medicament& medicament, float pretNou);

    // Constructor fara parametri
    Medicament(): id(0){
        this->nume = "Paracetamol";
        this->pretCutie = 10;
        this->nrIngrediente = 3;
        this->ingredientePrincipale = new string[nrIngrediente];
        this->ingredientePrincipale[0] = "N-acetil-4-aminofenol";
        this->ingredientePrincipale[1] = "Celuloză microcristalină";
        this->ingredientePrincipale[2] = "Amidon pregelatinizat";
        this->contor++;
    }

    // Constructor cu 4 parametri
    Medicament(string nume, float pretCutie, int nrIngrediente, string* ingrediente)
    : nume(nume), pretCutie(pretCutie), id(contor), nrIngrediente(nrIngrediente) {
        this->ingredientePrincipale = new string[nrIngrediente];
        for (int i = 0; i < nrIngrediente; i++) {
            this->ingredientePrincipale[i] = ingrediente[i];
        }
        this->contor++;
    }

    // Constructor cu 3 parametri
    Medicament(string nume, float pretCutie, string* ingrediente): nume(nume), pretCutie(pretCutie), id(contor), nrIngrediente(3), ingredientePrincipale(nullptr) {
        ingredientePrincipale = new string[nrIngrediente];
        for (int i = 0; i < nrIngrediente; i++)
            ingredientePrincipale[i] = ingrediente[i];
        this->contor++;
    }

    void afisare(){
        cout << "Numele medicamentului: " << this->nume << "\nPret cutie: " << this->pretCutie << "\nID: " << this->id << "\nAcesta contine "<<this->nrIngrediente<<" ingrediente principale: ";
        for (int i = 0; i < this->nrIngrediente - 1; i++)
            cout << this->ingredientePrincipale[i] << ", ";
        cout << this->ingredientePrincipale[nrIngrediente - 1] << ".\n";
    }

    // Functia statica de calcul
    static double calculareDozaRecomandata(double greutate, double concentratie){
        return greutate * concentratie;
    }

     // Constructor de copiere
    Medicament(const Medicament& medicament) : id(contor) {
        nume = medicament.nume;
        pretCutie = medicament.pretCutie;
        nrIngrediente = medicament.nrIngrediente;
        ingredientePrincipale = new string[nrIngrediente];
        for (int i = 0; i < nrIngrediente; i++) {
            ingredientePrincipale[i] = medicament.ingredientePrincipale[i];
        }
        contor++;
    }

    // Metode de acces
    string getNume() const {
        return nume;
    }

    float getPretCutie() const {
        return pretCutie;
    }

    int getId() const {
        return id;
    }

    int getNrIngrediente() const {
        return nrIngrediente;
    }

    string* getIngredientePrincipale() const {
        return ingredientePrincipale;
    }

    static int getContor() {
        return contor;
    }

    // Metode de modificare
    void setNume(const string& nume) {
        this->nume = nume;
    }

    void setPretCutie(float pretCutie) {
        this->pretCutie = pretCutie;
    }

    // destructorul 
    ~Medicament(){
        if (ingredientePrincipale != nullptr) {
            delete[] ingredientePrincipale;
            ingredientePrincipale = nullptr;
        }
    }
};
int Medicament::contor = 0;
// functia prietena cu clasa Medicament
void modificaPretMedicament(Medicament& medicament, float pretNou) {
    medicament.setPretCutie(pretNou);
}

class Pacient{
private:
    string nume;
    int varsta;
    string nrTelefon;
    static int contorFisePacienti;
    const long CNP;
    int nrAfectiuni;
    string* afectiuni;

public: 
    // Constructor fara parametri
    Pacient(): CNP(7394826157){
        this->nume = "Ion Popescu";
        this->varsta=21;
        this->nrTelefon="0712345678";
        this->nrAfectiuni=2;
        afectiuni = new string[nrAfectiuni];
        afectiuni[0] = "Astm";
        afectiuni[1] = "Insuficienta cardiaca";
        this->contorFisePacienti++;
    }

    // Constructor cu 2 parametri
    Pacient(string nume, int varsta): nume(nume), varsta(varsta), CNP(6848562849){
        this->nrTelefon= "07987654434";
        this->nrAfectiuni = 1;
        afectiuni = new string[nrAfectiuni];
        afectiuni[0] = "Hernie de disc";
        this->contorFisePacienti++;
    }

    // Constructor cu 1 parametru
    Pacient(string nume) : nume(nume), CNP(37585939576){
        this->varsta=17;
        this->nrTelefon="0712345678";
        this->nrAfectiuni=3;
        afectiuni = new string[nrAfectiuni];
        afectiuni[0] = "Pneumonie";
        afectiuni[1] = "Astm";
        afectiuni[2] = "Hipotensiune";
        this->contorFisePacienti++;
    }
    
     // Constructor de copiere
    Pacient(const Pacient& pacient) : CNP(pacient.CNP) {
        nume = pacient.nume;
        varsta = pacient.varsta;
        nrTelefon = pacient.nrTelefon;
        nrAfectiuni = pacient.nrAfectiuni;
        afectiuni = new string[nrAfectiuni];
        for (int i = 0; i < nrAfectiuni; i++) {
            afectiuni[i] = pacient.afectiuni[i];
        }
        contorFisePacienti++;
    }

    // Metode de acces
    string getNume() const {
        return nume;
    }

    int getVarsta() const {
        return varsta;
    }

    string getNrTelefon() const {
        return nrTelefon;
    }

    long getCNP() const {
        return CNP;
    }

    int getNrAfectiuni() const {
        return nrAfectiuni;
    }

    string* getAfectiuni() const {
        return afectiuni;
    }

    // Metode de modificare
    void setNume(const string& nume) {
        this->nume = nume;
    }

    void setVarsta(int varsta) {
        this->varsta = varsta;
    }

    void setNrTelefon(const string& nrTelefon) {
        this->nrTelefon = nrTelefon;
    }

    void afisare() {
        cout << "Pacient: " << this->nume << "\nVarsta: " << this->varsta << " ani\nCNP: " << this->CNP << "\nNr. telefon: " << this->nrTelefon << "\nAcesta sufera de " << this->nrAfectiuni << "afectiuni:\n";
        for (int i = 0; i < this->nrAfectiuni - 1; i++)
            cout << i+1<<". "<< this->afectiuni[i] << ",\n";
        cout << this->nrAfectiuni<<". "<< this->afectiuni[nrAfectiuni - 1] << ".\n\n";
    }

    // functie statica
    static int GetTotalPacienti() {
        return contorFisePacienti;
    }

    // destructorul
    ~Pacient(){
        if (afectiuni != NULL) {
            delete[] afectiuni;
            afectiuni = NULL;
        }
    }
};
int Pacient::contorFisePacienti = 0;

class Aparatura{
private: 
    string denumire;
    int pret;
    string sectie;
    static float TVA;
    const string marca;
    int nrMediciCareFolosescAparatul;
    string* numeMediciCareFolosescAparatul;


public:
    // declaratia de prietenie a functiei globalr
    friend void afisareAparatura(const Aparatura& aparat);

    //Constructor fara parametri
    Aparatura(): marca("Comen"){
        this->denumire = "Electrocardiograf";
        this->pret = 13000;
        this->sectie="Cardiologie";
        this->nrMediciCareFolosescAparatul = 2;
        numeMediciCareFolosescAparatul = new string[nrMediciCareFolosescAparatul];
        numeMediciCareFolosescAparatul[0] = "Dr. Ionel Popescu";
        numeMediciCareFolosescAparatul[1] = "Dr. Ioana Popa";
    }

    // Constructor cu 1 parametru
    Aparatura(string denumire): denumire(denumire), marca("Potec"){
        this->pret = 40000;
        this->sectie="Oftalmologie";
        this->nrMediciCareFolosescAparatul = 1;
        numeMediciCareFolosescAparatul = new string[nrMediciCareFolosescAparatul];
        numeMediciCareFolosescAparatul[0] = "Dr. Marcela Ionescu";
    }

    // Constructor cu 2 parametri
    Aparatura(string denumire, int pret): denumire(denumire), pret(pret), marca("Anke"){
        this->sectie="Radiologie";
        this->nrMediciCareFolosescAparatul = 3;
        numeMediciCareFolosescAparatul = new string[nrMediciCareFolosescAparatul];
        numeMediciCareFolosescAparatul[0] = "Dr. Andrei Popa";
        numeMediciCareFolosescAparatul[1] = "Dr. Alexandru Ionescu";
        numeMediciCareFolosescAparatul[2] = "Dr. Alisa Marinescu";
    }

    static void setTVA(float TVAnou) { 
        TVA = TVAnou;
    }
    
    // Constructor de copiere
    Aparatura(const Aparatura& aparatura) : marca(aparatura.marca) {
        denumire = aparatura.denumire;
        pret = aparatura.pret;
        sectie = aparatura.sectie;
        TVA = aparatura.TVA;
        nrMediciCareFolosescAparatul = aparatura.nrMediciCareFolosescAparatul;
        numeMediciCareFolosescAparatul = new string[nrMediciCareFolosescAparatul];
        for (int i = 0; i < nrMediciCareFolosescAparatul; i++) {
            numeMediciCareFolosescAparatul[i] = aparatura.numeMediciCareFolosescAparatul[i];
        }
    }

    // metode de acces
    string getDenumire() const {
        return denumire;
    }

    int getPret() const {
        return pret;
    }

    string getSectie() const {
        return sectie;
    }

    static float getTVA() {
        return TVA;
    }

    string getMarca() const {
        return marca;
    }

    int getNrMediciCareFolosescAparatul() const {
        return nrMediciCareFolosescAparatul;
    }

    string* getNumeMediciCareFolosescAparatul() const {
        return numeMediciCareFolosescAparatul;
    }

    // metode de modificare
    void setDenumire(const string& denumire) {
        this->denumire = denumire;
    }

    void setPret(int pret) {
        this->pret = pret;
    }

    void setSectie(const string& sectie) {
        this->sectie = sectie;
    }
    // destructorul
    ~Aparatura() {
        if (numeMediciCareFolosescAparatul != NULL){
            delete[] numeMediciCareFolosescAparatul;
            numeMediciCareFolosescAparatul = NULL;
        }
    }
};
float Aparatura::TVA = 0.19;
// functia prietena cu clasa Aparatura
void afisareAparatura(const Aparatura& aparat) {
    cout << "Denumire aparat: " << aparat.denumire << "\nPret: " << aparat.pret << "\nSectie: " << aparat.sectie << "\nTVA: " << aparat.TVA << "\nMarca: " << aparat.marca << "\nMedicii care pot folosi aparatul sunt urmatorii: ";
    for (int i = 0; i < aparat.nrMediciCareFolosescAparatul - 1; i++)
        cout <<aparat.numeMediciCareFolosescAparatul[i] << ", ";
    cout << aparat.numeMediciCareFolosescAparatul[aparat.nrMediciCareFolosescAparatul - 1] << ".\n";
}

int main() {
    // Pentru Medicament
    {
    // creez medicamentele cu constructorii
    Medicament medicament1; // Constructor fără parametri
    string ingrediente2[] = { "Ibuprofen", "Croscarmeloză sodică", "Celuloză microcristalină", "Amidon de porumb pregelatinizat" };
    Medicament medicament2("Nurofen", 15.0, 4, ingrediente2); // Constructor cu 4 parametri
    string ingrediente3[] = {"Desloratadină", "Amidon pregelatinizat", "Stereat de magneziu"};
    Medicament medicament3("Aerius", 20.0, ingrediente3); // Constructor cu 3 parametri

    // afisez cele 3 obiecte Medicament + atributele lor
    modificaPretMedicament(medicament1, 12.5);
    medicament1.afisare();
    cout<<"\n";

    medicament2.afisare();
    cout<<"\n";
    
    medicament3.afisare();
    cout<<"\n";

    // Calcularea dozei recomandate pentru un exemplu
    double greutatePacient = 52; // Greutatea pacientului în kg
    double concentratieMedicament3 = 0.5; // Concentrația medicamentului 3

   double dozaRecomandata = Medicament::calculareDozaRecomandata(greutatePacient, concentratieMedicament3);
   cout << "Doza recomandata de " << medicament3.getNume() << " pentru un pacient cu greutatea de " << greutatePacient << " kg si o concentratie de " << concentratieMedicament3 << " este " << dozaRecomandata << " grame.\n\n";
    }

    // Pentru Pacient
    {
        // creez cei 3 pacienti cu constructorii
        Pacient pacient1;
        Pacient pacient2("Maria Ionescu", 30);
        Pacient pacient3("Teodor Marinescu");

        cout<<"Numarul total de pacienti este "<<Pacient::GetTotalPacienti()<<".\n";

        // afisez informatii despre cei 3 pacienti
        pacient1.afisare();
        cout<<"\n";

        pacient2.afisare();
        cout<<"\n";

        pacient3.afisare();
        cout<<"\n";
    }
   
   // Pentru Aparatura Medicala
   {
    // creez cele 3 aparate cu constructorii
        Aparatura aparat1;
        Aparatura aparat2("Autorefractor");
        Aparatura aparat3("Computer Tomograf", 40000);

    // afisez aparatele
    afisareAparatura(aparat1);
    cout<<"\n";
    afisareAparatura(aparat2);
    cout<<"\n";
    Aparatura::setTVA(0.21); // aici am folosit functia statica, crescand TVA-ul
    afisareAparatura(aparat3);

   }
   
   return 0;
}
