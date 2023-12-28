#include <iostream>
#include <string>
#include <cstring>
#include <cmath>
#include <fstream>
#include <istream>
using namespace std;

/* Am incercat să structurez codul cât mai bine, folosind și comentarii. 
Totuși, am realizat și un README.md în care am oferit informații mai detaliate despre structura proiectului și funcționalități.
*/

// două clase abstracte care să fie moștenite de către clasele pe care le am deja de la început
// clasa abstracta Spital
class Spital{
private:
    string nume;
    string adresa;
public:
    // functii virtuale
    virtual void ePacientulMajor() = 0; // afiseaza daca pacientul este sau nu major
    virtual void istoricAfectiuni() = 0; // afiseaza numele + ce afectiuni a avut pacientul de-a lungul timpului
    virtual void eFolosit() = 0; // afiseaza daca un aparat este sau nu folosit in spital

     // constructor implicit
    Spital(){
        this->nume = "Floreasca";
        this->adresa = "Sos. Stefan cel Mare, nr. 7";
    }

    // destructor
    virtual ~Spital(){
    }
};

// clasa abstracta Farmacie
class Farmacie{
private:
    string nume;
    string adresa;

public:
    // functii virtuale
    virtual int cateIngredienteContine() = 0;
    virtual void eDecontataReteta() = 0;
    
    // constructor implicit
    Farmacie(){
        this->nume="Dr Max";
        this->adresa="Bd. Basarabilor, nr. 6";
    }

    // destructor
    virtual ~Farmacie(){
    }
};

// cele 3 clase de la început - Medicament, Pacient, Aparatura
class Medicament : public Farmacie{
private:
    string nume;
    float pretCutie; 
    const int id; // atribut constant
    static int contor; // atribut static, contor al medicamentelor administrate per total
    int nrIngrediente;
    string* ingredientePrincipale;

public:
    // functii virtuale din clasa abstracta Farmacie
    virtual int cateIngredienteContine(){
        return this->nrIngrediente;
    }

    virtual void eDecontataReteta(){
    }

    // declaratia de prietenie a functiei globale de modificare a pretului
    friend void modificaPretMedicament(Medicament& medicament, float pretNou);

    // constructor implicit
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

    // constructor cu 4 parametri
    Medicament(string nume, float pretCutie, int nrIngrediente, string* ingrediente)
    : nume(nume), pretCutie(pretCutie), id(contor), nrIngrediente(nrIngrediente) {
        this->ingredientePrincipale = new string[nrIngrediente];
        for (int i = 0; i < nrIngrediente; i++) {
            this->ingredientePrincipale[i] = ingrediente[i];
        }
        this->contor++;
    }

    // constructor cu 3 parametri
    Medicament(string nume, float pretCutie, string* ingrediente): nume(nume), pretCutie(pretCutie), id(contor), nrIngrediente(3), ingredientePrincipale(nullptr) {
        ingredientePrincipale = new string[nrIngrediente];
        for (int i = 0; i < nrIngrediente; i++)
            ingredientePrincipale[i] = ingrediente[i];
        this->contor++;
    }

    // functia membra de afisare
    void afisare() const {
        cout << "Numele medicamentului: " << this->nume << "\nPret cutie: " << this->pretCutie << "\nID: " << this->id << "\nAcesta contine "<<this->nrIngrediente<<" ingrediente principale: ";
        for (int i = 0; i < this->nrIngrediente - 1; i++)
            cout << this->ingredientePrincipale[i] << ", ";
        cout << this->ingredientePrincipale[nrIngrediente - 1] << ".\n";
    }

    // functia statica de calcul
    static double calculareDozaRecomandata(double greutate, double concentratie){
        return greutate * concentratie;
    }

     // constructor de copiere
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

    // metode de acces = getteri
    string getNume() const {
        return nume;
    }

    float getPretCutie() const {
        return pretCutie;
    }

    int getId() const {
        return this->id;
    }

    int getNrIngrediente() const {
        return this->nrIngrediente;
    }

    string* getIngredientePrincipale() const {
        return this->ingredientePrincipale;
    }   

    static int getContor() {
        return contor;
    }

    // metode de modificare = setteri
    void setNume(const string& nume) {
        this->nume = nume;
    }

    void setPretCutie(float pretCutie) {
        this->pretCutie = pretCutie;
    }

    void setIngredientePrincipale(string* ingrediente, int nrIngrediente) {
    if (ingredientePrincipale != nullptr) {
        delete[] ingredientePrincipale; // eliberez memoria alocata anterior
    }
    
    this->nrIngrediente = nrIngrediente;
    this->ingredientePrincipale = new string[nrIngrediente];
    for (int i = 0; i < nrIngrediente; ++i) {
        this->ingredientePrincipale[i] = ingrediente[i]; // aloc noul vector
    }
    }

    // destructorul 
    ~Medicament(){
        if (ingredientePrincipale != nullptr) {
            delete[] ingredientePrincipale;
        }
    }

    // supraincarcarea operatorilor
    // = atribui ingredientele princiaple ale unui medicament altuia
    Medicament& operator=(const Medicament& other) { 
        this->nrIngrediente = other.nrIngrediente;
        delete[] ingredientePrincipale; // eliberez memoria alocată anterior pentru ingredientePrincipale
        this->ingredientePrincipale = new string[nrIngrediente];
        for (int i = 0; i < nrIngrediente; i++) {
            this->ingredientePrincipale[i] = other.ingredientePrincipale[i];
        }
        return *this;
    }

    // + calculeaza suma preturilor pe cutie
    float operator+(const Medicament& other) {
        float suma;
        suma = this->pretCutie + other.pretCutie;
        return suma;
    }

    // - calculeaza diferenta de pret dintre 2 cutii din med1 si med 2
    float operator-(const Medicament& other) {
        float diferenta;
        diferenta = abs(this->pretCutie - other.pretCutie);
        return diferenta;
    }

    // == verifica daca 2 medicamente au acelasi numar de ingrediente
    bool operator==(const Medicament& other) {
        return this->nrIngrediente == other.nrIngrediente;
    }

    // >> pentru citire
    friend istream& operator>>(istream& input, Medicament& medicament) {
    cout << "Introduceti numele medicamentului: ";
    getline(input, medicament.nume);
    cout << "Introduceti pretul cutiei: ";
    input >> medicament.pretCutie;
    cout << "Introduceti numarul de ingrediente principale: ";
    input >> medicament.nrIngrediente;
    medicament.ingredientePrincipale = new string[medicament.nrIngrediente];
    cout << "Introduceti ingredientele principale:\n";
    for (int i = 0; i < medicament.nrIngrediente; ++i) {
        getline(input, medicament.ingredientePrincipale[i]);
    }
    return input;
    }

    // << pentru afisare
    friend ostream& operator<<(ostream& output, const Medicament& medicament) {
        output << "Numele medicamentului: " << medicament.nume << "\nPret cutie: " << medicament.pretCutie << "\nID: " << medicament.id << "\nAcesta contine " << medicament.nrIngrediente << " ingrediente principale: ";
        for (int i = 0; i < medicament.nrIngrediente - 1; i++)
            output << medicament.ingredientePrincipale[i] << ", ";
        output << medicament.ingredientePrincipale[medicament.nrIngrediente - 1] << ".\n";
        return output;
    }

    // >> pentru citire din fisier
    friend ifstream& operator>>(ifstream& input, Medicament& medicament) {
        input >> medicament.nume;
        input >> medicament.pretCutie;
        int val;
        input >> val;
        input >> val;
        input >> medicament.nrIngrediente;
        medicament.ingredientePrincipale = new string[medicament.nrIngrediente];
        for (int i = 0; i < medicament.nrIngrediente; i++) {
            input >> medicament.ingredientePrincipale[i];
        }
        return input;
    }

    // << pentru afisare din fisier
    friend ofstream& operator<<(ofstream& output, const Medicament& medicament) {
        output << medicament.nume << endl << medicament.pretCutie << endl << medicament.id << medicament.contor << endl << medicament.nrIngrediente;
        for (int i = 0; i < medicament.nrIngrediente - 1; i++)
            output << medicament.ingredientePrincipale[i] << " ";
        output << medicament.ingredientePrincipale[medicament.nrIngrediente - 1] << endl;
        return output;
    }
};
int Medicament::contor = 0;

// functia prietena cu clasa Medicament
void modificaPretMedicament(Medicament& medicament, float pretNou) {
    medicament.setPretCutie(pretNou);
}

class Pacient : public Spital{
private:
    string nume;
    int varsta;
    string nrTelefon;
    static int contorFisePacienti;
    const long long int CNP;
    int nrAfectiuni;
    string* afectiuni;

public: 
    // functii virtuale pentru clasa abstracta Spital
    virtual void ePacientulMajor(){
        if(this->varsta>=18)cout<<"Pacientul este major";
        else cout<<"Pacientul este minor";
    }

    virtual void istoricAfectiuni(){
        cout << "Pacientul " << this->nume << " are urmatoarele " << this->nrAfectiuni << " afectiuni:\n";
        for(int i=0;i<this->nrAfectiuni;i++)
            cout<<this->afectiuni[i]<<endl;
    }

    virtual void eFolosit(){}

    // constructor implicit
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

    // constructor cu 2 parametri
    Pacient(string nume, int varsta): nume(nume), varsta(varsta), CNP(6848562849){
        this->nrTelefon= "07987654434";
        this->nrAfectiuni = 1;
        afectiuni = new string[nrAfectiuni];
        afectiuni[0] = "Hernie de disc";
        this->contorFisePacienti++;
    }

    // constructor cu 1 parametru
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
    
    // functia de afisare
    void afisare() const {
        cout << "Pacient: " << this->nume << "\nVarsta: " << this->varsta << " ani\nCNP: " << this->CNP << "\nNr. telefon: " << this->nrTelefon << "\nAcesta sufera de " << this->nrAfectiuni << " afectiuni:\n";
        for (int i = 0; i < this->nrAfectiuni - 1; i++)
            cout << i+1<<". "<< this->afectiuni[i] << ",\n";
        cout << this->nrAfectiuni<<". "<< this->afectiuni[nrAfectiuni - 1] << ".\n\n";
    }

    // functie statica
    static int GetTotalPacienti() {
        return contorFisePacienti;
    }

    // constructor de copiere
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

    // metode de acces = getteri
    string getNume() const {
        return nume;
    }

    int getVarsta() const {
        return varsta;
    }

    string getNrTelefon() const {
        return nrTelefon;
    }

    int getContorFisePacienti() const {
        return contorFisePacienti;
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

    // metode de modificare = setteri
    void setNume(const string& nume) {
        this->nume = nume;
    }

    void setVarsta(int varsta) {
        this->varsta = varsta;
    }

    void setNrTelefon(const string& nrTelefon) {
        this->nrTelefon = nrTelefon;
    }

    void setAfectiuni(string* afectiuni, int nrAfectiuni) {
    if (this->afectiuni != nullptr) {
        delete[] this->afectiuni; // eliberez memoria alocata anterior
    }
    
    this->nrAfectiuni = nrAfectiuni;
    this->afectiuni = new string[nrAfectiuni];
    for (int i = 0; i < nrAfectiuni; ++i) {
        this->afectiuni[i] = afectiuni[i]; // aloc noul vector
    }
}


    // destructorul
    ~Pacient(){
        if (afectiuni != NULL)
            delete[] afectiuni;

    }

    // supraincarcarea operatorilor
    // = copiaza afectiunile unui pacient la altul
    Pacient& operator=(const Pacient& other) {
        delete[] this->afectiuni;
        this->afectiuni = new string[other.nrAfectiuni];
        for (int i = 0; i < other.nrAfectiuni; i++) {
            this->afectiuni[i] = other.afectiuni[i];
        }
        return *this;
    }

    // + adun numarul afectiunilor a 2 pacienti
    int operator+(const Pacient& other) {
        int suma;
        suma = this->nrAfectiuni + other.nrAfectiuni;
        return suma;
    }

    // - diferenta de varsta dintre 2 pacienti
    int operator-(const Pacient& other) {
        int diferenta;
        diferenta = abs(this->varsta - other.varsta);
        return diferenta;
    }

    // == verific daca 2 pacienti au aceeasi varsta
    bool operator==(const Pacient& other) {
        return this->varsta == other.varsta;
    }

    // >> pentru citire
    friend istream& operator>>(istream& input, Pacient& pacient) {
        cout << "Introduceti numele pacientului: ";
        input >> pacient.nume;
        cout << "Introduceti varsta pacientului: ";
        input >> pacient.varsta;
        cout << "Introduceti numarul de afectiuni: ";
        input >> pacient.nrAfectiuni;
        pacient.afectiuni = new string[pacient.nrAfectiuni];
        cout << "Introduceti afectiunile pacientului:\n";
        for (int i = 0; i < pacient.nrAfectiuni; ++i) {
            input >> pacient.afectiuni[i];
        }
        return input;
    }

    // << pentru afisare
    friend ostream& operator<<(ostream& output, const Pacient& pacient) {
        output << "Pacient: " << pacient.nume << "\nVarsta: " << pacient.varsta << " ani\nCNP: " << pacient.CNP << "\nNr. telefon: " << pacient.nrTelefon << "\nAcesta sufera de " << pacient.nrAfectiuni << " afectiuni:\n";
        for (int i = 0; i < pacient.nrAfectiuni - 1; i++)
            output << i + 1 << ". " << pacient.afectiuni[i] << ",\n";
        output << pacient.nrAfectiuni << ". " << pacient.afectiuni[pacient.nrAfectiuni - 1] << ".\n\n";
        return output;
    }

    // >> pentru citirea din fișier
    friend ifstream& operator>>(ifstream& input, Pacient& pacient) {
        input >> pacient.nume;
        input >> pacient.varsta;
        int val;
        input >> val;
        input >> val;
        input >> pacient.nrAfectiuni;
        pacient.afectiuni = new string[pacient.nrAfectiuni];
        for (int i = 0; i < pacient.nrAfectiuni; ++i) {
            input >> pacient.afectiuni[i];
        }
        return input;
    }

    // << pentru afisare in fisier
    friend ofstream& operator<<(ofstream& output, const Pacient& pacient) {
        output << pacient.nume << endl << pacient.varsta << endl << pacient.CNP << pacient.contorFisePacienti << endl << pacient.nrTelefon << endl << pacient.nrAfectiuni << endl;
        for (int i = 0; i < pacient.nrAfectiuni - 1; i++)
            output << i + 1 << endl << pacient.afectiuni[i] << " ";
        output << pacient.nrAfectiuni << " " << pacient.afectiuni[pacient.nrAfectiuni - 1] << endl;
        return output;
    }
};
int Pacient::contorFisePacienti = 0;

class Aparatura : public Spital{
private: 
    string denumire;
    float pret;
    string sectie;
    static float TVA;
    const string marca;
    int nrMediciCareFolosescAparatul;
    string* numeMediciCareFolosescAparatul;

public:
    // functii virtuale ale clasei abstracte Spital
    virtual void ePacientulMajor(){}
    virtual void istoricAfectiuni(){}

    virtual void eFolosit(){
        if(this->nrMediciCareFolosescAparatul>0)cout<<"Aparatul este folosit";
        else cout<<"Aparatul nu este folosit";
    }

    // declaratia de prietenie a functiei globale
    friend void afisareAparatura(const Aparatura& aparat);

    // constructor implicit
    Aparatura(): marca("Comen"){
        this->denumire = "Electrocardiograf";
        this->pret = 13000;
        this->sectie="Cardiologie";
        this->nrMediciCareFolosescAparatul = 2;
        numeMediciCareFolosescAparatul = new string[nrMediciCareFolosescAparatul];
        numeMediciCareFolosescAparatul[0] = "Dr. Ionel Popescu";
        numeMediciCareFolosescAparatul[1] = "Dr. Ioana Popa";
    }

    // constructor cu 1 parametru
    Aparatura(string denumire): denumire(denumire), marca("Potec"){
        this->pret = 40000;
        this->sectie="Oftalmologie";
        this->nrMediciCareFolosescAparatul = 1;
        numeMediciCareFolosescAparatul = new string[nrMediciCareFolosescAparatul];
        numeMediciCareFolosescAparatul[0] = "Dr. Marcela Ionescu";
    }

    // constructor cu 2 parametri
    Aparatura(string denumire, int pret): denumire(denumire), pret(pret), marca("Anke"){
        this->sectie="Radiologie";
        this->nrMediciCareFolosescAparatul = 3;
        numeMediciCareFolosescAparatul = new string[nrMediciCareFolosescAparatul];
        numeMediciCareFolosescAparatul[0] = "Dr. Andrei Popa";
        numeMediciCareFolosescAparatul[1] = "Dr. Alexandru Ionescu";
        numeMediciCareFolosescAparatul[2] = "Dr. Alisa Marinescu";
    }

    // functia ce modifica atributul static TVA pentru toate obiectele clasei
    static void setTVA(float TVAnou) { 
        TVA = TVAnou;
    }
    
    // constructor de copiere
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

    // metode de acces => getteri
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

    // metode de modificare => setteri
    void setDenumire(const string& denumire) {
        this->denumire = denumire;
    }

    void setPret(int pret) {
        this->pret = pret;
    }

    void setSectie(const string& sectie) {
        this->sectie = sectie;
    }

    void setNumeMediciCareFolosescAparatul(string* numeMedici, int nrMedici) {
        if(numeMediciCareFolosescAparatul != nullptr) {
            delete[] numeMediciCareFolosescAparatul; // eliberez memoria alocata anterior
        }

        this->nrMediciCareFolosescAparatul = nrMedici;
        this->numeMediciCareFolosescAparatul = new string[nrMedici];
        for (int i = 0; i < nrMedici; ++i) {
            this->numeMediciCareFolosescAparatul[i] = numeMedici[i]; // aloc noul vector
        }
    }

    // destructorul
    ~Aparatura() {
        if (numeMediciCareFolosescAparatul != nullptr)
            delete[] numeMediciCareFolosescAparatul;
    }

    // supraincarcare operatorilor
    // = atribui numele medicilor care folosesc aparatul 
    Aparatura& operator=(const Aparatura& other) {
        delete[] numeMediciCareFolosescAparatul;
        numeMediciCareFolosescAparatul = new string[other.nrMediciCareFolosescAparatul];
        for (int i = 0; i < other.nrMediciCareFolosescAparatul; i++) {
            numeMediciCareFolosescAparatul[i] = other.numeMediciCareFolosescAparatul[i];
        }
        return *this;
    }

    // + costul total al 2 aparate medicale
    float operator+(const Aparatura& other) {
        int suma;
        suma = this->pret + other.pret;
        return suma;
    }

    // - diferenta de pret dintre 2 aparate medicale
    float operator-(const Aparatura& other) {
        float diferenta;
        diferenta = abs(this->pret - other.pret);
        return diferenta;
    }

    // == verific daca 2 aparate au acelasi pret
    bool operator==(const Aparatura& other) {
        return this->pret == other.pret;
    }

    // >> pentru citire
    friend istream& operator>>(istream& input, Aparatura& aparat) {
    cout << "Introduceti denumirea aparatului: ";
    input >> aparat.denumire;
    cout << "Introduceti pretul aparatului: ";
    input >> aparat.pret;
    cout << "Introduceti sectia aparatului: ";
    input >> aparat.sectie;
    cout << "Introduceti numarul de medici care folosesc aparatul: ";
    input >> aparat.nrMediciCareFolosescAparatul;
    aparat.numeMediciCareFolosescAparatul = new string[aparat.nrMediciCareFolosescAparatul];
    cout << "Introduceti numele medicilor care folosesc aparatul:\n";
    for (int i = 0; i < aparat.nrMediciCareFolosescAparatul; ++i) {
        input >> aparat.numeMediciCareFolosescAparatul[i];
    }
    return input;
}

    // << pentru afisare
    friend ostream& operator<<(ostream& output, const Aparatura& aparat) {
        output << "Denumire aparat: " << aparat.denumire << "\nPret: " << aparat.pret << "\nSectie: " << aparat.sectie << "\nTVA: " << aparat.TVA << "\nMarca: " << aparat.marca << "\nMedicii care pot folosi aparatul sunt urmatorii: ";
        for (int i = 0; i < aparat.nrMediciCareFolosescAparatul - 1; i++)
            output << aparat.numeMediciCareFolosescAparatul[i] << ", ";
        output << aparat.numeMediciCareFolosescAparatul[aparat.nrMediciCareFolosescAparatul - 1] << ".\n";
    return output;
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

// clasa Reteta aflată în relatie de has-a cu Medicament și Pacient
class Reteta : public Farmacie {
private:
    Medicament* medicamentPrescris;
    bool decontataIntegral;
    string doctorCurant;
    Pacient beneficiar;

public:
    // functiile virtuale din clasa abstracta Farmacie
    virtual int cateIngredienteContine(){
        return 0;
    }

    virtual void eDecontataReteta(){
        if(this->decontataIntegral == 0) cout<<"Reteta nu este decontata integral:(\n";
        else cout<<"Reteta este decontata integral:)\n";
    };
    
    // constructor implicit
    Reteta() : medicamentPrescris(nullptr), decontataIntegral(false), doctorCurant(""), beneficiar() {}

    // destructor
    ~Reteta() {
        if(medicamentPrescris != NULL) 
            delete[] medicamentPrescris;
    }

    // metode de acces si de modificare pentru atributele clasei
    // getter si setter pentru medicamentPrescris
    void setMedicamentPrescris(Medicament* medicament) {
        this->medicamentPrescris = medicament;
    }

    Medicament* getMedicamentPrescris() const {
        return this->medicamentPrescris;
    }

    // getter si setter pentru decontataIntegral
    void setDecontataIntegral(bool decontata) {
        this->decontataIntegral = decontata;
    }

    bool getDecontataIntegral() const {
        return this->decontataIntegral;
    }

    // getter si setter pentru doctorCurant
    void setDoctorCurant(const string& doctor) {
        this->doctorCurant = doctor;
    }

    string getDoctorCurant() const {
        return this->doctorCurant;
    }

    // getter si setter pentru beneficiar
    void setBeneficiar(const Pacient& pacient) {
        this->beneficiar = pacient;
    }

    Pacient getBeneficiar() const {
        return this->beneficiar;
    }

    // supraincarcarea operatorilor
    // = atribuirea unui obiect altui obiect
    Reteta& operator=(const Reteta& reteta) {
        if (this != &reteta) {
            delete medicamentPrescris;
            this->medicamentPrescris = new Medicament(*reteta.medicamentPrescris);
            this->decontataIntegral = reteta.decontataIntegral;
            this->doctorCurant = reteta.doctorCurant;
            this->beneficiar = reteta.beneficiar;
        }
        return *this;
    }

    // << afisarea unui obiect
    friend ostream& operator<<(ostream& out, const Reteta& reteta) {
    out << "Medicament prescris: " << reteta.medicamentPrescris->getNume() << endl;
    out << "Decontata integral: " << boolalpha << reteta.decontataIntegral << endl;
    out << "Doctor curant: " << reteta.doctorCurant << endl;
    out << "Beneficiar: " << reteta.beneficiar.getNume() << endl;
    return out;
}


    // >> citirea unui obiect
    friend istream& operator>>(istream& in, Reteta& reteta) {
        Medicament* med = new Medicament();
        Pacient pac;
        cout << "Care dintre pacientii nostri este? "<<endl;
        in >> pac;
        reteta.setBeneficiar(pac);

        cout << "Care medicament este prescris? "<<endl;
        in >> *med;
        reteta.setMedicamentPrescris(med);

        cout << "Este decontata integral? (true/false): ";
        in >> boolalpha >> reteta.decontataIntegral;

        cout << "Medicul ce a prescris reteta: ";
        in.ignore(); // ignora newline characters din inputul anterior, deoarece daca nu fac asta nu se poate realiza citirea
        getline(in, reteta.doctorCurant);

        return in;
    }
};

// clasa PreparatFarmaceutic aflată in relatie de is-a cu Medicament, se referă la un acele medicamente care sunt preparate direct de catre farmacist in diverse concentratii de medicamente
class PreparatFarmaceutic : public Medicament{
private:
    float concentratie;
public:
    // constructor implicit
    PreparatFarmaceutic() : Medicament(), concentratie(0.0) {}

    // constructor cu 1 parametru
    PreparatFarmaceutic(string* ingredientePrincipale, int nrIngrediente):concentratie(0.1){
        this->setIngredientePrincipale(ingredientePrincipale, nrIngrediente);
    }

    // functia de afisare
    void afisare() const {
        Medicament::afisare();
        cout << "\nConcentratia preparatului farmaceutic: " << concentratie << endl;
    }

    // getteri si setteri
    float getConcentratie() const {
        return concentratie;
    }

    void setConcentratie(float concentratie) {
        this->concentratie = concentratie;
    }

    // supraincarcarea operatorului >> pentru citire
    friend istream& operator>>(istream& input, PreparatFarmaceutic& preparat) {
        // folosesc op >> supraincarcat in clasa de baza Medicament
        input >> static_cast<Medicament&>(preparat);
        
        // citesc atributele in plus ale PreparatFarmaceutic
        cout << "Concentratia preparatului farmaceutic: ";
        input >> preparat.concentratie;
        
        return input;
    }

    // destructor
    ~PreparatFarmaceutic(){
    }
};

// clasa PacientSpecial in relatie de is-a cu Pacient, se referă la acei pacienti special cu boli rare precum boala galbena
class PacientSpecial : public Pacient {
private:
    string boalaExtra;
public:
    // constructor implicit
    PacientSpecial() : Pacient(), boalaExtra("Febra Galbena") {}

    // constructorul cu 1 parametru
    PacientSpecial(string* afectiuni, int nrAfectiuni):boalaExtra("Coronavirus"){
        this->setAfectiuni(afectiuni, nrAfectiuni);
    }

    // afisare
    void afisare() const {
        Pacient::afisare();
        cout << "Boala speciala a sa: " << boalaExtra << endl;
    }

    // getteri si setteri
    string getBoalaExtra() const {
        return boalaExtra;
    }

    void setBoalaExtra(const string& boalaExtra) {
        this->boalaExtra = boalaExtra;
    }

    // supraincarcarea operatorului >> pentru citire
    friend istream& operator>>(istream& input, PacientSpecial& pacient) {
        // folosesc op >> de citire din clasa de baza Pacient
        input >> static_cast<Pacient&>(pacient);
        
        // citesc atributul in plus al PacientSpecial
        cout << "Boala speciala a pacientului: ";
        input >> pacient.boalaExtra;
        
        return input;
    }

    // destructor
    ~PacientSpecial(){
    }
};


// FISIERE BINARE
// afisarea obiectelor de tip Medicament in fisierul binar medicament.bin
void afisareBinaraMedicament()
{
    Medicament m1;

    string nume = m1.getNume();
    float pretCutie = m1.getPretCutie();
    int contor = m1.getContor(); //static
    float id = m1.getId(); // const
    int nrIngrediente = m1.getNrIngrediente();
    int sizeNume = nume.length();
    string* ingredientePrincipale = new string[nrIngrediente];
    for (int i = 0; i < nrIngrediente; i++)
        ingredientePrincipale[i] = m1.getIngredientePrincipale()[i];

    ifstream afisareBinaraMedicament("medicament.bin", ios::binary);

    if (afisareBinaraMedicament.is_open())
    {
        afisareBinaraMedicament.read((char*)&sizeNume, sizeof(int));
        nume.resize(sizeNume);
        afisareBinaraMedicament.read(&nume[0], sizeNume);

        afisareBinaraMedicament.read((char*)&pretCutie, sizeof(float));
        afisareBinaraMedicament.read((char*)&contor, sizeof(int));
        afisareBinaraMedicament.read((char*)&id, sizeof(int));
        afisareBinaraMedicament.read((char*)&nrIngrediente, sizeof(int));

        for (int i = 0; i < nrIngrediente; i++)
        {
            int strSize;
            afisareBinaraMedicament.read((char*)&strSize, sizeof(int));
            ingredientePrincipale[i].resize(strSize);
            afisareBinaraMedicament.read(&ingredientePrincipale[i][0], strSize);
        }

        afisareBinaraMedicament.close();

        cout << nume << "\n" << pretCutie << "\n" << contor << "\n" << id << "\n" << nrIngrediente << "\n";
        for (int i = 0; i < nrIngrediente; i++)
        {
            cout << ingredientePrincipale[i] << " ";
        }
        cout << "\n\n";

        delete[] ingredientePrincipale;
    }
    else
    {
        cout << "Nu s-a putut deschide fisierul binar.\n";
        delete[] ingredientePrincipale;
    }
} 

// citirea obiectelor de tip Medicament din fisierul binar
void citireBinaraMedicament()
{
    Medicament m1;

    string nume = m1.getNume();
    float pretCutie = m1.getPretCutie();
    int contor = m1.getContor(); //static
    float id = m1.getId(); // const
    int nrIngrediente = m1.getNrIngrediente();
    int sizeNume = nume.length();
    string* ingredientePrincipale = new string[nrIngrediente];
    for (int i = 0; i < nrIngrediente; i++)
        ingredientePrincipale[i] = m1.getIngredientePrincipale()[i];

    ofstream citireBinaraMedicament("medicament.bin", ios::binary | ios::out);

    if (citireBinaraMedicament.is_open())
    {
        citireBinaraMedicament.write((char*)&sizeNume, sizeof(int));
        citireBinaraMedicament.write(&nume[0], sizeNume);
        citireBinaraMedicament.write((char*)&pretCutie, sizeof(float));
        citireBinaraMedicament.write((char*)&contor, sizeof(int));
        citireBinaraMedicament.write((char*)&id, sizeof(float));
        citireBinaraMedicament.write((char*)&nrIngrediente, sizeof(int));

        for (int i = 0; i < nrIngrediente; i++)
        {
            int strSize = ingredientePrincipale[i].length();
            citireBinaraMedicament.write((char*)&strSize, sizeof(int));
            citireBinaraMedicament.write(&ingredientePrincipale[i][0], strSize);
        }

        citireBinaraMedicament.close();
        delete[] ingredientePrincipale;
    }
    else
    {
        cout << "Nu am putut deschide fisierul binar. \n";
        delete[] ingredientePrincipale;
    }
}

// afisarea obiectelor de tip Pacient in fisierul binar pacient.bin
void afisareBinaraPacient()
{
    Pacient p1;

    string nume = p1.getNume();
    int varsta = p1.getVarsta();
    string nrTelefon = p1.getNrTelefon(); 
    long CNP = p1.getCNP(); 
    int nrAfectiuni = p1.getNrAfectiuni();
    int sizeNume = nume.length();
    int sizeNrTelefon = nrTelefon.length();
    string* afectiuni = new string[nrAfectiuni];
    for (int i = 0; i < nrAfectiuni; i++)
        afectiuni[i] = p1.getAfectiuni()[i];

    ifstream afisareBinaraPacient("pacient.bin", ios::binary);

    if (afisareBinaraPacient.is_open())
    {
        afisareBinaraPacient.read((char*)&sizeNume, sizeof(int));
        nume.resize(sizeNume);
        afisareBinaraPacient.read(&nume[0], sizeNume);
        
        afisareBinaraPacient.read((char*)&varsta, sizeof(int));

        afisareBinaraPacient.read((char*)&sizeNrTelefon, sizeof(int));
        nrTelefon.resize(sizeNrTelefon);
        afisareBinaraPacient.read(&nrTelefon[0], sizeNrTelefon);

        
        afisareBinaraPacient.read((char*)&CNP, sizeof(long));
        afisareBinaraPacient.read((char*)&nrAfectiuni, sizeof(int));

        for (int i = 0; i < nrAfectiuni; i++)
        {
            int strSize;
            afisareBinaraPacient.read((char*)&strSize, sizeof(int));
            afectiuni[i].resize(strSize);
            afisareBinaraPacient.read(&afectiuni[i][0], strSize);
        }

        afisareBinaraPacient.close();

        cout << nume << "\n" << varsta << "\n" << nrTelefon << "\n" << CNP << "\n" << nrAfectiuni << "\n";
        for (int i = 0; i < nrAfectiuni; i++)
        {
            cout << afectiuni[i] << " ";
        }
        cout << "\n\n";

        delete[] afectiuni;
    }
    else
    {
        cout << "Nu s-a putut deschide fisierul binar.\n";
        delete[] afectiuni;
    }
} 

// citirea obiectelor de tip Pacient din fisierul binar
void citireBinaraPacient()
{
    Pacient p1;

    string nume = p1.getNume();
    int varsta = p1.getVarsta();
    string nrTelefon = p1.getNrTelefon(); 
    long CNP = p1.getCNP(); 
    int nrAfectiuni = p1.getNrAfectiuni();
    int sizeNume = nume.length();
    int sizeNrTelefon = nrTelefon.length();
    string* afectiuni = new string[nrAfectiuni];
    for (int i = 0; i < nrAfectiuni; i++)
        afectiuni[i] = p1.getAfectiuni()[i];

    ofstream citireBinaraPacient("pacient.bin", ios::binary | ios::out);

    if (citireBinaraPacient.is_open())
    {
        citireBinaraPacient.write((char*)&sizeNume, sizeof(int));
        citireBinaraPacient.write(&nume[0], sizeNume);
        citireBinaraPacient.write((char*)&varsta, sizeof(int));
        citireBinaraPacient.write((char*)&sizeNrTelefon, sizeof(int));
        citireBinaraPacient.write(&nume[0], sizeNrTelefon);
        citireBinaraPacient.write((char*)&CNP, sizeof(long));
        citireBinaraPacient.write((char*)&nrAfectiuni, sizeof(int));

        for (int i = 0; i < nrAfectiuni; i++)
        {
            int strSize = afectiuni[i].length();
            citireBinaraPacient.write((char*)&strSize, sizeof(int));
            citireBinaraPacient.write(&afectiuni[i][0], strSize);
        }

        citireBinaraPacient.close();
        delete[] afectiuni;
    }
    else
    {
        cout << "Nu am putut deschide fisierul binar. \n";
        delete[] afectiuni;
    }
}

int main() {
/*
// FAZA 1 + FAZA 2 + FAZA 3: crearea a trei obiecte din fiecare clasa, functii prietene, supraincarcare de operatori, getteri, setteri
// pentru Medicament
 {
// creez obiectele de tip Medicament cu constructorii
Medicament medicament1; // constructor implicit
string ingrediente2[] = { "Ibuprofen", "Croscarmeloză sodică", "Celuloză microcristalină", "Amidon de porumb pregelatinizat" };
Medicament medicament2("Nurofen", 15.0, 4, ingrediente2); // constructor cu 4 parametri
string ingrediente3[] = {"Desloratadină", "Amidon pregelatinizat", "Stereat de magneziu"};
Medicament medicament3("Aerius", 20.0, ingrediente3); // constructor cu 3 parametri

// afisez cele 3 obiecte de tip Medicament
modificaPretMedicament(medicament1, 12.5);
medicament1.afisare();
cout<<"\n";
medicament2.afisare();
cout<<"\n";
medicament3.afisare();
cout<<"\n";

// calcularea dozei recomandate pentru un exemplu - functie
double greutatePacient = 52; // Greutatea pacientului în kg
double concentratieMedicament3 = 0.5; // Concentrația medicamentului 3

double dozaRecomandata = Medicament::calculareDozaRecomandata(greutatePacient, concentratieMedicament3);
cout << "Doza recomandata de " << medicament3.getNume() << " pentru un pacient cu greutatea de " << greutatePacient << " kg si o concentratie de " << concentratieMedicament3 << " este " << dozaRecomandata << " grame.\n\n";
    

// supraincarcarilor operatorilor 
Medicament medicament4("Ibuprofen", 10.0, 0, NULL); 
// operatorul = folosit pentru copiere
medicament4 = medicament2; 
medicament4.afisare();
cout<<endl;

// operatorul + folosit pentru a afla suma preturilor a 2 medicamente
float sumaPret = medicament4 + medicament2; 
cout << "Costul total pentru "<< medicament2.getNume() <<" si "<< medicament4.getNume() << " este: " << sumaPret << endl;

// operatorul - folosit pentru a afla diferenta de pret intre 2 medicamente
float diferentaPret = medicament2 - medicament4; 
cout << "Diferenta de pret dintre "<< medicament2.getNume() <<" si "<< medicament4.getNume() << " este: " << diferentaPret << endl;

// operatorul == folosit pentru a vedea daca 2 medicamente au acelasi numar de ingrediente
bool acelasiNrIngrediente = medicament4 == medicament2; // apelul operatorului ==
cout << "Au acelasi numar de ingrediente "<< medicament2.getNume() <<" si "<< medicament3.getNume() <<"? "<< acelasiNrIngrediente << endl;


// testarea getterilor si a setterilor in main
medicament1.setNume("Nurofen");
cout << "Testarea daca setter Nume a functionat folosind un getter: " << medicament1.getNume() << endl;

medicament1.setPretCutie(13);
cout << "Testarea daca setter pretCutie a functionat folosind un getter: " << medicament1.getPretCutie() << endl;

cout << "Testarea getter id: " << medicament1.getId() << endl;
cout << "Testarea getter contor: " << medicament2.getContor() << endl;

string ingredienteNoi[] = {"Celuloza", "Lactoza"};
medicament1.setIngredientePrincipale(ingredienteNoi, 2);
cout << "Testarea daca setter nrIngrediente a funcitonat folosind getter: " << medicament1.getNrIngrediente() << endl;
cout << "Testarea daca setter ingredientePrincipale a functionat folosind getter:\n";
string* ingredienteG = medicament1.getIngredientePrincipale();
for (int i = 0; i < medicament1.getNrIngrediente(); i++) {
        cout << ingredienteG[i] << endl;
    }
cout << endl;

cout << endl;
}

// Pentru Pacient
{
// creez obiectele de tip Pacient cu constructorii
Pacient pacient1;
Pacient pacient2("Maria Ionescu", 30);
Pacient pacient3("Teodor Marinescu");

cout<<"Numarul total de pacienti pana acum este "<<Pacient::GetTotalPacienti()<<".\n";

// afisez cele 3 obiecte de tip Pacient
pacient1.afisare();
cout<<"\n";
pacient2.afisare();
cout<<"\n";
pacient3.afisare();
cout<<"\n";

// supraincarcarilor operatorilor 
Pacient pacient4("Elena Popa", 25);
// operatorul = folosit pentru atribuirea bolilor lui pacient2 lui pacient4
pacient4 = pacient2; 
pacient4.afisare();
cout<< endl;

// operatorul + folosit pentru aflarea nr total de afectiuni a 2 pacienti
int sumaAfectiuni = pacient1 + pacient3;
cout << "Suma numarului de afectiuni ale lui " << pacient4.getNume() << " si " << pacient3.getNume() << " este " << sumaAfectiuni << endl;

// operatorul - folosit pentru aflarea diferentei de varsta dintre 2 pacienti
int diferentaVarsta = pacient4 - pacient1;
cout << "Diferenta de varsta intre " << pacient4.getNume() << " si " << pacient1.getNume() << " este " << diferentaVarsta << " ani" << endl;

// operatorul == folosit pentru a afla daca 2 pacienti au aceeasi varsta
bool aceeasiVarsta = pacient1 == pacient3;
cout << pacient1.getNume() << " si " << pacient3.getNume() << " au aceeasi varsta? " << (aceeasiVarsta ? "Da" : "Nu") << endl;

// testarea getterilor si a setterilor in main
pacient2.setNume("Dana Popescu");
cout << "Testarea setter Nume folosind un getter: " << pacient2.getNume() << endl;

pacient2.setVarsta(54);
cout << "Testarea daca setter Varsta a functionat folosind un getter: " << pacient2.getVarsta() << endl;

pacient2.setNrTelefon("07547384");
cout << "Testarea daca setter nrTelefon a functionat folosind un getter: " << pacient2.getNrTelefon() << endl;

cout << "Testarea getter id: " << pacient2.getCNP() << endl;
cout << "Testarea getter contor: " << pacient2.getContorFisePacienti() << endl;

string afectiuni[] = {"Reumatism", "Hipotensiune arteriala"};
pacient2.setAfectiuni(afectiuni, 2);
cout << "Testare setter nrAfectiuni folosind getter: " << pacient2.getNrAfectiuni() << endl;
cout << "Testare setter afectiuni folosind getter:\n";
string* afectiuniG = pacient2.getAfectiuni();
for (int i = 0; i < pacient2.getNrAfectiuni(); i++) {
    cout << afectiuniG[i] << endl;
}
cout << endl;

cout << endl;
}

// Pentru Aparatura Medicala
{
// creez obiectele de tip Aparatura cu constructorii
Aparatura aparat1;
Aparatura aparat2("Autorefractor");
Aparatura aparat3("Computer Tomograf", 41000);

// afisez cele 3 obiecte de tip Aparatura
afisareAparatura(aparat1);
cout<<"\n";
afisareAparatura(aparat2);
cout<<"\n";
Aparatura::setTVA(0.21); // aici am folosit functia statica, crescand TVA-ul
afisareAparatura(aparat3);
cout<<"\n";


// supraincarcarilor operatorilor 
// operatorul = folosit pentru atribuirea medicilor care folosesc aparat3 lui aparat4
Aparatura aparat4("Fluoroscop");
aparat4 = aparat3;
afisareAparatura(aparat4);
cout<<endl; 

// operatorul + folosit pentru a afla costul total pentru achizitia a 2 aparate
float sumaPreturi = aparat1 + aparat2;
cout << "Costul total pentru achizita a aparatelor " << aparat1.getDenumire() << " si " << aparat2.getDenumire() << " este " << sumaPreturi << endl;

// operatorul - folosit pentru a afla diferenta de pret intre 2 aparate
float diferentaPret = aparat3 - aparat2;
cout << "Diferenta de pret intre " << aparat3.getDenumire() << " si " << aparat2.getDenumire() << " este " << diferentaPret << endl;

// operatorul == folosit pentru a vedea daca 2 aparate au acelasi pret
bool acelasiPret = aparat4 == aparat1;
cout << aparat4.getDenumire() << " si " << aparat1.getDenumire() << " au acelasi pret? " << (acelasiPret ? "Da" : "Nu") << endl;

// testarea getterilor si a setterilor in main
aparat3.setDenumire("Bronhoscop");
cout << "Testarea setter Denumire folosind un getter: " << aparat3.getDenumire() << endl;

aparat3.setPret(5400);
cout << "Testarea daca setter Pret a functionat folosind un getter: " << aparat3.getPret() << endl;

aparat3.setSectie("Pneumologie");
cout << "Testarea daca setter Sectie a functionat folosind un getter: " << aparat3.getSectie() << endl;

cout << "Testarea getter TVA: " << aparat3.getTVA() << endl;
cout << "Testarea getter marca: " << aparat3.getMarca() << endl;

string mediciNume[] = {"Dr. Marian Popa", "Dr. Alisa Marcu", "Dr. Maria Ionescu"};
aparat3.setNumeMediciCareFolosescAparatul(mediciNume, 3);
cout << "Testare setter nrMedici folosind getter: " << aparat3.getNrMediciCareFolosescAparatul() << endl;
cout << "Testare setter numeMedici folosind getter:\n";
string* mediciG = aparat3.getNumeMediciCareFolosescAparatul();
for (int i = 0; i < aparat3.getNrMediciCareFolosescAparatul(); i++) {
    cout << mediciG[i] << endl;
}
cout << endl;
cout << endl;
}
*/

// FAZA 4: 3 vectori in main de tipul celor 3 clase de baza - Medicament, Pacient, Aparatura
// declarari de dimensiuni + vectori in sine
int nrMed, nrPac, nrApar;
cout<<"Dimensiunea vectorului de medicamente: ";
cin>>nrMed;
cout<<"Dimensiunea vectorului de pacienti: ";
cin>>nrPac;
cout<<"Dimensiunea vectorului de aparate medicale: ";
cin>>nrApar;
Medicament vectorMedicamente[nrMed];
Pacient vectorPacienti[nrPac];
Aparatura vectorAparate[nrApar];

// citirea vectorilor de la tastatură
    cout << "Introduceti date pentru vectorul de medicamente:\n";
    for (int i = 0; i < nrMed; ++i) {
        cout << "Medicament " << i + 1 << ":\n";
        cin >> vectorMedicamente[i];
    }

    cout << "Introduceti date pentru vectorul de pacienti:\n";
    for (int i = 0; i < nrPac; ++i) {
        cout << "Pacient " << i + 1 << ":\n";
        cin >> vectorPacienti[i];
    }

    cout << "Introduceti date pentru vectorul de aparate medicale:\n";
    for (int i = 0; i < nrApar; ++i) {
        cout << "Aparat " << i + 1 << ":\n";
        cin >> vectorAparate[i];
    }

// afisarea vectorilor
    cout << "\nAfisare vector de medicamente:\n";
    for (int i = 0; i < nrMed; ++i) {
        cout << "Medicament " << i + 1 << ":\n";
        cout << vectorMedicamente[i];
        cout << endl;
    }

    cout << "\nAfisare vector de pacienti:\n";
    for (int i = 0; i < nrPac; ++i) {
        cout << "Pacient " << i + 1 << ":\n";
        cout << vectorPacienti[i];
        cout << endl;
    }

    cout << "\nAfisare vector de aparate medicale:\n";
    for (int i = 0; i < nrApar; ++i) {
        cout << "Aparatul " << i + 1 << ":\n";
        cout << vectorAparate[i];
        cout << endl;
    }

    /*
    // FAZA 5: clasa Reteta ce se afla in relatie de has-a cu clasele initiale Medicament si Pacient
    Reteta reteta;
    cin >> reteta;
    cout << reteta;


    // FAZA 6: citiri si afisari folosind fisiere text si binare
    // citirea si afisarea obiectelor Medicament si Pacient din și în fisier de tip text  
    Medicament medicament5;
    Pacient pacient5;
    ofstream afisareTextMedicament("medicament.txt", ios::out);
    afisareTextMedicament << medicament5;
    ifstream citireTextMedicament("medicament.txt", ios::in);
    
    ofstream afisareTextPacient("pacient.txt", ios::out);
    afisareTextPacient << pacient5;
    ifstream citireTextPacient("pacient.txt", ios::in);

    // citirea si afisarea obiectelor Medicament si Pacient din si in fisier de tip binar
    afisareBinaraMedicament();
    citireBinaraMedicament();
    
    afisareBinaraPacient();
    citireBinaraPacient();


   // FAZA 7: clasele aflate in relatie de is-a - PreparatFarmaceutic si PacientSpecial
   PreparatFarmaceutic preparat1;
   cin >> preparat1;
   cout << "\nDetaliile preparatului farmaceutic sunt:\n";
   preparat1.afisare();

   PacientSpecial pacientSpecial1;
   cin >> pacientSpecial1;
   cout << "\nDetaliile pacientului special sunt:\n";
   pacientSpecial1.afisare();


  // FAZA 8: clase abstracte, functii virtuale, late binding
  // late binding pentru Farmacie
    Medicament* pointerM;
    pointerM = new Medicament();
    cout << "Contine "<< pointerM->cateIngredienteContine() << " ingrediente.\n";
    delete pointerM;

    string* ingredienteM = new string[10];
    ingredienteM[0] = "Ibuprofen";
    ingredienteM[1] = "Aspirina";
    ingredienteM[2] = "Microcristalina";
    ingredienteM[3] = "Polisorbat 80";
    ingredienteM[4] = "Paracetamol";
    ingredienteM[5] = "Amidon";
    ingredienteM[6] = "Lactoza";
    ingredienteM[7] = "Dioxid de titan";
    ingredienteM[8] = "Celuloza";
    ingredienteM[9] = "Stereat de magneziu";
    pointerM = new PreparatFarmaceutic(ingredienteM, 10);
    cout << "Contine " << pointerM->cateIngredienteContine()<<" ingrediente.\n";
    delete pointerM;

    Farmacie** pointeri;
    pointeri = new Farmacie * [10];
    pointeri[0] = new Medicament();
    pointeri[1] = new PreparatFarmaceutic(ingredienteM, 10);
    for(int i = 2 ; i < 10 ; i++)
        pointeri[i] = new Medicament();
    for(int i=0; i< 10; i++){
        cout << "Nr ingrediente in medicamentul " << i << ": " << pointeri[i]->cateIngredienteContine() << endl;
    }   
    
    // late binding pentru Spital
    Pacient* pointerP;
    pointerP = new Pacient();
    cout << "Pacientul este major? " << endl;
    pointerP->ePacientulMajor();
    cout << endl;
    delete pointerP;

    string* afectiuniP = new string[10];
    afectiuniP[0] = "Gripa";
    afectiuniP[1] = "Reumatism";
    afectiuniP[2] = "Pneumonie";
    afectiuniP[3] = "Hipertensiune arterială";
    afectiuniP[4] = "Alzheimer";
    afectiuniP[5] = "Obezitate";
    afectiuniP[6] = "Artrită";
    afectiuniP[7] = "Hipotensiune arteriala";
    afectiuniP[8] = "Scolioza";
    afectiuniP[9] = "Hernie de disc";
    pointerP = new PacientSpecial(afectiuniP, 10);

    pointerP->istoricAfectiuni();
    cout<<"\n";
    delete pointerP;

    Spital** pointeri2;
    pointeri2 = new Spital * [10];
    pointeri2[0] = new Pacient();
    pointeri2[1] = new PacientSpecial(afectiuniP, 10);
    pointeri2[2] = new Pacient("Vasile Tudor", 43);
    pointeri2[3] = new Pacient("Mihai Mircea");

    for(int i = 4 ; i < 10 ; i++)
        pointeri2[i] = new Pacient();
    
    for(int i=0; i<10; i++)
        pointeri2[i]->istoricAfectiuni();
    */
}