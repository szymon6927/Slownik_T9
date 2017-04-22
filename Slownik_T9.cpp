// Slownik_T9.cpp : Defines the entry point for the console application.
//
#include <iostream>

using namespace std;

const int max_dlugosc = 100 + 1; //+1 dla znaku konca ci¹gu eg. \0

char kodowanie(char znak);

template <class T>
class vector
{
public:
	vector() : dane(nullptr), ilosc(0), pojemnosc(0) {}
	vector(const char slowo[]) : dane(nullptr) { //konstruktor incjujacy moje s³owo
		zmien_rozmiar(max_dlugosc); //tworzymy z banki tablice 16 plus jeden zeby wiadomo gdzie koniec
		for (int i = 0; i < max_dlugosc; i++) {
			if (slowo[i] == '\0') {
				ilosc = i;
				break;
			}
			else {
				dane[i] = slowo[i];
			}
		}
	}
	vector(const vector<T> &kopia) {
		dane = new T[kopia.rozmiar()];
		pojemnosc = kopia.rozmiar();
		for (int i = 0; i < kopia.rozmiar(); i++) {
			dane[i] = kopia[i];
		}
		ilosc = kopia.rozmiar();
	}
	~vector() { czysc_tablice(); } //likwidacja talicy

	void czysc_tablice() {
		if (dane != nullptr) {
			delete[] dane;
			dane = nullptr;
			pojemnosc = 0;
			ilosc = 0;
		}
	}

	void zmien_rozmiar(int nowy_rozmiar) {
		T *nowa_tablica = new T[nowy_rozmiar];
		if (dane != nullptr) {
			for (int i = 0; i < ilosc; i++) {
				nowa_tablica[i] = dane[i];
			}
			delete[] dane;
		}

		dane = nowa_tablica;
		pojemnosc = nowy_rozmiar;

	}

	int rozmiar() const {
		return ilosc;
	}

	void wstaw(int pozycja, const T& wartosc) { //w dowolne miejsce a nie na koniec dla zachowania kolejnoœci alfabetycznej
		if (ilosc == pojemnosc) {
			if (rozmiar() == 0) {
				zmien_rozmiar(2);
			}
			else {
				zmien_rozmiar(rozmiar() * 2);
			}
		}

		for (int i = rozmiar(); i > pozycja; i--) {
			dane[i] = dane[i - 1]; //do danych i przypisujemy dane wartosci z poprzednich komorek, przesuwajac w prawo
		}

		dane[pozycja] = wartosc;
		ilosc++;
	}

	void wstaw_na_koniec(T wartosc) {
		if (ilosc < pojemnosc) {
			dane[ilosc] = wartosc;
			ilosc++;
		}
		else {
			if (rozmiar() == 0) {
				zmien_rozmiar(2);
			}
			else {
				zmien_rozmiar(rozmiar() * 2);
			}
			dane[ilosc] = wartosc;
			ilosc++;
		}
	}

	void wyswietl() {
		for (int i = 0; i < rozmiar(); i++) {
			cout << dane[i];
		}
	}

	bool czy_pusta() {
		return ilosc == 0;
	}

	T& operator[](int index) {
		return dane[index];
	}

	const T& operator[](int index) const {
		return dane[index];
	}

	void operator=(const vector<T> &kopia) {
		if (pojemnosc < kopia.rozmiar()) {
			if (dane != nullptr) {
				delete[] dane;
			}
			dane = new T[kopia.rozmiar()];
			pojemnosc = kopia.rozmiar();
		}

		for (int i = 0; i < kopia.rozmiar(); i++) {
			dane[i] = kopia[i];
		}
		ilosc = kopia.rozmiar();
	}

private:
	T *dane;
	int ilosc;
	int pojemnosc;
};

class wezel
{
public:
	wezel() : litera('\0') {}
	wezel(char litera) : litera(litera) { }
	~wezel() { czysc_wezel(); }
	char litera;
	vector<wezel*> dziecko;
	vector<vector <char>> slowa;

	wezel* dodaj_dziecko(char znak) {
		int i;
		for (i = 0; i < dziecko.rozmiar(); i++) {
			//znajdz najwyzsza litera dla zachowania kolejnosci alfabetycznej
			if (dziecko[i]->litera > znak) {
				break;
			}
		}
		wezel* w = new wezel(znak);
		dziecko.wstaw(i, w);
		return w;
	}

	wezel* pobierz_dziecko(char znak) {
		for (int i = 0; i < dziecko.rozmiar(); i++) {
			if (dziecko[i]->litera == znak) {
				return dziecko[i];
			}
		}
		return nullptr;
	}

	void czysc_wezel() {
		for (int i = 0; i < dziecko.rozmiar(); i++) { //pozbywamy sie obiektowy na ktore wskazywa³y pointery
			delete dziecko[i];
		}

		dziecko.czysc_tablice(); //usuwamy te pointery
	}

	bool ktory_wiekszy(const vector<char> &slowo1, const vector<char> &slowo2) {
		int i;
		for (i = 0; (i < slowo1.rozmiar()) && (i < slowo2.rozmiar()); i++) {
			if (slowo2[i] < slowo1[i]) {
				return true;
			}
			if (slowo1[i] < slowo2[i]) {
				return false;
			}
		}

		return (i == slowo2.rozmiar()) && (i != slowo1.rozmiar());
	}

	void dodaj_slowo(const vector<char> &slowo) {
		int i;
		int ile_slow = slowa.rozmiar();
		for (i = 0; i < ile_slow; i++) {
			if (ktory_wiekszy(slowa[i], slowo) == true) {
				break;
			}
		}

		slowa.wstaw(i, slowo);
	}

};

class slownik_t9
{
public:
	~slownik_t9() { czysc_drzewo(); }
	void dodaj_do_slownika(const vector<char>& slowo) {
		wezel* w = &root;
		wezel* temp;

		int dlugosc_slowa = slowo.rozmiar();

		for (int i = 0; i < dlugosc_slowa; i++) {
			temp = w->pobierz_dziecko(kodowanie(slowo[i]));
			if (temp == nullptr) {
				w = w->dodaj_dziecko(kodowanie(slowo[i]));
			}
			else {
				w = temp;
			}
		}

		w->dodaj_slowo(slowo);
	}
	void wyswietl_slowa(const vector<char>& kod) {
		wezel* w = &root;
		wezel* temp;

		int i;
		int dlugosc_kodu = kod.rozmiar();

		for (i = 0; i < dlugosc_kodu; i++) {
			temp = w->pobierz_dziecko(kod[i]);

			if (temp == nullptr) {
				cout << "-\n";
				return;
			}
			else {
				w = temp;
			}
		}

		bool znajdz = false;
		dzieci_od_ost_kodu(w, znajdz);
		if (znajdz == true) {
			cout << "\n";
		}
		else {
			cout << "-\n";
		}
	}
	void dzieci_od_ost_kodu(wezel *w, bool& znajdz) {
		if (!w->slowa.czy_pusta()) {
			znajdz = true;
			int rozmiar = w->slowa.rozmiar();
			for (int i = 0; i < rozmiar; i++) {
				w->slowa[i].wyswietl();
				cout << " ";
			}
		}

		int ilosc_dzieci = w->dziecko.rozmiar();

		for (int i = 0; i < ilosc_dzieci; i++) {
			dzieci_od_ost_kodu(w->dziecko[i], znajdz);
		}
	}
	void czysc_drzewo() {
		root.czysc_wezel();
	}
private:
	wezel root;
};


int main()
{
	slownik_t9 t9;

	int ilosc;
	char slowo[101];

	cin >> ilosc;

	for (int i = ilosc; i > 0; i--) {
		cin >> slowo;
		t9.dodaj_do_slownika(slowo);
	}

	cin >> ilosc;

	for (int i = ilosc; i > 0; i--) {
		cin >> slowo;
		t9.wyswietl_slowa(slowo);
	}

	return 0;
}


char kodowanie(char znak) {
	if (znak == 'a' || znak == 'b' || znak == 'c') {
		return '2';
	}
	else if (znak == 'd' || znak == 'e' || znak == 'f') {
		return '3';
	}
	else if (znak == 'g' || znak == 'h' || znak == 'i') {
		return '4';
	}
	else if (znak == 'j' || znak == 'k' || znak == 'l') {
		return '5';
	}
	else if (znak == 'm' || znak == 'n' || znak == 'o') {
		return '6';
	}
	else if (znak == 'p' || znak == 'q' || znak == 'r' || znak == 's') {
		return '7';
	}
	else if (znak == 't' || znak == 'u' || znak == 'v') {
		return '8';
	}
	else
	{
		return '9';
	}
}
