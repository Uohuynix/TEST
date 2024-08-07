#include <iostream>
#include <string>
#include <list>

using namespace std;

// ��Ʒ��
class Product {
public:
    string code;
    string name;
    double price;
    int totalQuantity;
    int stockQuantity;

    Product(string c, string n, double p, int t) : code(c), name(n), price(p), totalQuantity(t), stockQuantity(t) {}

    void displayInfo() {
        cout << "Code: " << code << "\tName: " << name << "\tPrice: " << price << "\tStock: " << stockQuantity << "/" << totalQuantity << endl;
    }
};

// �����࣬��Ӷ�������
class Snack : public Product {
public:
    double weight;

    Snack(string c, string n, double p, int t, double w) : Product(c, n, p, t), weight(w) {}

    void displayInfo() {
        Product::displayInfo();
        cout << "Weight: " << weight << "g" << endl;
    }
};

// ������
class Currency {
public:
    int value;
    int quantity;

    Currency(int v, int q) : value(v), quantity(q) {}

    void displayInfo() {
        cout << "Value: " << value << "\tQuantity: " << quantity << endl;
    }
};

// �Զ��ۻ�����
class VendingMachine {
private:
    list<Product*> products;
    list<Currency*> currencies;
    double totalSales;

public:
    VendingMachine() : totalSales(0) {}

    // �����Ʒ��ͷ�巨
    void addProduct(Product* product) {
        products.push_front(product);
    }

    // ɾ��ָ��λ�õ���Ʒ
    void deleteProduct(int position) {
        if (position > 0 && position <= products.size()) {
            auto it = products.begin();
            advance(it, position - 1);
            products.erase(it);
        } else {
            cout << "Invalid position for deletion." << endl;
        }
    }

    // ɾ��ָ����Ʒ
    void deleteProduct(string code) {
        auto it = find_if(products.begin(), products.end(), [&](Product* p) { return p->code == code; });
        if (it != products.end()) {
            products.erase(it);
        } else {
            cout << "Product with code " << code << " not found." << endl;
        }
    }

    // ��ʾ������Ʒ��Ϣ
    void displayProducts() {
        for (auto& product : products) {
            product->displayInfo();
        }
    }

    // ��ӻ���
    void addCurrency(Currency* currency) {
        currencies.push_back(currency);
    }

    // ͳ�ƻ�����Ϣ�����۶�
    void displayCurrencyInfo() {
        double totalAmount = 0;

        cout << "Currency Information:" << endl;
        for (auto& currency : currencies) {
            currency->displayInfo();
            totalAmount += currency->value * currency->quantity;
        }

        cout << "Total Sales: " << totalSales << endl;

        if (totalAmount == totalSales) {
            cout << "Currency total matches total sales." << endl;
        } else {
            cout << "Currency total does not match total sales." << endl;
        }
    }

    // ��������
    void sellProduct(string code, int quantity, int insertedAmount) {
        auto it = find_if(products.begin(), products.end(), [&](Product* p) { return p->code == code; });
        if (it != products.end()) {
            Product* product = *it;

            if (product->stockQuantity >= quantity && insertedAmount >= (quantity * product->price)) {
                product->stockQuantity -= quantity;
                totalSales += quantity * product->price;

                // Calculate change
                int change = insertedAmount - quantity * product->price;
                giveChange(change);

                cout << "Sold " << quantity << " of " << product->name << " for " << quantity * product->price << ". Change: " << change << endl;
            } else {
                cout << "Insufficient stock or insufficient funds." << endl;
            }
        } else {
            cout << "Product with code " << code << " not found." << endl;
        }
    }

private:
    // ���㲢��������
    void giveChange(int change) {
        list<Currency*> changeCoins;

        int denominations[] = {10, 5, 1};

        for (int i = 0; i < 3; ++i) {
            int denomination = denominations[i];
            int count = change / denomination;

            if (count > 0) {
                changeCoins.push_back(new Currency(denomination, count));
                change %= denomination;
            }
        }

        cout << "Change: ";
        for (auto& coin : changeCoins) {
            coin->displayInfo();
        }
    }
};

int main() {
    // ������Ʒ
    Product* soda = new Product("001", "Soda", 1.5, 20);
    Snack* chips = new Snack("002", "Chips", 2.0, 15, 150);

    // ��������
    Currency* coin1 = new Currency(1, 50);
    Currency* coin5 = new Currency(5, 20);
    Currency* coin10 = new Currency(10, 10);

    // �����Զ��ۻ���
    VendingMachine vendingMachine;

    // �����Ʒ�ͻ���
    vendingMachine.addProduct(soda);
    vendingMachine.addProduct(chips);
    vendingMachine.addCurrency(coin1);
    vendingMachine.addCurrency(coin5);
    vendingMachine.addCurrency(coin10);

    // �������ۺ�����
    vendingMachine.sellProduct("001", 2, 5);

    // ��ʾ��Ʒ��Ϣ�ͻ�����Ϣ
    vendingMachine.displayProducts();
    vendingMachine.displayCurrencyInfo();

    // ɾ����Ʒ���ٴ���ʾ
    vendingMachine.deleteProduct(1);
    vendingMachine.displayProducts();

    // ɾ��ָ����Ʒ���ٴ���ʾ
    vendingMachine.deleteProduct("002");
    vendingMachine.displayProducts();

    return 0;
}
