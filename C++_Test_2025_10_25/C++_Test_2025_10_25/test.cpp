#include <vector>
#include <list>
#include <iostream>
using namespace std;

struct ListNode{
 	int val;
 	struct ListNode *next;
 	ListNode(int x) : val(x), next(nullptr) {}
 };


class Solution1 {
public:
    ListNode* ReverseList(ListNode* head) {
        if (head == nullptr)
            return nullptr;
        ListNode* prev = head;
        ListNode* cur = head->next;
        prev->next = nullptr;
        while (cur)
        {
            ListNode* tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
        return prev;
    }
};


//链表指定区域反转

class Solution2 {
public:
    ListNode* reverseBetween(ListNode* head, int m, int n) {
        if (head == nullptr)
            return nullptr;
        if (n == 1)
            return head;
        int count = 1;
        ListNode* cur = head;
        ListNode* tmp1, * tmp2, * tmp3, * tmp4 = nullptr;
        ListNode* prev = cur;
        ListNode* tmp = cur;
        if (m == 1)
        {
            tmp2 = cur;
            prev = cur;
            cur = cur->next;
            tmp = cur;
        }
        else
        {
            while (count < m - 1)
            {
                cur = cur->next;
                count++;
            }
            tmp1 = cur;
            tmp2 = cur->next;
            prev = cur->next;
            cur = prev->next;
            tmp = cur;
            count++;
        }
        while (count < n)
        {
            tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
            count++;
        }
        tmp3 = prev;
        tmp4 = cur;
        if (tmp1)
            tmp1->next = tmp3;
        tmp2->next = tmp4;
        if (m == 1)
            return tmp3;
        return head;
    }
};

//链表每k组反转

class Solution3 {
public:
    void reverse(ListNode* head, ListNode* tail)
    {
        ListNode* prev = head;
        ListNode* cur = head->next;
        ListNode* tmp = cur;
        while (prev != tail)
        {
            tmp = cur->next;
            cur->next = prev;
            prev = cur;
            cur = tmp;
        }
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        if (head == nullptr)
            return nullptr;
        if (k == 1)
            return head;
        int n = 1;
        int r = 1;
        ListNode* cur = head;
        int first = 1;
        ListNode* newhead = head;
        ListNode* tail1 = nullptr;
        while (r)
        {
            cout << "s" << endl;
            ListNode* tmp = cur;
            ListNode* tail = cur;
            while (n != k)
            {
                cur = cur->next;
                if (cur == nullptr)
                {
                    r = 0;
                    break;
                }
                n++;
            }
            n = 1;
            if (r == 0)
            {
                if (first == 1)
                {
                    break;
                }
                tail1->next = tmp;
            }
            else
            {
                tail = cur;
                cur = cur->next;
                reverse(tmp, tail);
                if (first == 1)
                {
                    newhead = tail;
                    tail1 = tmp;
                    first = 0;
                    if (cur == nullptr)
                    {
                        tmp->next = nullptr;
                        r = 0;
                    }
                    continue;
                }
                tail1->next = tail;
                tail1 = tmp;
            }
        }
        return newhead;
    }
};