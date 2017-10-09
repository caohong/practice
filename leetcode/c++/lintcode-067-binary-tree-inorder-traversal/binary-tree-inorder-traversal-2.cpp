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
        TreeNode* p = root;
        stack<TreeNode*> nodeStack;
        while (p!=NULL) {
            nodeStack.push(p);
            p = p->left;
        }
        while (!nodeStack.empty()) {
            p = nodeStack.top();
            nodeStack.pop();
            result.push_back(p->val);
            p = p->right;
            while (p!=NULL) {
                nodeStack.push(p);
                p = p->left;
            }
        }
        return result;
    }

};