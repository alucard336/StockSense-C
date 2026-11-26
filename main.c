#include <stdio.h>

#define MAX_ITEMS 100

// Structure to store inventory information
struct Item {
    char name[50];
    char category[20];
    char unit[10];
    float quantity;
    float minStock;
};

// Global inventory storage
struct Item inventory[MAX_ITEMS];
int itemCount = 0;

// Function declarations
void addItem();
void displayInventory();
void saveInventory();
void loadInventory();

int main() {
    int choice;

    // Load previously saved inventory when the program starts
    loadInventory();

    do {
        printf("\n====================================\n");
        printf("          STOCKSENSE SYSTEM\n");
        printf("       Restaurant Inventory\n");
        printf("====================================\n");

        printf("1. Add Inventory Item\n");
        printf("2. View Inventory\n");
        printf("3. Exit\n");

        printf("\nEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addItem();
                break;

            case 2:
                displayInventory();
                break;

            case 3:
                saveInventory();
                printf("\nExiting StockSense. Goodbye!\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } while (choice != 3);

    return 0;
}

// Add a new inventory item
void addItem() {
    if (itemCount >= MAX_ITEMS) {
        printf("\nInventory is full!\n");
        return;
    }

    printf("\n--- ADD INVENTORY ITEM ---\n");

    printf("Enter item name: ");
    scanf(" %49[^\n]", inventory[itemCount].name);

    int categoryChoice;

    printf("\nSelect category:\n");
    printf("1. Raw Material\n");
    printf("2. Finished Product\n");
    printf("Enter choice: ");
    scanf("%d", &categoryChoice);

    if (categoryChoice == 1) {
        snprintf(inventory[itemCount].category, 20, "Raw Material");
    }
    else if (categoryChoice == 2) {
        snprintf(inventory[itemCount].category, 20, "Finished Product");
    }
    else {
        printf("Invalid category!\n");
        return;
    }

    printf("Enter measurement unit (kg, L, pcs): ");
    scanf("%9s", inventory[itemCount].unit);

    printf("Enter current quantity: ");
    scanf("%f", &inventory[itemCount].quantity);

    printf("Enter minimum stock level: ");
    scanf("%f", &inventory[itemCount].minStock);

    itemCount++;

    printf("\nItem added successfully!\n");
    saveInventory();
}

// Display all inventory items
void displayInventory() {
    if (itemCount == 0) {
        printf("\nNo inventory items registered yet.\n");
        return;
    }

    printf("\n========== CURRENT INVENTORY ==========\n");

    for (int i = 0; i < itemCount; i++) {
        printf("\nItem: %s\n", inventory[i].name);
        printf("Category: %s\n", inventory[i].category);
        printf("Unit: %s\n", inventory[i].unit);
        printf("Quantity: %.2f %s\n",
               inventory[i].quantity,
               inventory[i].unit);
        printf("Minimum Stock: %.2f %s\n",
               inventory[i].minStock,
               inventory[i].unit);

        if (inventory[i].quantity <= inventory[i].minStock) {
            printf("Status: LOW STOCK!\n");
        }
        else {
            printf("Status: Available\n");
        }

        printf("---------------------------------------\n");
    }
}

// Save the current inventory to a text file
void saveInventory() {
    FILE *file = fopen("inventory.txt", "w");

    if (file == NULL) {
        printf("\nError: Could not save inventory!\n");
        return;
    }

    for (int i = 0; i < itemCount; i++) {
        fprintf(file, "%s|%s|%s|%.2f|%.2f\n",
                inventory[i].name,
                inventory[i].category,
                inventory[i].unit,
                inventory[i].quantity,
                inventory[i].minStock);
    }

    fclose(file);
    printf("Inventory saved successfully.\n");
}

// Load previously saved inventory from the text file
void loadInventory() {
    FILE *file = fopen("inventory.txt", "r");

    if (file == NULL) {
        // This is normal the first time the program runs
        return;
    }

    while (itemCount < MAX_ITEMS &&
           fscanf(file, "%49[^|]|%19[^|]|%9[^|]|%f|%f\n",
                  inventory[itemCount].name,
                  inventory[itemCount].category,
                  inventory[itemCount].unit,
                  &inventory[itemCount].quantity,
                  &inventory[itemCount].minStock) == 5) {
        itemCount++;
    }

    fclose(file);

    if (itemCount > 0) {
        printf("Loaded %d inventory item(s) from file.\n", itemCount);
    }
}
