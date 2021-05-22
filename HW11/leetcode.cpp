/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */



class Solution {
private:
    int ans;
    void dp(TreeNode *root, bool isleft, int depth)
    {
        if (root==nullptr) return ;
        ans=ans>depth+1?ans:depth+1;
        if (isleft)
        {
            dp(root->right,false, depth+1);
            dp(root->left,true,0);
        }
        else 
        {
            dp(root->left,true,depth+1);
            dp(root->right,false,0);

        }
    }
    
public:
    int longestZigZag(TreeNode* root) {
        this->ans=0;
        dp(root->left, true, 0);
        dp(root->right,false,0);
        return ans;
    }
};