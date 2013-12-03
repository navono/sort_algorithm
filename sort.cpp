void print(int *a, int n)
{
	int i;
	for (i = 0; i < n; i++)
		printf("%d\t", a[i]);
}


void quickSort(int arr[], int left, int right) {
	int i = left, j = right;
	int temp;
	int pivot = arr[(left + right) / 2];

	// partition
	while (i <= j) {
		while (arr[i] < pivot)
			i++;
		while (arr[j] > pivot)
			j--;

		if (i <= j) {
			temp = arr[i];
			arr[i] = arr[j];
			arr[j] = temp;
			i++;
			j--;
		}
	}

	// recursion
	if (left < j)
		quickSort(arr, left, j);
	if (i < right)
		quickSort(arr, i, right);
}

void bubbleSort(int arr[], int n) {
	bool swapped = true;
	int j = 0;
	int temp;

	while (swapped) {
		swapped = false;
		j++;
		for (int i = 0; i < n - j; ++i) {
			if (arr[i] > arr[i+1]) {
				temp = arr[i];
				arr[i] = arr[i+1];
				arr[i+1] = temp;
				swapped = true;
			}
		}
	}
}

void selectionSort(int arr[], int size) {
	int orderIdx, compIdx, minIdx, temp;
	for (orderIdx = 0; orderIdx < size-1; ++orderIdx) {
		minIdx = orderIdx;
		for (compIdx = orderIdx+1; compIdx < size; ++compIdx) {
			if (arr[compIdx] < arr[minIdx])
				minIdx = compIdx;
		}

		// Swap
		if (minIdx != orderIdx) {
			temp = arr[orderIdx];
			arr[orderIdx] = arr[minIdx];
			arr[minIdx] = temp;
		}
	}
}

void insertionSort(int arr[], int size) {
	int i, j, temp;
	for (i = 1; i < size; ++i) {
		for (j = i; (j>0) && (arr[j-1] > arr[j]); j--) {
			temp = arr[j];
			arr[j] = arr[j-1];
			arr[j-1] = temp;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

void insertionSort2(int arr[], int size, int increment) {
	int temp;
	for (int i = increment; i < size; i+=increment) {
		for (int j = i; 
			(j>=increment) && (arr[j-increment] > arr[j]); 
			j-=increment) {
				temp = arr[j];
				arr[j] = arr[j-increment];
				arr[j-increment] = temp;
		}

	}
}

void shellSort(int arr[], int size) {
	int increment = size / 2;
	for (int i = increment; i>2; i/=2) {
		for (int j=0; j<i; ++j) {
			insertionSort2(&arr[j], size-j, i);
		}
	}

	insertionSort2(arr, size, 1);
}

//////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////
// Bin Sort
typedef struct node {
	int key;
	struct node* next;
} KeyNode;

#define THRESHOLD 10

void binSort(int arr[], int size) {
	KeyNode **bucket_table = new KeyNode*[THRESHOLD];

	for (int i=0; i<THRESHOLD; ++i) {
		bucket_table[i] = new KeyNode();
		bucket_table[i]->key = 0;
		bucket_table[i]->next = nullptr;
	}

	for (int i=0; i<size; ++i) {
		KeyNode *node = new KeyNode();
		node->key = arr[i];
		node->next = nullptr;

		// map value to bucket number
		int index = arr[i] / THRESHOLD;
		KeyNode *p = bucket_table[index];
		
		if (p->key == 0) {		// bucket is empty
			bucket_table[index]->next = node;
			++(bucket_table[index]->key);
		}
		else {
			while ((p->next != nullptr) && 
				   (p->next->key <= node->key)) {
					   p = p->next;
			}

			node->next = p->next;
			p->next = node;
			++(bucket_table[index]->key);
		}
	}

	// Copy sorted data to array
	int idx = 0;
	for(int b=0; b<THRESHOLD; ++b) {
		for(KeyNode *k=bucket_table[b]->next;
			(k!=nullptr) && (k->key != 0); k=k->next) {
				arr[idx] = k->key;
				++idx;
		}
	}
}

//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
// Radix Sort
#define MAX 12
#define SHOWPASS

void radixSort(int arr[], int size) {
	int i, b[MAX], m = arr[0], exp = 1;
	for (i = 1; i < size; i++) {
		if (arr[i] > m)
			m = arr[i];
	}

	while (m / exp > 0) {

		// 10 is the radix.
		// Initialize bucket.
		int bucket[10] ={  0 };

		// Count the number of records for each bin on this pass.
		for (i = 0; i < size; i++)
			bucket[(arr[i] / exp) % 10]++;

		// Index b: bucket[i] will be index for last slot of bin i.
		for (i = 1; i < 10; i++)
			bucket[i] += bucket[i - 1];

		// Put records into bins, word from bottom of each bin.
		// Since bins fill from bottom, i counts downwards.
		for (i = size - 1; i >= 0; i--)
			b[--bucket[(arr[i] / exp) % 10]] = arr[i];

		// Copy data back.
		for (i = 0; i < size; i++)
			arr[i] = b[i];

		exp *= 10;

#ifdef SHOWPASS
		printf("\nPASS   : ");
		print(arr, size);
#endif
	}
}

//////////////////////////////////////////////////////////////////////////
