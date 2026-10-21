
class Solution {
    public int minOperations(String s) {
        int n = s.length();

        // Step 1: Check if the string is already sorted
        boolean sorted = true;

        for (int i = 1; i < n; i++) {
            if (s.charAt(i) < s.charAt(i - 1)) {
                sorted = false;
                break;
            }
        }

        if (sorted) {
            return 0;
        }

        // Step 2: A reversed string of length 2 cannot be sorted
        if (n == 2) {
            return -1;
        }

        // Step 3: Find minimum and maximum characters
        char min = 'z';
        char max = 'a';

        for (int i = 0; i < n; i++) {
            char c = s.charAt(i);

            if (c < min) {
                min = c;
            }

            if (c > max) {
                max = c;
            }
        }

        // Step 4: Check if one operation is enough
        if (s.charAt(0) == min || s.charAt(n - 1) == max) {
            return 1;
        }

        // Step 5: Check the middle characters
        for (int i = 1; i < n - 1; i++) {
            if (s.charAt(i) == min || s.charAt(i) == max) {
                return 2;
            }
        }

        // Step 6: Otherwise, three operations are needed
        return 3;
    }
}
//kr