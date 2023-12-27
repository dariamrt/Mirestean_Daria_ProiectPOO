# Proiect de Programare Orientată Obiect realizat de Daria Mireștean, grupa 1059

## Descriere
- Proiectul este o aplicație de gestiune din domeniul MeDical, realizată în C++.
- Acesta utilizează numeroase funcționalități ale programării orientate obiect.
- Clasele utilizate în cadrul proiectului sunt: 
  1. **Medicament, Pacient, Aparatură** - cele 3 clase de bază
  2. **Rețetă** - aflată în relație de has-a cu Medicament și Pacient
  3. **PacientSpecial** - aflată în relație de is-a cu Pacient, obiectele sale sunt Pacienți care au boli rare sau deosebit de periculoase, precum Febra galbenă
  4. **PreparatFarmaceutic** - aflată în relație de is-a cu Medicament, obiectele sale sunt niște Medicamente preparate în laboratorul farmaciei de către farmacist în diverse concentrații
  5. **Spital** și **Farmacie** - clase abstracte
--
## Cum Rulezi Proiectul?

### Cerințe
- Un compilator C++
- Un mediu de dezvoltare - eu recomand **Visual Studio** sau **Visual Studio Code**

### Pași pentru Rulare

1. **Descărcarea codului**
   - Descarcă folder-ul sau **clonează repository**-ul folosind comanda `git clone https://github.com/dariamrt/Mirestean_Daria_ProiectPOO` 

2. **Compilarea**

3. **Rularea**

---

## Structura Codului
- Acesta este împărțit în mai multe faze, conform cerințelor. Fazele au fost testate în main.
### Faza 1 - Implementarea claselor de bază
- Medicament, Pacient, Aparatura sunt clasele principale implementate pentru manipularea datelor, alese întrucât se află în domeniul MeDical
- Aceste clase au atribute normale, statice și constante, minimum un pointer per clasă, minimum 3 constructori cu numpr diferit de parametri per clasă, câte o funcție statică per clasă

### Faza 2 
- Atributele de la faza anterioară au fost trecute drept private
- Am realizat destructorul fiecărei clase
- Am realizat constructorul de copiere al fiecărei clase
- Am realizat getteri și setteri fiecărui atribut
- Am realizat 2 funcții globale ce utilizează obiecte de tipul claselor date, fiind prietene cu clasele menționate

### Faza 3 - Supraîncărcarea operatorilor
- Am supraîncărcat pentru fiecare clasă operatorul =, precum și minimum alți 3 operatori

### Faza 4 - Vectori
- Am realizat câte un vector de tipul fiecărei clase, citindu-i și afișându-i pe fiecare

### Faza 5 - Relația de has-a
- Am introdus o nouă clasă în proiect, Rețetă, aceasta aflându-se în relație de has-a atât cu Medicament, cât și cu Pacient
- Noua clasă are getteri și setteri pentru fiecare atribut
- În noua clasă am supraîncărcat alți minimum 3 operatori

### Faza 6 - Fișiere text și binare
- În această fază am realizat posibilitatea de a citi din fișiere text și din fișiere binare pentru 2 dintre clase(Medicament și Pacient)
- De asemenea, am implementat și opțiunea de a afișa în fișiere text și în fișiere binare pentru 2 dintre clase(Medicament și Pacient)

### Faza 7 - Relația de is-a
- Am introdus 2 noi clase, PacientSpecial și PreparatFarmaceutic, aflate în relații de is-a cu cu clasele Pacient, respectiv Medicament
- Pentru fiecare clasă am realizat getteri, setteri, destructor, constructori

### Faza 8 - Clase abstracte
- Am realizat 2 clase abstracte, numite Spital și Farmacie, pe care le-am adăugat la începutul codului pentru o mai bună vizibilitate
- Am creat pentru fiecare un vector de pointeri la tipul abstract
- Pentru fiecare dintre acestea am exemplificat în main conceptul de late-binding pentru cele 10 elemente din vector





