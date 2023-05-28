#include <iostream>
#include <algorithm>
#include <chrono>
#include <random>
#include <iomanip>

//#include <limits>
//#include <algorithm>
//#include <string>
//#include <iomanip>
//#include <fstream>
//#include <clocale>

#define EMPTY -1 // puste miejsce w tablicy mieszajacej
#define REMOVED -2 // puste miejsce tablicy mieszajacej z ktorego usuniety zostal jakis element

//Zad. 1 Wstawianie do tablicy mieszajacej (adresowanie liniowe)
/*1 procedure hash al wstaw(x);
2 begin
3 for i : = 0 to m − 1 do
4 k : = h(x, i);
5 if A[k] jest puste lub usunięte then
6 A[k] : = x;
7 return true;
8 end if;
9 end for;
10 return f alse;
11 end.

/** Funkcja wstawiajaca element x do tablicy mieszajacej tab o rozmiarze m
 @param tab tablica mieszajaca
 @param m rozmiar tablicy mieszajacej
 @param x element wstawiany do tablicy
 @return true, jesli element zostal wstawiony, false, jesli nie udalo sie wstawic elementu (brak miejsca w tablicy)
 */



int h(int x, int i, int m) {

    int k = (x % m + 1) % m
    z++;
    return k;
}
bool hash_al_wstaw(int* tab, int m, int x)
{
    int k;
    int i;
    for (int i = 0; i < m - 1; i++) {

        k = h(x, i, m);
            if (tab[k] == EMPTY || tab[k] == REMOVED) {
                tab[k] = x;
                return true;

            }
    }
    return false;
}

//zaimplementuj
bool hash_al_szuk(int* A, int m, int x) {
    for (int i = 0; i < m; i++)
    {
        int k = h(x, m, i);
        if (tab[k] == x)
        {
            return true;
        }
        if (tab[k] == EMPTY)
        {
            return false;
        }
    }
    return false;
}

int main()
{
 
std::cout << "Zadanie 1 i 2:\n";

    // Zad. 2 (rozgrzewka + test)
    const int m1 = 8; //rozmiar tablicy mieszajacej
    int t[m1]; //tablica mieszajaca
    // Wyczyszczenie tablicy mieszajacej t (Wypelnienie pustymi miejscami)
    for (int i = 0; i < m1; i++)
    {
        t[i] = EMPTY;
    }

    // Wstawianie elementów do tablicy mieszajacej t (uzyć funkcji hash_al_wstaw)
    hash_al_wstaw(t, m1, 12);
    hash_al_wstaw(t, m1, 10);
    hash_al_wstaw(t, m1, 34);
    hash_al_wstaw(t, m1, 56);


    // Wyswietlenie tablicy mieszajacej t o rozmiarze m1
    std::cout << std::setw(7) << "indeks:";
    for (int i = 0; i < m1; i++)
    {
        std::cout << std::setw(11) << i;
    }
    std::cout << std::endl;
    std::cout << std::setw(8) << "|";
    for (int i = 0; i < m1; i++)
    {
        std::cout << std::setw(10) << t[i] << "|";
    }
    std::cout << std::endl;


    // Zad. 3 Pomiary

    // a) Tablica z danymi
    // Tworzenie tablicy dane z danymi do wstawinia do tablicy mieszajacej
    int rozm_dane = 20000000; //liczba elementow w tablicy dane
    int* dane = new int[rozm_dane];
    //wypelnienie tablicy dane kolejnymi liczbami od 0 do rozm_dane-1
    for (int i = 0; i < rozm_dane; i++)
    {
        dane[i] = i;
    }
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(dane, dane + rozm_dane, g); //losowa permutacja elementow w tablicy dane (wymieszanie tablicy)


    // b) Tablica mieszajaca
    // Utworz pusta tablice mieszajaca tab o rozmiarze m = 2097152 (2 do potegi 21)
    const int m = 2097152;
    int* tab = new int[m]
    // int * tab = ...;
    // ...

    // c) Wstaw 10000 elemetow z tablicy dane do pustej tablicy mieszajacej tab (zapelnienie 0%). Na tej podstawie zmierz sredni czas wstawiania elementu oraz srednią liczbe wywolan funkcji mieszajacej przy wstawianiu elementu do pustej tablicy.
     z = 0;
    for (int i = 0; i < m; i++)
    {
        tab[i] = EMPTY;
    }

    std::cout << "Pomiary:\n";
    // Mierzenie czasu, przyklad:
    auto start = std::chrono::high_resolution_clock::now();
    for (int i = 0; i < 10000; i++) {
        hash_al_wstaw(tab, m, dane[i]);
    //tutaj mierzona operacja
    auto stop = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::micro> czas = stop - start;
    std::cerr << "Uplynelo: " << czas.count() << " us\n";
     std::cout << "Liczba pomiarow:";
    std::cout << z << "\n\n";
    // d) Zmierz sredni czas wstawiania elementu oraz srednią liczbe wywolan funkcji mieszajacej przy wstawianiu elementu do tablicy wypelnionej w 10%, 20%, 30%, 40%, 50%, 60%, 70%, 80%, 90% (dla próbki: 10000 elementów).
    //UWAGA! Do tablicy mieszajacej nie wstawiac elementow, ktore juz w niej sa.

    for (int i = 0; i < 10; i++) {
        int p = i * 0.1 * m;
        for (int j = 0; j < m; j++) {
            tab[j] = EMPTY;
        }

        if (i != 0)
        {
            for (int i = 0; i < p; i++) {
                hash_al_wstaw(tab, m, dane[i]);
            }
            //pomiary dla wyszukiwania
            int d = 0;
            int f = p / 10000;
            for (int i = 0; i < 10000; i++) {
                hash_al_szuk(tab, m, dane[d]);
                d = d + f;
            }

            //pomiary dla wstawiania
            z = 0;
            auto start = std::chrono::high_resolution_clock::now();
            for (int i = 0; i < 10000; i++) {
                hash_al_wstaw(tab, m, dane[i + p]);
            }

            auto stop = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double, std::micro> czas = stop - start;
            std::cerr << "Przy wypelnineiu tablicy w: " << i * 10 << " %\n";
            std::cerr << "Uplynelo: " << czas.count() << " us\n";
            std::cout << "Liczba pomiarow:";
            std::cout << z << "\n\n";

        }

    }

    return 0;
}
