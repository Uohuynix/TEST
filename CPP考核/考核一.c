#include <stdio.h>

// ��Ʒ�ṹ��
typedef struct {
    int code;
    char name[50];
    float price;
    int total_quantity;
    int stock_quantity;
} Product;

// ���ҽṹ��
typedef struct {
    int denomination;
    int quantity;
} Currency;

// ��������
void displayMenu();
void showInventory(Product products[], int numProducts);
void sellProduct(Product products[], int numProducts, Currency *money);
void showSalesStats(Product products[], int numProducts, Currency *money);
void showCurrencyStats(Currency *money); 
void resetMachine(Product products[], int numProducts, Currency *money);

//������ ��Ļ��ʾѡ����ú���
int main() {
    // ��Ʒ��ʼ��
    Product products[] = {
        {1, "Snack A", 1.5, 50, 50},
        {2, "Snack B", 2.0, 30, 30},
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
    printf("1. ����ѯ\n");
    printf("2. ���۲�ѯ\n");
    printf("3. ���Ҳ�ѯ\n");
    printf("4. ���۲�Ʒ\n");
    printf("5. ������Ʒ������\n");
    printf("0. �˳�����\n");
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
