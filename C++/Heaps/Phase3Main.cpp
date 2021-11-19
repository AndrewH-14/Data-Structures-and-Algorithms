#include <iostream>

using namespace std;

#include "Heap.cpp"
#include "FibHeap.cpp"

// Function to test the Heap copy constructor
void heap_copy_test(Heap<int> heap)
{
	heap.printKey();
}

int main() {

	// Main test cases provided
	#if 0
	string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int B[10] = {10,9,8,7,6,5,4,3,2,1};

	Heap<int> T1, T2(B,10);

	T2.printKey();
	//Should output  1 2 4 3 6 5 8 10 7 9

	for(int i=0; i<10; i++) T1.insert(B[i]);

	T1.printKey();
	// Should output 1 2 5 4 3 9 6 10 7 8

	cout << T2.peekKey() << endl;
	//Should output 1

	cout << T1.extractMin() << endl;
	//Should output 1

	T1.printKey();
	//Should output 2 3 5 4 8 9 6 10 7


	FibHeap<string> X(A,10), Y;

	X.printKey();
	//Should output
	//B1
	//J K
	//
	//B3
	//A E H I F C D B

	cout << X.extractMin() << endl;
	//Should output A

	X.printKey();
	//Should output
	//B0
	//B
	//
	//B3
	//C E H I F J K D

	X.insert("Z");
	X.insert("A");
	X.insert("P");

	X.printKey();
	//Should output
	//B0
	//B
	//
	//B3
	//C E H I F J K D
	//
	//B0
	//Z
	//
	//B0
	//A
	//
	//B0
	//P

	Y.insert("M");
	Y.insert("O");
	Y.insert("G");
	Y.insert("N");
	Y.insert("L");
	Y.insert("A");

	Y.extractMin();

	Y.printKey();
	//Should output
	//B0
	//L
	//
	//B2
	//G M O N

	Y.merge(X);
	cout << Y.peekKey() << endl;
	//Should output A

	Y.printKey();
	//Should output
	//B0
	//L
	//
	//B2
	//G M O N
	//
	//B0
	//B
	//
	//B3
	//C E H I F J K D
	//
	//B0
	//Z
	//
	//B0
	//A
	//
	//B0
	//P

	Y.extractMin();

	Y.printKey();
    //Should output
	//B4
	//B C E H I F J K D G M O N P Z L
	#endif

	// Tests extracting a node when there is only one node in the root list
	// and it has children
	#if 0
	int arr[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	FibHeap<int> H1(arr, 10);

	H1.printKey();

	// Extracts the tail of the root list that has children
	H1.extractMin();
	H1.printKey();

	// Extracts the head of the list with no children
	H1.extractMin();
	H1.printKey();

	// Extracts the only node in the root list and moves the children up
	H1.extractMin();
	H1.printKey();
	#endif

	// Test cases from lab 8
	#if 0
	int arr[11] = { 6, 2, 10, 7, 5, 1, 11, 9, 3, 4, 8 };
	FibHeap<int> H1(arr, 11);

	/**
	 * B0
	 * 8
	 *
	 * B1
	 * 3 4
	 *
	 * B3
	 * 1 2 7 10 6 9 11 5
	 *
	 */
	H1.printKey();

	/**
	 * B0
	 * 8
	 *
	 * B1
	 * 3 4
	 *
	 * B3
	 * 1 2 7 10 6 9 11 5
	 *
	 */
	FibHeap<int> H2 = H1;
	H2.printKey();

	#if 0
	/**
	 * B1
	 * 5 8
	 *
	 * B3
	 * 2 3 9 11 4 7 10 6
	 */
	H1.extractMin();
	H1.printKey();

	/**
	 * B1
	 * 5 8
	 *
	 * B3
	 * 2 3 9 11 4 7 10 6
	 *
	 * B0
	 * 15
	 *
	 * B0
	 * 19
	 *
	 * B0
	 * 22
	 */
	H1.insert(15);
	H1.insert(19);
	H1.insert(22);
	H1.printKey();

	/**
	 * B2
	 * 6 19 22 15
	 *
	 * B3
	 * 3 5 7 10 8 9 11 4
	 */
	H1.extractMin();
	H1.printKey();

	/**
	 * B0
	 * 4
	 *
	 * B1
	 * 9 11
	 *
	 * B3
	 * 5 6 7 10 22 15 19 8
	 */
	H1.extractMin();
	H1.printKey();
	#endif
	#endif

	// First half of test cases from lab 7
	#if 0
	Heap<int> H1;

	H1.insert(6);
	H1.insert(2);
	H1.insert(10);
	H1.insert(7);
	H1.insert(5);
	H1.insert(1);
	H1.insert(11);
	H1.insert(9);
	H1.insert(3);
	H1.insert(4);
	H1.insert(8);

	// 1 3 2 5 4 8 11 9 7 6 10
	H1.printKey();

	// 2 3 8 5 4 10 11 9 7 6
	H1.extractMin();
	H1.printKey();

	// 3 4 8 5 6 10 11 9 7
	H1.extractMin();
	H1.printKey();

	// 4 5 8 7 6 10 11 9
	H1.extractMin();
	H1.printKey();

	// 5 6 8 7 9 10 11
	H1.extractMin();
	H1.printKey();

	// 6 7 8 11 9 10
	H1.extractMin();
	H1.printKey();

	// 7 9 8 11 10
	H1.extractMin();
	H1.printKey();

	// 8 9 10 11
	H1.extractMin();
	H1.printKey();

	// 9 11 10
	H1.extractMin();
	H1.printKey();

	// 10 11
	H1.extractMin();
	H1.printKey();

	// 11
	H1.extractMin();
	H1.printKey();

	//
	H1.extractMin();
	H1.printKey();

	// 1 2 3
	H1.insert(1);
	H1.insert(2);
	H1.insert(3);
	H1.printKey();

	// 1 2 3
	Heap<int> H2 = H1;
	H2.printKey();
	#endif

	// Second half of test cases from lab 7
	#if 0
	int arr[11] = { 6, 2, 10, 7, 5, 1, 11, 9, 3, 4, 8 };
	Heap<int> H1(arr, 11);

	// 1 2 6 3 4 10 11 9 7 5 8
	H1.printKey();

	// 1 2 6 3 4 10 11 9 7 5 8
	heap_copy_test(H1);
	#endif

	return 0;
}
