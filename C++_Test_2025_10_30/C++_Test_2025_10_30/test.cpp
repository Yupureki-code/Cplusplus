#include <iostream>
#include <vector>
#include <list>
using namespace std;


struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};


//二叉树的前序遍历
class Solution1 {
public:
    vector<int> preorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> v;
        v.push_back(root->val);
        vector<int> tmp = preorderTraversal(root->left);
        v.insert(v.end(), tmp.begin(), tmp.end());
        tmp = preorderTraversal(root->right);
        v.insert(v.end(), tmp.begin(), tmp.end());
        return v;
    }
};

//二叉树的中序遍历

class Solution2 {
public:
    vector<int> inorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> v;
        vector<int> tmp = inorderTraversal(root->left);
        v.insert(v.end(), tmp.begin(), tmp.end());
        v.push_back(root->val);
        tmp = inorderTraversal(root->right);
        v.insert(v.end(), tmp.begin(), tmp.end());
        return v;
    }
};

//二叉树的后序遍历

class Solution3 {
public:
    vector<int> postorderTraversal(TreeNode* root) {
        if (root == nullptr)
            return vector<int>();
        vector<int> v;
        vector<int> tmp = postorderTraversal(root->left);
        v.insert(v.end(), tmp.begin(), tmp.end());
        tmp = postorderTraversal(root->right);
        v.insert(v.end(), tmp.begin(), tmp.end());
        v.push_back(root->val);
        return v;
    }
};

//前序遍历和中序遍历构建二叉树

class Solution4 {
public:

    TreeNode* build(vector<int>& preorder, vector<int>& inorder, int& prev, int inleft, int inright)
    {
        if (inleft > inright)
            return nullptr;
        TreeNode* root = new TreeNode(preorder[prev]);
        int i = inleft;
        while (inleft <= inright)
        {
            if (preorder[prev] == inorder[inleft])
                break;
            else
                inleft++;
        }
        prev++;
        root->left = build(preorder, inorder, prev, i, inleft - 1);
        root->right = build(preorder, inorder, prev, inleft + 1, inright);
        return root;
    }

    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int i = 0;
        return build(preorder, inorder, i, 0, inorder.size() - 1);
    }
};