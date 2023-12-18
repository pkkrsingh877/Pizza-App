#include 
#include 
#include 

struct item{
    char pizzaName[50];
    int price;
    struct item *next;
};

struct item *head = NULL; // store address of first node
struct item *temp = NULL; // traverse the items in cart
struct item *newnode = NULL; // create new items

void viewCart(){
    temp = head;
    printf("Name:\tPrice\n");
    while(temp != NULL){
        printf("%s\t%d\n", newnode -> pizzaName, newnode -> price);
        temp = temp -> next;
    }
}

void addItemsToCart(char pizzaName[], int price){
    newnode = (struct item*)malloc(sizeof(struct item));
    strcpy(newnode -> pizzaName, pizzaName);
    newnode -> price = price;
    newnode -> next = NULL;

    if(head == NULL){
        head = temp = newnode;
    }else{
        temp -> next = newnode;
        temp = newnode;
    }
}

void mainMenu(){
    printf("1. Veg Pizza\n");
    printf("2. Non Veg Pizza\n");
    printf("3. View Cart\n");
    printf("4. Exit\n");
}

void vegMenu(){
    printf("1. Cheese Pizza\n");
    printf("2. Veggie Pizza\n");
    printf("3. Pepperoni Pizza\n");
    printf("4. Exit\n");
}

void nonVegMenu(){
    printf("1. BBQ Chicken Pizza\n");
    printf("2. Meat Pizza\n");
    printf("3. Gamberi Pizza\n");
    printf("4. Exit\n");
}

int main(){
    int keepGoing = 1, choice;
    do{
        mainMenu();
        printf("Your Choice: ");
        scanf("%d", &choice);
        switch(choice){
            case 1:
                vegMenu();
                printf("Your Choice: ");
                scanf("%d", &choice);

                switch(choice){
                    case 1:
                        printf("Cheese Pizza Coming Right Up!\n");
                        addItemsToCart("Cheese Pizza", 50);
                        break;
                    case 2:
                        printf("Veggie Pizza Coming Right Up!\n");
                        addItemsToCart("Veggie Pizza", 50);
                        break;
                    case 3:
                        printf("Pepperoni Pizza Coming Right Up!\n");
                        addItemsToCart("Pepperoni Pizza", 50);
                        break;
                    case 4:
                        printf("Thanks for viewing Veg Pizza!\n");
                        break;
                    default: 
                        printf("Invalid Order\n");
                }
                break;
            case 2:
                nonVegMenu();
                printf("Your Choice: ");
                scanf("%d", &choice);

                switch(choice){
                    case 1:
                        printf("BBQ Chicken Pizza Coming Right Up!\n");
                        addItemsToCart("BBQ Chicken Pizza", 50);
                        break;
                    case 2:
                        printf("Meat Pizza Coming Right Up!\n");
                        addItemsToCart("Meat Pizza", 50);
                        break;
                    case 3:
                        printf("Gamberi Pizza Coming Right Up!\n");
                        addItemsToCart("Gamberi Pizza", 50);
                        break;
                    case 4:
                        printf("Thanks for viewing Non Veg Pizza!\n");
                        break;
                    default: 
                        printf("Invalid Order\n");
                }
                break;
            case 3:
                viewCart();
                break;
            case 4:
                printf("Thank You For Your Visit!\n");
                return 0;
            default: 
                printf("Something went wrong!\n");
                return -1;
        }
        printf("Do you want to continue(0:No): ");
        scanf("%d", &keepGoing);
    }while(keepGoing);
    
    return 0;
}