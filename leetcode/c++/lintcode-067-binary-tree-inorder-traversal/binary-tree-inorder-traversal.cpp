/**
 * Definition of TreeNode:
 * class TreeNode {
 * public:
 *     int val;
 *     TreeNode *left, *right;
 *     TreeNode(int val) {
 *         this->val = val;
 *         this->left = this->right = NULL;
 *     }
 * }
 */


class Solution {
public:
    /*
     * @param root: A Tree
     * @return: Inorder in ArrayList which contains node values.
     */
    vector<int> inorderTraversal(TreeNode * root) {
        vector<int> result;
        traverseTree(root, result);
        return result;
    }
    
    void traverseTree(TreeNode * node, vector<int> & result) {
        if (node == NULL) {
            return;
        }
        traverseTree(node->left, result);
        result.push_back(node->val);
        traverseTree(node->right, result);
        return;
    }
};
