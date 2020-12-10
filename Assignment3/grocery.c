/*******************************************************************************************/
/*                                                                                         */
/* grocery.c                                                                               */
/*                                                                                         */
/* The program is to simulate items being purchased at the a store.                        */
/*                                                                                         */
/* The program do adding items into a cart, packing these items into bags                  */
/* and removing perishable items                                                           */
/*                                                                                         */
/*******************************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define maximum number of items in a cart
// Define maximum number of items in a bag
// Define maximum weight in a bag
#define MAX_ITEMS_CART 100
#define MAX_WEIGHT 5
#define MAX_ITEMS_BAG 25

// Structure that represents a grocery item
typedef struct{
    char *name;
    float cost;
    float weight;
    int flag;
} GroceryItem;

// Structure that represents a bag
typedef struct{
    GroceryItem items[MAX_ITEMS_BAG];
    int numItems;
    float totalWeight;
} Bag;

// Structure that represents a cart
typedef struct{
    GroceryItem cartItems[MAX_ITEMS_CART];
    int numItem;
    Bag *groceryBags;
    int numBags;
} Cart;

// Function that add a grocery item into a cart
int addToCart(GroceryItem *addItem, Cart *aCart);
// Function that remove lossen item in items array in a cart
int removeLossenItem(GroceryItem *removeItem, Cart *aCart);
// Function that add a grocery item into a bag
int addToBag(GroceryItem *addItem, Bag *aBag);
// Function that remove a grocery item out of a bag
int removeBag(GroceryItem *removeItem, Bag *aBag);
// Function that display a grocery item
void printItem(GroceryItem *item);
// Function that display items in a bag
void printBag(Bag *aBag, int numBag);
// Function that display items in a cart
void printCart(Cart *aCart);
// Function that packs the items 
void packItems(Cart *aCart);
// Function that remove the perishable items from the shopping cart
void removePerishable(Cart *Cart);


int main(){

    // Test with random items
    // Generate items
    GroceryItem testItems[12];
    char *sampleItemNames[] = {"Smart-Ones Frozen Entrees", "SnackPack Pudding", "Breyers Chocolate Icecream", "Nabob Coffee", "Gold Seal Salmon", "Ocean Spray Cranberry Cocktail", "Heinz Beans Original", "Lean Ground Beef", "5-Alive Frozen Juice", "Coca-Cola 12-pack", "Toilet Paper - 48 pack", "Crate of milk"};
    float sampleItemPrices[] = {1.99, 0.99, 2.99, 3.99, 1.99, 2.99, 0.79, 4.94, 0.75, 3.49, 40.96, 12.99};
    float sampleItemWeights[] = {0.311, 0.396, 2.27, 0.326, 0.213, 2.26, 0.477, 0.75, 0.426, 5.112, 10.89f, 6.18f};
    float sampleItemPerish[] = {1, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 1};

    int i;
    GroceryItem *testItemPtr;
    testItemPtr = testItems;
    for (i = 0; i < 12; i++){
        GroceryItem anItem;
        anItem.name = sampleItemNames[i];
        anItem.cost = sampleItemPrices[i];
        anItem.weight = sampleItemWeights[i];
        anItem.flag = sampleItemPerish[i];
        *testItemPtr = anItem;
        if(i < 11){
            testItemPtr++;
        }
    }

    // Declare and initilize a cart
    Cart cart2;
    cart2.numItem = 0;
    Cart *cart2Ptr;
    cart2Ptr = &cart2;

    // Initialized items' name in the array of item to null
    for (i = 0; i < MAX_ITEMS_CART; i++){
        cart2Ptr->cartItems[i].name = NULL;
    }

    // Generate 50 random items for cart
    for (i = 0; i < 50; i++){
        int j;
        j = rand() % 12;
        GroceryItem *itemPtr;
        itemPtr = &testItems[j];
        addToCart(itemPtr, cart2Ptr);
    }
    
    // Print out result
    printf("\n");
    printf("Test with random items\n");
    printf("\n");
    printf("Shopping cart before packing\n");
    printf("\n");
    printCart(cart2Ptr);
    printf("\n");
    printf("Shopping cart after packing\n");
    printf("\n");
    packItems(cart2Ptr);
    
    return 0;
}

// Function that add a grocery item into a cart
int addToCart(GroceryItem *addItem, Cart *aCart){
    // Append a grocery item into cart
    if (aCart->numItem < MAX_ITEMS_CART){
        aCart->cartItems[aCart->numItem] = *addItem;
        aCart->numItem++;
        aCart->numBags = 0;
        return 1;
    }
    return 0;
}

// Function that remove lossen item in items array in a cart
int removeLossenItem(GroceryItem *removeItem, Cart *aCart){
    int index;
    int i;
    // Find position of removeItem;
    for (i = 0; i < aCart->numItem; i++){
        if (strcmp(aCart->cartItems[i].name, removeItem->name) == 0){
            index = i;
            break;
        }
    }
    // Remove the item 
    for (i = index; i < aCart->numItem - 1; i++){
        aCart->cartItems[i] = aCart->cartItems[i+1];
    }
    aCart->numItem--;
    return 0;  
}

// Function that add a grocery item into a bag
int addToBag(GroceryItem *addItem, Bag *aBag){
    // Append a grocery item into a bag
    if (aBag->numItems < MAX_ITEMS_BAG && (aBag->totalWeight + addItem->weight) < MAX_WEIGHT){
        aBag->items[aBag->numItems] = *addItem;
        aBag->numItems++;
        aBag->totalWeight += addItem->weight;
        return 1;
    }
    return 0;
}

// Function that remove a grocery item out of a bag
int removeBag(GroceryItem *removeItem, Bag *aBag){
    int index;
    int i;
    GroceryItem removeItemCopy;
    removeItemCopy = *removeItem;
    // Find position of removeItem;
    for (i = 0; i < aBag->numItems; i++){
        if (strcmp(aBag->items[i].name, removeItem->name) == 0){
            index = i;
        }
    }
    // Remove the item 
    for (i = index; i < aBag->numItems - 1; i++){
        aBag->items[i] = aBag->items[i+1];
    }
    aBag->numItems--;
    aBag->totalWeight -= removeItemCopy.weight;
    return 0; 
}

// Function that display a grocery item
void printItem(GroceryItem *item){
    // Print items information
    if (item->name != NULL){
        printf("%s weighting %0.3fkg with price $%0.2f\n", item->name, item->weight, item->cost);
    }
}

// Function that display items in a bag
void printBag(Bag *aBag, int numBag){
    int i;
    // Find the heaviest weigth
    float heaviestWeight = aBag->items[0].weight;
    for (i = 0; i < aBag->numItems; i++){
        if (aBag->items[i].weight > heaviestWeight){
            heaviestWeight = aBag->items[i].weight;
        }
    }
    printf("Bag %d (Total Weight = %0.3fkg)\n", numBag, aBag->totalWeight);
    
    // Display items
    GroceryItem *displayItem;
    displayItem = aBag->items;
    for (i = 0; i < aBag->numItems; i++){
        if (displayItem->weight == heaviestWeight){
            printf("   *");
            printItem(displayItem);
            displayItem++;
        }else{
            printf("    ");
            printItem(displayItem);
            displayItem++;
        }
    }
}

// Function that display items in a cart
void printCart(Cart *aCart){
    int i;
    int numItemsArray;
    if (sizeof(aCart->cartItems) > 0){
        numItemsArray = sizeof(aCart->cartItems) / sizeof(aCart->cartItems[0]);
    }
    // Print lossen items
    GroceryItem *itemInArray;
    itemInArray = aCart->cartItems;
    if (numItemsArray > 0){
        while(itemInArray->name != NULL){
            printItem(itemInArray);
            itemInArray++;
        }
    }
    // Print items in bags
    itemInArray--;
    if (aCart->numBags > 0){
        Bag *bagPtr;
        bagPtr = aCart->groceryBags;
        for (i = 0; i < aCart->numBags; i++){
            printBag(bagPtr, i+1);
            bagPtr++;
        }
    }
}

// Function that packs the items 
void packItems(Cart *aCart){
    int i;
    int trackingItems = aCart->numItem;
    // Array that stored all of items in the array
    GroceryItem *storedItems;
    storedItems = aCart->cartItems;
    // Temporary array of bags that pack items
    Bag *arrayBag, *arrayBagStart;
    arrayBag = arrayBagStart = (Bag *)malloc(sizeof(Bag) * aCart->numItem);
    int numBag = 0;
    // An array that store lossen items
    GroceryItem *lossenItems;
    lossenItems = (GroceryItem *)malloc(sizeof(GroceryItem) * aCart->numItem);
    int numLossenItems = 0;

    // Initialize values for a bag
    arrayBag->numItems = 0;
    arrayBag->totalWeight = 0;

    // Packing item into bags
    while (trackingItems > 0){
        if(arrayBag->numItems < MAX_ITEMS_BAG && arrayBag->totalWeight < MAX_WEIGHT && arrayBag->totalWeight + storedItems->weight< MAX_WEIGHT){
            addToBag(storedItems, arrayBag);
            storedItems++;
        }else if (storedItems->weight < MAX_WEIGHT){
            arrayBag++;
            arrayBag->numItems = 0;
            arrayBag->totalWeight = 0;
            numBag++;
            addToBag(storedItems, arrayBag);
            storedItems++;
        }else{
            lossenItems[numLossenItems] = *storedItems;
            numLossenItems++;
            storedItems++;
        }
        trackingItems--;
    }
    // Increase numBag by 1 to match the real number of bags
    numBag++;
    
    // Moving back arrayBag pointer to the beginning point
    for (i = 0; i < (2*numBag - 1); i++){
        arrayBag--;
    }
    // Official array that stored bags
    Bag *bagPtr;
    bagPtr = &arrayBag[0];
    aCart->numBags = numBag;
    Bag *bagStart;
    bagStart = aCart->groceryBags = (Bag *)malloc(sizeof(Bag ) * numBag);
    for (i = 0; i < numBag; i++){
        aCart->groceryBags = arrayBag;
        aCart->groceryBags++;
        arrayBag++;
    }
    
    // Change lossen items into cart 
    // A pointer to cart items array
    for (i = 0; i < aCart->numItem; i++){
        if (i < numLossenItems){
            GroceryItem temp = lossenItems[i];
            lossenItems[i] = aCart->cartItems[i];
            aCart->cartItems[i] = temp;
        }else{
            GroceryItem temp;
            temp.name = NULL;
            aCart->cartItems[i] = temp;
        }
    }

    // Print cart after packing
    printCart(aCart);
    printf("\n");
    // Remove perishable items
    printf("Shopping cart after remove perishable items\n");
    printf("\n");
    removePerishable(aCart);
    // Print cart after removing perishable items
    printCart(aCart);
    printf("\n");

    // Free dynamic allocated memory
    free(lossenItems);
    free(arrayBagStart);
    free(bagStart);
}

// Function that remove the perishable items from the shopping cart
void removePerishable(Cart *cart){
    // Remove perishable items in bags
    int i, j;
    Bag *bagPtr;
    bagPtr = cart->groceryBags;
    for (i = 0; i < cart->numBags; i++){
        for (j = 0; j < bagPtr->numItems; j++){
            if (bagPtr->items[j].flag == 1){
                GroceryItem *itemPtr;
                itemPtr = &(bagPtr->items[j]);
                removeBag(itemPtr, bagPtr);
                // Reduce j to match the index of next item which are moving to removing index
                j--;
                // Reduce the number of item in the cart
                cart->numItem--;
            }
        }
        // remove bag if the number of items in the bag is 0
        bagPtr++;
    }

    // Remove lossen perishable items in cart
    int numLossenItem = sizeof(cart->cartItems) / sizeof(GroceryItem);
    GroceryItem *lossenItem;
    lossenItem = cart->cartItems;
    // test print out lossen items
    while (lossenItem->name != NULL){
        if (lossenItem->flag == 1){
            removeLossenItem(lossenItem, cart);
        }else{
            lossenItem++;
        }
    }

}

