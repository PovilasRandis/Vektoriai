# Vektoriai
Realizuota vektorių klasė

### Pushback() test'inimas 

|                 |     10.000    |    100.000   |  1.000.000  | 10.000.000 | 100.000.000 |
| :-------------- |:------------- | :----------- | :---------- | :--------- | :---------- |
| std::vector     |   0.001995    |   0.0040026  |   0.0399758 | 0.388777   | 2.43061     |
| Mano Vector     |   0.0009987   |   0.00599    |   0.0439739 | 0.592662   | 2.65124     |


Užpildant vektorius 100.000 kartų, capacity() == size():
* std::vector - 18 kartų
* Mano Vector - 18 kartų

### Studentų test'inimas su 100.000 studentų

|                 |  Bendras laikas |
| :-------------- |:--------------- | 
| std::vector     |    0.115806     |
| Mano Vector     |    0.134953     |


## <a name="at"></a>Vector::at()
```c++
reference at(size_type position);
const_reference at(size_type position) const;
```
* Grąžina elementą tam tikroje vietoje. Jei paduotas argumentas yra už ribų, yra iškviečiamas `std::out_of_range` error.
```c++
// naudojimo pavyzdys
mVector<int> v {1,2,3};

cout<< v.at(0) <<endl; // 1
cout<< v.at(2) <<endl; // 3
cout<< v.at(1000) <<endl; // (mVector::at) out of range!!!
```

## <a name="rbegin"></a>Vector::rbegin()
```c++
reverse_iterator rbegin();
const_reverse_iterator rbegin() const;
```
* Grąžina iteratorių į pirmą elementą apverstame masyve, tai ekvivalentu end() iteratoriui paprastame vektoriuje.
```c++
// naudojimo pavyzdys
mVector<int> v {1,2,3};

std::reverse_iterator<int*> rbegin = v.rbegin();
int size = v.size();
for(int i = 0; i<size; i++) {
    cout<< *(rbegin + i)<<" "; // 3 2 1
}
```

## <a name="size"></a>Vector::size()
```c++
size_type size() const;
```
* Grąžina elementų skaičių vektoriuje
```c++
// naudojimo pavyzdys
mVector<int> v {1,2,3}; 
mVector<int> g; 
cout<<v.size()<<endl; // 3
cout<<g.size()<<endl; // 0
```

## <a name="insert"></a>Vector::insert()
```c++
iterator insert(iterator pos, const T& value);
iterator insert(iterator pos, size_type count, const T& value);
iterator insert(iterator pos, InputIterator first, InputIterator last);
iterator insert(iterator pos, std::initializer_list<T> initializer);
```
* Įdeda elementą prieš nurodytą vietą:  
  1.) Įdeda vieną elementą  
  2.) Įdeda `count` kopijų elemento  
  3.) Įdeda elementus iš iteratorių srauto  
  4.) Įdeda elementus iš `std::initializer_list`  
  
```c++
 Vector<int> v {1,2,3};
 Vector<int> g {9, 8, 7};

v.insert(v.begin() + 2, 77); // 1 2 (77) 3
v.insert(v.begin() + 2, 3, 77); // 1 2 (77 77 77) 3
v.insert(v.begin() + 2, g.begin(), g.end()); // 1 2 (9 8 7) 3
v.insert(v.begin() + 2, {4,4,4}); // 1 2 (4 4 4) 3
```

## <a name="equal"></a>Vector:: palyginimo operatorius '=='
```c++
bool operator==(mVector<T>& other);
```
* Patikrina ar du Vector klasės objektai yra lygūs.
```c++
Vector<int> v {1,2,3};
Vector<int> g {1,2,3};
Vector<int> c {3,4,5};

cout<< (v == g) << endl; // 1
cout<< (v == c) << endl; // 0
```
