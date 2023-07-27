#include <iostream>
#include <vector>
#include <stack>

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    explicit TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
    TreeNode(int value, TreeNode* left, TreeNode* right) : val(value), left(left), right(right) {}
};

void PrintPostorder(TreeNode* root) {
    if (!root) {
        return;
    }
    PrintPostorder(root->left);
    PrintPostorder(root->right);
    std::cout << root->val << " ";
}

void PrintInorder(TreeNode* root) {
    if (!root) {
        return;
    }
    PrintInorder(root->left);
    std::cout << (root->val) << " ";
    PrintInorder(root->right);
}

void FreeMemory(TreeNode* root) {
    if (!root) {
        return;
    }
    FreeMemory(root->left);
    FreeMemory(root->right);
    delete root;
}

TreeNode* BuildTree(const std::vector<int>& preorder) {
    if (preorder.empty()) {
        return nullptr;
    }
    auto root = new TreeNode(preorder[0]);
    std::stack<TreeNode*> all;
    all.push(root);
    std::stack<TreeNode*> left;

    TreeNode* curr_vertex = root;
    for (size_t ind = 1; ind < preorder.size(); ++ind) {
        auto new_vertex = new TreeNode(preorder[ind]);
        if (new_vertex->val < curr_vertex->val) {
            left.push(curr_vertex);
            curr_vertex->left = new_vertex;
            curr_vertex = curr_vertex->left;
        } else {
            while (!(left.empty() or left.top()->val > new_vertex->val)) {
                all.pop();
                left.pop();
            }
            curr_vertex = all.top();
            all.pop();
            curr_vertex->right = new_vertex;
            curr_vertex = curr_vertex->right;
        }
        all.push(new_vertex);
    }

    return root;
}

std::vector<int> ReadInput() {
    int size;
    std::cin >> size;
    std::vector<int> input(size);
    for (auto& it : input) {
        std::cin >> it;
    }
    return input;
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    auto preorder = ReadInput();
    auto root = BuildTree(preorder);
    PrintPostorder(root);
    std::cout << "\n";
    PrintInorder(root);
    FreeMemory(root);

    return 0;
}
