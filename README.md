# Bibliotecă online in C (Structuri de date)
### 1. **Introducere**  
Fiecare carte va avea: un **titlu** unic, un **autor**, un **rating** (număr întreg, recomandare) și **numărul de pagini**.
Putem **să introducem** cărți noi și **să cautam** după cărți deja introduse într-un mod eficient. De asemenea, programul are o opțiune de **auto-complete** pentru titlul sau autorul unei cărți.
### 2.  **Implementare**
Pentru gestionarea cărților, am folosit următoarele structuri de date:
1.  **T1:** un arbore de prefixe (trie), în care cheia este titlul cărții, iar informația reținută la finalul căii este un pointer către o structură cu informațiile cărții;

1.  **T2:** un alt arbore de prefixe (trie), în care cheia este un autor, iar informația reținută este un alt arbore de prefixe (trie), în care sunt reținute cărțile scrise de acel autor, reținute asemenea structurii 1. 
### **2.1. Arbori de prefixe (Trie)**
Este un arbore multi-căi (fiecare nod poate avea oricât descendenți). Este un tip de arbore de căutare cu următoarele proprietăți:
- Fiecare nod poate avea între 0 și |Σ| descendenți (|Σ| reprezinta dimensiunea alfabetului).
- Spre deosebire de un arbore binar de căutare, unde fiecărui nod i se asociază o cheie, la arborele de prefixe cheile se asociază căii până la nod.
```
Exemplu:
Andrei a primit următoarele recomandări de cărți:
- ”1998”, George Orwell;
- ”Anna Karenina”, Lev Tolstoi;
- ”The Idiot”, Dostoievsky;
- ”Animal Farm”, George Orwell;
- ”The Possessed”, Dostroievsky.
Structurile sunt populate ca mai jos. Fiecare nod albastru din T2 are o legătură către 
un alt arbore de prefixe, asemănător arborelui T1, dar conținând doar cărțile scrise de 
autorul respectiv.
```

```
Structura T1		Structura T2:
```
![enter image description here](https://i.imgur.com/GFuGEQj.png)![Structura T1](https://i.imgur.com/H1XsXfs.jpg)

### 3.  Gestionare
Cartile se gestioneaza cu urmatoarele comenzi:
#### 3.1.  **Adăugare recomandare carte**
```
Sintaxă : add_book <titlu>:<autor>:<rating>:<numar_pagini>
Mod de funcționare : cartea este adăugată atât în T1, cât și în arborele de cărți corespunzător
autorului său din T2. Dacă pentru autor nu există încă o cheie în T2, atunci va fi adăugat.
Dacă în T1 și T2 deja există cartea, atunci structurile rămân nemodificate. 
Exemplu : add_book Wuthering Heights:Emily Bronte:9:391 /*  *se parcurge arborele T1 pe calea
dată de titlul ”Wuthering Heights”. Dacă nodurile din această cale nu existau deja, ele sunt
create. În ultimul nod, se păstrează informația legată de carte; similar, se parcurge arborele
T2 pe calea dată de numele autorului ”Emily Bronte”, se crează arborele corespondent cărților
sale și apoi în acela se adaugă pe calea ”Wuthering Heights” informația legată de carte. */
```

#### 3.2.  **Căutare carte**
```
Sintaxă :search_book <titlu>
Mod de funcționare m: cartea este căutată în T1. Dacă nu există, va fi întors un mesaj de 
forma: Cartea <titlu> nu exista in recomandarile tale.
Altfel, dacă este găsită cartea, se va afișa un mesaj de forma:
Informatii recomandare: <titlu>, <autor>, <rating>, <numar_pagini>
Exemplu : search_book Wuthering Heights /* se caută în T1 calea ”Wuthering Heights” */ 
Cartea Wuthering Heights nu exista in recomandarile tale. /* în caz că nu se găsește în T1 */
Informatii recomandare: Wuthering Heights, Emily Bronte, 9, 391 */\* în caz că a fost găsită */
```
  

#### 3.3.  **Auto-complete pentru căutare carte**
``` 
Sintaxă : search_book <prefix\_titlu>~
Mod de funcționare : se caută în T1 cărți al căror titlu începe cu<prefix\_titlu>. Se afișează 
pe câte un rând primele maxim 3 titluri de cărți care încep cu<prefix\_titlu> (primele din 
punct de vedere lexicografic).
<titlu\_carte1>
<titlu\_carte2>
<titlu\_carte3>
Dacă nu există nicio carte care începe cu prefix\_titlu, se afișează mesajul:
Nicio carte gasita.
Exemplu : search_book Wuthering~ /* caută în T1 calea ”Wuthering” și afișează primele maxim 
3 chei pană la un nod ce conține o carte */
Wuthering Heights
```  

#### 3.4.  **Afișare cărți autor**
```
Sintaxă : list_author <autor>
Mod de funcționare : se va căuta în T2 după numele autorului. După vor fi afișate toate 
cărțile din arborele de căutare corespondent lui, în ordine lexicografică: 
<titlu\_carte1>
<titlu\_carte2>  
<titlu\_carte3>
…
Dacă autorul nu există în T2, atunci se va afișa un mesaj de forma:
Autorul <autor> nu face parte din recomandarile tale.
Exemplu : list_author Emily Bronte /* caută în T2 după cheia ”Emily Bronte” și parcurge 
arborele corespondent cărților sale, afișând toate titlurile */
Wuthering Heights
```
#### 3.5.  **Auto-complete pentru afișare cărți autor**
```
Sintaxă : list_author <prefix_autor>~  
Mod de funcționare : se caută în T2 autori al căror nume începe cu <prefix_autor>. Se afișează
pe câte un rând primii maxim 3 autori care încep cu <prefix_autor> (primii din punct de 
vedere lexicografic).
<nume_autor1>
<nume_autor2>
<nume_autor3>
Dacă nu există niciun autor care începe cu <prefix\_autor>, se va afișa mesajul: 
Niciun autor gasit.
```
#### 3.6.  **Căutare în cărțile unui autor**
```
Sintaxă : search_by_author <autor>:<titlu>
Mod de funcționare : se caută în T2 după numele autorului, iar apoi în arborele de 
căutare corespondent lui, după titlul cărții. Dacă autorul nu există, se afișează mesajul: 
Autorul <autor> nu face parte din recomandarile tale.
Altfel, mesajele sunt aceleași ca pentru comanda: search_book <titlu>.
Exemplu : search_by_author Emily Bronte:Wuthering Heights /* se parcurge T2 
pe calea ”Emily Bronte”, iar în arborele corespondent autoarei, se caută calea 
”Wuthering Heights” */
```
#### 3.7.  **Auto-complete pentru căutare în cărțile unui autor**
```
Sintaxă : search_by_author <prefix_autor>~
Mod de funcționare : idem comanda list_author <prefix_autor>~
Sintaxa : search_by_author <autor>:<prefix_titlu>~
Mod de funcționare : idem comanda search_book <prefix_titlu>~, doar că se va căuta mai întâi 
în T2 după numele autorului, apoi în arborele de căutare corespondent lui, după <prefix_titlu>
Dacă autorul nu există în T2, atunci se va afișa un mesaj de forma:
Autorul <autor> nu face parte din recomandarile tale.  
```
#### 3.8.  **Ștergere recomandare**
```
Sintaxă : delete_book <titlu>
Mod de funcționare : comanda șterge atât informațiile despre carte, cât și cheile din T1 
și din arborele aferent autorului din T2. Dacă nu mai există alte cărți pentru acel autor, 
atunci trebuie să fie ștearsă și cheia autorului din T2, precum și eliberată memoria ocupată 
de arborele de căutare corespondent cărților sale.
Dacă titlul nu există, atunci se va afișa un mesaj de forma:
Cartea <titlu> nu exista în recomandarile tale.
```
### 4.  **Restricții și precizări**
- Titlul unei cărți este un șir de maxim 50 de caractere.
- Nu există două cărți cu același nume.
- Ordinea lexicografică este dată de următorul alfabet (fără ghilimele): **"abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789.-'?! "**
- Numele unui autor este un șir de maxim 40 de caractere. Pentru simplitate, vom considera că toate caracterele din numele autorului aparțin alfabetului de mai sus.
- Programul va fi rulat astfel: ./tema3 input_file output_file.

### 5.  **Exemple**
|**Intrare**|**Ieșire**|
| - | - |
|<p>add_book Bosnia - A Short History:Noel Malcolm:4:384</p><p>add_book Wild Horses:Dick Francis:4:352</p> <p>add_book Inferno:Dante Alighieri:4:396</p><p>add_book Ports of Call:Jack Vance:4:300</p> <p>add_book Going Native:Stephen Wright:4:320</p><p>add_book Seventeen and In-Between:Barthe DeClements:4:176</p> <p>add_book Personal Finance for Dummies:Eric Tyson:4:454</p><p>search_book Seventeen and In-Between</p><p>search_book Young Warriors - Stories of Strength</p><p>search_book Ports of Call</p><p>list_author Jack Vance</p><p>list_author Arthur C. Clarke</p><p>search_by_author Jack Vance:Ports of Call</p> <p>search_by_author Anita Shreve:Eden Close</p><p>list_author D~ </p><p>list_author Step~ </p><p>search_book Ab~</p>|<p>Informatii recomandare: Seventeen and In-Between, Barthe DeClements, 4, 176</p><p>Cartea "Young Warriors - Stories of Strength" nu exista in recomandarile tale.</p><p>Informatii recomandare: Ports of Call, Jack Vance, 4, 300</p><p>Ports of Call</p><p> Autorul Arthur C. Clarke nu face parte din recomandarile tale.</p><p>Informatii recomandare: Ports of Call, Jack Vance, 4, 300</p><p> Autorul Anita Shreve nu face parte din recomandarile tale.</p><p> Dante Alighieri</p><p>Dick Francis</p><p>Stephen Wright</p><p>Nicio carte gasita.</p><p>Personal Finance for Dummies</p><p>Jack Vance</p><p> Seventeen and In-Between</p>

**Explicații:**
1. Se adaugă cheia ”Bosnia - A Short History” în T1 și cheia ”Noel Malcolm” în T2. Se rețin informațiile despre carte. Se procedează la fel și pentru restul comenziilor ”add\_book”.
1. Pentru fiecare comandă search\_book, este parcurs arborele T1 de la rădăcină, pe calea indicată de titlul căutat. Dacă nu există calea indicată sau la finalul său nu sunt marcate informații despre o carte, înseamnă că acea carte nu se află în recomandări.
1. Pentru fiecare comandă list\_author, este parcurs arborele T2 de la rădăcină, pe calea indicată de numele autorului. Dacă nu există calea indicată sau finalul căii nu se află un arbore aferent autorului, înseamnă că autorul nu se află în recomandări. Altfel, este parcurs întreg arborele aferent autorului și sunt afișate toate cheile (titlurile cărților sale).
1. Pentru fiecare comandă terminată în ‘~’ (auto-complete), se parcurge arborele T1 sau T2 (în funcție de comandă) pe calea indicată de prefix. Apoi, din nodul curent, se încearcă găsirea a maxim 3 chei din subarbore.
1. Pentru fiecare comandă search\_by\_author, se parcurge întâi arborele T2, apoi arborele trie aferent acelui autor.
1. Comenzile delete\_book șterg informațiile despre carte, cheia dată de titlul cărții din T1 și din arborele aferent autorului din T2. De asemenea, dacă autorul nu mai are nicio altă carte în recomandări, este distrus arborele de căutare aferent cărților sale și ștearsă cheia din T2.

### Copyright 
Enuntul temei, `check.sh` cat si datele din fisierele de intrare `_test` apartin echipei SD 2020-2021, UPB. Dreptul asupra restul fisierelor si continutul lor (fisierele `.c` si `.h`, `Makefile`) apartin [vanyadarkov](https://github.com/vanyadarkov).
