int threeSumClosest(int* nums, int numsSize, int target)
{
    int closest = nums[0] + nums[1] + nums[2];

    // Sort the array
    for (int i = 0; i < numsSize - 1; i++)
    {
        for (int j = i + 1; j < numsSize; j++)
        {
            if (nums[i] > nums[j])
            {
                int temp = nums[i];
                nums[i] = nums[j];
                nums[j] = temp;
            }
        }
    }

    for (int i = 0; i < numsSize - 2; i++)
    {
        int left = i + 1;
        int right = numsSize - 1;

        while (left < right)
        {
            int sum = nums[i] + nums[left] + nums[right];

            if (sum == target)
                return sum;

            if (abs(sum - target) < abs(closest - target))
                closest = sum;

            if (sum < target)
                left++;
            else
                right--;
        }
    }

    return closest;
}
//krish