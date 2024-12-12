// task5.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
using namespace std;

void swap(int& a, int& b) {
	int temp = a;
	a = b;
	b = temp;
}


void swapDisks(string arr[], int size) {
	int moves = 0;

	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - 1; j++) {
			if (arr[j] == "dark" && arr[j + 1] == "light") {
				swap(arr[j], arr[j + 1]);
				moves++;
			}
		}
	}

	cout << "Number of moves: " << moves << endl;
}

int main()
{
	string disks[] = { "dark", "light", "dark", "light", "dark", "light" };
	int size = sizeof(disks) / sizeof(disks[0]);

	cout << "Original array: " << endl;
	for (int i = 0; i < size; i++) {
		cout << disks[i] << " ";
	}
	cout << endl;

	swapDisks(disks, size);

	cout << "Sorted Array: " << endl;
	for (int i = 0; i < size; i++) {
		cout << disks[i] << " ";
	}

}
