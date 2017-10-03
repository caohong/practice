

class Solution {
public:
    /*
     * @param root: A Tree
     * @return: Preorder in ArrayList which contains node values.
     */
    vector<int> preorderTraversal(TreeNode * root) {
        vector<int> result;
        if (root == NULL) {
            return result;
        }
        add2Vector(root, result);
        return result;
    }
    
    void add2Vector(TreeNode* node, vector<int>& result) {
        if (node == NULL) {
            return;
        }
        result.push_back(node->val);
        add2Vector(node->left, result);
        add2Vector(node->right, result);
    }
};
