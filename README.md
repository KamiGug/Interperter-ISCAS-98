# Symulator ISCAS'89
ten projekt służy jako narzędzie typu cli do sprawdzania pokrycia testów, lub rozwiązywania układów kombinacyjnych (+ z przerzutnikiem typu D).

## Użycie

tester.exe nazwa_pliku_iscas [nazwa_pliku_ftl] [-f file_to_save_to] [-o] [-t] [-g] [-i] [-s] [-b] [-c nazwa_pliku_z_wektorami_testowymi] [-fotgisb file_to_save_to] [-otgisb] [-otgisbc nazwa_pliku_z_wektorami_testowymi] 

Kolejność podanych argumentów nie ma znaczenie.
Znaczenia przełączników podane są poniżej.
Nie podanie pliku (lub podanie nie istniejącego) .ftl nie wiąże się z błędem - zwyczajnie przeprowadzona zostanie prosta symulacja.

### Bramki:
- And
- Nand
- Nor
- Not
- Or
- Xnor
- Xor

### Przerzutniki:
- Delay

### Uwagi

Aby podać sygnał do wejścia zegarowego przerzutnika należy sygnał poprzedzić `clk:`.\
Nazwy nie są czułe na wielkość liter w plikach iscas oraz ftl.\
Istnieje możliwość podania stałego sygnału na wejście bramki - należy podać `high` lub `low`. 

## Domyślne moduły

### Interpreter
Istnieje jeden interpreter - ISCAS'89


### Generator wektorów testowych
Domyślny jest binarny generator wszystkich testów.

### Generator wyniku
Domyślnie generowany jest prosty raport z wejściami i wyjściami.

## Dostępne moduły

### Generator wektorów testowy
#### Binarny generator
Domyślny moduł w swojej kategorii (również dostępny pod przełącznikiem -b).
Traktuje wektor wejść jako liczbę binarną i generuje każdą możliwą liczbę na tej liczbie bitów.

#### CSV generator
Aby wykorzystać ten moduł należy podać przełącznik "-c", a po nim wskazać plik zawierający odpowiednie wektory.
Moduł pozwala wczytać wybrany podzbiór testów z pliku. 
Poziomy na wejściach są oddzielone znakiem ',', a kolejne wektory znakiem końca lini.


### Generator wyniku
Domyślnym zachowaniem jest zapis na ekran. 
Aby zapisać do pliku należy podać przełącznik "-f".
Aby zapisać na ekran i do pliku należy podać dwa przełączniki "-f" i "-o".
#### Prosty wypis
Domyślny moduł w swojej kategorii (również dostępny pod przełącznikiem -s).
Wypisuje prosty raport ze wszystkimi wejściami, wyjściami, usterkami i stanami zegara (jeśli są jakieś przerzutniki).

#### Prosty raport pokrycia
Aby wykorzystać ten moduł należy podać przełącznik "-t".
Oblicza współczynnik pokrycia usterek oraz wskazuje jeden wektor testowy dla którego istnieje rozróżnienie w wyjściach.

#### Generator pliku CSV grupujący po wektorach wejściowych
Aby wykorzystać ten moduł należy podać przełącznik "-i".
Grupuje resultaty o identycznych wektorach.
wypisuje dany wektor wejściowy.
Następnie zależnie od tego, czy wykorzystane były przerzutniki:
- jeśli tak: \
wypisuje jaka usterka była w danym teście, a następnie wektory wyjściowe wraz z sygnałem zegara
- jeśli nie: \
wypisuje wektor wyjściowy wraz z usterką
## Przykładowe pliki

### Plik w formacie ISCAS89

```
#some=comment

#asda

INPUT(input0)
INPUT(input1)
INPUT(input2)
INPUT(input3)
OUTPUT(output0)
nOt1=not(input1)
and1=and(input0, not1)
and2=and(input2, not1)
nor1=nor(input3, high)
output0=nor(and1, and2, nor1)
```

### Plik .ftl

```
gate_A->gate_B /1
gate_A->gate_B /0
gate_A /1
gate_B /1
```

### Plik CSV z wektorami testowymi
```
0,0,0,1
1,1,0,0
1,0,1,0
```

## Znane ograniczenia
- Obecna implementacja nie pozwala na sprzężenie zwrotne z wykorzystaniem bramek, w szczególności nie istnieje możliwość zaimplementowania przerzutnika z wykorzystaniem bramek (aby to zmienić wymagana jest znaczna zmiana struktury)
- Przerzutniki są sterowane zboczem malejącym (kwestia implementacyjna)
- Podanie nazwy bramki w pliku .ftl, którego nie ma w pliku ISCAS powoduje wystąpienie wyjątku (kwestia wyboru)
- W raporcie pokrycia podawany jest dokładnie jeden wektor
- Kolejność argumentów ma znaczenie