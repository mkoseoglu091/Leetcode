#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
   public:
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

    // Test for 392
    /*
    string s = "abc";
    string t = "ahbgdc";
    cout << Solution::isSubsequence(s, t);
    */
    /*********************************************************/

    // Test for 724
    /*
    vector<int> v{1, 7, 3, 6, 5, 6};
    int pivot = Solution::pivotIndex(v);
    cout << pivot << endl;
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