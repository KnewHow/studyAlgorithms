#include "Solution.h"

std::vector<std::vector<int>> Solution::zigzagLevelOrder(TreeNode* root)
{
    std::vector<std::vector<int>> levelOrderValues;
    doLevelOrder(root, levelOrderValues, 0);
    for (int i = 1; i < levelOrderValues.size(); i += 2) {
        std::reverse(levelOrderValues[i].begin(), levelOrderValues[i].end());
    }
    return levelOrderValues;
}

void Solution::doLevelOrder(TreeNode* root, std::vector<std::vector<int>>& levelOrderValues, int currentLevel)
{
    if (root == nullptr) {
        return;
    }
    else {
        if (levelOrderValues.size() == currentLevel) {
            levelOrderValues.push_back(std::vector<int>()); // create vector
            levelOrderValues[currentLevel].push_back(root->val);
        }
        else {
            levelOrderValues[currentLevel].push_back(root->val);
        }
        doLevelOrder(root->left, levelOrderValues, currentLevel + 1);
        doLevelOrder(root->right, levelOrderValues, currentLevel + 1);
    }
}
