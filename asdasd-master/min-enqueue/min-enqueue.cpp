#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

template <class H>
class MinHeap {
    private:
        H** A;
        int length;
        int heapsize;
        void swap(int i, int j);
        double compare(H* a, H* b) { return (*a) - (*b); }
        void heapify(int i);
        int left(int i) { return i << 1; }
        int right(int i) { return (i << 1)|1; }
        int parent(int i) { return i >> 1; }
    public:
        MinHeap(int size);
        MinHeap(H** v, int n);
        H* extractMin();
        MinHeap<H>* enqueue(H key);
        void buildHeap();
        int size() { return heapsize; }
        string print() const;
};

template <class H>
void MinHeap<H> :: swap(int i, int j) {
    H* tmp = A[i];
    A[i] = A[j];
    A[j] = tmp;
}

template <class H>
void MinHeap<H> :: heapify(int i) {
    int l = left(i);
    int r = right(r);
    int min = i;
    if(l <= heapsize && compare(A[i], A[l]) > 0) min = l;
    if(r <= heapsize && compare(A[min], A[r]) > 0) min = r;
    if(i != min) {
        swap(i, min);
        heapify(min);
    }
}

template <class H>
MinHeap<H> :: MinHeap(int size) {
    A = new H*[size];
    length = size;
    heapsize = 0;
}

template <class H>
MinHeap<H> :: MinHeap(H** v, int n) {
    A = v;
    length = n;
    heapsize = n - 1;
}

template <class H>
H* MinHeap<H> :: extractMin() {
    if(heapsize == 0) return NULL;
    swap(1,heapsize);
    heapsize--;
    heapify(1);
    return A[heapsize + 1];
}

template <class H> 
void MinHeap<H> :: buildHeap() {
    for(int i = heapsize/2; i > 0; i--)
        heapify(i);
}
 
template <class H>
MinHeap<H>* MinHeap<H> :: enqueue(H key) {
    if(heapsize == length - 1) cout << "Array Pieno\n";
    else {
        heapsize++;
        A[heapsize] = new H(key);
        int i = heapsize;
        while(i > 1 && compare(A[i], A[parent(i)]) < 0) {
            swap(i,parent(i));
            i = parent(i);
        }
    }
}

template <class H>
string MinHeap<H> :: print() const {
    stringstream out;
    for(int i = 1; i <= heapsize; i++)
        out << *(A[i]) << " ";
    return out.str();
}

void metodo(ifstream &input, ofstream &output) {
    string tipo;
    int n;
    input >> tipo;
    input >> n; 
    if(tipo == "int") {
        int x;
        MinHeap<int> *m = new MinHeap<int>(n+1);
        for(int i = 0; i < n; i++) {
            input >> x;
            m->enqueue(x);
        }

        output << m->print() << endl;
    }
    if(tipo == "bool") {
        bool x;
        MinHeap<bool> *m = new MinHeap<bool>(n+1);
        for(int i = 0; i < n; i++) {
            input >> x;
            m->enqueue(x);
        }
        
        output << m->print() << endl;
    }
    if(tipo == "char") {
        char x;
        MinHeap<char> *m = new MinHeap<char>(n+1);
        for(int i = 0; i < n; i++) {
            input >> x;
            m->enqueue(x);
        }
        
        output << m->print() << endl;
    }
    if(tipo == "double") {
        MinHeap<double> *m = new MinHeap<double>(n+1); 
        double x;
        for(int i = 0; i < n; i++) {
            input >> x;
            m->enqueue(x);
        }

        output << m->print() << endl;
    }
}

int main() {
    ifstream input("input.txt");
    ofstream output("output.txt");

    for(int i = 0; i < 100; i++)
        metodo(input, output);
}