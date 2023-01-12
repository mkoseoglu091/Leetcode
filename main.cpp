#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    /**
     * 724. Find Pivot Index
     * Accepts an integer vector as input returns the index where
     * the sum of elements on the right of the pivot is equal to
     * elements on the left of the pivot. If no such index exists, returns -1
     */
    static int pivotIndex(vector<int> &nums)
    {
        vector<int> leftSum;
        int sumL{0};
        int size = nums.size();

        // create a list that holds the running sum of all elements starting on left
        for (int i{0}; i < size; ++i)
        {
            sumL += nums[i];
            leftSum.push_back(sumL);
        }

        vector<int> rightSum;
        rightSum.push_back(sumL);

        // create a list that holds the running sum starting on right
        for (int i{0}; i < size; ++i)
        {
            sumL -= nums[i];
            rightSum.push_back(sumL);
        }

        // compare left sum with right sum, return index
        for (int i{0}; i < size; ++i)
        {
            if (leftSum[i] == rightSum[i])
            {
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
    static vector<int> runningSum(vector<int> &nums)
    {
        vector<int> result;
        int sum = 0;
        int vectorSize = nums.size();

        // keep the running sum, add to list
        for (int i = 0; i < vectorSize; ++i)
        {
            result.push_back(sum + nums[i]);
            sum += nums[i];
        }

        return result;
    }
};

int main()
{
    // Test for 724
    /*
    vector<int> v{1, 7, 3, 6, 5, 6};
    int pivot = Solution::pivotIndex(v);
    cout << pivot << endl;
    */

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

    return 0;
}