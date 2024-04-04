//Stephen Omondi Charles
//SCT221-0277/2022
//RPN Calculator Assignment

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

void push(char c) {
    if (top == MAX_SIZE - 1) {
        printf("Stack Overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack Underflow\n");
        exit(1);
    }
    return stack[top--];
}

int precedence(char c) {
    if (c == '*' || c == '/' || c == '%') {
        return 2;
    } else if (c == '+' || c == '-') {
        return 1;
    } else {
        return 0;
    }
}

void infixToPostfix(char *infix, char *postfix) {
    int i, j = 0;
    for (i = 0; infix[i]; i++) {
        if (infix[i] >= 'a' && infix[i] <= 'z') {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(infix[i]);
        } else if (infix[i] == ')') {
            while (stack[top] != '(') {
                postfix[j++] = pop();
            }
            pop(); // Discard the opening parenthesis
        } else {
            while (top != -1 && precedence(stack[top]) >= precedence(infix[i])) {
                postfix[j++] = pop();
            }
            push(infix[i]);
        }
    }

    while (top != -1) {
        postfix[j++] = pop();
    }
    postfix[j] = '\0';
}

int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];
    
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    
    printf("Postfix expression: %s\n", postfix);
    
    return 0;
}
