#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct item{
    char pizzaName[50];
    int price;
    struct item *next;
};

// Structure to represent a customer
struct customer {
    char name[50];
    char gender[10];
    int age;
    long int orderId; // Assuming orderId is of type long
};

// Structure to represent an Order
struct order {
    long int orderId;
    char allItems[1000];
    int totalCost;
};

struct item *head = NULL; // store address of first node
struct item *temp = NULL; // traverse the items in cart
struct item *newnode = NULL; // create new items
struct item *removeNode = NULL; // remove nodes
struct item *tail = NULL; // stores address of last node

void makeOrder();
void removeItems();
void viewCart();
void addItemsToCart(char pizzaName[], int price);
void mainMenu();
void vegMenu();
void nonVegMenu();
long int generateOrderId();

int main(){
    int keepGoing = 1, choice;
    do{
        mainMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                vegMenu();
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch(choice){
                    case 1:
                        printf("Adding Cheese Pizza to your cart.\n");
                        addItemsToCart("Cheese Pizza", 50);
                        break;
                    case 2:
                        printf("Adding Veggie Pizza to your cart.\n");
                        addItemsToCart("Veggie Pizza", 50);
                        break;
                    case 3:
                        printf("Adding Pepperoni Pizza to your cart.\n");
                        addItemsToCart("Pepperoni Pizza", 50);
                        break;
                    case 4:
                        printf("Returning to Main Menu.\n");
                        break;
                    default: 
                        printf("Invalid choice.\n");
                }
                break;
            case 2:
                nonVegMenu();
                printf("Enter your choice: ");
                scanf("%d", &choice);

                switch(choice){
                    case 1:
                        printf("Adding BBQ Chicken Pizza to your cart.\n");
                        addItemsToCart("BBQ Chicken Pizza", 60);
                        break;
                    case 2:
                        printf("Adding Meat Pizza to your cart.\n");
                        addItemsToCart("Meat Pizza", 60);
                        break;
                    case 3:
                        printf("Adding Gamberi Pizza to your cart.\n");
                        addItemsToCart("Gamberi Pizza", 60);
                        break;
                    case 4:
                        printf("Returning to Main Menu.\n");
                        break;
                    default: 
                        printf("Invalid choice.\n");
                }
                break;
            case 3:
                viewCart();
                break;
            case 4:
                makeOrder();
                break;
            case 5:
                printf("Thank you for visiting!\n");
                exit(1);
            default: 
                printf("Invalid choice.\n");
                exit(0);
        }
        printf("Do you want to continue (0: No)? ");
        scanf("%d", &keepGoing);
    }while(keepGoing);
    
    removeItems();
    return 0;
}

// Function to make the order
void makeOrder() {
    // Display the current cart
    viewCart();

    // Prompt the user to confirm the order
    char choice;
    printf("Do you want to make this order? (Y/N): ");
    scanf(" %c", &choice);

    // If the user confirms, display a message and clear the cart
    if (choice == 'Y' || choice == 'y') {
        printf("Thank you for your order!\n");
        removeItems();
    } else {
        printf("Order canceled.\n");
    }
}

void removeItems(){
    temp = head;
    while(temp != NULL){
        removeNode = temp;
        temp = temp -> next;
        printf("Removing: %s\n", removeNode -> pizzaName);
        free(removeNode);
    }
    head = tail = NULL; // Reset head and tail pointers
}

void viewCart(){
    temp = head;
    int price = 0;
    printf("\n--------- Your Cart ---------\n");
    printf("Name\t\tPrice\n");
    printf("--------------------------------\n");
    while(temp != NULL){
        printf("%-20s %d\n", temp -> pizzaName, temp -> price);
        price += temp -> price;
        temp = temp -> next;
    }
    printf("--------------------------------\n");
    printf("Total Cost: %d\n\n", price);
}

void addItemsToCart(char pizzaName[], int price){
    newnode = (struct item*)malloc(sizeof(struct item));
    strcpy(newnode -> pizzaName, pizzaName);
    newnode -> price = price;
    newnode -> next = NULL;

    if(head == NULL){
        head = tail = newnode;
    }else{
        tail -> next = newnode;
        tail = newnode;
    }
}

void mainMenu(){
    printf("\n---------- Main Menu ----------\n");
    printf("1. Veg Pizza\n");
    printf("2. Non Veg Pizza\n");
    printf("3. View Cart\n");
    printf("4. Make Order\n");
    printf("5. Exit\n");
    printf("------------------------------\n");
}

void vegMenu(){
    printf("\n--------- Veg Pizza ---------\n");
    printf("1. Cheese Pizza\n");
    printf("2. Veggie Pizza\n");
    printf("3. Pepperoni Pizza\n");
    printf("4. Back to Main Menu\n");
    printf("-----------------------------\n");
}

void nonVegMenu(){
    printf("\n-------- Non Veg Pizza --------\n");
    printf("1. BBQ Chicken Pizza\n");
    printf("2. Meat Pizza\n");
    printf("3. Gamberi Pizza\n");
    printf("4. Back to Main Menu\n");
    printf("-------------------------------\n");
}

// Function to generate a 16-digit long orderId
long int generateOrderId() {
    long int orderId = 0;
    // Seed the random number generator
    srand(time(NULL));

    // Generate random digits for the orderId
    for (int i = 0; i < 16; i++) {
        orderId = orderId * 10 + rand() % 10;
    }

    return orderId;
}