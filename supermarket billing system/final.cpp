#include <iostream>
#include <fstream>
#include <cstring>
#include <windows.h>
using namespace std;

// Product class
class Product
{
private:
    int id;
    char name[50];
    float price;
    float customer_price; // Add customer_price field
    int quantity;

public:
    void set_id(int product_id) {
        id = product_id;
    }

    void set_name(const char* product_name) {
        strncpy(name, product_name, sizeof(name));
    }

    void set_price(float product_price) {
        price = product_price;
    }

    void set_customer_price(float productCustomerPrice) {
        customer_price = productCustomerPrice;
    }

    void set_quantity(int product_quantity) {
        quantity = product_quantity;
    }

    int get_id() {
        return id;
    }

    const char* get_name() {
        return name;
    }

    float get_price() {
        return price;
    }

    float get_customer_price() {
        return customer_price;
    }

    int get_quantity() {
        return quantity;
    }

    void display() {
        cout << "ID: " << id << endl;
        cout << "Name: " << name << endl;
        cout << "Price: $" << price << endl;
        cout << "Customer Price: $" << customer_price << endl;
        cout << "Quantity: " << quantity << endl;
    }
};

// Function to add a product to the stock
void add_product()
{
    ofstream file;
    file.open("stock.txt", ios::app);

    if (!file)
    {
        cout << "Error opening file!\n";
        return;
    }

    Product product;

    cout << "Enter product ID: ";
    int id;
    cin >> id;
    product.set_id(id);

    cout << "Enter product name: ";
    char name[50];
    cin.ignore();
    cin.getline(name, 50);
    product.set_name(name);

  /*  cout << "Enter product price: ";
    float price;
    cin >> price;
    product.set_price(price);*/

    cout << "Enter product customer price: "; // Added customer price input
    float customer_price;
    cin >> customer_price;
    product.set_customer_price(customer_price);

    cout << "Enter product quantity: ";
    int quantity;
    cin >> quantity;
    product.set_quantity(quantity);

    file.write((char*)&product, sizeof(Product));
    file.close();

    cout << "\nProduct added successfully!\n";
}

// Function to display all products in stock
void display_stock()
{
    ifstream file;
    file.open("stock.txt", ios::in);

    if (!file)
    {
        cout << "Stock is empty!\n";
        return;
    }

    Product product;

    cout << "\nStock:\n";
    while (file.read((char*)&product, sizeof(Product)))
    {
        product.display();
        cout << endl;
    }

    file.close();
}

// Function to search and delete a product by ID
void delete_product()
{
    int id;
    cout << "Enter product ID to delete: ";
    cin >> id;

    ifstream file;
    ofstream temp;
    file.open("stock.txt", ios::in);
    temp.open("temp.txt", ios::out);

    Product product;

    bool found = false;

    while (file.read((char*)&product, sizeof(Product)))
    {
        if (product.get_id() == id)
        {
            found = true;
            continue;
        }
        temp.write((char*)&product, sizeof(Product));
    }

    file.close();
    temp.close();

    remove("stock.txt");
    rename("temp.txt", "stock.txt");

    if (found)
        cout << "\nProduct deleted successfully!\n";
    else
        cout << "\nProduct not found!\n";
}

// ... (rest of the Product class)


// Function to calculate and display the bill
void calculate_bill()
{
    ifstream file;
    file.open("stock.txt", ios::in);

    if (!file)
    {
        cout << "Stock is empty!\n";
        return;
    }

    Product product;
    int id, quantity;
    float total = 0;

    cout << "Enter the number of products to buy: ";
    int numProducts;
    cin >> numProducts;

    for (int i = 0; i < numProducts; i++)
    {
        cout << "Product " << i + 1 << " - Enter product ID: ";
        cin >> id;

        bool found = false;

        while (file.read((char*)&product, sizeof(Product)))
        {
            if (product.get_id() == id)
            {
                found = true;
                product.display();
                cout << "Enter quantity: ";
                cin >> quantity;
                total += product.get_customer_price() * quantity; // Use customer price here
                break;
            }
        }

        if (!found)
            cout << "\nProduct not found!\n";

        file.clear();
        file.seekg(0, ios::beg);
    }

    file.close();
    cout << "\nTotal bill: $" << total << endl;
}

// ... (previously defined code)


// Function to search for a product by ID
void search_product()
{
    int id;
    cout << "Enter product ID to search: ";
    cin >> id;

    ifstream file;
    file.open("stock.txt", ios::in);

    if (!file)
    {
        cout << "Stock is empty!\n";
        return;
    }

    Product product;
    bool found = false;

    while (file.read((char*)&product, sizeof(Product)))
    {
        if (product.get_id() == id)
        {
            found = true;
            cout << "\nProduct found:\n";
            product.display();
            break;
        }
    }

    file.close();

    if (!found)
        cout << "\nProduct not found!\n";
}

// Main menu for customer
void customer_menu()
{
    int choice;

    do
    {
        cout << "\nCustomer Menu\n";
        cout << "1. Calculate Bill\n";
        cout << "2. Add Product\n";
        cout << "3. Display Stock\n";
        cout << "4. Delete Product\n";
        cout << "5. Search Product\n";
        cout << "6. Exit\n";
        cout << "Enter your choice:";
        cin >> choice;

        switch (choice)
        {
        case 1:
            calculate_bill();
            break;
        case 2:
            add_product();
            break;
        case 3:
            display_stock();
            break;
        case 4:
            delete_product();
            break;
        case 5:
            search_product();
            break;
        case 6:
            cout << "\nExiting Customer Menu...\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 6);
}

// Administrator menu

int main()
{
 system("color 1F");
        customer_menu();


    return 0;
}
