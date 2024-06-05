
#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

using namespace std;

const int MAX_PRODUCTS = 10;
struct product {
    string name;
    int quantity;
    double price;
    double totalInventoryValue = 0;
};
struct Category {
    string name;
    product products[MAX_PRODUCTS];
    int productCount = 0;
    void addproduct(const product& product) {
        if (productCount < MAX_PRODUCTS) {
            products[productCount++] = product;
            cout << "Product added successfully.\n";
        } else {
            cout<<"Cannot add more products. Maximum limit reached.\n";
        }
    }
    void updateProductPrice(const string& productName, double newPrice){
        for (int i = 0; i < productCount; ++i) {
            if (products[i].name == productName) {
                products[i].price = newPrice;
                cout<<"Price updated successfully for product: " << productName << endl;
                return;
            }
        }
        cout<< "Product not found!\n";
    }
    void updateproductCount(const string& productName, int newQuantity) {
        for (int i = 0; i < productCount; ++i) {
            if (products[i].name == productName) {
                products[i].quantity = newQuantity;
                cout << "Quantity updated successfully for product: " << productName << endl;
                return;
            }
        }
        cout<< "Product not found!\n";
    }
    void deleteProduct(const string& productName) {
        for (int i = 0; i < productCount; ++i) {
            if (products[i].name == productName){
                for (int j = i; j < productCount - 1; ++j) {
                    products[j] = products[j + 1];
                }
                --productCount;
                cout<<"Product deleted successfully: " << productName << endl;
                return;
            }
        }
        cout<<"Product not found!\n";
    }
    void searchProduct(const string& productName){
        for (int i = 0; i < productCount; ++i) {
            if (products[i].name == productName){
                cout<<"Product found: " << productName << endl;
                cout<<"Available quantity: " << products[i].quantity << endl;
                return;
            }
        }
        cout<<"Product not found!\n";
    }
    void displayCurrentStock(const string& productName){
        for (int i = 0; i < productCount; ++i){
            if (products[i].name == productName){
                cout<<"Current stock of " << productName << ": " << products[i].quantity << endl;
                return;
            }
        }
        cout<<"Product not found!\n";
    }
    void calculateCost(const string& productName){
        for (int i = 0; i< productCount; ++i){
            if (products[i].name == productName){
                cout<<"Cost of "<< productName << ": " << products[i].quantity * products[i].price << endl;
                return;
            }
        }
        cout<<"Product not found!\n";
    }
    void loadFromFile(const string& filename) {
        ifstream infile(filename);
        if (!infile) {
            cerr<< "Error opening file: " <<filename << endl;
            return;
        }
        infile>> name;
        productCount = 0;
        while (infile >> products[productCount].name >> products[productCount].quantity >> products[productCount].price) {
            productCount++;
        }
        infile.close();
        cout<<"Data loaded from file successfully.\n";
    }
    void saveToFile(const string& filename) const {
        ofstream outfile(filename);
        if (!outfile) {
            cerr << "Error opening file: " << filename << endl;
            return;
        }

        outfile<<name<< endl;
        for (int i = 0; i < productCount; ++i) {
            outfile << products[i].name <<" " << products[i].quantity << " " << products[i].price << endl;
        }
        outfile.close();
        cout<< "Data saved to file successfully.\n";
    }
    void arrangeByQuantity() {
        sort(products, products + productCount, [](const product& a, const product& b) {
            return a.quantity < b.quantity;
        });
        cout<<"Products arranged by quantity.\n";
    }
    void arrangeByPrice() {
        sort(products, products + productCount, [](const product& a, const product& b) {
            return a.price < b.price;
        });
        cout<<"Products arranged by price.\n";
    }
};
string printMenu() {
    cout<< "Menu:\n";
    cout<< "1. Add product\n";
    cout<< "2. Update product quantity\n";
    cout<< "3. Update product price\n";
    cout<< "4. Delete product\n";
    cout<< "5. Search for product\n";
    cout<< "6. Display current stock\n";
    cout<< "7. Calculate cost\n";
    cout<< "8. Load data from file\n";
    cout<< "9. Save data to file\n";
    cout<< "10. Arrange by quantity\n";
    cout<< "11. Arrange by price\n";
    cout<< "12. Exit\n";
    cout<< "Enter your choice: ";
    string choice;
    cin>>choice;
    return choice;
}
int main() {
    Category foodcat;
    while (true) {
        string choice = printMenu();
        if (choice == "12") {
            break;
        }
        switch (stoi(choice)){
            case 1: {
                cout<<"Enter the products for the category " << foodcat.name << " (type 'done' to finish):\n";
                while (true) {
                    product product;
                    cout<< "Product name: ";
                    cin>> product.name;
                    if (product.name == "done") {
                        break;
                    }
                    cout<<"Quantity: ";
                    cin>> product.quantity;
                    cout<< "Price: ";
                    cin>> product.price;
                    foodcat.addproduct(product);
                }
                break;
            }
            case 2: {
                cout<<"Enter the name of the product to update (type 'done' to finish): ";
                string productName;
                cin >> productName;
                if (productName != "done") {
                    cout << "Enter the new quantity: ";
                    int newQuantity;
                    cin>>newQuantity;
                    foodcat.updateproductCount(productName, newQuantity);
                }
                break;
            }
            case 3: {
                cout<< "Enter the name of the product to update price (type 'done' to finish): ";
                string productName;
                cin >> productName;
                if (productName != "done") {
                    cout<< "Enter the new price: ";
                    double newPrice;
                    cin >> newPrice;
                    foodcat.updateProductPrice(productName, newPrice);
                }
                break;
            }
            case 4: {
                cout<< "Enter the name of the product to delete (type 'done' to finish): ";
                string productName;
                cin >> productName;
                if (productName != "done") {
                    foodcat.deleteProduct(productName);
                }
                break;
            }
            case 5: {
                cout<< "Enter the name of the product to search (type 'done' to finish): ";
                string productName;
                cin >> productName;
                if (productName != "done") {
                    foodcat.searchProduct(productName);
                }
                break;
            }
            case 6: {
                cout<< "Enter the name of the product to display current stock (type 'done' to finish): ";
                string productName;
                cin >> productName;
                if (productName != "done") {
                    foodcat.displayCurrentStock(productName);
                }
                break;
            }
            case 7: {
                cout<< "Enter the name of the product to calculate cost (type 'done' to finish): ";
                string productName;
                cin >> productName;
                if (productName != "done") {
                    foodcat.calculateCost(productName);
                }
                break;
            }
            case 8: {
                cout<< "Enter the filename to load the data from (or 'skip' to skip loading): ";
                string filename;
                cin >> filename;
                if (filename != "skip") {
                    foodcat.loadFromFile(filename);
                }
                break;
            }
            case 9: {
                cout<< "Enter the filename to save the data to (or 'skip' to skip saving): ";
                string filename;
                cin>> filename;
                if (filename != "skip") {
                    foodcat.saveToFile(filename);
                }
                break;
            }
            case 10: {
                foodcat.arrangeByQuantity();
                break;
            }
            case 11: {
                foodcat.arrangeByPrice();
                break;
            }
            default:
                cout<< "Invalid choice. Please try again.\n";
        }
        double totalInventoryValue = 0;
        for (int i = 0; i < foodcat.productCount; i++) {
            totalInventoryValue += foodcat.products[i].quantity * foodcat.products[i].price;
        }
        cout<<"Total inventory value: " << totalInventoryValue << endl;
    }

    return 0;
}