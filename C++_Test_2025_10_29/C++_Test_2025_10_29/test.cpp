#include <iostream>
#include <string>
#include <vector>
#include <stack>
#include <list>
using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    
};

//根据二叉树创建字符串
class Solution1 {
public:
    string tree2str(TreeNode* root) {
        if (root == nullptr)
            return string();
        string ret;
        string ch = to_string(root->val);
        ret += ch;
        if (root->left)
        {
            ret += '(';
            ret += tree2str(root->left);
            ret += ')';
            if (root->right)
            {
                ret += '(';
                ret += tree2str(root->right);
                ret += ')';
            }
        }
        else if (root->right)
        {
            ret += '(';
            ret += ')';
            ret += '(';
            ret += tree2str(root->right);
            ret += ')';
        }
        return ret;
    }
};

//查找公共祖先
class Solution2 {
public:
    bool findnode(TreeNode* root, TreeNode* node)
    {
        if (root == nullptr)
            return false;
        if (root == node)
            return true;
        return findnode(root->left, node) || findnode(root->right, node);
    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        if (root == nullptr)
            return nullptr;
        if (root == p || root == q)
            return root;
        bool pright = findnode(root->right, p);
        bool pleft = !pright;
        bool qright = findnode(root->right, q);
        bool qleft = !qright;
        if ((pright && qleft) || (pleft && qright))
            return root;
        else if (pright && qright)
            return lowestCommonAncestor(root->right, p, q);
        else
            return lowestCommonAncestor(root->left, p, q);
    }
};

class Solution3 {
public:
    list<TreeNode*> convert(TreeNode* root)
    {
        if (root == nullptr)
            return list<TreeNode*>();
        list<TreeNode*> lt;
        list<TreeNode*> lf = convert(root->left);
        lt.insert(lt.end(), lf.begin(), lf.end());
        list<TreeNode*> rg = convert(root->right);
        lt.insert(lt.end(), rg.begin(), rg.end());
        return lt;
    }
    TreeNode* Convert(TreeNode* pRootOfTree) {
        list<TreeNode*> lt = convert(pRootOfTree);
        return *(lt.begin());
    }
};

//二叉树与双向链表
class Solution4 {
public:
    void convert(TreeNode* root, list<TreeNode*>& head)
    {
        if (root == nullptr)
            return;
        convert(root->left, head);
        TreeNode* newnode = new TreeNode(root->val);
        head.push_back(newnode);
        convert(root->right, head);
        return;
    }
    TreeNode* Convert(TreeNode* pRootOfTree) {
        list<TreeNode*> head({ new TreeNode(0) });
        convert(pRootOfTree, head);
        head.erase(head.begin());
        TreeNode* prev = nullptr;
        TreeNode* phead = nullptr;

        for (auto node : head) {
            node->left = prev;
            if (prev != nullptr) {
                prev->right = node;
            }
            else {
                phead = node;  // 第一个节点作为链表头
            }
            prev = node;
        }
        return head.front();
    }
};


int main()
{}
