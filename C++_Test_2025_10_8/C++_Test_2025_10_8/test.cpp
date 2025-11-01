#define _CRT_SECURE_NO_WARNINGS 1
#include <iostream>
#include <string>
using namespace std;
//模拟实现atoi
class Solution1 {
public:
    int myAtoi(string str) {
        int cur = 0;
        while (str[cur] == ' ')
        {
            cur++;
        }
        int ret = 1;
        if (str[cur] == '-')
        {
            ret = -1;
            cur++;
        }
        else if (str[cur] == '+')
        {
            cur++;
        }
        int left = cur;
        long long num = 0;
        while (str[cur] >= '0' && str[cur] <= '9')
        {
            int n = str[cur] - '0';
            num = num * 10 + n;
            if (ret == 1 && num > INT_MAX)
            {
                return INT_MAX;
            }
            if (ret == -1 && -num < INT_MIN)
            {

                return INT_MIN;
            }
            cur++;
        }
        return ret * num;
    }
};

//字符串相加
class Solution2 {
public:
    string addStrings(string num1, string num2) {
        string tmp = "";
        int cur1 = num1.size() - 1;
        int cur2 = num2.size() - 1;
        int n3 = 0;
        while (cur1 >= 0 || cur2 >= 0 || n3)
        {
            int n1 = 0;
            int n2 = 0;
            if (cur1 >= 0)
            {
                n1 = num1[cur1] - '0';
                cur1--;
            }
            if (cur2 >= 0)
            {
                n2 = num2[cur2] - '0';
                cur2--;
            }
            int sum = n1 + n2 + n3;
            n3 = sum / 10;
            tmp += sum % 10 + '0';
        }
        reverse(tmp.begin(), tmp.end());
        return tmp;
    }
};

//反转字符串
void reverseString(char* s, int sSize) {
    int left = 0;
    int right = sSize - 1;
    while (left <= right)
    {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        left++;
        right--;
    }
    return;
}

//反转字符串2
void reverse(string& s, int left, int right)
{
    while (left <= right)
    {
        char tmp = s[left];
        s[left] = s[right];
        s[right] = tmp;
        left++;
        right--;
    }
}


class Solution {
public:
    string reverseStr(string s, int k) {
        int count = 1;
        int last = 0;
        while (count <= s.size())
        {
            if (count % (2 * k) == 0)
            {
                reverse(s, last, last + k - 1);
                last = count;
            }
            count++;
        }
        count--;
        if (count - last < k)
        {
            reverse(s, last, count - 1);
        }
        if ((count - last) >= k && (count - last) < 2 * k)
        {
            reverse(s, last, last + k - 1);
        }
        return s;
    }
};

