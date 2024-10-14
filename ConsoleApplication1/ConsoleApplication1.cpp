#include <iostream>
using namespace std;
/*
	Ёта программа €вл€етс€ лишь примером того как можно заполнить массив по спирали на €зыке —++
	“акже в этой программе € решил укрепить какие то навыки работы с классами, так что не судите строго, за громоздкий код...
	¬ целом часть кода в этой программе вообще можно опустить, оп€ть же все написанное здесь, дл€ укреплени€ работы с классами
*/
class ClassListWithMods {
private:
	int** data;
	int size;
	bool r = false;
	bool l = false;
	bool d = false;
	bool up = false;
	// функци€ заполн€юща€ массив
	void FillArrayPrivate(int** arr, int rows, int cols) {
		int counter = 1;				
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				this->data[i][j] = counter;
				counter++;
			}
		}
	}
public:
	// конструктор класса ClassListWithMods
	ClassListWithMods(int size) {
		this->size = size;
		this->data = new int*[size];
		for (int i = 0; i < size; i++)
		{
			this->data[i] = new int[size];
		}
		FillArrayPrivate(data, size, size);
	};
	// геттеры и сеттеры
	int** GetData() {
		return data;
	}
	bool GetModeR() {
		return this->r;
	}
	void ChangeModeR() {
		this->r = !this->r;
	}
	bool GetModeL() {
		return this->l;
	}
	void ChangeModeL() {
		this->l = !this->l;
	}
	bool GetModeD() {
		return this->d;
	}
	void ChangeModeD() {
		this->d = !this->d;
	}
	bool GetModeUp() {
		return this->up;
	}
	void ChangeModeUp() {
		this->up = !this->up;
	}

	// деструктор класса ClassListWithMods
	~ClassListWithMods() {
		for (int i = 0; i < this->size; i++)
		{
			delete[] this->data[i];
		}
		delete[] this->data;
		data = nullptr;
	};

	// конструктор копировани€ класса ClassListWithMods
	ClassListWithMods(const ClassListWithMods& other) {
		this->size = other.size;
		this->data = new int*[other.size];
		for (int i = 0; i < size; i++)
		{
			this->data[i] = new int[other.size];
		}
		for (int i = 0; i < other.size; i++)
		{
			for (int j = 0; j < other.size; j++)
			{
				this->data[i][j] = other.data[i][j];
			}
		}
	}
};
void PrintArray(int** arr, int rows, int cols);
int main() {
	setlocale(LC_ALL, "ru");
	int size = 3, rows = size, cols = size;
	int m = 0, n = 0, left = 0, up = 0, down = cols - 1, right = rows - 1;
	ClassListWithMods arr(size);
	ClassListWithMods secondArr(arr);
	int** copyMainArr = arr.GetData();
	int** copyArr = secondArr.GetData();
	// задаем начало движени€ спирали(в нашем случае направо)
	arr.ChangeModeR();
	while (m < size) { // здесь начало цикла, который будет перебирать все элементы и ставить их согласно задаче.
		if (arr.GetModeR()) { // условие при движении направо
			for (int i = left; i <= right; i++)
			{
				copyArr[up][i] = copyMainArr[m][n];
				n++;
				if (n > cols - 1) {
					m++;
					n = 0;
				}
			}
			up++;
			arr.ChangeModeR();
			arr.ChangeModeD();
		}
		else if (arr.GetModeD()) { // условие при движении вниз
			for (int i = up; i <= down; i++)
			{
				copyArr[i][right] = copyMainArr[m][n];
				n++;
				if (n > cols - 1) {
					m++;
					n = 0;
				}
			}
			right--;
			arr.ChangeModeD();
			arr.ChangeModeL();
		}
		else if (arr.GetModeL()) { // условие при движении влево
			for (int i = right; i >= left; i--)
			{
				copyArr[down][i] = copyMainArr[m][n];
				n++;
				if (n > cols - 1) {
					m++;
					n = 0;
				}
			}
			down--;
			arr.ChangeModeL();
			arr.ChangeModeUp();
		}
		else if (arr.GetModeUp()) { // условие при движении вверх
			for (int i = down; i >= up; i--)
			{
				copyArr[i][left] = copyMainArr[m][n];
				n++;
				if (n > cols - 1) {
					m++;
					n = 0;
				}
			}
			left++;
			arr.ChangeModeUp();
			arr.ChangeModeR();
		}
	}
	cout << "Original Array:" << endl;
	PrintArray(copyMainArr, size, size);
	cout << "Spiral Array:" << endl;
	PrintArray(copyArr, size, size);
	return 0;
}
//‘ункци€ вывода массива
void PrintArray(int** arr, int rows, int cols) {
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < cols; j++)
		{
			cout << arr[i][j] << '\t';
		}
		cout << endl;
	}
}