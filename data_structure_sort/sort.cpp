#include<iostream>

void selectionSort(int data[], int size)
{   
    
    for (int i = 0; i < size; i++) {
        int min = i;

        for (int j = i+1; j < size; j++)
        {
            
            if (data[j] < data[min])
            {
                min = j;
            }
        }
        int temp = data[min];
        data[min] = data[i];
        data[i] = temp;
    }
    
}

void insertionSort(int data[], int size)
{
    

    for (int i = 1; i < size; i++) {
        int c = data[i];
        int j = i;
        while (j>0&&data[j - 1] > c) {

            
            data[j] = data[j - 1];
            j--;
        }
        data[j] = c;
    }
   
}

void bubbleSort(int data[], int size)
{
    int flag;
    int left = 0;
    int right = size - 1;
    
    do {
        flag = 1;
        int lastSwap = 0;

        for (int i = left + 1; i <= right; i++) {

            if (data[i - 1] > data[i]) {
                int tmp = data[i - 1];
                data[i - 1] = data[i];
                data[i] = tmp;
                flag = 0;
                lastSwap = i;
            }
        }

        right = lastSwap;

        /*if (flag == 1) break;

        for (int i = right; i >left; i--) {

            if (data[i - 1] > data[i]) {
                int tmp = data[i - 1];
                data[i - 1] = data[i];
                data[i] = tmp;
                flag = 0;
            }
        }
        left++;*/
       
    } while (flag == 0);

}

void countingSort(int data[], int size)
{
    int max = data[0];

    for (int i = 1; i < size; i++)
    {
        if (data[i] > max)
        {
            max = data[i];
        }
    }

    int M = max + 1;

    int* count = new int[M];
    int* tmp = new int[size];

    for (int j = 0; j < M; j++)
    {
        count[j] = 0;
    }

    for (int i = 0; i < size; i++)
    {

        count[data[i]]++;
    }

   
    for (int j = 1; j < M; j++)
    {
        count[j] = count[j - 1] + count[j];
    }


    for (int i = size - 1; i >= 0; i--)
    {
        tmp[count[data[i]] - 1] = data[i];
        count[data[i]]--;
    }

  
    for (int i = 0; i < size; i++)
    {
        data[i] = tmp[i];
    }

    delete[] count;
    delete[] tmp;
}

void straightradixSort(int data[], int size)
{
    if (size <= 1)
        return;

    int maxValue = data[0];

    for (int i = 1; i < size; i++) {
        if (data[i] > maxValue)
            maxValue = data[i];
    }

 
    int highestBit = 0;
    while (maxValue > 1) {
        maxValue /= 2;
        highestBit++;
    }

    int* tmp = new int[size];

 
    for (int bit = 0; bit <= highestBit; bit++) {
        int count[2] = { 0, 0 };


        for (int i = 0; i < size; i++) {
            int digit = (data[i] >> bit) & 1;
            count[digit]++;
        }

 
        count[1] += count[0];


        for (int i = size - 1; i >= 0; i--) {
            int digit = (data[i] >> bit) & 1;

            tmp[count[digit] - 1] = data[i];
            count[digit]--;
        }

       
        for (int i = 0; i < size; i++) {
            data[i] = tmp[i];
        }
    }

    delete[] tmp;
}


void radixexchangeSort(int data[], int size,int left = 0, int right = -1, int bit = -1) {
    
    if (right == -1) {
        if (size <= 1)
            return;
        right = size - 1;

        int maxValue = data[0];
        for (int k = 1; k < size; k++) {
            if (data[k] > maxValue)
                maxValue = data[k];
        }

        bit = 0;
        while (maxValue > 1) {
            maxValue /=2 ;
            bit++;
        }
    }

    if (left >= right || bit < 0)
        return;

    int i = left;
    int j = right;

    do {
        while (((data[i] >> bit) & 1) == 0 && i < j)  //(data[i] >>bit)&1會把要看的位元移到最右邊只留下出最右一個位元
            i++;

        while (((data[j] >> bit) & 1) == 1 && i < j)
            j--;

        int temp = data[i];
        data[i] = data[j];
        data[j] = temp;

    } while (i != j);

    if (((data[right] >> bit) & 1) == 0)
        j++;

    
    if (left < j - 1)
        radixexchangeSort(data, size, left, j - 1, bit - 1);

    if (j < right)
        radixexchangeSort(data, size, j, right, bit - 1);
}

void QuickSort(int data[], int size, int left, int right) {
    if (left >= right) return;

    int tmp;
    int mid = left +right / 2;
    tmp = data[mid];
    data[mid] = data[right];
    data[right] = tmp;

    int pe = data[right];
    
    int i = left - 1;
    int j = right;
    
    
    while (true) {
        do { i++; } while (data[i] < pe);
        do { j--; } while (j >= left && data[j] >= pe);

        if (i >= j)
            break;

        tmp = data[i];
        data[i] = data[j];
        data[j] = tmp;
    }

    tmp = data[i];
    data[i] = data[right];
    data[right] = tmp;

    QuickSort(data, size, left, i - 1);
    QuickSort(data, size, i + 1, right);
} 


void quick_sort(int data[], int size) {
    QuickSort(data, size, 0, size - 1);
}