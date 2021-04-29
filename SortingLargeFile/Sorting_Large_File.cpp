#include <iostream>
#include <string>
#include<fstream>
#include <ctime>
#include <chrono> 
#include"TimSort.h"

//using namespace std;
void writeArr(const std::string& filename, const int* arr, const int n)  // функция записи в файл
{
	std::fstream fs;
	fs.open(filename, std::fstream::out);
	if (fs.is_open())// проверяем что файл успешно открыт
	{
		fs << n << '\n';//записываем размер массива
		for (int i = 0; i < n; i++)
			fs << arr[i] << ' ';//записываем значения через пробел
		fs << '\n';

		fs.close();//закрываем файл
	}
}

void readArr(const std::string& filename, int*& arr, int& n)//функция чтения из файла
{
	std::fstream fs;

	fs.open(filename, std::fstream::in);
	if (fs.is_open())// проверяем что файл успешно открыт
	{
		fs >> n; // читаем размер массива
		arr = new int[n];

		for (int i = 0; i < n; ++i)
			fs >> arr[i];// читаем из файла разделительные символы - пробел и перенос строки

		fs.close();//закрываем файл
	}
}

void fillingArray(int* rand_arr, const int size, const int  range_len) // функция заполнения массива случайными числами
{

	
	std::srand(static_cast<unsigned int>(std::time(NULL)));//Устанавливаем  начальное значение для rand, и преобразовываем еог в unsigned int
	 
	
	for (int i = 0; i < size;++i ) // заполняем массив
	{
		
		rand_arr[i] = std::rand() % range_len;
	}

}
void writeSortedNumbersToFile(std::string filename,const int size, const int range_len)//заполнение массива значениями, сортировка и запись в файл
{
	int* arr = new int[size];
	fillingArray(arr, size, range_len);
	timSort(arr, size);
	writeArr(filename, arr, size);//записываем массив в файл
	delete[]arr;

}

void mergeFiles(std::string filenameFirst, std::string filenameSecond, std::string filenameMerge)// объединяем файлы
{
	int *firstArr = nullptr;
	int sizeFirst = 0;
	readArr(filenameFirst, firstArr, sizeFirst);
	int* secondArr = nullptr;
	int sizeSecond = 0;
	readArr(filenameSecond, secondArr, sizeSecond);
	int sizeMerge = sizeFirst + sizeSecond;
	int* mergeArr = new int[sizeMerge];
		
	for (int i = 0,j=0,k=0; i < sizeMerge; ++i)
	{
		if (firstArr[j] <=secondArr[k]&&j< sizeFirst||k>= sizeSecond)
		{
			mergeArr[i] = firstArr[j];
			++j;
		}
		
		else if(firstArr[j] > secondArr[k] && k < sizeSecond||j>= sizeFirst)
		{
			mergeArr[i] = secondArr[k];
			++k;
		}

	}

	writeArr(filenameMerge, mergeArr, sizeMerge);
	delete[]firstArr;
		delete[]secondArr;
		delete[]mergeArr;
}

int main()

{
	const int size = 50;
	const int range_len = 1000;
	writeSortedNumbersToFile("first_file.txt", size, range_len);
	writeSortedNumbersToFile( "second_file.txt", size, range_len+1);
	writeSortedNumbersToFile("third_file.txt", size, range_len+2);
	writeSortedNumbersToFile("fourth_file.txt", size, range_len+3);
	mergeFiles("first_file.txt", "second_file.txt", "first_merged_file.txt");
	mergeFiles("third_file.txt", "fourth_file.txt", "second_merged_file.txt");
	mergeFiles("first_merged_file.txt", "second_merged_file.txt", "large_merged_file.txt");
	return 0;
}