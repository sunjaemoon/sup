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

/* Funkcja wstawiajaca element x do tablicy mieszajacej tab o rozmiarze m
 @param tab tablica mieszajaca
 @param m rozmiar tablicy mieszajacej
@param x element wstawiany do tablicy
@return true, jesli element zostal wstawiony, false, jesli nie udalo sie wstawic elementu (brak miejsca w tablicy)
 */
 // liczba wywołań funkcji mieszającej
unsigned long long z = 0;

// funkcja mieszająca (liniowa)
int h(int x, int i, int m)
{
    int k = (x % m + i) % m;
    z++;
    return k;
}

// wstawianie liniowe
bool hash_al_wstaw(int* tab, int m, int x)
{
    int k;
    // int i;
    for (int i = 0; i <= m - 1; i++)
    {

        k = h(x, i, m);
        if (tab[k] == EMPTY || tab[k] == REMOVED)
        {
            tab[k] = x;
            return true;
        }
    }
    return false;
}
// szukanie liniowe
bool hash_al_szuk(int* tab, int m, int x)
{
    for (int i = 0; i < m; i++)
    {
        int k = h(x, i, m);
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
//funkcja haszująca, która oblicza indeks k dla wartości x
int h1(int x, int m) {
    return x % m;
}

int h2(int x, int m) {
    return 2 * (200003 - (x % 200003)) + 1;
}
//zmniejszyć prawdopodobieństwo wystąpienia kolizji o tej samej wartości. 
// funkcja mieszająca (kwadratowa)
int h_kw(int x, int i, int m)
{
    int k = ((h1(x, m) + 5 * i * i - 2 * i) % m);
    //z++;
    return k;
}
// wstawianie kwadratowe
bool hash_al_wstaw_kw(int* tab, int m, int x)
{
    int k;
    // int i;
    for (int i = 0; i <= m - 1; i++)
    {

        k = h_kw(x, i, m);
        if (tab[k] == EMPTY || tab[k] == REMOVED)
        {
            tab[k] = x;
            return true;
        }
    }
    return false;
}
// szukanie liniowe
bool hash_al_szuk_kw(int* tab, int m, int x)
{
    for (int i = 0; i < m; i++)
    {
        int k = h_kw(x, i, m);
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


// funkcja mieszająca (podwojna)
int h_pdw(int x, int i, int m)
{
    int k = (h1(x, m) + i * h2(x, m)) % m;
    //z++;
    return k;

}
// wstawianie podwojne
bool hash_al_wstaw_pdw(int* tab, int m, int x)
{
    int k;
    // int i;
    for (int i = 0; i <= m - 1; i++)
    {

        k = h_pdw(x, i, m);
        if (tab[k] == EMPTY || tab[k] == REMOVED)
        {
            tab[k] = x;
            return true;
        }
    }
    return false;
}

// szukanie liniowe
bool hash_al_szuk_pdw(int* tab, int m, int x)
{
    for (int i = 0; i < m; i++)
    {
        int k = h_pdw(x, i, m);
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
int losowa_liczba(int min, int max)
{
    static std::default_random_engine gen(std::random_device{}());
    static std::uniform_int_distribution<int> dist;
    return dist(gen, std::uniform_int_distribution<int>::param_type{ min, max });
}
int main()
{

    // Zad. 2 (rozgrzewka + test)
    const int m1 = 8; //rozmiar tablicy mieszajacej
    int t[m1]; //tablica mieszajaca
    // Wyczyszczenie tablicy mieszajacej t (Wypelnienie pustymi miejscami)
    for (int i = 0; i < m1; i++)
    {
        t[i] = EMPTY;
    }

    // Wstawianie elementów do tablicy mieszajacej t (uzyć funkcji hash_al_wstaw)
    // ...
    hash_al_wstaw(t, m1, 34);
    hash_al_wstaw(t, m1, 12);
    hash_al_wstaw(t, m1, 10);
    hash_al_wstaw(t, m1, 56);
    hash_al_wstaw(t, m1, 44);
    hash_al_wstaw(t, m1, 76);
    hash_al_wstaw(t, m1, 89);
    hash_al_wstaw(t, m1, 49);
    hash_al_wstaw(t, m1, 87);

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

    int* tab = new int[m];
    // int * tab = ...;
    // ...
    // wyzeruj tablice mieszajaca
    for (int i = 0; i < m; i++)
    {
        tab[i] = EMPTY;
    }
    // c) Wstaw 10000 elemetow z tablicy dane do pustej tablicy mieszajacej tab (zapelnienie 0%). Na tej podstawie zmierz sredni czas wstawiania elementu oraz srednią liczbe wywolan funkcji mieszajacej przy wstawianiu elementu do pustej tablicy.
    z = 0;

    // nie wstawiamy elementow ktore juz tam sa
    int dane_ptr = 0;
    //wskaźnik do iteracji po tablicy dane, która zawiera dane, które mają być wstawione do tablicy haszującej.
    for (int i = 0; i <= 90; i += 10)
        //pętla jest odpowiedzialna za wypełnianie tablicy haszującej do określonego progu procentowego.
    {

        //pomiary szukanie
        z = 0;

        if (i > 0)
        {
            for (int i = 0; i < 1000; i++) {
                int los = losowa_liczba(0, dane_ptr);
                int wybrana = dane[los];

                hash_al_szuk(tab, m, wybrana);
            }
            std::cout << "Liczba pomiarow dla szukania:";
            std::cout << z << "\n\n";
        }

        //pomiary wstawianie
        std::cout << "Wypelnianie " << i << "%... \n";
        z = 0;
        auto start = std::chrono::high_resolution_clock::now();
        //rozpoczyna sie pomiar czasu
        for (int i = 0; i < 10000; i++) {
            hash_al_wstaw(tab, m, dane[dane_ptr]);
            dane_ptr++;
            //Powoduje przesunięcie wskaźnika do kolejnej porcji danych w tablicy dane.
        }
       
        auto stop = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::micro> czas = stop - start;
        std::cout << "Pomiary:\n";
        auto avg_czas = std::chrono::duration_cast<std::chrono::microseconds>(stop - start) / 10000.0;
        std::cerr << "Sredni czas wstawiania: " << avg_czas.count() << " us\n";
        std::cout << "Srednia liczba wywolan funkcji mieszajacej: " << z / 10000.0 << "\n\n";

        // Dopełnij tablice do kolejnego progu %
        std::cout << "Dopelnianie tablicy do  " << i + 10 << "%... \n";
        int items = (2097152 / 10) - 10000;
        int prog = (2097152 / 10) * ((i + 10) / 10);
        while (dane_ptr < prog) {
            hash_al_wstaw(tab, m, dane[dane_ptr]);
            dane_ptr++;
        }
    }
    //prog - ilosc elementow ktore powinny znajdowac sie w tablicy

    // d) Zmierz sredni czas wstawiania elementu oraz srednią liczbe wywolan funkcji mieszajacej przy wstawianiu elementu do tablicy wypelnionej w 10%, 20%, 30%, 40%, 50%, 60%, 70%, 80%, 90% (dla próbki: 10000 elementów).
    //UWAGA! Do tablicy mieszajacej nie wstawiac elementow, ktore juz w niej sa.

    //...
   /*
    for (int i = 0; i < 10; i++)
    {
        int p = i * 0.1 * m;
        for (int j = 0; j < m; j++)
        {
            tab[j] = EMPTY;
        }

        if (i != 0)
        {
            for (int i = 0; i < p; i++)
            {
                hash_al_wstaw(tab, m, dane[i]);
            }
        }
        return 0;

        z = 0;

        //pomiary dla szukania
        for (int i = 0; i < 1000; i++) {
            int los = losowa_liczba(0, p);
            int wybrana = dane[los];

            hash_al_szuk(tab, m, wybrana);
        }
        std::cout << "Liczba pomiarow dla szukania:";
        std::cout << z << "\n\n";

        
        //pomiary dla wstawiania 
        z = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) {
            hash_al_wstaw(tab, m, dane[i + p]);
        }
    }

    for (int i = 0; i < 10; i++)
    {
        int p = i * 0.1 * m;
        for (int j = 0; j < m; j++)
        {
            tab[j] = EMPTY;
        }

        if (i != 0)
        {
            for (int i = 0; i < p; i++)
            {
                hash_al_wstaw_kw(tab, m, dane[i]);
            }
        }
        return 0;

        z = 0;

        //pomiary dla szukania 
        for (int i = 0; i < 1000; i++) {
            int los = losowa_liczba(0, p);
            int wybrana = dane[los];

            hash_al_szuk_kw(tab, m, wybrana);
        }
        std::cout << "Liczba pomiarow dla szukania kwadratowego:";
        std::cout << z << "\n\n";


        //pomiary dla wstawiania kw
        z = 0;
        auto start = std::chrono::high_resolution_clock::now();
        for (int i = 0; i < 10000; i++) {
            hash_al_wstaw_kw(tab, m, dane[i + p]);
        }
    }*/
}
