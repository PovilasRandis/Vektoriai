
//#pragma once

#include <algorithm>
#include <limits>
#include <iostream>

using namespace std;

template <class P>
class Vector {
private:
    P * elem;
    unsigned int _size;
    unsigned int _capacity;

public:
// Konstruktoriai
    Vector();
    Vector(unsigned int size);
    Vector(unsigned int size, const P & initial);
    Vector(const Vector<P> & v);   

// Destruktorius
    ~Vector();

// Iteratoriai
    typedef P * iterator;
    iterator begin();
    iterator end(); 

// Dydziai
    unsigned int capacity() const;
    size_t max_size() const;
    unsigned int size() const;
    bool empty() const;
    void reserve(unsigned int capacity);   
    void resize(unsigned int size);
    void shrink_to_fit();

// Elementu pasiekimas
    P & operator[](unsigned int index);  
    P & at(int pos);
    P & front();
    P & back();

// Modifikatoriai
    void push_back(const P & value); 
    void pop_back(); 
    void clear();
    iterator insert(iterator ndx, const P& val);
    iterator erase(iterator ndx);
    iterator erase(iterator first, iterator last);
    void swap(Vector& vect);
    void swap(P& x, P& y);

// Operatoriai
    Vector<P> & operator=(const Vector<P> &);
    Vector<P> & operator=(Vector&&);
    bool operator==(const Vector<P>& vect) const;
    bool operator>=(const Vector<P>& vect) const;
    bool operator<=(const Vector<P>& vect) const;
    bool operator!=(const Vector<P>& vect) const;
    bool operator>(const Vector<P>& vect) const;
    bool operator<(const Vector<P>& vect) const;
};


// Konstruktoriai
template<class P>
Vector<P>::Vector(){
    _capacity = 0;
    _size = 0;
    elem = 0;
}

template<class P>
Vector<P>::Vector(const Vector<P> & v){
    _size = v._size;
    _capacity = v._capacity;
    elem = new P[_size];  
    for (unsigned int i = 0; i < _size; i++)
        elem[i] = v.elem[i];  
}

template<class P>
Vector<P>::Vector(unsigned int size){
    _capacity = size;
    _size = size;
    elem = new P[size];
}

template<class P>
Vector<P>::Vector(unsigned int size, const P & initial){
    _size = size;
    _capacity = size;
    elem = new P [size];
    for (unsigned int i = 0; i < size; i++)
        elem[i] = initial;
}


// Destruktorius
template<class P>
Vector<P>::~Vector(){
    delete[] elem;
}


// Iteratoriai
template<class P>
typename Vector<P>::iterator Vector<P>::begin(){
    return elem;
}

template<class P>
typename Vector<P>::iterator Vector<P>::end(){
    return elem + size();
}


// Dydziai
template<class P>
unsigned int Vector<P>::capacity()const{
    return _capacity;
}

template <class P>
size_t Vector<P>::max_size() const 
{
    return std::numeric_limits<size_t>::max();
}

template<class P>
unsigned int Vector<P>::size()const{
    return _size;
}

template <class P>
bool Vector<P>::empty() const{
    return (_size == 0);
}

template<class P>
void Vector<P>::reserve(unsigned int capacity){
    if(elem == 0){
        _size = 0;
        _capacity = 0;
    }    
    P * NewElem = new P [capacity];
    unsigned int l_Size = capacity < _size ? capacity : _size;

    for (unsigned int i = 0; i < l_Size; i++)
        NewElem[i] = elem[i];

    _capacity = capacity;
    delete[] elem;
    elem = NewElem;
}

template<class P>
void Vector<P>::resize(unsigned int size){
    reserve(size);
    _size = size;
}

template <class P>
void Vector<P>::shrink_to_fit() {
    P* temp = new P[_size];

    for (int i = 0; i < _size; i++)
        temp[i] = elem[i];

    delete[] elem;
    elem = temp;
    _capacity = _size;
}

// Elementu pasiekimas
template<class P>
P& Vector<P>::operator[](unsigned int index){
    return elem[index];
}  

template <class P>
P& Vector<P>::at(int pos){
    if (pos >= _size)
        cout << "The index is not in range.";
    return elem[pos];
}

template<class P>
P& Vector<P>::front(){
    return elem[0];
}

template<class P>
P& Vector<P>::back(){
    return elem[_size - 1];
}


// Modifikatoriai
template<class P>
void Vector<P>::push_back(const P & v){
    if (_size >= _capacity)
        reserve(_capacity + 1000);
    elem[_size++] = v;
}

template<class P>
void Vector<P>::pop_back(){
    _size--;
}

template <class P>
void Vector<P>::clear(){
    _capacity = 0;
    _size = 0;
    elem = 0;
}

template<class valueType>
typename Vector<valueType>::iterator Vector<valueType>::erase(iterator ndx) 
{
    int i = 0;
    auto it = (this).begin();
    for (it; it != ndx; it++, i++);
    for (auto it = ndx + 1; it != (this).end(); it++, i++)
        elem[i] = elem[i + 1];
    _size--;
    return ndx;
}

template<class valueType>
typename Vector<valueType>::iterator Vector<valueType>::erase(iterator first, iterator last) 
{
    int i = 0;
    int temp = 0;
    auto it = (this).begin();
    for (it; it != first; it++, i++);
    for (it = first; it != last; it++, temp++, i++);
    for (auto it = last; it != (this).end(); it++, i++)
        elem[i - temp] = elem[i];
    _size -= temp;
    return last;
}

template<class P>
void Vector<P>::swap(Vector& vect){
    swap(elem, vect.elem);
    swap(_size, vect._size);
    swap(_capacity, vect._capacity);
}

template <class P>
void Vector<P>::swap(P& x, P& y){
    P temp = x;
    x = y;
    y = temp;
}

template<class P>
typename Vector<P>::iterator Vector<P>::insert(iterator iter, const P& val){
    int i = 0;

    if (_capacity > _size) 
    {
        for (iterator it(elem + _size); it != iter; it--, i++)
            elem[_size - i] = elem[_size - i - 1];
        iter = val;
        _size++;
    }
    else 
    {
        P temp = new P [_size + 1];
        for (iterator it(elem); it != iter; it++, i++)
            temp[i] = elem[i];
        temp[i] = val;
        i++;

        for (iterator it(elem + i + 1); it != elem + _size + 2; it++, i++)
            temp[i] = elem[i - 1];
        delete[] elem;
        elem = temp;
        _size++;
        _capacity = _size;
    }
    return iter;
}

// Operatoriai
template <class P>
Vector<P>& Vector<P>::operator=(Vector&& vec){
    if (&vec == this)
        return *this;
    elem = vec.elem;
    elem = vec._size;
    _capacity = vec._capacity;
    vec.elem = nullptr;
    vec._size = 0;
    vec._capacity = 0;
    return *this;
}

template<class P>
Vector<P> & Vector<P>::operator=(const Vector<P> & v){
    delete[ ] elem;
    _size = v._size;
    _capacity = v._capacity;
    elem = new P [_size];
    for (unsigned int i = 0; i < _size; i++)
        elem[i] = v.elem[i];
    return *this;
}
template<class P>
bool Vector<P>::operator==(const Vector<P>& vect) const {
    if (_size == vect._size && _capacity == vect._capacity) 
    {
        for (int i = 0; i < _size; i++)
            if (elem[i] != vect.elem[i])
                return false;
        return true;
    }
    return false;
}

template<class P>
bool Vector<P>::operator>=(const Vector<P>& vect) const{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (elem[i] <= vect.elem[i])
                return false;
        return true;
    }
    else return (_size >= vect._size && _capacity >= vect._capacity);
}

template<class P>
bool Vector<P>::operator<=(const Vector<P>& vect) const{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (elem[i] >= vect.elem[i])
                return false;
        return true;
    }
    else return (_size <= vect._size && _capacity <= vect._capacity);
}

template<class P>
bool Vector<P>::operator!=(const Vector<P>& vect) const{
    return !operator==(vect);
}

template<class P>
bool Vector<P>::operator>(const Vector<P>& vect) const{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (elem[i] < vect.elem[i])
                return false;
        return true;
    }
    else return (_size > vect._size && _capacity > vect._capacity);
}

template<class P>
bool Vector<P>::operator<(const Vector<P>& vect) const{
    if (_size == vect._size && _capacity == vect._capacity)
    {
        for (int i = 0; i < _size; i++)
            if (elem[i] > vect.elem[i])
                return false;
        return true;
    }
    else return (_size < vect._size && _capacity < vect._capacity);
}