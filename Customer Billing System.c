#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LENGTH 50
#define MAX_ITEMS 100

// Define the structure for a customer
struct Customer {
    char name[MAX_NAME_LENGTH];
    char mobileNumber[15];
    float amountDue;
    float amountPaid;
    char itemsPurchased[MAX_ITEMS][MAX_NAME_LENGTH];
    int numItems;
};

// Function to add a new customer to the billing system
void addCustomer(FILE *file, struct Customer *customers, int *numCustomers) {
    struct Customer newCustomer;

    printf("Enter customer name: ");
    scanf("%s", newCustomer.name);

    printf("Enter mobile number: ");
    scanf("%s", newCustomer.mobileNumber);

    printf("Enter the number of items purchased: ");
    scanf("%d", &newCustomer.numItems);

    printf("Enter items purchased:\n");
    for (int i = 0; i < newCustomer.numItems; i++) {
        printf("Item %d: ", i + 1);
        scanf("%s", newCustomer.itemsPurchased[i]);
    }

    printf("Enter amount due: ");
    scanf("%f", &newCustomer.amountDue);

    printf("Enter amount paid: ");
    scanf("%f", &newCustomer.amountPaid);

    // Append the new customer to the end of the file
    fseek(file, 0, SEEK_END);
    fwrite(&newCustomer, sizeof(struct Customer), 1, file);

    // Update the in-memory array of customers
    customers[*numCustomers] = newCustomer;
    (*numCustomers)++;

    printf("Customer added successfully!\n");
}

// Function to display all customers in the billing system
void displayCustomers(struct Customer *customers, int numCustomers) {
    printf("Customers in the billing system:\n");
    for (int i = 0; i < numCustomers; i++) {
        printf("Customer %d:\n", i + 1);
        printf("Name: %s\n", customers[i].name);
        printf("Mobile Number: %s\n", customers[i].mobileNumber);
        printf("Items Purchased:\n");
        for (int j = 0; j < customers[i].numItems; j++) {
            printf("  %s\n", customers[i].itemsPurchased[j]);
        }
        printf("Amount Due: %.2f\n", customers[i].amountDue);
        printf("Amount Paid: %.2f\n", customers[i].amountPaid);
        printf("\n");
    }
}

int main() {
    FILE *file = fopen("billing.dat", "r+");

    if (file == NULL) {
        // If the file doesn't exist, create it
        file = fopen("billing.dat", "w+");
    }

    if (file == NULL) {
        fprintf(stderr, "Error opening the billing file.\n");
        return 1;
    }

    struct Customer customers[100]; // Assuming a maximum of 100 customers
    int numCustomers = 0;

    // Read existing customers from the file into memory
    while (fread(&customers[numCustomers], sizeof(struct Customer), 1, file) == 1) {
        numCustomers++;
    }

    int choice;

    do {
        printf("Customer Billing System\n");
        printf("1. Add Customer\n");
        printf("2. Display Customers\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addCustomer(file, customers, &numCustomers);
                break;
            case 2:
                displayCustomers(customers, numCustomers);
                break;
            case 3:
                printf("Exiting the billing system.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);

    fclose(file);

    return 0;
}

