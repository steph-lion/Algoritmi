#include <iostream>
#include <fstream>
#include <cstdlib>

using namespace std;

void sort(int* s, int* f, int n) {
    for(int i = 0; i < n; i++) {
        for(int j = i; j < n; j++) {
            if(f[i] > f[j]) {
                int tmp = f[i];
                f[i] = f[j];
                f[j] = tmp;
                
                tmp = s[i];
                s[i] = s[j];
                s[j] = tmp;
            }
        }
    }
}

//Attività i di indice più alto ma minore di j e compatibile con l'attività j
int p(int* s, int* f, int j) {
    int k = 0;
    for(int i = 1; i < j; i++) {
        if(f[i] <= s[j])
            k = i;
    }
    return k;
}

int activity(int* s, int* f, int n){
   int* a = new int[n];
   a[0] = 0;
   for(int i = 1; i < n; i++) {
       int x = f[i] - s[i] + a[p(s,f,i)], y = a[i-1];
       a[i] = (x > y ? x : y);
   }
   return a[n-1];
}

//Gli indici delle attività iniziano da 1
void metodo(ifstream& input, ofstream& output) {
     int n;
     input >> n;
     n++;
     int* s = new int[n];
     int* f = new int[n];
     s[0] = f[0] = 0;
     string x;
     for(int i = 1; i < n; i++) {
        input >> x;
        s[i] = atoi(x.substr(1).c_str());
        input >> x;
        f[i] = atoi(x.substr(0, x.length()-1).c_str());
     }
     //Le attività vengono ordinate in ordine di fine
     sort(s, f, n);
     output << activity(s, f, n) << endl;
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}