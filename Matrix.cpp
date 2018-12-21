
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>
#include "Matrix.h"

using namespace std;


string  Matrix::get_Name()
{
	return Name;
}
void  Matrix::set_Name(string _Name)
{
	this->Name= _Name;
}
int  Matrix::get_Columns()
{
	return Columns;
}
void  Matrix::set_Columns(int Columns)
{
	this->Columns = Columns;
}
int  Matrix::get_Rows()
{
	return Rows;
}
void  Matrix::set_Rows(int Rows)
{
	this->Rows = Rows;
}
void DataStore::set_Number(int number)
{
	this->number = number;
}
int DataStore::get_Number()
{ return number; }


void Matrix::Show()	//Метод для вывода информации о матрице в консоль
{
	cout << "=========================================================" << endl;
	cout << "Матрица: " << get_Name() << endl;
	cout << "Строк: " << get_Rows() << endl;
	cout << "Столбцов: " << get_Columns() << endl;

	for (size_t i = 0; i < values.size(); i++)
	{
		for (size_t j = 0; j < values[i].size(); j++)
		{
			cout << values[i][j] << " ";
		}
		cout << "\n";
	}
}

int DataStore::Get_num(const string & s, vector <long long> & v) //функция для считывания размеров
{
	istringstream is(s);//строковой поток ввода,т.е. мы передаем строку и работаем с ней как с потоком
	int n;
	while (is >> n) {
		v.push_back(n);
	}
	return v.size();
}
void DataStore::LoadData(string file_name)//функция для считывания матриц из файла
{

	ifstream file;
	string line;
	int line1;
	int line2;
	int _number = 0;
	

	int rows;//строки
	int cols;//столбцы
	
	set_Number(_number);

	vector<long long> buffValues;//для считывания

	file.open(file_name);

	while (true)
	{
		file >> line;

		if (line == "end") break;
		Matrix matrix;

		matrix.set_Name(line);

		_number++;
		set_Number(_number);
		file >> line1 >> line2; 

		matrix.set_Rows(line1);
		matrix.set_Columns(line2);
		
		int i = 0;

		getline(file, line);
		getline(file, line);

		cols = Get_num(line, buffValues);
		matrix.values.push_back(buffValues);
		buffValues.clear();

		if (cols > matrix.get_Columns())
		{
			cout << "Столбцов в матрице " << matrix.get_Name() << " больше, чем указано!" << endl;
			break;
		}

		if (cols < matrix.get_Columns())
		{
			cout << "Столбцов в матрице " << matrix.get_Name() << " меньше, чем указано!" << endl;
			break;
		}

		for (i = 1; i < INT_MAX; i++) {
			getline(file, line);
			if (line == "&") break;
			Get_num(line, buffValues);
			matrix.values.push_back(buffValues);
			buffValues.clear();
		}

		rows = i;

		if (rows > matrix.get_Rows())
		{
			cout << "Строк в матрице " << matrix.get_Name() << " больше, чем указано!" << endl;
			break;
		}

		if (rows < matrix.get_Rows())
		{
			cout << "Строк в матрице " << matrix.get_Name() << " меньше, чем указано!" << endl;
			break;
		}
		AllMatrix.push_back(matrix);
	}

	if (AllMatrix.size() > 1)
	{
		sizes.push_back(AllMatrix[0].get_Rows());

		for (int i = 0; i < AllMatrix.size(); i++)
		{
			sizes.push_back(AllMatrix[i].get_Columns());
		}
	}
	file.close();

	int k = get_Number();
	k++;
	m = new long long *[k];
	s = new long long *[k];

	for (int i = 0; i < k; i++)
	{
		m[i] = new long long[k];
		s[i] = new long long[k];
	}

	for (int i = 0; i < k; i++)
	{
		for (int j = 0; j < k; j++)
		{
			if (i == j) m[i][j] = 0;
			else m[i][j] = INT_MAX;

			s[i][j] = 0;
		}
	}
}
void Main::Start(string file_name)
{
	Data.LoadData(file_name);


	if (CheckMatrix( Data.AllMatrix))
	{
		for (int i = 0; i < Data.AllMatrix.size(); i++)
		{
			Data.AllMatrix[i].Show();
		}
		cout << "=========================================================" << endl;
		cout << "Всего матриц: " << Data.get_Number() << endl;
		cout << "=========================================================" << endl;
		cout << "Размеры матриц: ";

		for (int i = 0; i < Data.sizes.size(); i++)
		{
			cout << Data.sizes[i] << " ";
		}
		cout << endl;
		cout << "=========================================================" << endl;

		int result = Mult(1, Data.get_Number());
		string Answer = Print(1, Data.get_Number());
		cout << Answer << " = " << result;
	}
	else
	{
		cout << "Матрицы НЕСОВМЕСТИМЫ по отношению к матричному умножению!" << endl;
		cout << "=========================================================" << endl;
		cout << "Конец программы..." << endl;
	}
}
bool Main:: CheckMatrix (vector<Matrix> AllMatrix) //Метод проверки матриц на совместимость к перемножению
{
	if (AllMatrix.size() > 1)
	{
		for (int i = 0; i < AllMatrix.size() - 1; i++)
		{
			if (AllMatrix[i].get_Columns() != AllMatrix[i + 1].get_Rows()) return false;
		}
		return true;
	}
	else
	{
		cout << "Матриц слишком мало для перемножения" << endl;
		return false;
	}
}
long long Main:: Mult(int i, int j)//заполняем матрицы умножений
{
	if (Data.m[i][j] == INT_MAX)
	{
		for (int k = i; k <= j - 1; k++)
		{
			long long temp = Mult(i, k) + Mult(k + 1, j) + Data.sizes[i - 1] * Data.sizes[k] * Data.sizes[j];
			if (temp < Data.m[i][j])
			{
				Data.m[i][j] = temp;
				Data.s[i][j] = k;
			}
		}
	}
	return Data.m[i][j];
}
string Main::Print(int i, int j)//вывод 

{

	if (i == j) return Data.AllMatrix[i - 1].get_Name();

	return "(" + Print(i, Data.s[i][j]) + " x " + Print(Data.s[i][j] + 1, j) + ")";

}
