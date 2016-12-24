#include <iostream>

using namespace std;

int Partition(int a[], int p, int r){

    int x = a[r];

    int i = p-1;
    int j = i+1;

    while(j <= r-1){
      if(a[j] >= x){
        i = i+1;
        swap(a[i],a[j]);
      }
      j++;
    }
    swap(a[i+1],a[r]);
    return i+1;


}

void quickSort(int a[], int p, int r){

    if(p < r){
      int  q = Partition(a,p,r);
      for(int i=0; i < 8; ++i){
        cout << a[i] << " ";
      }
      cout << endl;
      quickSort(a,p,q-1);
      quickSort(a,q+1,r);
    }

}

int main()
{
    int a[8] = {2,8,7,1,3,5,6,4};
    cout << "Array before sorting" << endl;
    for(int i=0; i < 8; ++i){
        cout << a[i] << endl;
    }

    quickSort(a,0,7);

    cout << "Array after sorting" << endl;
    for(int i=0; i < 8; ++i){
        cout << a[i] << endl;
    }

    cout << "Hello world!" << endl;
    return 0;
}
