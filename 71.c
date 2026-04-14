#include <stdio.h>

// Function to find the first repeated character
char findFirstRepeated(const char* s) {
    // Array to keep track of seen characters (size 256 for all ASCII characters)
    int seen[256] = {0}; 

    for (int i = 0; s[i] != '\0'; i++) {
        // If the character is already marked as seen, it's our answer
        if (seen[(unsigned char)s[i]]) {
            return s[i];
        }
        // Otherwise, mark the current character as seen
        seen[(unsigned char)s[i]] = 1;
    }

    // Return null character if no repetitions are found
    return '\0'; 
}

int main() {
    // Assuming a reasonably large maximum string length
    char s[100005];

    // Read the string from standard input
    if (scanf("%100004s", s) == 1) {
        char result = findFirstRepeated(s);

        if (result != '\0') {
            printf("%c\n", result);
        } else {
            printf("-1\n");
        }
    }

    return 0;
}