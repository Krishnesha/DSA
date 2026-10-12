
import java.util.*;

class Solution {
    public int maxSum(List<Integer> nums, int k) {
        long MOD = 1_000_000_007L;
        int n = nums.size();
        long[] bits = new long[32];

        // Count how many numbers contain each bit
        for (int num : nums) {
            for (int b = 0; b < 32; b++) {
                if ((num & (1 << b)) != 0) {
                    bits[b]++;
                }
            }
        }

        long ans = 0;

        // Construct the largest k numbers
        for (int i = 0; i < k; i++) {
            long x = 0;

            for (int b = 31; b >= 0; b--) {
                if (bits[b] > 0) {
                    x |= (1L << b);
                    bits[b]--;
                }
            }

            ans = (ans + x * x) % MOD;
        }

        return (int) ans;
    }
}
//kri