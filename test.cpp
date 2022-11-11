#include <iostream>
using namespace std;
#include "Heap.cpp"
#include "FibHeap.cpp"


int main(){
	string A[10] = {"A","B","C","D","E","F","H","I","J","K"};
	int B[10] = {10,9,8,7,6,5,4,3,2,1};
	
	Heap<int> T1;
	Heap<int> T2(B,10);

	Heap<int> T3(T2);
	Heap<int> T4;
	T4 = T2;

	T2.printKey();
	T3.printKey();
	T4.printKey();
	//Should output  1 2 4 3 6 5 8 10 7 9
	
	for(int i=0; i<10; i++) T1.insert(B[i]);
	
	T1.printKey();
	// Should output 1 2 5 4 3 9 6 10 7 8
	
	cout << T2.peekKey() << endl;
	cout << T3.peekKey() << endl;
	cout << T4.peekKey() << endl;

	//Should output 1
	cout << T2.extractMin() << endl;
	cout << T3.extractMin() << endl;
	cout << T4.extractMin() << endl;

	T2.printKey();
	T3.printKey();
	T4.printKey();

	
	cout << T1.extractMin() << endl;
	//Should output 1
	
	T1.printKey();
	//Should output 2 3 5 4 8 9 6 10 7
	
	return 0;
}