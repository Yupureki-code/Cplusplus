#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;

//找出字符串的唯一的字符
class Solution1 {
public:
    int firstUniqChar(string s) {
        int max = s[0];
        int min = s[0];
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] > max)
            {
                max = s[i];
            }
            if (s[i] < min)
            {
                min = s[i];
            }
        }
        int* arr = new int[max - min + 1]();
        for (int i = 0; i < s.size(); i++)
        {
            int num = s[i];
            arr[num - min]++;
        }
        for (int i = 0; i < s.size(); i++)
        {
            if (arr[s[i] - min] == 1)
            {
                return i;
            }
        }
        return -1;
    }
};
//反转单词

void reverse(string& rs, int left, int right)
{
    while (left <= right)
    {
        char tmp = rs[left];
        rs[left] = rs[right];
        rs[right] = tmp;
        left++;
        right--;
    }
}

class Solution {
public:
    string reverseWords(string s) {
        int pos = 0;
        int left = 0;
        while ((pos = s.find(' ', pos)) != s.npos)
        {
            reverse(s, left, pos - 1);
            left = pos + 1;
            pos++;
        }
        reverse(s, left, s.size() - 1);
        return s;
    }
};
