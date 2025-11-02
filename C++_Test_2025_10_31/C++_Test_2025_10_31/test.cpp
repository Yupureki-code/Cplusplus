#include <iostream>
using namespace std;

struct ListNode {
    int val;
    struct ListNode* next;
    ListNode(int x) : val(x), next(nullptr) {}
};

//合并链表
class Solution1 {
public:
    ListNode* Merge(ListNode* pHead1, ListNode* pHead2) {
        if (pHead1 == nullptr) return pHead2;
        if (pHead2 == nullptr) return pHead1;
        ListNode* cur1 = pHead1;
        ListNode* cur2 = pHead2;
        ListNode* head = new ListNode(0);
        ListNode* cur = head;
        while (cur1 != nullptr && cur2 != nullptr)
        {
            if (cur1->val > cur2->val)
            {
                cur->next = cur2;
                cur2 = cur2->next;
            }
            else
            {
                cur->next = cur1;
                cur1 = cur1->next;
            }
            cur = cur->next;
        }
        if (cur1)
        {
            cur->next = cur1;
        }
        if (cur2)
        {
            cur->next = cur2;
        }
        return head->next;
    }
};

//合并k个有序链表
class Solution2 {
public:

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if (lists.size() == 0)
            return nullptr;
        vector<int> v;
        auto it = lists.begin();
        while (it != lists.end())
        {
            ListNode* cur = *it;
            while (cur)
            {
                if (cur == nullptr)
                    break;
                v.push_back(cur->val);
                cur = cur->next;
            }
            it++;
        }
        if (v.size() == 0)
            return nullptr;
        sort(v.begin(), v.end());
        ListNode* head = new ListNode(v[0]);
        ListNode* cur = head;
        auto it2 = v.begin() + 1;
        while (it2 != v.end())
        {
            ListNode* newnode = new ListNode(*it2);
            cur->next = newnode;
            cur = cur->next;
            it2++;
        }
        return head;


    }
};