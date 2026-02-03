//{Problem: Implement linear search to find key k in an array. Count and display the number of comparisons performed.

//Input:
//- First line: integer n (array size)
//- Second line: n space-separated integers
//- Third line: integer k (key to search)

//Output:
//- Line 1: "Found at index i" OR "Not Found"
//Line 2: "Comparisons = c"

//Example:
//Input:
//5
//10 20 30 40 50
//30

//Output:
//Found at index 2
//Comparisons = 3

//Explanation: Compared with 10, 20, 30 (found at index 2 with 3 comparisons)



//solution




#include <stdio.h>
int main() {
    int n, k, i;
    
  
        scanf("%d", &n);   // Read array size
    
    int arr[n];
    for (i = 0; i < n; i++) {
        scanf("%d", &arr[i]);    // Read array elements
    }
    
    scanf("%d", &k); //find number
    
   
    int comparisons = 0;  //Search
    int found_index = -1; //not found 
    
    for (i = 0; i < n; i++) {
        comparisons++;       // Count comparison
        if (arr[i] == k) {
            found_index = i; // We found the number! Save the index.
            break;           // Stop searching.
        }
    }
    
    
    if (found_index == -1) {
        printf("Not Found\n");
    } else {
        printf("Found at index %d\n", found_index); //Print the results
    }
    printf("Comparisons = %d\n", comparisons);
    
    return 0;
}