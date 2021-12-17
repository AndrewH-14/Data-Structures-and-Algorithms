#include <iostream>
using namespace std;
#include "Heap.cpp"

void printErrors(string errors, int numOfErrors){
	if(numOfErrors < 5){
		cout << errors << " caused less than 5 errors so +1 line" << endl;
	}
	if(numOfErrors < 100){
		cout << errors << " caused less than 100 errors so +1 line" << endl;
	}
	if (numOfErrors < 500){
		cout << errors << " caused less than 500 errors so +1 line" << endl;
	}
	if (numOfErrors < 5000){
		cout << errors << " caused less than 5000 errors so +1 line" << endl;
	}
	else{
		cout << errors << " caused more than 5000 errors resulting in 0 points" << endl;
	}
}

int main(){
	string A[25] = {"AZ","AD","V","AB","A","B","U","C","D","E","W","F","G","H","I","X","J","K","L","M","Q","Y","R","S","T"};

	Heap<string> T1, T2(A,25);

	T2.printKey();

	for(int i=0; i<25; i++) T1.insert(A[i]);

	T1.printKey();

	cout << T2.peekKey() << endl;
	cout << T2.extractMin() << endl;

	cout << T1.peekKey() << endl;
	cout << T1.extractMin() << endl;
	cout << T1.extractMin() << endl;
	cout << T1.extractMin() << endl;
	cout << T1.extractMin() << endl;

	T1.printKey();

	Heap<int> X;
	for(int i = 0; i < 100000; i++){
		X.insert((i-50000));
	}
	X.printKey();
	int peakKey=0;
	int extractMin=0;
	for(int i = 0; i < 99999; i++){
		if(X.peekKey() != (i-50000)) peakKey++;
		if(X.extractMin() != (i-50000)) extractMin++;
	}
	printErrors("peakKey",peakKey);
	printErrors("extractMin",extractMin);

	return 0;
}