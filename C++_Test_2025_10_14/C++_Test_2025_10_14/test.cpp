#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;


//二叉树层序遍历1
class Solution1 {
public:
    vector<vector<int>> levelOrder(TreeNode* root) {
        vector<vector<int>> ret;
        if (root == nullptr)
        {
            return ret;
        }
        queue<TreeNode*> qu;
        qu.push(root);
        int levelsize = 1;
        int level = 0;
        while (!qu.empty())
        {
            int tmp = 0;
            while (levelsize--)
            {
                TreeNode* node = qu.front();
                qu.pop();
                if (ret.size() == level)
                {
                    ret.resize(ret.size() + 1);
                }
                ret[level].push_back(node->val);
                if (node->left != nullptr)
                {
                    qu.push(node->left);
                    tmp++;
                }
                if (node->right != nullptr)
                {
                    qu.push(node->right);
                    tmp++;
                }
            }
            level++;
            levelsize = tmp;
        }
        return ret;
    }
};

//最小栈

class MinStack {
public:
    MinStack()
    {
    }
    void push(int val) {
        st.push(val);
        if (min.empty() || min.top() >= val)
        {
            min.push(val);
        }
    }

    void pop() {
        int val = st.top();
        st.pop();
        if (val == min.top())
        {
            min.pop();
        }
    }

    int top() {
        return st.top();
    }

    int getMin() {
        return min.top();

    }
private:
    stack<int> st;
    stack<int> min;
};

//栈的压入，弹出序列

class Solution {
public:
    /**
     * 代码中的类名、方法名、参数名已经指定，请勿修改，直接返回方法规定的值即可
     *
     *
     * @param pushV int整型vector
     * @param popV int整型vector
     * @return bool布尔型
     */
    bool IsPopOrder(vector<int>& pushV, vector<int>& popV) {
        stack<int> tmp;
        int count = 0;
        for (int i = 0; i < pushV.size(); i++)
        {
            tmp.push(pushV[i]);
            int val = pushV[i];
            while (val == popV[count] && count < popV.size())
            {
                count++;
                tmp.pop();
                if (tmp.empty())
                {
                    break;
                }
                val = tmp.top();
            }
        }
        if (tmp.empty())
        {
            return true;
        }
        return false;
    }
};