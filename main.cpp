#include <algorithm>
#include <iostream>
#include <map>
#include <queue>
#include <vector>

using namespace std;

// Helper structs and classes

// Helper ListNode struct used in problems with linked lists provided by leetcode
struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

// Helper Node struct used in N-ary tree
class Node {
   public:
    int val;
    vector<Node *> children;

    Node() {}

    Node(int _val) {
        val = _val;
    }

    Node(int _val, vector<Node *> _children) {
        val = _val;
        children = _children;
    }
};

// Helper TreeNode struct used in binary tree related questions
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};

/*********************************************************/

class Solution {
   public:
    // leetcode provided palceholders
    static bool isBadVersion(int n) { return n >= 5; }  // used in 278

    /**
     * 21. Merge Two Sorted Lists
     * Given two sorted linked lists, returns a single merged linked list
     */
    static ListNode *mergeTwoLists(ListNode *list1, ListNode *list2) {
        // if list 1 or 2 is null, return the other list
        if (list1 == NULL) {
            return list2;
        }
        if (list2 == NULL) {
            return list1;
        }

        // recursively add the merger of rest of the elements to the smallest head
        if (list1->val <= list2->val) {
            list1->next = mergeTwoLists(list1->next, list2);
            return list1;
        } else {
            list2->next = mergeTwoLists(list1, list2->next);
            return list2;
        }
    }

    /**
     * 70. Climbing Stairs
     * If a person can climb the stairs 1 or 2 steps at a time, how many different
     * ways can they climb to the top of a stair with n steps. This boils down to
     * the fibonacci sequence. For speed, this algorithm calculates up to n steps
     * in a vector, and returns the nth step instead of solving it recursively
     */
    static int climbStairs(int n) {
        vector<int> stairs{1, 1};
        for (int i{2}; i < n + 1; i++) {
            stairs.push_back(stairs[i - 1] + stairs[i - 2]);
        }
        return stairs[n];
    }

    /**
     * 98. Validate Binary Search Tree
     * Given the root of a binary tree determine if its a valid binary search tree
     */
    static void helper(TreeNode *root, vector<int> &ans) {  // inorder traversal
        if (root == NULL) return;
        helper(root->left, ans);
        ans.push_back(root->val);
        helper(root->right, ans);
    }
    static bool isValidBST(TreeNode *root) {
        vector<int> ans;
        helper(root, ans);  // populates ans with inorder traversal
        // inorder traversal of binary search tree has to be in ascending order
        for (int i = 0; i < ans.size() - 1; i++) {
            if (ans[i] >= ans[i + 1]) return false;
        }
        return true;
    }

    /**
     * 102. Binary Tree Level Order Traversal
     * Given the root of a binary tree, return the level order
     * traversal as a vector<vector<int>> with each level in a
     * separate vector
     */
    static vector<vector<int>> levelOrder(TreeNode *root) {
        if (!root) return {};
        vector<vector<int>> res;
        queue<TreeNode *> q{{root}};
        while (!q.empty()) {
            vector<int> oneLevel;
            for (int i = q.size(); i > 0; --i) {
                TreeNode *t = q.front();
                q.pop();
                oneLevel.push_back(t->val);
                if (t->left) q.push(t->left);
                if (t->right) q.push(t->right);
            }
            res.push_back(oneLevel);
        }
        return res;
    }

    /**
     * 121. Best Time To Buy and Sell Stock
     * Given a vector of integer prices, maximize profit by finding the best
     * day to buy and a later day to sell, return the maximum profit
     */
    static int maxProfit(vector<int> &prices) {
        int x = INT_MAX, y = 0;

        for (auto p : prices) {
            x = min(p, x);
            y = max(y, p - x);
        }
        return y;
    }

    /**
     * 142. Linked List Cycle II
     * Given head of a linked list, return the node where a
     * cycle begins, if no cycle exists in the list return null
     */
    static ListNode *detectCycle(ListNode *head) {
        vector<ListNode *> v;
        if (head == NULL) {
            return NULL;
        }
        while (head->next != NULL) {
            if (count(v.begin(), v.end(), head)) {
                break;
            }
            v.push_back(head);
            head = head->next;
        }
        if (head->next == NULL) {
            return NULL;
        }
        return head;
    }

    /**
     * 200. Number of Islands
     * Given m x n 2d grid of characters made up of '1' and '0', where
     * 1 represents land, and 0 represents water, return the number of islands
     * where an island is 4-directionally connected positions of 1s.
     */
    static int numIslands(vector<vector<char>> &grid) {
        int r = grid.size();
        int c = grid[0].size();
        int islands = 0;
        for (int i{0}; i < r; ++i) {
            for (int j{0}; j < c; ++j) {
                if (grid[i][j] == '1') {
                    islands++;
                    DFS(grid, i, j);
                }
            }
        }
        return islands;
    }

    // helper function to do flood fill
    static void DFS(vector<vector<char>> &grid, int i, int j) {
        // boundary checking
        if (i < 0 || i >= grid.size() || j < 0 || j >= grid[0].size())
            return;
        // return if current position is of water or is already visited
        if (grid[i][j] == '2' || grid[i][j] == '0')
            return;

        // mark the current as visited
        grid[i][j] = '2';

        // do DFS in all 4 directions
        DFS(grid, i + 1, j);
        DFS(grid, i, j - 1);
        DFS(grid, i - 1, j);
        DFS(grid, i, j + 1);
    }

    /**
     * 205. Isomorphic Strings
     * Given strings s and t, determine if they are isomorphic
     * example: egg -> add. letters can be replaced to get the second string
     */
    static bool isIsomorphic(string s, string t) {
        map<char, char> dictionary;
        vector<char> added;
        // loop through every char, if not in dictionary add to dictionary, while adding if val already exists return false
        for (size_t i{0}; i < s.length(); i++) {
            if (dictionary.find(s[i]) == dictionary.end()) {
                if (count(added.begin(), added.end(), t[i])) {  // count requires <algorithm> to be included
                    return false;
                }
                dictionary[s[i]] = t[i];
                added.push_back(t[i]);
            } else {
                if (dictionary[s[i]] != t[i]) {
                    return false;
                }
            }
        }
        return true;
    }

    /**
     * 206. Reverse Linked List
     * Given a linked list, returns the reversed linked list
     * I solved this recursively and iteratively
     */
    static ListNode *reverseList(ListNode *head) {
        /* Recursive
        if(head==NULL || head->next == NULL){
            return head;
        }
        ListNode* rest = reverseList(head->next);
        head->next->next = head;
        head->next = NULL;
        return rest;
        */

        ListNode *prevNode = nullptr;
        auto curNode = head;
        while (curNode) {
            auto nextNode = curNode->next;
            curNode->next = prevNode;
            prevNode = curNode;
            curNode = nextNode;
        }
        return prevNode;
    }

    /**
     * 235. Lowest Common Ancestor of a Binary Search Tree
     * Given a binary search tree, find the lowest common ancestor of two nodes
     */
    static TreeNode *lowestCommonAncestor(TreeNode *root, TreeNode *p, TreeNode *q) {
        if (root == NULL) return NULL;
        // if p and q are on opposing sides of the binary tree, lowest common ancestor has to be root
        // otherwise we can treat left or right node  as the root and call the function recursively to find lowest common ancestor
        if (p->val > root->val && q->val > root->val) {
            return lowestCommonAncestor(root->right, p, q);
        } else if (p->val < root->val && q->val < root->val) {
            return lowestCommonAncestor(root->left, p, q);
        } else {
            return root;
        }
    }

    /**
     * 278. First Bad Version
     * The function isBadVersion is provided, which returns if the version is
     * bad or not given the version in integer. This function finds the first
     * bad version, for example if the versions after V3 are bad, the function should
     * return 3.
     * The placeholder isBadVersion assumes first bad is always 5th version for simplicity
     */
    static int firstBadVersion(int n) {
        int st = 1, end = n;
        while (st <= end) {
            int mid = st + (end - st) / 2;
            if (isBadVersion(mid) == false) {
                st = mid + 1;
            } else
                end = mid - 1;
        }
        return st;
    }

    /**
     * 392. Is Subsequence
     * Given strings s and t, determine if s is a subsequence of t
     * relative order must be same. example: abc is a subsequence of ahbgdc
     */
    static bool isSubsequence(string s, string t) {
        int i{0};
        int j{0};

        // checks
        if (s.length() == 0) {
            return true;
        }
        if (t.length() == 0) {
            return false;
        }

        // main loop
        while (true) {
            if (s[i] == t[j]) {
                i++;
                j++;
            } else {
                j++;
            }
            if (j == t.length()) {
                if (i == s.length()) {
                    return true;
                } else {
                    return false;
                }
            }
        }
    }

    /**
     * 409. Longest Palindrome
     * Given a string s, which can consist of both upper and lower case characters, return longest possible palindrome
     * Letters are case sensitive.
     * Example: "abccccdd" can create the palindrome "dccaccd", so the output would be 7 (number of characters)
     */
    static int longestPalindrome(string s) {
        map<char, int> map;
        for (char x : s) {
            map[x]++;
        }
        int length = 0;
        int carry = 0;
        for (auto x : map) {  // take all even numbered characters, for any odd, carry 1, take rest of the characters (for 3, carry 1 take 2, for 1 carry 1 take none etc.)
            if (x.second % 2 == 1) {
                carry = 1;
                length += (x.second - 1);
            } else
                length += x.second;
        }
        return length + carry;
    }

    /**
     * 509. Fibonacci Number
     * Given integer n, return the nth value of the fibonacci sequence
     */
    static int fib(int n) {
        if (n == 0) {
            return 0;
        }
        if (n == 1) {
            return 1;
        }
        return fib(n - 1) + fib(n - 2);
    }

    /**
     * 589. N-ary Tree Preorder Traversal
     * Given the root node of an n-ary tree, return preorder traversal of nodes
     */
    static void solve(Node *root, vector<int> &ans) {
        if (root == NULL) return;
        ans.push_back(root->val);
        for (int i = 0; i < root->children.size(); i++) {
            solve(root->children[i], ans);
        }
    }
    static vector<int> preorder(Node *root) {
        vector<int> ans;
        solve(root, ans);
        return ans;
    }

    /**
     * 704. Binary Search
     * Given a vector of integers sorted in ascending order, returns the index of target
     * If target is not found returns -1
     */
    static int search(vector<int> &nums, int target) {
        int end = nums.size() - 1;
        int start = 0;
        while (start <= end) {
            int mid = start + ((end - start) / 2);
            if (nums[mid] == target) {
                return mid;
            } else if (nums[mid] > target) {
                end = mid - 1;
            } else {
                start = mid + 1;
            }
        }
        return -1;
    }

    /**
     * 724. Find Pivot Index
     * Accepts an integer vector as input returns the index where
     * the sum of elements on the right of the pivot is equal to
     * elements on the left of the pivot. If no such index exists, returns -1
     */
    static int pivotIndex(vector<int> &nums) {
        vector<int> leftSum;
        int sumL{0};
        int size = nums.size();

        // create a list that holds the running sum of all elements starting on left
        for (int i{0}; i < size; ++i) {
            sumL += nums[i];
            leftSum.push_back(sumL);
        }

        vector<int> rightSum;
        rightSum.push_back(sumL);

        // create a list that holds the running sum starting on right
        for (int i{0}; i < size; ++i) {
            sumL -= nums[i];
            rightSum.push_back(sumL);
        }

        // compare left sum with right sum, return index
        for (int i{0}; i < size; ++i) {
            if (leftSum[i] == rightSum[i]) {
                return i;
            }
        }
        return -1;
    }

    /**
     * 733. Flood Fill
     * Given an image represented as a m x n grid of vector<vector<int>> type,
     * provided a coordinate (sr,sc) and a color, perform flood fill so the seleted
     * coordinate and all coordinates 4-directionally connected recursively are painted to
     * the given color (int)
     */
    static vector<vector<int>> floodFill(vector<vector<int>> &image, int sr, int sc, int color) {
        int curColor = image[sr][sc];
        if (curColor == color) {
            return image;
        }

        image[sr][sc] = color;

        if (sr + 1 < image.size() && image[sr + 1][sc] == curColor) {
            floodFill(image, sr + 1, sc, color);
        }
        if (sr - 1 >= 0 && image[sr - 1][sc] == curColor) {
            floodFill(image, sr - 1, sc, color);
        }
        if (sc + 1 < image[0].size() && image[sr][sc + 1] == curColor) {
            floodFill(image, sr, sc + 1, color);
        }
        if (sc - 1 >= 0 && image[sr][sc - 1] == curColor) {
            floodFill(image, sr, sc - 1, color);
        }
        return image;
    }

    /**
     * 876. Middle of Linked List
     * Given head of singly linked list returns the middle Node
     */
    static ListNode *middleNode(ListNode *head) {
        ListNode *slow = head;
        ListNode *fast = head;
        while (fast != NULL && fast->next != NULL) {
            slow = slow->next;
            fast = fast->next->next;
        }
        return slow;
    }

    /**
     * 1480. Running Sum of 1d Array
     * Accepts an integer vector as input, calculates the running sum
     * for each element and returns it as an integer vector
     */
    static vector<int> runningSum(vector<int> &nums) {
        vector<int> result;
        int sum = 0;
        int vectorSize = nums.size();

        // keep the running sum, add to list
        for (int i = 0; i < vectorSize; ++i) {
            result.push_back(sum + nums[i]);
            sum += nums[i];
        }

        return result;
    }
};

int main() {
    // Test for 21
    /*
    ListNode listElement = ListNode(5);
    ListNode list1 = ListNode(1, &listElement);  // [1, 5]
    ListNode list2 = ListNode(3);                // [3]
    ListNode merge = *Solution::mergeTwoLists(&list1, &list2);
    while (merge.val) {
        cout << merge.val << ", ";
        merge = *merge.next;
    }
    */
    /*********************************************************/

    // Test for 70
    /*
    cout << Solution::climbStairs(5);
    */
    /*********************************************************/

    // Test for 98
    /*
    TreeNode gl = TreeNode(3);
    TreeNode gr = TreeNode(6);
    TreeNode cl = TreeNode(1);
    TreeNode cr = TreeNode(4, &gl, &gr);
    TreeNode root = TreeNode(5, &cl, &cr);
    // input tree:
    //     5
    //  1     4
    //      3   6

    cout << Solution::isValidBST(&root); // expected 0
    */
    /*********************************************************/

    // Test for 102
    /*
    TreeNode gl = TreeNode(15);
    TreeNode gr = TreeNode(7);
    TreeNode cl = TreeNode(9);
    TreeNode cr = TreeNode(20, &gl, &gr);
    TreeNode root = TreeNode(3, &cl, &cr);
    vector<vector<int>> levelOrderVector = Solution::levelOrder(&root);
    // input tree:
    //      3
    //   9     20
    //       15   7

    cout << "[";
    for (auto v : levelOrderVector) {
        cout << "[";
        for (int i : v) {
            cout << i << " ,";
        }
        cout << "]";
    }
    cout << "]" << endl;
    */
    /*********************************************************/

    // Test for 121
    /*
    vector<int> prices {7, 1, 5, 3, 6, 4};
    cout << Solution::maxProfit(prices);
    */
    /*********************************************************/

    // Test for 142
    /*
    ListNode n5 = ListNode(5);
    ListNode n4 = ListNode(4, &n5);
    ListNode n3 = ListNode(3, &n4);
    ListNode n2 = ListNode(2, &n3);
    ListNode n1 = ListNode(1, &n2);  // [1,2,3,4,5] expected middle 3
    n5.next = &n2;                   // after 5th node, the list loops back to 2nd node

    ListNode m = *Solution::detectCycle(&n1);
    cout << m.val;
    */
    /*********************************************************/

    // Test for 200
    /*
    vector<vector<char>> grid = {{'1', '1', '0', '0', '0'}, {'1', '1', '0', '0', '0'}, {'0', '0', '1', '0', '0'}, {'0', '0', '0', '1', '1'}};
    cout << Solution::numIslands(grid);
    */
    /*********************************************************/

    // Test for 205
    /*
    string s = "paper";
    string t = "title";
    cout << Solution::isIsomorphic(s, t);
    */
    /*********************************************************/

    // Test for 206
    /*
    ListNode last = ListNode(5);
    ListNode middle = ListNode(3, &last);
    ListNode first = ListNode(1, &middle);  // [1, 3, 5]
    ListNode reversed = *Solution::reverseList(&first);
    while (reversed.val) {
        cout << reversed.val << " ,";
        reversed = *reversed.next;
    }
    */
    /*********************************************************/

    // Test for 235
    /*
    TreeNode cl = TreeNode(2);
    TreeNode cr = TreeNode(8);
    TreeNode root = TreeNode(6, &cl, &cr);
    // input tree:
    //      6
    //    2   8

    TreeNode lowestCommon = *Solution::lowestCommonAncestor(&root, &cl, &cr);
    cout << lowestCommon.val;
    */
    /*********************************************************/

    // Test for 278
    /*
    cout << Solution::firstBadVersion(10);
    */
    /*********************************************************/

    // Test for 392
    /*
    string s = "abc";
    string t = "ahbgdc";
    cout << Solution::isSubsequence(s, t);
    */
    /*********************************************************/

    // Test for 409
    /*
    string s = "abccccdd";
    cout << Solution::longestPalindrome(s);
    */
    /*********************************************************/

    // Test for 509
    /*
    cout << Solution::fib(8);
    */
    /*********************************************************/

    // Test for 589
    /*
    Node g1 = Node(5);
    Node g2 = Node(6);
    vector<Node *> grandchildren = {&g1, &g2};
    Node c1 = Node(3, grandchildren);
    Node c2 = Node(2);
    Node c3 = Node(4);
    vector<Node *> children = {&c1, &c2, &c3};
    Node root = Node(1, children);
    // input tree:
    //      1
    //  3   2   4
    // 5 6

    vector<int> preorderVector = Solution::preorder(&root);
    for (int i : preorderVector) {
        cout << i << ", ";
    }
    cout << endl;
    */
    /*********************************************************/

    // Test for 704
    /*
    vector<int> v{-1, 0, 3, 5, 9, 12};
    cout << Solution::search(v, 9);
    */
    /*********************************************************/

    // Test for 724
    /*
    vector<int> v{1, 7, 3, 6, 5, 6};
    int pivot = Solution::pivotIndex(v);
    cout << pivot << endl;
    */
    /*********************************************************/

    // Test for 733
    /*
    vector<vector<int>> image = {{1, 1, 1}, {1, 1, 0}, {1, 0, 1}};
    for (auto v : image) {
        for (auto i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
    cout << endl;
    image = Solution::floodFill(image, 1, 1, 2);
    for (auto v : image) {
        for (auto i : v) {
            cout << i << " ";
        }
        cout << endl;
    }
    */
    /*********************************************************/

    // Test for 876
    /*
    ListNode n5 = ListNode(5);
    ListNode n4 = ListNode(4, &n5);
    ListNode n3 = ListNode(3, &n4);
    ListNode n2 = ListNode(2, &n3);
    ListNode n1 = ListNode(1, &n2);  // [1,2,3,4,5] expected middle 3

    ListNode m = *Solution::middleNode(&n1);
    cout << m.val;
    */
    /*********************************************************/

    // Test for 1480
    /*
    vector<int> v = {1, 2, 3, 4, 5};
    vector<int> rs = Solution::runningSum(v); // expected {1, 3, 6, 10, 15}
    for (int i : rs)
    {
        cout << i << " ";
    }
    cout << endl;
    */
    /*********************************************************/

    return 0;
}