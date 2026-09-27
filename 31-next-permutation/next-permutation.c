void nextPermutation(int* nums, int numsSize)
{
    int i, j, temp;

    // Step 1: Find the first decreasing element
    i = numsSize - 2;

    while (i >= 0 && nums[i] >= nums[i + 1])
    {
        i--;
    }

    // Step 2: If such an element exists
    if (i >= 0)
    {
        // Find element just larger than nums[i]
        j = numsSize - 1;

        while (nums[j] <= nums[i])
        {
            j--;
        }

        // Swap
        temp = nums[i];
        nums[i] = nums[j];
        nums[j] = temp;
    }

    // Step 3: Reverse the remaining part
    int left = i + 1;
    int right = numsSize - 1;

    while (left < right)
    {
        temp = nums[left];
        nums[left] = nums[right];
        nums[right] = temp;

        left++;
        right--;
    }
}
//krish