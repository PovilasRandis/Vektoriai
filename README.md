# Vektoriai
Realizuota vektorių klasė

### Pushback() test'inimas 

|                 |     10.000    |    100.000   |  1.000.000  | 10.000.000 | 100.000.000 |
| :-------------- |:------------- | :----------- | :---------- | :--------- | :---------- |
| std::vector     |   0.001995    |   0.0040026  |   0.0399758 | 0.388777   | 2.43061     |
| Mano Vector     |   0.0009987   |   0.00599    |   0.0439739 | 0.592662   | 2.65124     |


Užpildant vektorius 100.000 kartų, capacity() == size():
* std::vector - 27 kartų
* Mano Vector - 27 kartų

### Studentų test'inimas su 100.000 studentų

|                 |  Bendras laikas |
| :-------------- |:--------------- | 
| std::vector     |    0.349473     |
| Mano Vector     |    0.342772     |
