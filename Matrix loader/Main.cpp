#include "Macierz.h"
#include "read_csv.h"
#include "QR.h"
using namespace std;
int main()
{
	Macierz plik("Test_1.csv");
	Macierz plik2("Test_2.csv");
	Macierz plik3("Test_3.csv");
	Macierz Identity("Macierz_kw.csv");
	
	/*
		Testy dla operacji mnozenie, dodawanie / odejmowanie, transpozyzcja,
		macierz jednostkowa
	*/

	/*
	cout << Identity << endl;
	Macierz Assig;
	Assig = Identity.I();
	cout << Assig << endl;
	Macierz Trans = Identity.Transponse();
	cout << Trans << endl;
	*/
	Macierz Assig;
	Assig = Identity.I();
	Macierz Operacja;
	Macierz M1 = Identity.Transponse();
	Operacja = M1.I() + M1;
	cout << Operacja << endl;
	
	
	/*
	std::cout << Identity << endl;
	std::cout << "**Jednostkowa** " << Identity.I() << endl;
	cout << endl;
	Macierz Dodawanie = plik + plik;
	cout << "**Dodawanie**" << endl;
	cout << Dodawanie << endl;
	cout << "**Transpozycja**" << endl << Dodawanie.Transponse();
	
	cout << plik2 << endl;
	cout << plik3 << endl;
	cout << "**Mnozenie**" << endl;
	Macierz Mnozenie = plik2 * plik3;

	cout << Mnozenie << endl;
	*/
	return 0;
}

