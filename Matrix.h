#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

class Matrix //класс матрицы
{
   public:
	string get_Name();
	void  set_Name(string Name);
	int get_Rows();
	void  set_Rows(int Rows);
	int get_Columns();
	void  set_Columns(int Columns);
	vector<vector<long long>> values;//Двумерный вектор значений матрицы
	void Show();	//Метод для вывода информации о матрице в консоль
	Matrix() {};
   private:
	string Name;//имя матрицы
	int Rows;//Количество строк
	int Columns;//Количество столбцов
 
};

class DataStore	//Класс для хранения данных
{
   public:

	DataStore() {};
	
	vector<long long> sizes;//Вектор размеров матриц,где каждое значение повторяется однократно,т.к. кол-во строк первой=кол-ву столбцов второй
	vector<Matrix> AllMatrix;//Вектор всех загруженных матриц
	void set_Number(int number);
	int get_Number();
	void LoadData(string file_name);//функция для считывания матриц из файла
	long long **m;// массив для хранения всех возможных количеств умножения каждых матриц
	long long **s;//массив для хранения матрицы оптимального выражения

   private:
	int Get_num(const string & s, vector <long long> & v);//функция для считывания размеров
	int number;//Количество матриц
	
};

class Main //здесь творится история
{
    public:
		Main(string filename) 
		{
		   Start(filename);
		};
	DataStore Data;	//Экземпляр класса с данными
	

   private:

	bool CheckMatrix(vector<Matrix> AllMatrix); //Метод проверки матриц на совместимость к перемножению
	long long Mult(int i, int j);//заполняем матрицы умножений
	string Print(int i, int j);//вывод 
	void Start(string file_name);
};
