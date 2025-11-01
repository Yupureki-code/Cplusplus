#include <iostream>
using namespace std;
#include <vector>
#include <string>
#include <algorithm>

//删除重复元素
class Solution1 {
public:
    int removeDuplicates(vector<int>& nums) {
        vector<int>::iterator begin = nums.begin();
        while (begin != nums.end())
        {
            vector<int>::iterator cur = begin + 1;
            while (cur != nums.end())
            {
                if (nums[cur - nums.begin()] == nums[begin - nums.begin()])
                {
                    nums.erase(cur);
                }
                else
                {
                    cur++;
                }
            }
            begin++;
        }
        return nums.end() - nums.begin();
    }
};

//数组中超过一半的元素
class Solution2 {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param numbers int整型vector
     * @return int整型
     */
    int MoreThanHalfNum_Solution(vector<int>& numbers) {
        int num = 0;
        int count = 0;
        int n = 0;
        while (n != numbers.size())
        {
            if (count == 0)
            {
                num = numbers[n];
                count++;
            }
            else if (num == numbers[n])
            {
                count++;
            }
            else
            {
                count--;
            }
            n++;
        }
        return num;
    }
};

//只出现1次的数字，其余出现3次
class Solution {
public:
    int singleNumber(vector<int>& nums) {
        if (nums.size() == 1)
        {
            return *nums.begin();
        }
        sort(nums.begin(), nums.end());
        vector<int>::iterator cur = nums.begin();
        if (*cur != *(cur + 1))
        {
            return *cur;
        }
        cur++;
        while (cur != nums.end() - 1)
        {
            if (*(cur - 1) != *(cur) && (*cur) != *(cur + 1))
            {
                return *cur;
            }
            cur++;
        }
        return *cur;
    }
};