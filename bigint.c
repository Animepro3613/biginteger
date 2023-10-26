#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "bigint.h"
struct node {
    int data;
    struct node* next;
};

struct BigInteger {
    struct node* L;
    int length;
    int sign;
};

struct node* list(char str[]) {
    struct node* head = NULL, *itr = NULL;

    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] >= '0' && str[i] <= '9') {
            struct node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->data = str[i] - '0'; 
            newNode->next = NULL;

            if (head == NULL) {
                head = newNode;
                itr = head;
            } else {
                itr->next = newNode;
                itr = itr->next;
            }
        }
    }
    return head;
} 

struct node* reverse(struct node* head) {
    struct node* cur = head, *next, *prev = NULL;

    while (cur) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    return prev;
}


struct BigInteger reverseBigInteger(struct BigInteger num) {
    struct node* prev = NULL;
    struct node* current = num.L;
    struct node* next = NULL;

    while (current != NULL) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }

    struct BigInteger result;
    result.L = prev;
    result.length = num.length;
    result.sign = num.sign;

    return result;
}



int length(struct node* head) {
    int l = 0; 
    while (head) {
        ++l;
        head = head->next;
    }
    return l;
}

void display(struct node* head) {
    while (head) {
        printf("%d", head->data);
        head = head->next;
    }
}

struct node* newNode(int val) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->data = val;
    temp->next = NULL;
    return temp;
}

struct BigInteger createBigInteger(char str[], int sign) {
    struct BigInteger bigint;
    bigint.L = reverse(list(str)); // Reverse the list
    bigint.length = length(bigint.L);
    bigint.sign = sign;
    return bigint;
}

struct BigInteger add(struct BigInteger num1, struct BigInteger num2) {
    struct node* l1 = num1.L;
    struct node* l2 = num2.L;
    struct node* res = NULL;
    struct node* itr = NULL;
    int sum, carry = 0;

    while (l1 || l2) {
        int val1 = (l1) ? l1->data : 0;
        int val2 = (l2) ? l2->data : 0;

        sum = val1 + val2 + carry;
        carry = sum / 10;

        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = sum % 10;
        newNode->next = NULL;

        if (res == NULL) {
            res = newNode;
            itr = res;
        } else {
            itr->next = newNode;
            itr = itr->next;
        }

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    if (carry) {
        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = carry;
        newNode->next = NULL;

        itr->next = newNode;
    }

    struct BigInteger result;
    result.L = reverse(res); // Reverse the result back to correct order
    result.length = length(result.L);
    result.sign = num1.sign; // Assuming both numbers have the same sign

    return result;
}

struct BigInteger initialize(char *s) {
    int sign = 1; // Assume positive initially

    if (*s == '-') {
        sign = -1; // Change sign to negative
        s++; // Move pointer past '-'
    }

    return createBigInteger(s, sign);
}
int compare(struct BigInteger num1, struct BigInteger num2) {
    // Compare lengths first
    if (num1.length > num2.length) {
        return 1;
    } else if (num1.length < num2.length) {
        return -1;
    }

    // If lengths are equal, compare each digit from left to right
    struct node* l1 = num1.L;
    struct node* l2 = num2.L;

    while (l1 && l2) {
        if (l1->data > l2->data) {
            return 1;
        } else if (l1->data < l2->data) {
            return -1;
        }
        l1 = l1->next;
        l2 = l2->next;
    }

    // If all digits are equal, the numbers are equal
    return 0;
}

struct BigInteger sub(struct BigInteger num1, struct BigInteger num2) {
    
    if(num1.length>=2||num2.length>=2)
    {
    if (compare(num1, num2) < 0) {
        // Swap num1 and num2 if num2 is greater
        struct BigInteger temp = num1;
        num1 = num2;
        num2 = temp;
    }

    struct node* l1 = num1.L;
    struct node* l2 = num2.L;
    struct node* res = NULL;
    struct node* itr = NULL;
    int diff, borrow = 0;

    while (l1 || l2) {
        int val1 = (l1) ? l1->data : 0;
        int val2 = (l2) ? l2->data : 0;

        // Adjust the difference calculation
        diff = val1 - val2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        struct node* newNode = (struct node*)malloc(sizeof(struct node));
        newNode->data = diff;
        newNode->next = NULL;

        if (res == NULL) {
            res = newNode;
            itr = res;
        } else {
            itr->next = newNode;
            itr = itr->next;
        }

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    struct BigInteger result;
    result.L = reverse(res);
    result.length = length(result.L);
    result.sign = num1.sign;

    // Special case: both numbers are zero
    if (result.length == 1 && result.L->data == 0) {
        result.sign = '+';
    }

    return result;
    }
    else 
    {
        struct BigInteger sub(struct BigInteger num1, struct BigInteger num2) {
    if (compare(num1, num2) < 0) {
        // Swap num1 and num2 if num2 is greater
        struct BigInteger temp = num1;
        num1 = num2;
        num2 = temp;
    }

    struct node* l1 = num1.L;
    struct node* l2 = num2.L;
    struct node* res = NULL;
    struct node* itr = NULL;
    int diff, borrow = 0;

    while (l1 || l2) {
        int val1 = (l1) ? l1->data : 0;
        int val2 = (l2) ? l2->data : 0;

        // Adjust the difference calculation
        diff = val1 - val2 - borrow;

        if (diff < 0) {
            diff += 10;
            borrow = 1;
        } else {
            borrow = 0;
        }

        if (diff != 0 || res != NULL) { // Skip leading zeroes
            struct node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->data = diff;
            newNode->next = NULL;

            if (res == NULL) {
                res = newNode;
                itr = res;
            } else {
                itr->next = newNode;
                itr = itr->next;
            }
        }

        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
    }

    struct BigInteger result;
    result.L = reverse(res);
    result.length = length(result.L);
    result.sign = num1.sign;

    return result;
}

    }
}

struct BigInteger div1(struct BigInteger num1, struct BigInteger num2) {
    // Add your code for division here
    // ...
}

void inst(struct BigInteger* headRef, int data) {
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    if (newNode == NULL) {
        printf("Memory allocation failed\n");
        return;
    }
    newNode->data = data;
    newNode->next=NULL;
    headRef->length+=1;

    if (headRef->L == NULL) {
        headRef->L = newNode;
        return;
    }

    struct node* current = headRef->L;
    while (current->next != NULL) {
        current = current->next;
    }

    current->next = newNode;
}

struct BigInteger mul(struct BigInteger num1, struct BigInteger num2) {
    struct node* n1 = num1.L;
    struct node* n2 = num2.L;
    if (n1 == NULL || n2 == NULL) {
        struct BigInteger result;
        result.L = NULL;
        result.length = 0;
        return result;
    }

    struct BigInteger result;
    result.L = NULL;
    result.length = 0;

    int i = 0;
    while (n2 != NULL) {
        struct node* current_n1 = num1.L;
        int carry = 0;

        // Initialize a temporary result for this iteration
        struct node* tempResult = NULL;
        struct node* tempItr = NULL;

        for (int j = 0; j < i; j++) {
            struct node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->data = 0;
            newNode->next = NULL;
            if (tempResult == NULL) {
                tempResult = newNode;
                tempItr = tempResult;
            } else {
                tempItr->next = newNode;
                tempItr = tempItr->next;
            }
        }

        while (current_n1 != NULL) {
            int product = (current_n1->data) * (n2->data) + carry;
            struct node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->data = product % 10;
            newNode->next = NULL;
            if (tempResult == NULL) {
                tempResult = newNode;
                tempItr = tempResult;
            } else {
                tempItr->next = newNode;
                tempItr = tempItr->next;
            }
            carry = product / 10;
            current_n1 = current_n1->next;
        }
        if (carry > 0) {
            struct node* newNode = (struct node*)malloc(sizeof(struct node));
            newNode->data = carry;
            newNode->next = NULL;
            tempItr->next = newNode;
        }

        // Add tempResult to result manually
        struct node* r = result.L;
        struct node* t = tempResult;
        carry = 0;

        while (t != NULL) {
            int sum = (r ? r->data : 0) + t->data + carry;
            carry = sum / 10;
            if (r) {
                r->data = sum % 10;
                r = r->next;
            } else {
                inst(&result, sum % 10);
            }
            t = t->next;
        }

        while (carry > 0) {
            if (r) {
                int sum = r->data + carry;
                r->data = sum % 10;
                carry = sum / 10;
                r = r->next;
            } else {
                inst(&result, carry);
                carry = 0;
            }
        }

        // Free the memory used by tempResult
        while (tempResult != NULL) {
            struct node* temp = tempResult;
            tempResult = tempResult->next;
            free(temp);
        }

        n2 = n2->next;
        i++;
    }
    result=reverseBigInteger(result);
    return result;
}

struct BigInteger mod(struct BigInteger num1, struct BigInteger num2) {
    // Add your code for modulus here
    // ...
}


int main() {
    char s1[100], s2[100];
    printf("Enter first number: ");
    fgets(s1, 100, stdin);
    printf("Enter second number: ");
    fgets(s2, 100, stdin);

    struct BigInteger num1 = initialize(s1);
    struct BigInteger num2 = initialize(s2);

    struct BigInteger sum = add(num1, num2);
    struct BigInteger division = div1(num1, num2);
    struct BigInteger product = mul(num1, num2);
    struct BigInteger modulus = mod(num1, num2);
    struct BigInteger difference = sub(num1, num2);

    printf("Sum: ");
    display(sum.L);
    printf("\n");

printf("Difference: ");
    display(difference.L);
    printf("\n");

    printf("Product: ");
    display(product.L);
    printf("\n");

printf("Division: ");
    display(division.L);
    printf("\n");
    
    printf("Modulus: ");
    display(modulus.L);
    printf("\n");

    

    return 0;
}