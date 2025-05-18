int find_insert_point(int *array, int size, int target)
{
    int left;
    int right;
    int mid;

    left = 0;
    right = size - 1;
    if (array[left] < array[right] && (target < array[left] || target > array[right]))
        return (0);
    if (array[right] < target && target < array[left])
        return (0);
    while (right - left > 1)
    {
        mid = (right - left) / 2 + left;
        if (array[mid] < array[right])
        {
            if (target > array[mid] && target < array[right])
                left = mid;
            else
                right = mid;
        }
        else
        {
            if (target > array[left] && target < array[mid])
                right = mid;
            else
                left = mid;
        }
    }
    return (right);
}

#include <stdio.h>
int main()
{
    int array[6] = {5, 7, 9};
    printf("%d", find_insert_point(array, 3, 6));
}