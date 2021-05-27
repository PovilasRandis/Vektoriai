#include "vektoriai.hpp"
#include <iostream>
#include <vector>
#include "timer.h"

using namespace std;

int main()
{
    int kiek = 0, kiek2 = 0;
    Timer timer;
    // Pradėti v1 užpildymo laiko matavimą
    unsigned int sz =  10000;

    int mem_keitimas_1 = 0;

    timer.reset();
    std::vector<int> v1;
    for (int i = 1; i <= sz; ++i) {
        if(v1.size() == v1.capacity()) kiek += 1;
        v1.push_back(i);
    }
    cout<<"std::vector laikas su " << sz << ": "<< timer.current_time()<<endl;


    int mem_keitimas_2 = 0;

    timer.reset();
    Vector<int> v2;
    for (int i = 1; i <= sz; ++i) {
        if(v2.size() == v2.capacity()) kiek2 += 1;
        v2.push_back(i);
    }
    
    cout<<"Sukurtojo vektoriaus laikas su " << sz << ": "<< timer.current_time()<<endl;
    cout<<"std::vector pakeitimai: "<<mem_keitimas_1<<endl;
    cout<<"Sukurtojo vektoriaus pakeitimai: "<<mem_keitimas_2<<endl;
}