#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    /**
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
    // Test for runningSum
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