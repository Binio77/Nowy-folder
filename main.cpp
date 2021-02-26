#include<iostream>
#include<fstream>
#include <chrono> 
#include<ctime>
#include<algorithm>
#include <map>
#include<vector>
using namespace std::chrono; 
using namespace std;

float selection(int tab[], int n)
{  
    auto start = high_resolution_clock::now();

    int i, j, min_index;  
    for (i = 0; i < n-1; i++)  
    {  
        min_index = i;
        for (j = i+1; j < n; j++)  
            if (tab[j] < tab[min_index])  
                min_index = j;  
        swap(tab[min_index], tab[i]);  
    }

    auto end = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(end - start).count();
    return duration  * 1.0 / nano::den;
}  

float alg_sort(int tab[], int n)
{
    auto start = high_resolution_clock::now();

    sort(tab, tab+n);

    auto end = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(end - start).count();
    return duration * 1.0 / nano::den;
}

float bucket(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 

    map <int, vector <int>> b;                     
    int max_value = *max_element(tab, tab+n) + 1;   
    for (int i=0; i<n; i++)                        
    {
        int bi = 1.0 * n * tab[i] / max_value;    
        b[int(bi)].push_back(tab[i]);
    }

    for (int i=0; i<n; i++)                         
       sort(b[i].begin(), b[i].end());
 
    int bucket = 0;
    for (int i = 0; i < n; i++)                     
        for (int j = 0; j < b[i].size(); j++)
          tab[bucket++] = b[i][j];

    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start).count();
    return duration * 1.0 / nano::den;
}

float bubble(int tab[], int n)
{
    auto start = high_resolution_clock::now();

    for(int i=0; i<n-1; i++)
        for (int j=0; j<n-i-1; j++)  
            if (tab[j] > tab[j+1])  
                swap(tab[j], tab[j+1]);

    auto end = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(end - start).count();
    return duration * 1.0 / nano::den;
}

float insert(int tab[], int n)
{
    auto start = high_resolution_clock::now(); 

    for(int i=1; i<n; i++)
    {
        int elem = tab[i];
        int k = i-1;
        
        while(k >= 0 && tab[k] > elem)
        {
            tab[k+1] = tab[k];
            k--;
        }
        tab[k+1] = elem;
    }

    auto end = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(end - start).count();
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

    const string nazwySort[] {"Bubble", "Bucket", "Insert", "Algorithm", "Selection"};
    const string nazwyWypel[] {"Optymistycznie", "Pesymistycznie", "Losowo"};
    const int rozmiary[] {200, 500, 1000, 10000, 100000};

    float (*(wskaz_sortowania[5]))(int [], int);
    wskaz_sortowania[0] = bubble;
    wskaz_sortowania[1] = bucket;
    wskaz_sortowania[2] = insert;
    wskaz_sortowania[3] = alg_sort;
    wskaz_sortowania[4] = selection;

    void (*(wskaz_wypelnienia[3]))(int[], int);
    wskaz_wypelnienia[0] = odPdoK;
    wskaz_wypelnienia[1] = odKdoP;
    wskaz_wypelnienia[2] = losowo;

    for(int w=0; w<3; w++)
    {
        cout<<nazwyWypel[w]<<endl;
        for(int size=0; size<5; size++)
        {
            int n = rozmiary[size];
            int tab[n];
            cout << "[" << rozmiary[size] << "] ";
            for(int s=0; s<5; s++)
            {
                wskaz_wypelnienia[w](tab, n);
                f_wyj << wskaz_sortowania[s](tab, n) << '\t';
                cout << nazwySort[s] << ", " << flush ;
            }
            cout << endl;
            f_wyj << endl;
        }
        f_wyj << endl;
    }

    getchar();
    getchar();
    return 0;
}
