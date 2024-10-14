#include <iostream>
using namespace std;
/*
	��� ��������� �������� ���� �������� ���� ��� ����� ��������� ������ �� ������� �� ����� �++
	����� � ���� ��������� � ����� �������� ����� �� ������ ������ � ��������, ��� ��� �� ������ ������, �� ���������� ���...
	� ����� ����� ���� � ���� ��������� ������ ����� ��������, ����� �� ��� ���������� �����, ��� ���������� ������ � ��������
*/
class ClassListWithMods {
private:
	int** data;
	int size;
	bool r = false;
	bool l = false;
	bool d = false;
	bool up = false;
	// ������� ����������� ������
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
	// ����������� ������ ClassListWithMods
	ClassListWithMods(int size) {
		this->size = size;
		this->data = new int*[size];
		for (int i = 0; i < size; i++)
		{
			this->data[i] = new int[size];
		}
		FillArrayPrivate(data, size, size);
	};
	// ������� � �������
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

	// ���������� ������ ClassListWithMods
	~ClassListWithMods() {
		for (int i = 0; i < this->size; i++)
		{
			delete[] this->data[i];
		}
		delete[] this->data;
		data = nullptr;
	};

	// ����������� ����������� ������ ClassListWithMods
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
	// ������ ������ �������� �������(� ����� ������ �������)
	arr.ChangeModeR();
	while (m < size) { // ����� ������ �����, ������� ����� ���������� ��� �������� � ������� �� �������� ������.
		if (arr.GetModeR()) { // ������� ��� �������� �������
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
		else if (arr.GetModeD()) { // ������� ��� �������� ����
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
		else if (arr.GetModeL()) { // ������� ��� �������� �����
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
		else if (arr.GetModeUp()) { // ������� ��� �������� �����
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
//������� ������ �������
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