#Słownik T9

Większość telefonów pozwala wprowadzać tekst przy pomocy słownika T9. Wprowadzanie polega na wpisywaniu cyfr przyporządkowanym literom. Słownik automatycznie przekształca ciąg cyfr na wyraz. Słownik potrafi także domyślać się dalszego ciągu słowa - na podstawie początkowego ciągu cyfr próbuje domyślić się, jaka będzie końcówka. Kodowanie to jest niestety niejednoznaczne (np. i mam i nam mają kody 626). Przyporządkowanie cyfr do liter jest następujące: abc = 2, def = 3, ghi = 4, jkl = 5, mno = 6, pqrs = 7, tuv = 8, wxyz = 9. Zatem np. wyraz pies ma kod T9 równy 7437. Napisz program, który dla zadaniego początkowego fragmentu kodu T9 znajdzie wszystkie pasujące do niego słowa ze słownika.
Wejście

Na wejściu pojawi się: liczba n określająca, ile słow jest w słowniku, n wyrazów, każdy w osobnej linii, należących do słownika, składających się wyłącznie z małych liter, liczba m określająca liczbę zapytań, m napisów określających zapytania, składających się wyłącznie z cyfr, każde w osobnej linii. Długości wyrazów i zapytań nie przekroczą 100 znaków.
Wyjście

Dla każdego zapytania, na wyjściu należy wypisać wszystkie pasujące słowa, w kolejności leksykograficznej ich kodów T9 (kod 123 jest zatem mniejszy niż kod 33). Słowa o takim samym kodzie powinny być uporządkowane leksykograficznie i rozdzielone spacją. Jeżeli do zapytania nie pasują żadne wyrazy, należy wypisać znak - (minus). Odpowiedź na każde zapytanie powinien kończyć znak nowej linii.
Przykład

##Wejście:
10<br />
ccc<br />
bbb<br />
aaa<br />
aba<br />
abc<br />
pies<br />
samochod<br />
samolot<br />
potrzebny<br />
paliwo<br />
10<br />
2<br />
22<br />
222<br />
2222<br />
7<br />
72<br />
726<br />
743<br />
7437<br />
744<br />

##Wyjście:
aaa aba abc bbb ccc<br />
aaa aba abc bbb ccc<br />
aaa aba abc bbb ccc<br />
-<br />
paliwo samochod samolot pies potrzebny<br />
paliwo samochod samolot<br />
samochod samolot<br />
pies<br />
pies<br />
-<br />