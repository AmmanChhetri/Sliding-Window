// Leetcode - 239



// Approach 1 - BruteForce 

// Time Complexity is O(n*k)....
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        vector<int> ans;

        for(int i = 0;i<=nums.size()-k;i++) {
            int maxi = INT_MIN;
            for(int j = 0;j<k;j++) {
                maxi = max(maxi,nums[i+j]);
            }

            ans.push_back(maxi);

        }



        return ans;
        
    }
};









// Approach 2 - Using monotonic Decreasing Deque....

// Time Complexity is O(n)...as every element is added and popped only once...


// Refer - https://www.youtube.com/watch?v=CZQGRp93K4k 

// Refer - https://www.youtube.com/watch?v=29OnjVQ-fk4



// !! Important !! - Dry Run this logic and you will understand much better... 

// What intuition i got from here is....
// first of all we need to observe that we are forming a monotonic decreasing deque....(which means values of the deque will monotonically  decrease)...but here we will be storing index...which will be in increasing fashion...so index is increasing but the value at indexes are decreasing....this is a very important observation....

// suppose the example.... nums = {1,3,-1,-3,5,3,6,7}..... and lets say k = 3...

// when we start traversing ...we are at index 0....as of now the deque is empty so we just insert this nums[0] to deque....now...when we are at index 1...now the first thing we need to do is...we need to remove all the elements that are not going to be in this window...as k = 3...so for this index we dont have any elements to remove...but if we see nums[1] = 3...which is higher than the last value of deque(ie. 1)...so we remove 1 and add 3....now why we are doing this is very important to understand?...

// first of all see if we dont remove the 1...our array wont be in decreasing order...also what i understood is ...we know we have a higher number for the same window...like in the window we have 1 and in the same window we have 3...so we wont store 1 in our deuque....also as 3 is occuring after 1...so 3 has higher probability to stay as highest....

// now when we are at index 1...value is -1...now our deque has 3...now this -1 < 3...so we wont remove anything and add -1 in our deque after 3...by doing this our decreasing pattern is maintained...also see -1 is the next larger number after 3 in the window...so if by chance 3 is deleted...then -1 can become the maximum of next window(remember we are moving forward(which means it has some probability))...so in this way we are goinf to solve this problem...this understanding is very important....



// we do the step 2 from the below steps...because...see whenever we get a new element..and if its the largest among all the elements that are stored in the deque...then we remove all the elements of tehe deque and add this current element...because this element will be also in other windows...as we are moving forward...
// and this element will have higher probability of being maximum in the next window as well compared to values that are lesser than this number(numbers we are deleting)...so that's why we wont keep the lesser values....

/*
We will solve the problem using these 4 points...in the order... :-

    1. Whenever a new element(nums[i]) comes...makes space for it...by removing the elemetns that wont be in the window anymore....

    2. Now when nums[i] comes...there is no need to store the elements lesser than nums[i]...so pop them...

    3. now pushing i to deque for nums[i]..

    4. if(i >= k-1)...then dq.front() is our answer for that window...this check basically finds the index from which the windows will start forming(this i represents the end of each window)....


*/


// This problem uses monotonic increasing deque...similary we can have monotonic increasing/decreasing queue or stack or deque....

class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {

        int n = nums.size();

        deque<int> dq;

        vector<int> result;

        for(int i = 0;i<n;i++) {

            // step 1 - making space for nums[i]...or simply removing elements that should not be in this window...
            while(!dq.empty() && dq.front() <= i-k) {
                dq.pop_front();
            }

            // step 2 - remvoing elements that are lesser then this nums[i]...
            while(!dq.empty() && nums[dq.back()] < nums[i] ) {
                dq.pop_back();
            }
            
            // step 3 - Adding element to dq....(adding index)
            dq.push_back(i);


            // step 4 - when i >= k-1....the window is started to form (with this index 'i' as the ending of one window...)
            if(i >= k-1) {
                result.push_back(nums[dq.front()]);
            }
        }



        return result;
        
    }
};



// if we wnat to create a monotonic increasing deque...then just change the sign from step 2 as following-

        // while(!dq.empty() && nums[dq.back()] < nums[i] ) {
        //     dq.pop_back();
        // }









// Approach 3 - Using priority Queue (max Heap implementation)...

// Time Complexity is O(n*log(n))..



// The concept is same as previous...here in the priority queue we are storing both value and index....
//now whenver we encounter a element we dont need to delete the elements from priority queue...because as priority queue(maxheap) always store elements in descending order...we just have to make sure that the top element is not out of window....


// dry run this code....with this example you will understand it completely...
//  nums = [1,3,-1,-3,5,3,6,7], k = 3

// lets say i = 4...now for k = 3...the window will be of index 2,3,4....the index < 2..will be out of window...
class Solution {
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {


        int n = nums.size();

        priority_queue< pair<int,int> > pq;


        vector<int> result;

        for(int i = 0;i<n;i++) {

            // removing out of window elements
            while(!pq.empty() && pq.top().second <= i-k) {
                pq.pop();
            }


            pq.push({nums[i],i});


            if(i >= k-1) {
                result.push_back(pq.top().first);
            }
        }



        return result;
        
    }
};