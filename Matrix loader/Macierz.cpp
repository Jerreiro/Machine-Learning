#include "Macierz.h"
#include "read_csv.h"

using namespace std;


Macierz::Macierz()
{
	
}

Macierz::Macierz(std::vector<std::vector<double>> M)
{
	for (int i = 0; i < M.size(); i++)
	{
		string temp_1 = std::to_string(i + 1);
		dataRowNames.push_back(temp_1);
	}

	for (int i = 0; i < M.size(); i++)
	{
		string temp_1 = std::to_string(i + 1);
		dataHeaders.push_back(temp_1);
	}
	m_matrix = M;
}

Macierz::~Macierz() 
{

}

Macierz::Macierz(const Macierz & M)
{
	this->dataHeaders = M.dataHeaders;
	this->dataRowNames = M.dataRowNames;
	this->m_matrix = M.m_matrix;
}

Macierz::Macierz(std::string filename)
{	
	CSVReader reader(filename);
	std::vector<std::vector<std::string> > dataList = reader.getData();
	std::vector<std::vector<std::string>> splitter; // kontener zeby mial dane ze znakami ";"

	for (int i = 1; i < dataList[0].size(); i++)
		dataHeaders.push_back(dataList[0][i]);

	for (int i = 1; i < dataList.size(); i++)
	{ 
		std::vector <double> temp;
		for (int j = 1; j < dataList[i].size(); j++)
			temp.push_back(std::stod(dataList[i][j]));
		m_matrix.push_back(temp);
		dataRowNames.push_back(dataList[i][0]);
	}
}

std::vector<std::vector<double>> Macierz::getMatrix() const
{
	return m_matrix;
}

std::vector<std::string> Macierz::getHeaders()
{
	return dataHeaders;
}

std::vector<std::string> Macierz::getRowNames()
{
	return dataRowNames;
}

Macierz Macierz::I()
{
	std::vector<std::vector<double> > I; // macierz jednostkowa
	
	// Petla zeby zrobic macierz jednostkowa o odpowiednich wymiarach
	
	for (int i = 0; i < m_matrix.size(); i++)
	{
		std::vector<double> temp;
		double temp_1 = 0.0;
		for (int j = 0; j < m_matrix.size(); j++)
			temp.push_back(temp_1);
		I.push_back(temp);
		I[i][i] = 1.0;
	}
	return Macierz(I);
}


Macierz Macierz::Transponse()
{
	std::vector<std::vector<double> > T_matrix;
	unsigned i, j;
	for (i = 0; i < m_matrix[0].size(); i++)
	{
		vector<double> temp_row;
		for (j = 0; j < m_matrix.size(); j++)
		{
			temp_row.push_back(this->m_matrix[j][i]);			
		}
		T_matrix.push_back(temp_row);
	}
	return Macierz(T_matrix);
}

void Macierz::householderDecomposition(Macierz& Q, Macierz& R)
{

}
void Macierz::print() const
{
	cout << "Macierz: " << endl;
	for (unsigned i = 0; i < m_matrix.size(); i++) {
		for (unsigned j = 0; j < m_matrix[0].size(); j++) {
			cout << "[" << m_matrix[i][j] << "] ";
		}
		cout << endl;
	}
}

double& Macierz::operator()(int i, int j)
{
	return m_matrix[i][j];
}

Macierz Macierz::operator=(const Macierz& source)
{
	m_matrix = source.m_matrix;
	return m_matrix;
}

Macierz Macierz::operator*(Macierz& B) {

	std::vector<std::vector<double>> multip;
	if (dataHeaders.size() != B.dataRowNames.size())
	{
		cout << "Nie równa dlugosc kolumn i wierszy!";
	}

	else
	{
		unsigned i, j, k;
		std::vector<double>temp;
		double temp_wartosc = 0.0;
		for (i = 0; i < dataRowNames.size(); i++)
		{			
			for (j = 0; j < B.dataHeaders.size(); j++)
			{
				double temp_wartosc = 0.0;
				for (k = 0; k < dataHeaders.size(); k++)
				{
					temp_wartosc += m_matrix[i][k] * B(k, j);
				}
				temp.push_back(temp_wartosc);
				//temp_wartosc = 0.0;
			}
			multip.push_back(temp);			
		}	
	}
	return Macierz(multip);
}

Macierz Macierz::operator+(Macierz& B) {
	
	std::vector<std::vector<double> > temp_matrix;
	unsigned i, j;
	for (i = 0; i < dataRowNames.size(); i++)
	{
		std::vector<double> temp_row;
		for (j = 0; j < dataHeaders.size(); j++)
		{
			temp_row.push_back(this->m_matrix[i][j] + B(i, j));
		}
		temp_matrix.push_back(temp_row);
	}
	
	return Macierz(temp_matrix);
}

Macierz Macierz::operator-(Macierz& B) {

	std::vector<std::vector<double> > temp_matrix;
	unsigned i, j;
	for (i = 0; i < m_matrix.size(); i++)
	{
		std::vector<double> temp_row;
		for (j = 0; j < m_matrix[0].size(); j++)
		{
			temp_row.push_back(this->m_matrix[i][j] - B(i, j));
		}
		temp_matrix.push_back(temp_row);
	}

	return Macierz(temp_matrix);
}

std::ostream& operator<< (std::ostream& os, const Macierz& t)
{
	os << "Macierz: " << endl;
	for (unsigned i = 0; i < t.m_matrix.size(); i++) {
		cout << "[";
		for (unsigned j = 0; j < t.m_matrix[0].size(); j++) {
			cout << t.getMatrix()[i][j] << " ";;
		}
		cout << "]" << endl;
	}
	return os;
}


/*
#include "Macierz.h"
#include "read_csv.h"
#include "QR.h"
using namespace std;

Macierz::Macierz()
{

}

Macierz::Macierz(std::vector<std::vector<double>> M)
{
	m_matrix = M;
}


Macierz::Macierz(unsigned row, unsigned col, double initial)
{
	m_row = row;
	m_col = col;
	m_matrix.resize(row);
	for (int i = 0; i < m_matrix.size(); i++)
	{
		m_matrix[i].resize(col, initial);
	}
}

Macierz::~Macierz()
{

}


Macierz::Macierz(const Macierz& M)
{
	this->dataHeaders = M.dataHeaders;
	this->dataRowNames = M.dataRowNames;
	this->m_matrix = M.m_matrix;
}


Macierz::Macierz(std::string filename)
{

	CSVReader reader(filename);
	std::vector<std::vector<std::string> > dataList = reader.getData();
	std::vector<std::vector<std::string>> splitter; // kontener zeby mial dane ze znakami ";"

	for (int i = 1; i < dataList[0].size(); i++)
		dataHeaders.push_back(dataList[0][i]);

	for (int i = 1; i < dataList.size(); i++)
	{
		std::vector <double> temp;
		for (int j = 1; j < dataList[i].size(); j++)
			temp.push_back(std::stod(dataList[i][j]));
		m_matrix.push_back(temp);
		dataRowNames.push_back(dataList[i][0]);
	}
	//QR m_matrix(m_matrix);

}

unsigned Macierz::getRow() const
{
	return this->m_row;
}

unsigned Macierz::getCol() const
{
	return this->m_col;
}


std::vector<std::vector<double>> Macierz::getMatrix() const
{
	return m_matrix;
}

std::vector<std::string> Macierz::getHeaders()
{
	return dataHeaders;
}


Macierz Macierz::operator+(Macierz &B) {
	Macierz sum(m_col, m_row, 0.0);
	unsigned i, j;
	for (i = 0; i < m_row; i++)
	{
		for (j = 0; j < m_col; j++)
		{
			sum(i, j) = this->m_matrix[i][j] + B(i, j);
		}
	}
	return sum;
}

Macierz Macierz::operator-(Macierz & B) {
	Macierz diff(m_col, m_row, 0.0);
	unsigned i, j;
	for (i = 0; i < m_row; i++)
	{
		for (j = 0; j < m_col; j++)
		{
			diff(i, j) = this->m_matrix[i][j] - B(i, j);
		}
	}

	return diff;
}

Macierz Macierz::operator*(Macierz & B) {

	//std::vector<std::vector<double>> multip[B.getHeaders.size()][B.getHeaders.size()];
	if (B.dataHeaders.size() != B.dataRowNames.size())
	{
		cout << "Nie równa ilosc kolumn i wierszy!";
	}

	else
	{
		unsigned i, j, k;

		double temp = 0.0;
		for (i = 0; i < B.dataRowNames.size(); i++)
		{
			for (j = 0; j < B.dataHeaders.size(); j++)
				temp = 0.0;
			for (k = 0; k < B.dataRowNames.size(); k++)
			{
				temp += m_matrix[i][k] * B(k, j);
			}
			m_matrix[i][j] = temp;
			//cout << multip(i,j) << " ";
		}
		//cout << endl;
	}

	return m_matrix;

	
	Macierz multip(m_row, B.getCol(), 0.0);
	if (m_col == B.getRow())
	{
		unsigned i, j, k;
		double temp = 0.0;
		for (i = 0; i < m_row; i++)
		{
			for (j = 0; j < B.getCol(); j++)
			{
				temp = 0.0;
				for (k = 0; k < m_col; k++)
				{
					temp += m_matrix[i][k] * B(k, j);
				}
				multip(i, j) = temp;
				//cout << multip(i,j) << " ";
			}
			//cout << endl;
		}
		return multip;
	}
	else
	{
		cout << "Nie rowna wartosc wierszy i kolumn!";
	}
	
}

Macierz Macierz::operator*(double scalar) {
	Macierz result(m_row, m_col, 0.0);
	unsigned i, j;
	for (i = 0; i < m_row; i++)
	{
		for (j = 0; j < m_col; j++)
		{
			result(i, j) = this->m_matrix[i][j] * scalar;
		}
	}
	return result;
}


double& Macierz::operator()(const unsigned& row, const unsigned& col)
{
	return this->m_matrix[row][col];
}

void Macierz::print() const
{

	cout << "Macierz: " << endl;
	for (unsigned i = 0; i < m_matrix.size(); i++) {
		for (unsigned j = 0; j < m_matrix.size(); j++) {
			cout << "[" << m_matrix[i][j] << "] ";
		}
		cout << endl;
	}


}


std::ostream& operator<< (std::ostream & os, const Macierz & t)
{
	//std::vector<std::vector<double>> m = t.getMatrix();

	os << "Macierz: " << endl;
	for (unsigned i = 0; i < t.getMatrix().size(); i++) {
		for (unsigned j = 0; j < t.getMatrix().size(); j++) {
			cout << "[" << t.getMatrix()[i][j] << "] ";
		}
		cout << endl;
	}
	return os;
}

*/