#ifndef MACIERZ_H_
#define MACIERZ_H_
#include <iostream>
#include <vector>
#include "read_csv.h"

class Macierz
{
private:
	
	std::vector<std::string>  dataHeaders; // pierwszy wiersz z datalist
	std::vector<std::string>  dataRowNames;
	std::vector<std::vector<double>> m_matrix; // macierz

public:
	Macierz();
	Macierz(std::vector<std::vector<double>>);
	
	Macierz(const Macierz &);
	Macierz(std::string filename); // konstruktor przymujacy plik csv jako argument
	~Macierz();

	
	std::vector<std::vector<double>> getMatrix() const;
	std::vector<std::string> getHeaders();
	std::vector<std::string> getRowNames();

	
	double& operator()(int i, int j);
	//Macierz& operator=(const Macierz& source);
	Macierz operator+(Macierz&);
	Macierz operator-(Macierz&);
	Macierz operator*(Macierz&);
	Macierz operator=(const Macierz&);
	Macierz I(); // macierz jednostkowa 
	//void I();
	//std::vector<std::vector<double>> I(std::vector<std::vector<double>>);
	Macierz Transponse();
	
	void print() const;	
	friend std::ostream& operator<< (std::ostream& out, const Macierz& t);
	void householderDecomposition(Macierz& Q, Macierz& R);
};


#endif


/*
private:
	//unsigned m_row;
	//unsigned m_col;
	std::vector<std::string>  dataHeaders; // pierwszy wiersz z datalist
	std::vector<std::string>  dataRowNames;
	std::vector<std::vector<double>> m_matrix; // macierz

public:
	Macierz();
	Macierz(std::vector<std::vector<double>>);
	//Macierz(unsigned, unsigned, double); // zamiast double trzeba ciag(vector)double

	//Macierz();
	//Matrix(const char *);
	Macierz(const Macierz &);
	Macierz(std::string filename); // konstruktor przymujacy plik csv jako argument
	~Macierz();

	//unsigned getRow() const;
	//unsigned getCol() const;
	std::vector<std::vector<double>> getMatrix() const;
	std::vector<std::string> getHeaders();


	double& operator()(const unsigned &, const unsigned &);
	void print() const;

	Macierz operator+(Macierz &);
	Macierz operator-(Macierz &);
	Macierz operator*(Macierz &);
	Macierz operator*(double); //skalar

	//friend ostream& operator<<(ostream& os, Macierz& t);
	friend std::ostream& operator<< (std::ostream& out, const Macierz& t);*/