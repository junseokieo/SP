#include <stdio.h>
#define N 10

void print_data(int* data);
void sum_average_data(int *data);
void sort_data(int data[]);
void reverse_data(int* data);

int main(void){
    int array[N] = {10, 30, 50, 22, 90, 45, 88, 15, 86, 4};

    print_data(array);
    sum_average_data(array);
    sort_data(array);
    print_data(array);
    reverse_data(array);

    return 0;
}

void print_data(int* data){
    printf("배열의 내용 =");
    for (int i=0; i<N; i++){
        printf(" %d", *(data+i));
    }
    printf("\n");
}

void sum_average_data(int *data){
    int sum = 0;
    for (int i=0; i<N; i++){
        sum += *(data+i);
    }
    printf("배열값의 합 = %d\n", sum);
    printf("배열의 평균 = %d\n", sum/N);
}

void sort_data(int data[]){
    for (int i=0; i<N-1; i++){
        for (int j=i+1; j<N; j++){
            if(data[i] > data[j]){
                int temp = data[i];
                data[i] = data[j];
                data[j] = temp;
            }
        }
    }
    printf("Sort    후 ");
}

void reverse_data(int* data){
    int kim[N];
    int j = N-1;
    for (int i=0; i<N; i++){
            kim[i] = *(data+j);
            j--;
    }
    printf("Reverse 후 ");
    print_data(kim);
}
