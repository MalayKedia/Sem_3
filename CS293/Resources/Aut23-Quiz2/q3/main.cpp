#include "ropes.cpp"

int main()
{
    int T;
    cin >> T;
    int arr[100000];
    for (int i = 0; i < T;i++)
    {
        int size;
        cin >> size;
        for (int j = 0;j<size;j++) cin >> arr[j];
        cout << minCost(arr, size) << std::endl; // Write a function mincost which takes the array and size as parameters and returns the integer solution
    }
	return 0;
}
