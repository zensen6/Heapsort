#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

typedef int Data;

int max(Data d1, Data d2) {

	return d1 >= d2 ? d1 : d2;
}

int min(Data d1, Data d2) {

	return d1 <= d2 ? d1 : d2;

}


class heapnode {
public:
	Data data;

public:
	heapnode(Data data):data(data){}
	void getdata(Data data) {
		this->data = data;
	}
};

class heap {
public:
	heapnode* nodes;
	int capacity;
	int usedsize;

public:
	heap(int c) {
		
		capacity = c;
		usedsize = 0;
		nodes = (heapnode*) malloc(capacity * sizeof(heapnode));
	}

	void heap_destroy(heap* h);
	void heap_insert(Data data);
	void heap_deletemin();
	int heap_getparent(int index);
	int heap_getleftchild(int index);
	int heap_getrightchild(int index);
	void heap_swapnode(int index1, int index2);
	void heap_printnode(heap* h);
	bool used_size_empty();
};
bool heap::used_size_empty() {

	return usedsize == 0 ? true : false;
}


void heap::heap_destroy(heap* h) {

	delete[] h->nodes;
	delete[] h;

}

void heap::heap_insert(Data data) {

	int insertind = usedsize;
	int parentind = insertind / 2;

	if (usedsize == capacity) {
		capacity *= 2;
		nodes = (heapnode*)realloc(nodes, capacity * sizeof(heapnode));
	}

	nodes[usedsize++].getdata(data);

	while (nodes[insertind].data < nodes[parentind].data) {
		heap_swapnode(insertind, parentind);
		insertind = heap_getparent(insertind);
		parentind = heap_getparent(parentind);
	}

}

void heap::heap_deletemin() {

	int curindex = 0;
	int leftindex = 1;
	int rightindex = 2;
	
	heap_swapnode(curindex, usedsize - 1);
	usedsize--;
	nodes = (heapnode*)realloc(nodes, (usedsize) * sizeof(heapnode));
	if (usedsize == capacity / 2) {

		capacity /= 2;

	}
	
	while (1) {

		if (heap_getleftchild(curindex) > usedsize - 1) break;
		else if (nodes[curindex].data < min(nodes[leftindex].data, nodes[rightindex].data)) break;
		else if (heap_getrightchild(curindex) == usedsize) {

			if (nodes[curindex].data > nodes[leftindex].data) {
				heap_swapnode(curindex, leftindex);
				curindex = leftindex;

			}
			else {

				break;
			}
		}

		else if (nodes[curindex].data > nodes[leftindex].data && nodes[curindex].data > nodes[rightindex].data) {

			if (nodes[leftindex].data > nodes[rightindex].data) {
				heap_swapnode(curindex, rightindex);
				curindex = rightindex;
			}
			else {

				heap_swapnode(curindex, leftindex);
				curindex = leftindex;

			}
			
		}
		else if (nodes[curindex].data > nodes[rightindex].data) {
		
				heap_swapnode(curindex, rightindex);
				curindex = rightindex;

		}
		else if (nodes[curindex].data > nodes[leftindex].data) {

				heap_swapnode(curindex, leftindex);
				curindex = leftindex;
		}
		rightindex = heap_getrightchild(curindex);
		leftindex = heap_getleftchild(curindex);
	}

	

}

int heap::heap_getparent(int index) {

	return index / 2;

}

int heap::heap_getleftchild(int index) {

	return index * 2 + 1;

}
int heap::heap_getrightchild(int index) {

	return index * 2 + 2;

}


void heap::heap_swapnode(int index1, int index2) {

	Data swp = nodes[index1].data;
	nodes[index1].data = nodes[index2].data;
	nodes[index2].data = swp;

}

void heap::heap_printnode(heap* h) {

	cout << "used size:" << usedsize << endl;
	int i = 0;
	for (i = 0; i < h->usedsize; i++) {

		cout << h->nodes[i].data << ' ';

	}
	cout << endl;
}

int main() {

	srand(time(NULL));
	int random;

	int initialsize;
	int N;
	cin >> initialsize;
	cin >> N;
	heap* H = new heap(initialsize);
	int i = 0;
	while (i++ < N) {
		random = (rand() % 100) + 1;
		H->heap_insert(random);
	}
	while (!(H->used_size_empty())) {

		H->heap_printnode(H);
		H->heap_deletemin();
	}


	/*H->heap_insert(24);
	H->heap_insert(87);
	H->heap_insert(111);
	H->heap_insert(34);
	H->heap_insert(16);
	H->heap_insert(75);
	H->heap_printnode(H);
	H->heap_deletemin();
	H->heap_printnode(H);
	H->heap_deletemin();
	H->heap_printnode(H);
	H->heap_deletemin();
	H->heap_printnode(H);
	H->heap_deletemin();
	H->heap_printnode(H);
	H->heap_deletemin();
	H->heap_printnode(H);
	H->heap_deletemin();
	H->heap_printnode(H);
	*/
}