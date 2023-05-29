#include <omp.h>
#include <iostream>
#include <vector>
using namespace std;

void bubble_sort_odd_even(vector<int>& arr) {
    bool isSorted = false;
    while (!isSorted) {
        isSorted = true;
        
        #pragma omp parallel for
        for (int i = 0; i < arr.size() - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
        #pragma omp parallel for
        for (int i = 1; i < arr.size() - 1; i += 2) {
            if (arr[i] > arr[i + 1]) {
                swap(arr[i], arr[i + 1]);
                isSorted = false;
            }
        }
    }
}

int main() {
    int n;
    cin >> n;
    int a;
    vector<int> arr;
    
    double start, end;

    for (int i = 0; i < n; i++) {
        cin >> a;
        arr.push_back(a);
    }

    // Measure performance of parallel bubble sort using odd-
    // even transposition
    start = omp_get_wtime();
    bubble_sort_odd_even(arr);
    end = omp_get_wtime();
    cout << "Parallel bubble sort using odd-even transposition time: "<<end - start<<endl;


    for (int i = 0; i < n ; i++){
        cout<<" "<<arr[i];
    }
}
