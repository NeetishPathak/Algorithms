#include <iostream>

using namespace std;

void selectionsort(int a[], int len){
    for(int i=0; i < len-1; ++i){
        for(int j = i+1; j < len; ++j){
            if(a[j] < a[i]){
                swap(a[j],a[i]);
            }
        }
    }

}


void selectionsort1(int a[], int len){
    for(int i=0; i < len; ++i){
            int x = a[i];
        for(int j = i; j > 0; j--){
            if(a[j] < a[j-1]){
                a[j] = a[j-1];
            }else{
                break;
            }
            a[j-1] = x;
        }
    }

}

int main()
{
    int arr[5] = {1,2,3,4,5};
    int brr[5] = {3,3,3,3,3};

    selectionsort1(arr,5);

    for(int i=0; i < 5; ++i){
        cout << arr[i] << " ";
    }
    cout << endl;
    cout << "Hello world!" << endl;
    return 0;
}
