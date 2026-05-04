#include <stdio.h>

int intSqrt(int x) {
    if (x == 0 || x == 1) return x;

    int low = 1, high = x, ans = 0;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if ((long long)mid * mid <= x) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ans;
}

int main() {
    int x = 17;
    printf("%d\n", intSqrt(x));
    return 0;
}