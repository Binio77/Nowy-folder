#include<iostream>
#include<fstream>
#include <chrono> 
#include<ctime>
#include<algorithm>
using namespace std::chrono; 
using namespace std;

float selection(int tab[], int n)
{  
    auto start = high_resolution_clock::now(); 
    int i, j, min_idx;  
  
    for (i = 0; i < n-1; i++)  
    {  
        min_idx = i;  
        for (j = i+1; j < n; j++)  
        if (tab[j] < tab[min_idx])  
            min_idx = j;  
  
        swap(tab[min_idx], tab[i]);  
    }  
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    return duration.count()/100000.0;
}  

float alg_sort(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 
    sort(tab, tab+n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    return duration.count()/100000.0;
}

float index(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 
    int x = *max_element(tab, tab+n) + 1;
    int B[x] {0};
    for(int i=0; i<n; i++)
        B[tab[i]]++;

    for(int i=0; i<x; i++)
        if(B[i] != 0)
            for(int j=0; j<B[i]; j++)
                break;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    return duration.count()/100000.0;
}

float bubble(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 
    for(int i=0; i<n; i++)
    {
        for(int j=i+1; j<n; j++)
        {
            if(tab[i] > tab[j])
                swap(tab[i], tab[j]);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    return duration.count()/100000.0;
}

float insert(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 
    for(int i=0; i<n; i++)
    {
        int elem = tab[i];
        int k = i-1;
        while(tab[k] > elem)
        {
            tab[k+1] = tab[k];
            k--;
        }
        tab[k+1] = elem;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start); 
    return duration.count()/100000.0;
}

void odPdoK(int tab[], int n)
{
    for(int i=0; i<n; i++)
        tab[i] = i;
}
void odKdoP(int tab[], int n)
{
    for(int i=0; i<n; i++)
        tab[i] = n-i;
}

void losowo(int tab[], int n)
{
    for(int i=0; i<n; i++)
        tab[i] = rand() % 500 + 1;
}

int main()
{
    ofstream f_wyj ("wyjscie.txt");
    srand(time(NULL));

    int rozmiary[5] {200, 500, 1000, 10000, 100000};
    int tab1[200], tab2[500], tab3[1000], tab4[10000], tab5[100000];
    int *tablica[5] {tab1, tab2, tab3, tab4, tab5};
    
    for(int i=0; i<5; i++)
    {
        odPdoK(tablica[i], rozmiary[i]);
        f_wyj << bubble(tablica[i], rozmiary[i]) << '\t';
        cout << "a" ;
        odPdoK(tablica[i], rozmiary[i]);
        f_wyj << index(tablica[i], rozmiary[i]) << '\t';
        cout << "b" ;
        odPdoK(tablica[i], rozmiary[i]);
        f_wyj << insert(tablica[i], rozmiary[i]) << '\t';
        cout << "c" ;
        odPdoK(tablica[i], rozmiary[i]);
        f_wyj << alg_sort(tablica[i], rozmiary[i]) << '\t';
        cout << "d" ;
        odPdoK(tablica[i], rozmiary[i]);
        f_wyj << selection(tablica[i], rozmiary[i]) << endl;
        cout << "e"<< endl;
    }
    cout << "1" << endl;
    f_wyj << endl;
    
    for(int i=0; i<5; i++)
    {
        odKdoP(tablica[i], rozmiary[i]);
        f_wyj << bubble(tablica[i], rozmiary[i]) << '\t';
        cout << "a" ;
        odKdoP(tablica[i], rozmiary[i]);
        f_wyj << index(tablica[i], rozmiary[i]) << '\t';
        cout << "b" ;
        odKdoP(tablica[i], rozmiary[i]);
        f_wyj << insert(tablica[i], rozmiary[i]) << '\t';
        cout << "c" ;
        odKdoP(tablica[i], rozmiary[i]);
        f_wyj << alg_sort(tablica[i], rozmiary[i]) << '\t';
        cout << "d" ;
        odKdoP(tablica[i], rozmiary[i]);
        f_wyj << selection(tablica[i], rozmiary[i]) << endl;
        cout << "e" << endl ;
    }
    cout << "2" << endl;
    f_wyj << endl;

    for(int i=0; i<5; i++)
    {
        losowo(tablica[i], rozmiary[i]);
        f_wyj << bubble(tablica[i], rozmiary[i]) << '\t';
        cout << "a" ;
        losowo(tablica[i], rozmiary[i]);
        f_wyj << index(tablica[i], rozmiary[i]) << '\t';
        cout << "b" ;
        losowo(tablica[i], rozmiary[i]);
        f_wyj << insert(tablica[i], rozmiary[i]) << '\t';
        cout << "c" ;
        losowo(tablica[i], rozmiary[i]);
        f_wyj << alg_sort(tablica[i], rozmiary[i]) << '\t';
        cout << "d" ;
        losowo(tablica[i], rozmiary[i]);
        f_wyj << selection(tablica[i], rozmiary[i]) << endl;
        cout << "e" << endl;
    }
    cout << "3" ;
    cout << "KONIEC" ;

    return 0;
}
