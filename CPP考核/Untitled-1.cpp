#include<iostream>
#include<string>
using namespace std;


// ��Ʒ�ṹ��
class Product {
    public:
    int code;
    string name;
    float price;
    int total_quantity;
    int stock_quantity;
    Product(int c, string n, double p, int t) : code(c), name(n), price(p), total_quantity(t), stock_quantity(t) {}

    void displayInfo() {
        cout << "Code: " << code << "\tName: " << name << "\tPrice: " << price << "\tStock: " << stock_quantity << "/" << total_quantity << endl;
    }
} ;

// ���ҽṹ��
class Currency {
    public:
    int denomination;
    int quantity;
};

class Water : public Product {
public:
    double netContent;
    Water(int c, string n, double p, int t, double w) : Product(c, n, p, t), netContent(w){}

    void displayInfo() {
        cout << "Code: " << code << "\tName: " << name << "\tPrice: " << price << "\tStock: " << stock_quantity << "/" << total_quantity << endl;
        cout << "netContent=" << netContent << "ml" << endl;
    }
};

class Biscuit : public Product {
public:
    double  weight;

    void displayInfo() {
        cout << "Code: " << code << "\tName: " << name << "\tPrice: " << price << "\tStock: " << stock_quantity << "/" << total_quantity << endl;
        cout << "weight=" << weight << "g" << endl;
    }
};



// ��������
void displayMenu();
void showInventory(Product products[], int numProducts);
void sellProduct(Product products[], int numProducts, Currency *money);
void showSalesStats(Product products[], int numProducts, Currency *money);
void showCurrencyStats(Currency *money); 
void resetMachine(Product products[], int numProducts, Currency *money);
void displayInfo();
//������ ��Ļ��ʾѡ����ú���
int main() {

    // ��Ʒ��ʼ��
    Product products[] = {
        {1, "��Ȫˮ", 3.0, 50},
        {2, "����", 2.0, 30},
        //��ʳѡ���ʳ���࣬��ʳ���ۣ���ʳ���
    };
    int numProducts = sizeof(products) / sizeof(products[0]);        //��δ���������Ǽ���һ��������Ԫ�صĸ��������ȣ�`sizeof(products)`������������ `products` ���ֽڴ�С��Ȼ��`sizeof(products[0])`���������е�һ��Ԫ�ص��ֽڴ�С��ͨ��������������ֽڴ�С���Ե�һ��Ԫ�ص��ֽڴ�С�����Եõ�������Ԫ�صĸ�������󣬽���������ֵ������ `numProducts`����ʾ���� `products` ��Ԫ�صĸ�����

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
        printf("����ѡ��: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                showInventory(products, numProducts);
                displayInfo();
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
                printf("�˳�����\n");
                break;
            default:
                printf("��������������һ��\n");
        }

    } while (choice != 0);

    return 0;
}
//չʾ�˵�
void displayMenu() {
   cout<<"1. ����ѯ"<<endl;
   cout<<"2. ���۲�ѯ"<<endl;
   cout<<"3. ���Ҳ�ѯ"<<endl;
   cout<<"4. ���۲�Ʒ"<<endl;
   cout<<"5. ������Ʒ������"<<endl;
   cout<<"0. �˳�����"<<endl;
}

//��ʾ���
void showInventory(Product products[], int numProducts) {
    printf("\n===== ��� =====\n");
    for (int i = 0; i < numProducts; i++) {
        printf("����: %d, ��Ʒ����: %s, ����: $%.2f, �������: %d\n",products[i].code, products[i].name, products[i].price, products[i].stock_quantity);
    }
}

//��ʾ����ͳ��
void showSalesStats(Product products[], int numProducts, Currency *money) {
    printf("\n===== ����ͳ�� =====\n");
    float totalSales = 0;//��ʼ�����۶�Ϊ0
    for (int i = 0; i < numProducts; i++) {
        printf("��Ʒ���: %s, ��������: %d, ���۽��: $%.2f\n",products[i].name, products[i].total_quantity - products[i].stock_quantity,
(products[i].total_quantity - products[i].stock_quantity) * products[i].price);
        totalSales += (products[i].total_quantity - products[i].stock_quantity) * products[i].price;
    }

    printf("\n�����۶�: $%.2f\n", totalSales);
}

//����ͳ��
void showCurrencyStats(Currency *money) {
    printf("\n===== ����ͳ�� =====\n");
    int totalMoney = 0;
    for (int i = 0; i < 4; i++) {
        printf("$%d ��Ʊ: %d\n", money[i].denomination, money[i].quantity);
        totalMoney += money[i].denomination * money[i].quantity;
    }
    printf("\n�����ܶ�: $%d\n", totalMoney);
}

//ѡ���Ʒ������
void sellProduct(Product products[], int numProducts, Currency *money) {
    int productCode, quantity;
    printf("\n�����Ʒ����: ");
    scanf("%d", &productCode);
    printf("����Ҫ���������: ");
    scanf("%d", &quantity);
    

    float totalCost = quantity * products[productCode - 1].price;
    printf("\n��������: $%.2f\n", totalCost);

    int amountPaid = 0;
    do {
        int denomination;
        printf("����Ӳ��/��Ʊ���: ");
        scanf("%d", &denomination);

        if (denomination == 0) {
            break;
        }

        int quantityPaid;
        printf("��������: ");
        scanf("%d", &quantityPaid);

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
        printf("\n�˻����: $%d\n", change);
        printf("���׳ɹ���\n");
    } else {
        printf("�ʽ��㡣������.\n");
    }
}

//���û���
void resetMachine(Product products[], int numProducts, Currency *money) {
    printf("\n===== �����Զ��ۻ��� =====\n");

    // ������Ʒ����
    for (int i = 0; i < numProducts; i++) {
        products[i].stock_quantity = products[i].total_quantity;
    }

    // ���û�������
    for (int i = 0; i < 4; i++) {
        money[i].quantity = 0;
    }

    printf("�Զ��ۻ���������.\n");
}
