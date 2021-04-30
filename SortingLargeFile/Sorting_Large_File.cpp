#include <iostream>
#include <string>
#include<fstream>
#include <ctime>
#include <chrono> 
#include <cstdlib> // для использования функции exit()
#include"TimSort.h"


void writeArr(const std::string& filename, const int* arr, const  int& n)  // функция записи в файл
{
	std::fstream fs;
	fs.open(filename, std::fstream::out);
	if (fs.is_open())// проверяем что файл успешно открыт
	{
		fs << n << '\n';//записываем размер массива
		for (int i = 0; i < n; i++)
		{
			fs << arr[i] << ' ';//записываем значения через пробел
			if (i % 20 == 0 && i > 0)
			{
				fs << '\n';
			}
		}
		fs << '\n';

		fs.close();//закрываем файл
	}
}

void readArr(const std::string& filename, int*& arr, int& n)//функция чтения из файла
{
	std::fstream fs; // переменнная для записи данных в массив

	fs.open(filename, std::fstream::in);  // открываем файл
	if (fs.is_open())// проверяем что файл успешно открыт
	{
		fs >> n; // читаем размер массива
		arr = new  int[n];

		for (int i = 0; i < n; ++i)
			fs >> arr[i];// читаем из файла 


		fs.close();//закрываем файл
	}
	std::ofstream ofs;// переменная для очистки данных из массива
	ofs.open(filename, std::ofstream::trunc);
	ofs.trunc;    // очищаем и 
	ofs.close();//закрываем файл

}

void fillingArray(int* rand_arr, const int& size, const  int& range_len) // функция заполнения массива случайными числами
{

	std::srand(static_cast<unsigned int>(std::time(NULL)));//Устанавливаем  начальное значение для rand, и преобразовываем еог в unsigned int


	for (int i = 0; i < size; ++i) // заполняем массив
	{

		rand_arr[i] = std::rand() % range_len;
	}

}
void writeSortedNumbersToFile(std::string filename, const int size, const  int range_len)//заполнение массива значениями, сортировка и запись в файл
{
	int* arr = new int[size];
	fillingArray(arr, size, range_len);
	timSort(arr, size);
	writeArr(filename, arr, size);//записываем массив в файл
	delete[]arr;

}

void mergeFiles(std::string filenameFirst, std::string filenameSecond, std::string filenameMerge)// объединяем файлы
{
	int* firstArr = nullptr;
	int sizeFirst = 0;
	readArr(filenameFirst, firstArr, sizeFirst);
	int* secondArr = nullptr;
	int sizeSecond = 0;
	readArr(filenameSecond, secondArr, sizeSecond);
	int sizeMerge = sizeFirst + sizeSecond;
	int* mergeArr = new int[sizeMerge];

	for (int i = 0, j = 0, k = 0; i < sizeMerge; ++i)
	{
		if (firstArr[j] <= secondArr[k] && j < sizeFirst || k >= sizeSecond)
		{
			mergeArr[i] = firstArr[j];
			++j;
		}

		else if (firstArr[j] > secondArr[k] && k < sizeSecond || j >= sizeFirst)
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
	setlocale(LC_ALL, "ru");
	const unsigned  int size = 100000; // размер массива для самых маленьких файлов
	const unsigned int range_len = 10000; // максимальное число массива
	// запоняем и сортируем  массив. Вносим его значения в  файл
	writeSortedNumbersToFile("first_file.txt", size, range_len);
	writeSortedNumbersToFile("second_file.txt", size, range_len + 1);// добавляем к каждому макимальному числу по единице,
	writeSortedNumbersToFile("third_file.txt", size, range_len + 2); // чтобы массивы получились разные
	writeSortedNumbersToFile("fourth_file.txt", size, range_len + 3); //  т.к srand не успевает обновляться
	// объединяем полученные массивы в два
	mergeFiles("first_file.txt", "second_file.txt", "first_merged_file.txt");
	mergeFiles("third_file.txt", "fourth_file.txt", "second_merged_file.txt");
	// и оставшиеся два массива объдиняем в один
	mergeFiles("first_merged_file.txt", "second_merged_file.txt", "large_merged_file.txt");
	// выводим файл на консоль
	std::ifstream filename("large_merged_file.txt");// переменная для чтения массива

	if (!filename)// Если мы не можем открыть файл для чтения его содержимого,
	{
		std::cerr << "Uh oh, SomeText.txt could not be opened for reading!" << std::endl;// то выводим следующее сообщение об ошибке и выполняем функцию exit()
		exit(1);
	}
	std::cout << "Количество чисел: "; // добавляем сообщение о количестве элементов массива         

	while (filename)// Пока есть, что читать,
	{
		std::string mergeArray; // то перемещаем то, что можем прочитать, в строку, а затем выводим эту строку на экран
		getline(filename, mergeArray);
		std::cout << mergeArray << std::endl;
	}
	// очищаем большой файл
	std::ofstream ofs;// переменная для очистки данных из массива
	ofs.open("large_merged_file.txt", std::ofstream::trunc);
	ofs.trunc;    // очищаем и 
	ofs.close();//закрываем файл*/

	return 0;
}