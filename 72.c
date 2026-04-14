#include <stdio.h>
#include <string.h>

// Function to find the first non-repeating character
char firstNonRepeatingChar(char* s) {
    int count[26] = {0}; // Array to store frequencies of 'a' to 'z'
    int i;

    // Step 1: Count the frequency of each character
    for (i = 0; s[i] != '\0'; i++) {
        count[s[i] - 'a']++;
    }

    // Step 2: Find the first character with a frequency of 1
    for (i = 0; s[i] != '\0'; i++) {
        if (count[s[i] - 'a'] == 1) {
            return s[i];
        }
    }

    // Step 3: If no non-repeating character is found
    return '$';
}

int main() {
    char s[10000]; // Buffer to hold the input string
    
    // Read the input string
    if (scanf("%s", s) == 1) {
        char result = firstNonRepeatingChar(s);
        printf("%c\n", result);
    }
    
    return 0;
}