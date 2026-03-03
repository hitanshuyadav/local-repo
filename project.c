 #include<stdio.h>
#include<stdlib.h>

typedef struct node{
    int coeff;
    int exp;
    struct node *next;
}node;

// Insert term in sorted order (descending exponent)
void insert(node **head, int c, int e){
    node *newnode, *ptr, *prev=NULL;
    newnode = (node*)malloc(sizeof(node));
    newnode->coeff = c;
    newnode->exp = e;
    newnode->next = NULL;

    if(*head == NULL || (*head)->exp < e){
        newnode->next = *head;
        *head = newnode;
    }
    else{
        ptr = *head;
        while(ptr != NULL && ptr->exp >= e){
            prev = ptr;
            ptr = ptr->next;
        }
        prev->next = newnode;
        newnode->next = ptr;
    }
}

// Add two polynomials
node* addPolynomial(node *p1, node *p2){
   node *result = NULL;

    while(p1 != NULL && p2 != NULL){
        if(p1->exp == p2->exp){
            insert(&result, p1->coeff + p2->coeff, p1->exp);
            p1 = p1->next;
            p2 = p2->next;
        }
        else if(p1->exp > p2->exp){
            insert(&result, p1->coeff, p1->exp);
            p1 = p1->next;
        }
        else{
            insert(&result, p2->coeff, p2->exp);
            p2 = p2->next;
        }
    }

    while(p1 != NULL){
        insert(&result, p1->coeff, p1->exp);
        p1 = p1->next;
    }

    while(p2 != NULL){
        insert(&result, p2->coeff, p2->exp);
        p2 = p2->next;
    }

    return result;
}

// Display polynomial
void display(node *head){
    while(head != NULL){
        printf("%dx^%d", head->coeff, head->exp);
        if(head->next != NULL)
            printf(" + ");
        head = head->next;
    }
    printf("\n");
}

int main(){
    node *poly1 = NULL;
    node *poly2 = NULL;
    node *result = NULL;
    int n, c, e;

    printf("Enter number of terms in Polynomial 1: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &c, &e);
        insert(&poly1, c, e);
    }

    printf("Enter number of terms in Polynomial 2: ");
    scanf("%d", &n);
    for(int i=0; i<n; i++){
        printf("Enter coefficient and exponent: ");
        scanf("%d %d", &c, &e);
        insert(&poly2, c, e);
    }

    printf("\nPolynomial 1: ");
    display(poly1);

    printf("Polynomial 2: ");
    display(poly2);

   result= addPolynomial(poly1, poly2);

    printf("Resultant Polynomial: ");
    display(result);

    return 0;
}