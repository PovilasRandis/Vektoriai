#include <chrono>
#include <vector>
#include "vektoriai.hpp"

using namespace chrono;

template <class T>
void Isvedimas(Vector<T>);
Vector<int> VektoriausSukurimas(int, int);        
template <class T>      
void ArTuscias(Vector<T>);
void PushBackLaikas();

int main(){
    Vector<int> A = VektoriausSukurimas(3, 5);          // Vektoriaus priskyrimas
    Isvedimas(A);

    ArTuscias(A);                         

    PushBackLaikas();
}

Vector<int> VektoriausSukurimas(int size, int value){   // Vektoriaus sukurimas konstruktoriumi
    Vector<int> A(size, value);
    Isvedimas(A);
    return A;
}

template <class T>
void Isvedimas(Vector<T> A){
    cout << "Vektoriaus elementai: ";
    for (int i=0; i<A.size(); i++)                      // Spausdina vektoriaus elementus pasinaudojus size() funkcija
        cout << A[i] << " ";                            // Pasiekia atitinkama elementa su [] operatoriumi
    cout << endl << endl;
}

template <class T>
void ArTuscias(Vector<T> A){                            // Patikrina ar vektorius yra tuscias
    if (A.empty())
        cout << "Vektorius: tuscias" << endl << endl;
    else
        cout << "Vektorius: ne tuscias" << endl << endl;
}

void PushBackLaikas(){
    steady_clock::time_point beginvec1;
    steady_clock::time_point endvec1;
    steady_clock::time_point beginvec2;
    steady_clock::time_point endvec2;

    beginvec1 = steady_clock::now();

    int size[3] = {10000, 100000, 1000000};

    for (int indx = 0; indx < 3; indx++)
    {
        unsigned int sz = size[indx];
        cout << "Dydis: " << sz << endl;

        vector<int> vec1;
        for (int i = 1; i <= sz; ++i)
            vec1.push_back(i);

        endvec1 = steady_clock::now();

        beginvec2 = steady_clock::now();

        Vector<int> vec2;
        for (int i = 1; i <= sz; ++i)
            vec2.push_back(i);

        endvec2 = steady_clock::now();

        cout << "std::vector uztruko:" << duration_cast<milliseconds>(endvec1 - beginvec1).count() << "ms" << endl;
        cout << "Mano Vector uztruko: " << duration_cast<milliseconds>(endvec2 - beginvec2).count() << "ms" << endl;
        cout << endl;
    }
}