#include <iostream>
#include <vector>
#include <stack>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class PreorderIterative {
public:
    std::vector<int> preorderTraversal(TreeNode* root) {
        std::vector<int> result;
        std::stack<TreeNode*> vertices;
        vertices.push(root);
        while (!vertices.empty()) {
            TreeNode* curr_vertex = vertices.top();
            vertices.pop();
            if (curr_vertex) {
                result.push_back(curr_vertex->val);
                vertices.push(curr_vertex->right); // dad, left son, right son.
                vertices.push(curr_vertex->left);
            }
        }
        return result;
    }
};

class TreeTraversal {
public:
    void PreorderRecursion(TreeNode* root, std::vector<int>* result) {
        if (!root) {
            return;
        }
        result->push_back(root->val);
        PreorderRecursion(root->left, result);
        PreorderRecursion(root->right, result);
    }

    void InorderRecursion(TreeNode* root, std::vector<int>* result) {
        if (!root) {
            return;
        }
        InorderRecursion(root->left, result);
        result->push_back(root->val);
        InorderRecursion(root->right, result);
    }

    void PostorderRecursion(TreeNode* root, std::vector<int>* result) {
        if (!root) {
            return;
        }
        PostorderRecursion(root->left, result);
        PostorderRecursion(root->right, result);
        result->push_back(root->val);
    }
};

