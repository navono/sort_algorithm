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
