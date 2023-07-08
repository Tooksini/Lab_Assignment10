# include <stdio.h>

void swap(int *l, int *r){
    int tmp = *l;
    *l = *r;
    *r = tmp;
}

void bubbleSort(int arr[], int n){
    int i, j;
    int numSwaps[] = {0,0,0,0,0,0,0,0,0};

    for(i = 0; i < n - 1; i++){
        for(j = 0; j < n - i - 1; j++){
            // Last i elements are already in place. So, stop j
            // before n-i as we will compare j with j+1, we will
            // stop j before n+i-1 
            if(arr[j] > arr[j + 1]){
                swap(&arr[j], &arr[j + 1]);
                numSwaps[i]++;
            }
        }
    }
    for(int k = 0; k < n; k++){
        printf("%d ", numSwaps[k]);
    }
    printf("\n");
}


int main(){

    int array[] = {97, 16, 45, 63, 13, 22, 7, 58, 72};
    int s = sizeof(array) / sizeof(int);

    bubbleSort(array, s);
    
    for(int i = 0; i < s; i++){
        printf("%d ", array[i]);
    }
    printf("\n");

    return 0;
}