int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;

    while (left < right) {
        int mid = left + (right - left) / 2;

        if (nums[mid] < nums[right]) {
            // Minimum is at mid or to the left
            right = mid;
        }
        else if (nums[mid] > nums[right]) {
            // Minimum is to the right of mid
            left = mid + 1;
        }
        else {
            /*
             * nums[mid] == nums[right]
             *
             * We cannot determine which side contains
             * the minimum, so safely discard right.
             */
            right--;
        }
    }

    return nums[left];
}
//krish