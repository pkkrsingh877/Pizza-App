#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Structure to represent an item
struct item {
    char pizzaName[50];
    int price;
    struct item *next;
};

// Structure to represent a customer
struct customer {
    char name[50];
    char gender[10];
    int age;
    unsigned long long int orderId; // Assuming orderId is of type long long
};

// Structure to represent an Order
struct order {
    unsigned long long int orderId;
    char allItems[1000];
    int totalCost;
};

// Global variables
struct item *head = NULL; // Store address of first node
struct item *tail = NULL; // Store address of last node

// Function prototypes
void makeOrder(struct customer *cust, struct item *head);
void removeItems();
void viewCart();
void addItemsToCart(char pizzaName[], int price);
void mainMenu();
void vegMenu();
void nonVegMenu();
long int generateOrderId();
struct customer* addCustomer();
void writeCustomerToFile(struct customer *);
void writeOrderToFile(struct order *, struct customer *, struct item *);
void readAndPrintCustomers();
void readAndPrintOrders();

int main() {
    int choice, keepGoing = 1;
    do {
        printf("1. View Customer Data\n");
        printf("2. View Order Data\n");
        printf("3. Add Customer and Proceed\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                readAndPrintCustomers();
                break;
            case 2:
                readAndPrintOrders();
                break;
            case 3: {
                struct customer* cust = addCustomer();
                do {
                    mainMenu();
                    printf("Enter your choice: ");
                    scanf("%d", &choice);
                    switch (choice) {
                        case 1:
                            vegMenu();
                            printf("Enter your choice: ");
                            scanf("%d", &choice);
                            switch (choice) {
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
                            switch (choice) {
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
                            makeOrder(cust, head);
                            break;
                        default:
                            printf("Invalid Choice\n");
                            break;
                    }
                    printf("Do you want to continue (0: No)? ");
                    scanf("%d", &keepGoing);
                } while (keepGoing);
                removeItems();
            }
            break;
            case 4:
                printf("Thank you for visiting!\n");
                exit(1);
            default:
                printf("Invalid Choice\n");
                exit(0);
        }

        printf("Do you want to continue (0: No)? ");
        scanf("%d", &choice);
    } while (choice != 0);

    return 0;
}

// Function to make the order
void makeOrder(struct customer *cust, struct item *head) {
    // Display the current cart
    viewCart();

    // Prompt the user to confirm the order
    char choice;
    printf("Do you want to make this order? (Y/N): ");
    scanf(" %c", &choice);

    // If the user confirms, display a message and clear the cart
    if (choice == 'Y' || choice == 'y') {
        struct order ord;
        writeOrderToFile(&ord, cust, head);
        printf("Thank you for your order!\n");
        removeItems();
    } else {
        printf("Order canceled.\n");
    }
}

// Function to remove items from the cart
void removeItems() {
    struct item *temp = head;
    while (temp != NULL) {
        struct item *removeNode = temp;
        temp = temp->next;
        printf("Removing: %s\n", removeNode->pizzaName);
        free(removeNode);
    }
    head = tail = NULL; // Reset head and tail pointers
}

// Function to view items in the cart
void viewCart() {
    struct item *temp = head;
    int price = 0;
    printf("\n--------- Your Cart ---------\n");
    printf("Name\t\tPrice\n");
    printf("--------------------------------\n");
    while (temp != NULL) {
        printf("%-20s %d\n", temp->pizzaName, temp->price);
        price += temp->price;
        temp = temp->next;
    }
    printf("--------------------------------\n");
    printf("Total Cost: %d\n\n", price);
}

// Function to add items to the cart
void addItemsToCart(char pizzaName[], int price) {
    struct item *newnode = (struct item *) malloc(sizeof(struct item));
    strcpy(newnode->pizzaName, pizzaName);
    newnode->price = price;
    newnode->next = NULL;

    if (head == NULL) {
        head = tail = newnode;
    } else {
        tail->next = newnode;
        tail = newnode;
    }
}

// Function to display the main menu
void mainMenu() {
    printf("\n---------- Main Menu ----------\n");
    printf("1. Veg Pizza\n");
    printf("2. Non Veg Pizza\n");
    printf("3. View Cart\n");
    printf("4. Make Order\n");
    printf("------------------------------\n");
}

// Function to display the vegetarian pizza menu
void vegMenu() {
    printf("\n--------- Veg Pizza ---------\n");
    printf("1. Cheese Pizza\n");
    printf("2. Veggie Pizza\n");
    printf("3. Pepperoni Pizza\n");
    printf("4. Back to Main Menu\n");
    printf("-----------------------------\n");
}

// Function to display the non-vegetarian pizza menu
void nonVegMenu() {
    printf("\n-------- Non Veg Pizza --------\n");
    printf("1. BBQ Chicken Pizza\n");
    printf("2. Meat Pizza\n");
    printf("3. Gamberi Pizza\n");
    printf("4. Back to Main Menu\n");
    printf("-------------------------------\n");
}

// Function to generate a 16-digit long orderId
long int generateOrderId() {
    long long int orderId = 0;
    // Seed the random number generator
    srand(time(NULL));

    // Generate random digits for the orderId
    for (int i = 0; i < 16; i++) {
        orderId = orderId * 10 + abs(rand() % 10);
    }

    return orderId;
}

// Function to get customer details as input and write to customer.csv file
void writeCustomerToFile(struct customer *cust) {
    // Open the file for writing in append mode
    FILE *file = fopen("customers.csv", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Write customer data to the file
    fprintf(file, "%s,%s,%d,%llu\n", cust->name, cust->gender, cust->age, cust->orderId);

    // Close the file
    fclose(file);

    printf("Customer data written to customer.csv successfully.\n");
}

// Function to add a customer by getting details as input and writing to customer.csv file
struct customer* addCustomer() {
    // Declare a customer object to store input
    static struct customer cust; // Declared as static to retain its value outside the function

    getchar();
    // Get customer details as input
    printf("Enter name: ");
    fgets(cust.name, sizeof(cust.name), stdin);
    // Remove the newline character from the end of the name
    cust.name[strcspn(cust.name, "\n")] = '\0';

    printf("Enter gender (male/female): ");
    fgets(cust.gender, sizeof(cust.gender), stdin);
    // Remove the newline character from the end of the gender
    cust.gender[strcspn(cust.gender, "\n")] = '\0';

    printf("Enter age: ");
    scanf("%d", &cust.age);

    getchar();
    // Generate orderId using the generateOrderId function
    cust.orderId = generateOrderId();

    writeCustomerToFile(&cust);

    return &cust;
}

// Function to write order data to the order.csv file
void writeOrderToFile(struct order *ord, struct customer *cust, struct item *head) {
    // Open the file for writing in append mode
    FILE *file = fopen("orders.csv", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    // Traverse through items to create a string with item names and calculate total price
    char allItems[1000] = ""; // Initialize an empty string for all items
    int totalPrice = 0;
    struct item *temp = head;
    while (temp != NULL) {
        // Concatenate each item name to the allItems string
        strcat(allItems, temp->pizzaName);
        strcat(allItems, " | ");
        // Add the item price to the total price
        totalPrice += temp->price;
        temp = temp->next;
    }

    // Write order data to the file
    fprintf(file, "%llu,%s,%s,%d\n", cust->orderId, allItems, cust->name, totalPrice);

    // Close the file
    fclose(file);

    printf("Order data written to orders.csv successfully.\n");
}

void readAndPrintOrders() {
    // Open the order file for reading
    FILE *file = fopen("orders.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nOrder Data:\n");
    printf("OrderID\t|\tItems\t|\tCustomer Name\t|\tTotal Cost\n");
    printf("---------------------------------------------------------\n");

    char line[1000];
    while (fgets(line, sizeof(line), file)) {
        unsigned long long int orderId;
        char items[1000];
        char customerName[50];
        int totalCost;

        // Parse each line to extract order data
        sscanf(line, "%llu,%[^,],%[^,],%d", &orderId, items, customerName, &totalCost);

        // Print the extracted order data in a formatted manner
        printf("%llu\t|%s\t|%s\t|%d\n", orderId, items, customerName, totalCost);
    }

    fclose(file); // Close the file
}

void readAndPrintCustomers() {
    // Open the customer file for reading
    FILE *file = fopen("customers.csv", "r");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }

    printf("\nCustomer Data:\n");
    printf("Name\t|\tGender\t|\tAge\t|\tOrderID\n");
    printf("-----------------------------------------------\n");

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        char name[50];
        char gender[10];
        int age;
        unsigned long long int orderId;

        // Parse each line to extract customer data
        sscanf(line, "%[^,],%[^,],%d,%llu", name, gender, &age, &orderId);

        // Print the extracted customer data in a formatted manner
        printf("%s\t|%s\t|%d\t|%llu\n", name, gender, age, orderId);
    }

    fclose(file); // Close the file
}


