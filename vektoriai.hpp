
//#pragma once

#include <iostream>
#include <memory>
#include <stdexcept>

using namespace std;

//čia tam kad konvertuotusi iteratoriai 
    template<typename InputIterator>
    using RequireInputIterator = typename
    std::enable_if<std::is_convertible<typename
                                       std::iterator_traits<InputIterator>::iterator_category,
                                       std::input_iterator_tag>::value>::type;


template <class T>
class Vector
{
    public:
        using iterator = T*;
        using const_iterator = const T*;
        using size_type = size_t;
        using value_type = T;
        using allocator_type = allocator<T>;
        using difference_type = ptrdiff_t;

        using reference = value_type&;
        using const_reference = const value_type&;
        using pointer = typename std::allocator_traits<allocator_type>::pointer;
        using const_pointer = typename std::allocator_traits<allocator_type>::const_pointer;
        using reverse_iterator = std::reverse_iterator<iterator>;
        using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    private:
        iterator data; //pirmasis elementas
        iterator avail; // pirmasis po paskutinio sukonstruoto elem
        iterator limit; //kitas po paskutinio elementas

        //atminties išskyrimo valdymui
        allocator<T> alloc;

        // inicializuoja tuščia vektorių
        void create() { data = avail = limit = nullptr; }

        // išskiria n elemetų ir juos užpildo val reikšme
        void create(size_type n, const T& val) {
            data = alloc.allocate(n);
            limit = avail = data + n;
            uninitialized_fill(data, limit, val);
        }

        //išskiria ir užpildo vietą iš iteratorių
        template<class InputIterator>
        void create(InputIterator i, InputIterator j) {
                data = alloc.allocate(j-i);
                limit = avail = uninitialized_copy(i, j, data);
        }

        void create_move(iterator i, iterator j) {
                data = alloc.allocate(j-i);
                limit = avail = uninitialized_copy(
                        std::make_move_iterator(i),
                        std::make_move_iterator(j), data);
        }

        //sunaikina elementus ir atlaisvina vietą
        void uncreate() {
            if(data) {
                //sunaikinti sukonstruotus elementus
                iterator it = avail;
                while(it != data) alloc.destroy(--it);

                //atlaisvinti iskirta atminti
                alloc.deallocate(data, limit - data);
            }
            //reset pointers
            data = limit = avail = nullptr;
        }

        //padidina vektoriaus vietą
        void grow(size_type new_cap = ptrdiff_t(1), bool manual_cap = false) {
            
            size_type new_size;
            if(manual_cap) new_size = new_cap;
            else new_size = max(new_cap, 2*capacity());

            iterator new_data = alloc.allocate(new_size);
            iterator new_avail = uninitialized_copy(data, avail, new_data);
            uncreate();

            data = new_data;
            avail = new_avail;
            limit = data + new_size;
        }
        void unchecked_append(const T& val) { alloc.construct(avail++, val); }
        void unchecked_append(const T&& val) { alloc.construct(avail++, std::move(val)); }

    public:
        
        //konstruktoriai
        ////////////////

        //default konstruktorius
        Vector() { create(); } 

        //konstruktorius, kuris užpildo vektorių n vietų ir val reikšme
        explicit Vector(size_type n, const T& val = T{}) { create(n, val); }

        //konstruktorius, kuris sukuria vektorių iš iteratorių
        template <class InputIterator, class = RequireInputIterator<InputIterator>>
        Vector(InputIterator first, InputIterator last) { create(first, last); }

        //initializer konstruktorius
        Vector(std::initializer_list<T> initializer)
        { create(initializer.begin(), initializer.end()); }

        //copy konstruktorius
        Vector(const Vector& other) { create(other.begin(), other.end()); }

        //move konstruktorius
        Vector(Vector&& other) 
        { create_move(other.begin(), other.end()); other.uncreate(); }

        //destruktorius
        ~Vector() { uncreate(); }

        //copy operatorius
        Vector& operator=(const Vector& other);

        //move operatorius
        Vector& operator=(Vector&& other);

        //initializer list operatorius
        Vector& operator=(std::initializer_list<T> initializer);
        
        //assign užpildo *count* elemetų su *value* reikšme
        void assign(size_type count, const T& value);

        //assign užpildo iš iteratoių srauto
        template <class InputIterator, class = RequireInputIterator<InputIterator>>
        void assign(InputIterator first, InputIterator last) {
            uncreate();
            create(first, last);
        }

        //assign užpildo iš initializer listo
        void assign(std::initializer_list<T> initializer);

        //grąžina allocator
        allocator_type get_allocator() const { return alloc; }



        ///////////////
        //Element access

        // at access
        reference at(size_type position) {
            if(position >= 0 && position < size()) {
                return data[position];
            } else { throw std::out_of_range("(Vector::at) out of range!!!"); }
        }

        const_reference at(size_type position) const {
            if(position >= 0 && position < size()) {
                return data[position];
            } else { throw std::out_of_range("(Vector::at) out of range!!!"); }
        }

        //random-access
        reference operator[] (size_type i) { return data[i]; }
        const_reference operator[] (size_type i) const { return data[i]; }

        // pirmas elementas
        reference front() { return data[0]; }
        const_reference front() const {return data[0];}

        //paskutinis elementas
        reference back() { return data[size() - 1] ;}
        const_reference back() const {return data[size() - 1]; }

        //gauti pointerį į pirmą elementą
        T* get_data() { return data; }
        const T* get_data() const { return data; }

        //Element access
        ////////////////
        

        ///////////
        //Iterators
        
        iterator begin() { return data; }
        const_iterator begin() const { return data; }
        iterator end() {return avail;}
        const_iterator end() const {return avail;}
        reverse_iterator rbegin() { return reverse_iterator(end()); }
        const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); }
        reverse_iterator rend()  { return reverse_iterator(begin()); }
        const_reverse_iterator rend() const { return const_reverse_iterator(begin()); }

        //Iterators
        ///////////


        //////////
        //Capacity
        bool empty() { return begin() == end(); }
        size_type size() const { return avail - data;}
        size_type max_size() const { return alloc.max_size(); }
        void reserve(size_type new_cap);
        size_type capacity() const { return limit - data; } 
        void shrink_to_fit();

        //Capacity
        //////////


        ///////////
        //Modifiers

        void clear();
        iterator insert(iterator pos, const T& value) {
            size_type count = 1;
            return insert(pos, count, value);
        }

        iterator insert(iterator pos, size_type count, const T& value) {
            if(pos < begin() || pos > end()) throw std::out_of_range("(Vector::insert) out of range!!!");
            if(size() + count > capacity()) {

                size_type before = pos - begin();
                grow(capacity() + count, true);
                pos = before + begin();
            } 

            // pastumti elementus i prieki
            for(iterator i = avail - 1; i >= pos; i--) alloc.construct(i + count, *i);

            //padidiname savo sukontruotų elementų iteratorių
            avail += count;

            //užpildome dabar tuščia vietą reikšmėmis
            uninitialized_fill(pos, pos + count, value);

            return pos;

        }

        template <class InputIterator, class = RequireInputIterator<InputIterator>>
        iterator insert(iterator pos, InputIterator first, InputIterator last) {
            if(pos < begin() || pos > end()) throw std::out_of_range("(Vector::insert) out of range!!!");

            size_type count = last - first;
            if(size() + count > capacity()) {

                size_type before = pos - begin();
                grow(capacity() + count, true);
                pos = before + begin();
            }

            // pastumti elementus i prieki
            for(iterator i = avail - 1; i >= pos; i--) alloc.construct(i + count, *i);

            //padidiname savo sukontruotų elementų iteratorių
            avail += count;
            uninitialized_copy(first, last, pos);
            return pos;
        }

        iterator insert(iterator pos, std::initializer_list<T> initializer) {
            return insert(pos, initializer.begin(), initializer.end());
        }

        template<class... Args>
        iterator emplace(iterator pos, Args&&... args){
            if(pos < begin() || pos > end()) throw std::out_of_range("(Vector::insert) out of range!!!");

            size_type count = 1;
            if(size() + count > capacity()) {

                size_type before = pos - begin();
                grow(capacity() + count, true);
                pos = before + begin();
            } 

            // pastumti elementus i prieki
            for(iterator i = avail - 1; i >= pos; i--) alloc.construct(i + count, *i);

            //padidiname savo sukontruotų elementų iteratorių
            avail += count;

            //užpildome dabar tuščia vietą reikšmėmis
            alloc.construct(pos, std::forward<Args>(args)...);

            return pos;
        }

        iterator erase(iterator pos) {
            if(pos < begin() || pos > end()) throw std::out_of_range("(Vector::insert) out of range!!!");
            if(pos == end()) return end();
            alloc.destroy(pos);
            avail = uninitialized_copy(pos + 1, end(), pos);
            return pos;
        }

        iterator erase(iterator first, iterator last) {
            if(first < begin() || last > end()) throw std::out_of_range("(Vector::insert) out of range!!!");

            iterator it = last;
            while(it != first) alloc.destroy(--it);
            avail = uninitialized_copy(last, end(), first);
            return last;
        }


        void push_back(const T& val) {
            if (avail == limit) grow();
            unchecked_append(val);
        }

        void push_back(const T&& val) {
            if (avail == limit) grow();
            unchecked_append(std::move(val));
        }

        template<class... Args>
        void emplace_back(Args&&... args){
            alloc.construct(avail++, std::forward<Args>(args)...);
        }

        void pop_back() {
            alloc.destroy(--avail);
        }

        void resize(size_type count, const value_type& value = 0) {
            if(size() > count) erase(begin() + count, end());
            if(size() < count) {

                size_type old_avail = end() - begin();
                if(capacity() < count) grow(count, true);
                avail =  begin() + count;

                uninitialized_fill(begin() + old_avail, avail, value);
            }      
        }

        void swap(Vector<T>& other) {
            std::swap(data, other.data);
            std::swap(avail, other.avail);
            std::swap(limit, other.limit);
        }

        //Modifiers
        ///////////


        ////////////////////////
        //Non - member functions

        bool operator==(Vector<T>& other) {
            return this->size () == other.size() && std::equal(this->begin(), this->end(), other.begin());
        }

        bool operator!=(Vector<T>& other) {
            return !(*this == other);
        }

        bool operator<(Vector<T>& other) {
            return std::lexicographical_compare(this->begin(), this->end(), other.begin(), other.end());
        }

        bool operator<=(Vector<T>& other) {
            return !(other < *this);
        }

        bool operator>(Vector<T>& other) {
            return other < *this;
        }

        bool operator>=(Vector<T>& other) {
            return !(*this < other);
        }
        
        //Non - member functions
        ////////////////////////

    
};

template <class T>
Vector<T>& Vector<T>::operator=(const Vector& other) {
    if(&other != this) {
        uncreate();
        create(other.begin(), other.end());
    } 
    return *this;
}


template <class T>
Vector<T>& Vector<T>::operator=(Vector&& other) {
    if(&other != this) {
        uncreate();
        create_move(other.begin(), other.end());
        other.uncreate();
    }
    return *this;
}

template <class T>
Vector<T>& Vector<T>::operator=(std::initializer_list<T> initializer) {
    uncreate();
    create(initializer.begin(), initializer.end());
    return *this;
}

template <class T>
void Vector<T>::assign(size_type count, const T& value) {
    uncreate();
    create(count, value);
}

template <class T>
void Vector<T>::assign(std::initializer_list<T> initializer) {
    uncreate();
    create(initializer.begin(), initializer.end());
}

template <class T>
void Vector<T>::reserve(Vector<T>::size_type new_cap) {
    if(new_cap > capacity()) {
        grow(new_cap, true);
    }
}

template <class T>
void Vector<T>::shrink_to_fit() {
    grow(size(), true);
}

template <class T>
void Vector<T>::clear() {
    iterator it = avail;
    while(it != data) alloc.destroy(--it);
    avail = data;
}