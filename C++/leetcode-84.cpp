//
// Created by 邓岩 on 2019/5/24.
//

# include <iostream>

// 柱面图中的最大矩形面积

int largestRectangleArea(vector<int>& heights) {
    heights.push_back(0);
    stack<int> stk;
    int maxArea = 0;
    for(int i = 0;i<heights.size();i++)
    {
        while(!stk.empty() && heights[i]<heights[stk.top()])
        {
            /*
             * 栈中的元素大小由栈底向栈顶递增，那么也就是说栈中每一个元素的前一个元素就是它的左边界
             * 当新读入一个元素小于栈顶时，那么这个新元素就是栈顶元素的右边界
             * 每次出栈元素就等于计算以这个栈顶元素为高的最大面积
             */
            int top= stk.top();
            stk.pop();
            maxArea = max(maxArea,heights[top]*(stk.empty()? i:(i - stk.top() -1)));
        }
        stk.push(i);
    }
    return maxArea;
}

int main(void) {

}