#include <iostream>
#include <string>
using namespace std;

// 商品类
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

// 货币类
class Currency {
public:
    int denomination;
    int quantity;
};

//矿泉水类
class Water : public Product {
public:
    double netContent;

    Water(int c, string n, float p, int tq, int sq, double w)
        : Product(c, n, p, tq, sq), netContent(w) {}

    void displayInfo() {
        cout << "Product: " << name << "\tPrice: " << price << "\tNet Content: " << netContent << "L" << endl;
    }
};

//曲奇类
class Biscuit : public Product {
public:
    double netContent;

    Biscuit(int c, string n, float p, int tq, int sq, double w)
        : Product(c, n, p, tq, sq), netContent(w) {}

    void displayInfo() {
        cout << "Product: " << name << "\tPrice: " << price << "\tWeight: " << netContent << "g" << endl;
    }
};

// 函数声明
void displayMenu();
void showInventory(Product products[], int numProducts);
void sellProduct(Product products[], int numProducts, Currency *money);
void showSalesStats(Product products[], int numProducts, Currency *money);
void showCurrencyStats(Currency *money);
void resetMachine(Product products[], int numProducts, Currency *money);
void displayInfo(Water& water, Biscuit& biscuit);

// 主函数 屏幕显示选项并调用函数
int main() {
    // 商品初始化
    Water water(1, "矿泉水", 3.0, 50, 50, 0.5);
    Biscuit biscuit(2, "饼干", 2.0, 30, 30, 100);
    Product products[] = { water, biscuit };

    int numProducts = sizeof(products) / sizeof(products[0]);

    // 货币初始化
    Currency money[] = {
        {1, 0},
        {5, 0},
        {10, 0},
        {20, 0}
    };

    int choice;
    do {
        displayMenu();
        cout << "输入选项: ";
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
            cout << "退出程序" << endl;
            break;
        default:
            cout << "操作出错，请再试一次" << endl;
        }

    } while (choice != 0);

    return 0;
}

// 展示菜单
void displayMenu() {
    cout << "1. 库存查询" << endl;
    cout << "2. 销售查询" << endl;
    cout << "3. 货币查询" << endl;
    cout << "4. 销售产品" << endl;
    cout << "5. 重置商品及货币" << endl;
    cout << "0. 退出程序" << endl;
}

// 显示库存
void showInventory(Product products[], int numProducts) {
    cout << "\n===== 库存 =====\n";
    for (int i = 0; i < numProducts; i++) {
        cout << "代码: " << products[i].code
            << ", 产品名称: " << products[i].name
            << ", 单价: $" << products[i].price
            << ", 库存数量: " << products[i].stock_quantity << endl;
    }
}

// 显示销售统计
void showSalesStats(Product products[], int numProducts, Currency *money) {
    cout << "\n===== 销售统计 =====\n";
    float totalSales = 0; // 初始总销售额为0
    for (int i = 0; i < numProducts; i++) {
        cout << "产品类别: " << products[i].name
            << ", 销售数量: " << products[i].total_quantity - products[i].stock_quantity
            << ", 销售金额: $" << (products[i].total_quantity - products[i].stock_quantity) * products[i].price << endl;
        totalSales += (products[i].total_quantity - products[i].stock_quantity) * products[i].price;
    }

    cout << "\n总销售额: $" << totalSales << endl;
}

// 货币统计
void showCurrencyStats(Currency *money) {
    cout << "\n===== 货币统计 =====\n";
    int totalMoney = 0;
    for (int i = 0; i < 4; i++) {
        cout << "$" << money[i].denomination << " 钞票: " << money[i].quantity << endl;
        totalMoney += money[i].denomination * money[i].quantity;
    }
    cout << "\n货币总额: $" << totalMoney << endl;
}

// 选择产品及数量
void sellProduct(Product products[], int numProducts, Currency *money) {
    int productCode, quantity;
    cout << "\n输入产品代码: ";
    cin >> productCode;
    cout << "输入要购买的数量: ";
    cin >> quantity;

    float totalCost = quantity * products[productCode - 1].price;
    cout << "\n共计消费: $" << totalCost << endl;

    int amountPaid = 0;
    do {
        int denomination;
        cout << "输入硬币/钞票面额: ";
        cin >> denomination;

        if (denomination == 0) {
            break;
        }

        int quantityPaid;
        cout << "输入数量: ";
        cin >> quantityPaid;

        amountPaid += denomination * quantityPaid;

        for (int i = 0; i < 4; i++) {
            if (money[i].denomination == denomination) {
                money[i].quantity += quantityPaid;
            }
        }
    } while (amountPaid < totalCost);

    if (amountPaid >= totalCost) {
        // 更新商品库存
        products[productCode - 1].stock_quantity -= quantity;
        products[productCode - 1].total_quantity += quantity;

        // 计算并退还金额
        int change = amountPaid - totalCost;
        cout << "\n退还金额: $" << change << endl;
        cout << "交易成功！" << endl;
    }
    else {
        cout << "资金不足。请重试." << endl;
    }
}

// 重置机器
void resetMachine(Product products[], int numProducts, Currency *money) {
    cout << "\n===== 重置自动售货机 =====\n";

    // 重置商品数量
    for (int i = 0; i < numProducts; i++) {
        products[i].stock_quantity = products[i].total_quantity;
    }

    // 重置货币数量
    for (int i = 0; i < 4; i++) {
        money[i].quantity = 0;
    }

    cout << "自动售货机已重置.\n";
}

// 显示商品信息
void displayInfo(Water& water, Biscuit& biscuit) {
    cout << "\n===== 商品信息 =====\n";
    water.displayInfo();
    biscuit.displayInfo();
}
