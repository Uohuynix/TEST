#include <iostream>
#include <string>
using namespace std;

// ��Ʒ��
class Product {
public:
    int code;
    string name;
    float price;
    int total_quantity;
    int stock_quantity;

    Product(int c, string n, float p, int tq, int sq)
        : code(c), name(n), price(p), total_quantity(tq), stock_quantity(sq) {}
};

// ������
class Currency {
public:
    int denomination;
    int quantity;
};

//��Ȫˮ��
class Water : public Product {
public:
    double netContent;

    Water(int c, string n, float p, int tq, int sq, double w)
        : Product(c, n, p, tq, sq), netContent(w) {}

    void displayInfo() {
        cout << "Product: " << name << "\tPrice: " << price << "\tNet Content: " << netContent << "L" << endl;
    }
};

//������
class Biscuit : public Product {
public:
    double netContent;

    Biscuit(int c, string n, float p, int tq, int sq, double w)
        : Product(c, n, p, tq, sq), netContent(w) {}

    void displayInfo() {
        cout << "Product: " << name << "\tPrice: " << price << "\tWeight: " << netContent << "g" << endl;
    }
};

// ��������
void displayMenu();
void showInventory(Product products[], int numProducts);
void sellProduct(Product products[], int numProducts, Currency *money);
void showSalesStats(Product products[], int numProducts, Currency *money);
void showCurrencyStats(Currency *money);
void resetMachine(Product products[], int numProducts, Currency *money);
void displayInfo(Water& water, Biscuit& biscuit);

// ������ ��Ļ��ʾѡ����ú���
int main() {
    // ��Ʒ��ʼ��
    Water water(1, "��Ȫˮ", 3.0, 50, 50, 0.5);
    Biscuit biscuit(2, "����", 2.0, 30, 30, 100);
    Product products[] = { water, biscuit };

    int numProducts = sizeof(products) / sizeof(products[0]);

    // ���ҳ�ʼ��
    Currency money[] = {
        {1, 0},
        {5, 0},
        {10, 0},
        {20, 0}
    };

    int choice;
    do {
        displayMenu();
        cout << "����ѡ��: ";
        cin >> choice;

        switch (choice) {
        case 1:
            showInventory(products, numProducts);
            displayInfo(water, biscuit);
            break;
        case 2:
            showSalesStats(products, numProducts, money);
            break;
        case 3:
            showCurrencyStats(money);
            break;
        case 4:
            sellProduct(products, numProducts, money);
            break;
        case 5:
            resetMachine(products, numProducts, money);
            break;
        case 0:
            cout << "�˳�����" << endl;
            break;
        default:
            cout << "��������������һ��" << endl;
        }

    } while (choice != 0);

    return 0;
}

// չʾ�˵�
void displayMenu() {
    cout << "1. ����ѯ" << endl;
    cout << "2. ���۲�ѯ" << endl;
    cout << "3. ���Ҳ�ѯ" << endl;
    cout << "4. ���۲�Ʒ" << endl;
    cout << "5. ������Ʒ������" << endl;
    cout << "0. �˳�����" << endl;
}

// ��ʾ���
void showInventory(Product products[], int numProducts) {
    cout << "\n===== ��� =====\n";
    for (int i = 0; i < numProducts; i++) {
        cout << "����: " << products[i].code
            << ", ��Ʒ����: " << products[i].name
            << ", ����: $" << products[i].price
            << ", �������: " << products[i].stock_quantity << endl;
    }
}

// ��ʾ����ͳ��
void showSalesStats(Product products[], int numProducts, Currency *money) {
    cout << "\n===== ����ͳ�� =====\n";
    float totalSales = 0; // ��ʼ�����۶�Ϊ0
    for (int i = 0; i < numProducts; i++) {
        cout << "��Ʒ���: " << products[i].name
            << ", ��������: " << products[i].total_quantity - products[i].stock_quantity
            << ", ���۽��: $" << (products[i].total_quantity - products[i].stock_quantity) * products[i].price << endl;
        totalSales += (products[i].total_quantity - products[i].stock_quantity) * products[i].price;
    }

    cout << "\n�����۶�: $" << totalSales << endl;
}

// ����ͳ��
void showCurrencyStats(Currency *money) {
    cout << "\n===== ����ͳ�� =====\n";
    int totalMoney = 0;
    for (int i = 0; i < 4; i++) {
        cout << "$" << money[i].denomination << " ��Ʊ: " << money[i].quantity << endl;
        totalMoney += money[i].denomination * money[i].quantity;
    }
    cout << "\n�����ܶ�: $" << totalMoney << endl;
}

// ѡ���Ʒ������
void sellProduct(Product products[], int numProducts, Currency *money) {
    int productCode, quantity;
    cout << "\n�����Ʒ����: ";
    cin >> productCode;
    cout << "����Ҫ���������: ";
    cin >> quantity;

    float totalCost = quantity * products[productCode - 1].price;
    cout << "\n��������: $" << totalCost << endl;

    int amountPaid = 0;
    do {
        int denomination;
        cout << "����Ӳ��/��Ʊ���: ";
        cin >> denomination;

        if (denomination == 0) {
            break;
        }

        int quantityPaid;
        cout << "��������: ";
        cin >> quantityPaid;

        amountPaid += denomination * quantityPaid;

        for (int i = 0; i < 4; i++) {
            if (money[i].denomination == denomination) {
                money[i].quantity += quantityPaid;
            }
        }
    } while (amountPaid < totalCost);

    if (amountPaid >= totalCost) {
        // ������Ʒ���
        products[productCode - 1].stock_quantity -= quantity;
        products[productCode - 1].total_quantity += quantity;

        // ���㲢�˻����
        int change = amountPaid - totalCost;
        cout << "\n�˻����: $" << change << endl;
        cout << "���׳ɹ���" << endl;
    }
    else {
        cout << "�ʽ��㡣������." << endl;
    }
}

// ���û���
void resetMachine(Product products[], int numProducts, Currency *money) {
    cout << "\n===== �����Զ��ۻ��� =====\n";

    // ������Ʒ����
    for (int i = 0; i < numProducts; i++) {
        products[i].stock_quantity = products[i].total_quantity;
    }

    // ���û�������
    for (int i = 0; i < 4; i++) {
        money[i].quantity = 0;
    }

    cout << "�Զ��ۻ���������.\n";
}

// ��ʾ��Ʒ��Ϣ
void displayInfo(Water& water, Biscuit& biscuit) {
    cout << "\n===== ��Ʒ��Ϣ =====\n";
    water.displayInfo();
    biscuit.displayInfo();
}
