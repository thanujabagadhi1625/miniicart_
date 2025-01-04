#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 50
#define MAX_NAME_LENGTH 50

// Structure to represent an item in the cart
typedef struct {
    char name[MAX_NAME_LENGTH];
    float price;
    int quantity;
} Item;

// Function prototypes
void displayMenu();
void addItem(Item cart[], int *itemCount);
void viewCart(Item cart[], int itemCount);
void removeItem(Item cart[], int *itemCount);
void clearCart(int *itemCount);
void saveCart(Item cart[], int itemCount);
void loadCart(Item cart[], int *itemCount);
float calculateTotal(Item cart[], int itemCount);

int main() {
    Item cart[MAX_ITEMS];
    int itemCount = 0;
    char choice;

    loadCart(cart, &itemCount);

    do {
        displayMenu();
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        switch(choice) {
            case '1':
                addItem(cart, &itemCount);
                break;
            case '2':
                viewCart(cart, itemCount);
                break;
            case '3':
                removeItem(cart, &itemCount);
                break;
            case '4':
                clearCart(&itemCount);
                break;
            case '5':
                saveCart(cart, itemCount);
                printf("Cart saved successfully.\n");
                break;
            case '6':
                printf("Total cost: $%.2f\n", calculateTotal(cart, itemCount));
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while(choice != '6');

    return 0;
}

void displayMenu() {
    printf("\nShopping Cart Menu\n");
    printf("1. Add item to cart\n");
    printf("2. View cart\n");
    printf("3. Remove item from cart\n");
    printf("4. Clear cart\n");
    printf("5. Save cart\n");
    printf("6. Calculate total\n");
    printf("7. Exit\n");
}

void addItem(Item cart[], int *itemCount) {
    if (*itemCount == MAX_ITEMS) {
        printf("Cart is full. Cannot add more items.\n");
        return;
    }

    printf("Enter item name: ");
    scanf("%s", cart[*itemCount].name);
    printf("Enter item price: ");
    scanf("%f", &cart[*itemCount].price);
    printf("Enter item quantity: ");
    scanf("%d", &cart[*itemCount].quantity);

    (*itemCount)++;
}

void viewCart(Item cart[], int itemCount) {
    if (itemCount == 0) {
        printf("Cart is empty.\n");
        return;
    }

    printf("Cart Items:\n");
    int i;
    for (i= 0; i < itemCount; i++) {
        printf("%d. %s - $%.2f - Quantity: %d\n", i + 1, cart[i].name, cart[i].price, cart[i].quantity);
    }
}

void removeItem(Item cart[], int *itemCount) {
    int index;
    viewCart(cart, *itemCount);

    if (*itemCount == 0) {
        printf("Cart is empty. Nothing to remove.\n");
        return;
    }

    printf("Enter item index to remove: ");
    scanf("%d", &index);

    if (index < 1 || index > *itemCount) {
        printf("Invalid index.\n");
        return;
    }
	int i;
    for (i= index - 1; i < *itemCount - 1; i++) {
        cart[i] = cart[i + 1];
    }

    (*itemCount)--;
    printf("Item removed from cart.\n");
}

void clearCart(int *itemCount) {
    *itemCount = 0;
    printf("Cart cleared.\n");
}

void saveCart(Item cart[], int itemCount) {
    FILE *fp = fopen("cart.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return;
    }
	int i;
    for (i= 0; i < itemCount; i++) {
        fprintf(fp, "%s %.2f %d\n", cart[i].name, cart[i].price, cart[i].quantity);
    }

    fclose(fp);
}

void loadCart(Item cart[], int *itemCount) {
    FILE *fp = fopen("cart.txt", "r");
    if (fp == NULL) {
        printf("Cart file not found. Starting with an empty cart.\n");
        return;
    }

    while (fscanf(fp, "%s %f %d", cart[*itemCount].name, &cart[*itemCount].price, &cart[*itemCount].quantity) == 3) {
        (*itemCount)++;
        if (*itemCount >= MAX_ITEMS) {
            break;
        }
    }

    fclose(fp);
}

float calculateTotal(Item cart[], int itemCount) {
    float total = 0;
    int i;
    for (i = 0; i < itemCount; i++) {
        total += cart[i].price * cart[i].quantity;
    }
    return total;
}
