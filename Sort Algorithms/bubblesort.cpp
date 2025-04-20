#include <iostream>

int* bubbleSort(int array[], int length)
{
    for(int i = 0; i < length; i++)
    {
        for(int j = 0; j < length - i - 1; j++)
        {
            if(array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
    return array;
}

int main()
{
    int array[] = {-2, 3, 1, 0, 5, -1};
    int length = sizeof(array)/sizeof(array[0]);

    for(int i = 0; i < length; i++)
    {
        std::cout << array[i] << ", ";
    }
    std::cout << std::endl;

    bubbleSort(array, length);

    for(int i = 0; i < length; i++)
    {
        std::cout << array[i] << ", ";
    }

    return 0;
}
