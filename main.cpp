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
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    return duration * 1.0 / nano::den;
}  

float alg_sort(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 
    sort(tab, tab+n);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    return duration * 1.0 / nano::den;
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
                continue;

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    return duration * 1.0 / nano::den;
}

float bubble(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 
    for(int i=0; i<n-1; i++)
    {
        for(int j=0; j<n-i-1; j++)
        {
            if(tab[i] > tab[j])
                swap(tab[i], tab[j]);
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    return duration * 1.0 / nano::den;
}

float insert(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 
    for(int i=1; i<n; i++)
    {
        int elem = tab[i];
        int k = i-1;
        while(tab[k] > elem && k>0)
        {
            tab[k+1] = tab[k];
            k--;
        }
        tab[k+1] = elem;
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    return duration * 1.0 / nano::den;
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
    
    float (*(wskaz_funkcji[5]))(int [], int);
    wskaz_funkcji[0] = bubble;
    wskaz_funkcji[1] = index;
    wskaz_funkcji[2] = insert;
    wskaz_funkcji[3] = alg_sort;
    wskaz_funkcji[4] = selection;

    for(int i=0; i<5; i++)
    {
        int n = rozmiary[i];
        int tab[n];

        for(int j=0; j<5; j++)
        {
            odPdoK(tab, n);
            f_wyj << wskaz_funkcji[j](tab, n) << '\t';
            cout << "a"<<flush ;
        }
        cout << endl;
        f_wyj << endl;
    }
    cout << "1" << endl;
    f_wyj << endl;
    
    for(int i=0; i<5; i++)
    {
        int n = rozmiary[i];
        int tab[n];

        for(int j=0; j<5; j++)
        {
            odKdoP(tab, n);
            f_wyj << wskaz_funkcji[j](tab, n) << '\t';
            cout << "a"<<flush ;
        }
        cout << endl;
        f_wyj << endl;
    }
    cout << "2" << endl;
    f_wyj << endl;

    for(int i=0; i<5; i++)
    {
        int n = rozmiary[i];
        int tab[n];

        for(int j=0; j<5; j++)
        {
            losowo(tab, n);
            f_wyj << wskaz_funkcji[j](tab, n) << '\t';
            cout << "a"<<flush ;
        }
        cout << endl;
        f_wyj << endl;
    }
    cout << "3" ;
    cout << "KONIEC" ;

    getchar();
    getchar();
    return 0;
}
