
/*********************************************************************************
 *      Copyright:  (C) 2020 shx
 *                  All rights reserved.
 *
 *         Author:  tianjincheng <473892093@qq.com>
 *
 ********************************************************************************/
#include <iostream>

using namespace std;
inline int sawp(int& arr1, int& arr2)
{
    int tmp = -1;
    tmp =arr1;
    arr1 = arr2;
    arr2 = tmp;

}
//使用分而治之的方法实现
void arr_convert_1(int* arr, int lo, int hi)
{
    if (lo < hi)
    {
        swap(arr[lo], arr[hi]);
        arr_convert_1(arr, ++lo, --hi);
    }
}
//用迭代的方法实现法一
void arr_convert_2(int* arr, int lo, int hi)
{
    while (lo < hi)
    {
        swap(arr[lo++],arr[hi--]);

    }
}
//用迭代的方法实现法二

void arr_convert_3(int* arr, int lo, int hi)
{
next:
    if (lo < hi)
    {
        swap(arr[lo++], arr[hi--]);
        goto next;
    }
}


void test()
{
    int i = 0;
    int arr[10] = {-1};
    for (i = 0; i < (sizeof(arr) / sizeof(arr[0])); i++)
        arr[i] = i+1;

    arr_convert_3(arr,0, (sizeof(arr) / sizeof(arr[0])) -1);
    for (i = 0; i < (sizeof(arr)/sizeof(arr[0])); i++)
        cout << arr[i] << endl;

}
int main(int argc, char** argv)
{
    test();

    return 0;
}

