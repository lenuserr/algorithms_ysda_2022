#include <iostream>
#include <vector>
#include <memory>

struct TreeNode {
    int val;
    int left_subtree_size = 0;
    std::shared_ptr<TreeNode> left;
    std::shared_ptr<TreeNode> right;
    explicit TreeNode(int value) : val(value), left(nullptr), right(nullptr) {}
};

void Insert(const std::shared_ptr<TreeNode>& root, const std::shared_ptr<TreeNode>& dad, int key) {
    if (!root) {
        if (dad->val > key) {
            dad->left = std::make_shared<TreeNode>(key);
        } else {
            dad->right = std::make_shared<TreeNode>(key);
        }
        return;
    }

    if (root->val > key) {
        Insert(root->left, root, key);
    } else {
        Insert(root->right, root, key);
    }
}

void BuildSubtree(int left, int right,
                  const std::vector<int>& vertices, const std::shared_ptr<TreeNode>& root) {
    if (left == right) {
        return;
    }
    int index = (left + right) / 2;
    Insert(root, nullptr, vertices[index]);
    BuildSubtree(left, index, vertices, root);
    BuildSubtree(index + 1, right, vertices, root);
}

std::shared_ptr<TreeNode> BuildTree(int nn) {
    std::vector<int> vertices(nn);
    for (int i = 1; i <= nn; ++i) {
        vertices[i - 1] = i;
    }
    int index = (0 + nn) / 2;
    auto root = std::make_shared<TreeNode>(vertices[index]);
    BuildSubtree(0, index, vertices, root);
    BuildSubtree(index + 1, nn, vertices, root);

    return root;
}

int TreeInitialization(const std::shared_ptr<TreeNode>& root, int* total) {
    if (!root) {
        return *total;
    }
    (*total)++;
    int size = *total;
    root->left_subtree_size = TreeInitialization(root->left, total) - size;
    TreeInitialization(root->right, total);
    return *total;
}

void Successor(const std::shared_ptr<TreeNode>& root) {
    auto dad = root;
    auto successor = root->right;
    while (successor->left) {
        successor->left_subtree_size--;
        dad = successor;
        successor = successor->left;
    }
    root->val = successor->val;

    if (dad == root) {
        if (!successor->right) {
            root->right = nullptr;
        } else {
            root->right = successor->right;
        }
        return;
    }

    if (!successor->right) {
        dad->left = nullptr;
    } else {
        dad->left = successor->right;
    }
}

std::shared_ptr<TreeNode> Delete(const std::shared_ptr<TreeNode>& root,
                                 const std::shared_ptr<TreeNode>& dad, int key) {
    if (root->val > key) {
        root->left_subtree_size--;
        Delete(root->left, root, key);
    } else if (root->val < key) {
        Delete(root->right, root, key);
    } else {
        if (!root->left || !root->right) {
            if (!dad) {
                if (!root->left && !root->right) {
                    return nullptr;
                } else if (root->left) {
                    return root->left;
                } else {
                    return root->right;
                }
            }
            if (!root->left && !root->right) {
                if (dad->val > key) {
                    dad->left = nullptr;
                } else {
                    dad->right = nullptr;
                }
            } else if (!root->left) {
                if (dad->val > key) {
                    dad->left = root->right;
                } else {
                    dad->right = root->right;
                }
            } else {
                if (dad->val > key) {
                    dad->left = root->left;
                } else {
                    dad->right = root->left;
                }
            }
        } else {
            Successor(root);
        }
    }

    return root;
}

int SearchKthStatistic(const std::shared_ptr<TreeNode>& root, int kk) {
    if (root->left_subtree_size + 1 > kk) {
        return SearchKthStatistic(root->left, kk);
    } else if (root->left_subtree_size + 1 < kk) {
        return SearchKthStatistic(root->right, kk - root->left_subtree_size - 1);
    } else {
        return root->val;
    }
}

int main() {

    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    int nn, kk;
    std::cin >> nn >> kk;

    auto root = BuildTree(nn);
    int total = 0;
    TreeInitialization(root, &total);

    int curr_ind = 0;
    int curr_size = nn;

    auto curr_root = root;
    for (int i = 0; i < nn; ++i) {
        curr_ind = (curr_ind - 1 + kk) % curr_size;
        int value = SearchKthStatistic(curr_root, curr_ind + 1);
        std::cout << value << " ";
        curr_root = Delete(curr_root, nullptr, value);
        curr_size--;
    }
    std::cout << "\n";

    return 0;
}
