#include <stdio.h>

// 商品结构体
typedef struct {
    int code;
    char name[50];
    float price;
    int total_quantity;
    int stock_quantity;
} Product;

// 货币结构体
typedef struct {
    int denomination;
    int quantity;
} Currency;

// 函数声明
void displayMenu();
void showInventory(Product products[], int numProducts);
void sellProduct(Product products[], int numProducts, Currency *money);
void showSalesStats(Product products[], int numProducts, Currency *money);
void showCurrencyStats(Currency *money); 
void resetMachine(Product products[], int numProducts, Currency *money);

//主函数 屏幕显示选项并调用函数
int main() {
    // 商品初始化
    Product products[] = {
        {1, "Snack A", 1.5, 50, 50},
        {2, "Snack B", 2.0, 30, 30},
        //零食选项，零食种类，零食单价，零食库存
    };
    int numProducts = sizeof(products) / sizeof(products[0]);        //这段代码的作用是计算一个数组中元素的个数。首先，`sizeof(products)`返回整个数组 `products` 的字节大小。然后，`sizeof(products[0])`返回数组中第一个元素的字节大小。通过将整个数组的字节大小除以第一个元素的字节大小，可以得到数组中元素的个数。最后，将计算结果赋值给变量 `numProducts`，表示数组 `products` 中元素的个数。

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
        printf("输入选项: ");
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
                printf("退出程序\n");
                break;
            default:
                printf("操作出错，请再试一次\n");
        }

    } while (choice != 0);

    return 0;
}
//展示菜单
void displayMenu() {
    printf("1. 库存查询\n");
    printf("2. 销售查询\n");
    printf("3. 货币查询\n");
    printf("4. 销售产品\n");
    printf("5. 重置商品及货币\n");
    printf("0. 退出程序\n");
}

//显示库存
void showInventory(Product products[], int numProducts) {
    printf("\n===== 库存 =====\n");
    for (int i = 0; i < numProducts; i++) {
        printf("代码: %d, 产品名称: %s, 单价: $%.2f, 库存数量: %d\n",products[i].code, products[i].name, products[i].price, products[i].stock_quantity);
    }
}

//显示销售统计
void showSalesStats(Product products[], int numProducts, Currency *money) {
    printf("\n===== 销售统计 =====\n");
    float totalSales = 0;//初始总销售额为0
    for (int i = 0; i < numProducts; i++) {
        printf("产品类别: %s, 销售数量: %d, 销售金额: $%.2f\n",products[i].name, products[i].total_quantity - products[i].stock_quantity,
(products[i].total_quantity - products[i].stock_quantity) * products[i].price);
        totalSales += (products[i].total_quantity - products[i].stock_quantity) * products[i].price;
    }

    printf("\n总销售额: $%.2f\n", totalSales);
}

//货币统计
void showCurrencyStats(Currency *money) {
    printf("\n===== 货币统计 =====\n");
    int totalMoney = 0;
    for (int i = 0; i < 4; i++) {
        printf("$%d 钞票: %d\n", money[i].denomination, money[i].quantity);
        totalMoney += money[i].denomination * money[i].quantity;
    }
    printf("\n货币总额: $%d\n", totalMoney);
}

//选择产品及数量
void sellProduct(Product products[], int numProducts, Currency *money) {
    int productCode, quantity;
    printf("\n输入产品代码: ");
    scanf("%d", &productCode);
    printf("输入要购买的数量: ");
    scanf("%d", &quantity);
    

    float totalCost = quantity * products[productCode - 1].price;
    printf("\n共计消费: $%.2f\n", totalCost);

    int amountPaid = 0;
    do {
        int denomination;
        printf("输入硬币/钞票面额: ");
        scanf("%d", &denomination);

        if (denomination == 0) {
            break;
        }

        int quantityPaid;
        printf("输入数量: ");
        scanf("%d", &quantityPaid);

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
        printf("\n退还金额: $%d\n", change);
        printf("交易成功！\n");
    } else {
        printf("资金不足。请重试.\n");
    }
}

//重置机器
void resetMachine(Product products[], int numProducts, Currency *money) {
    printf("\n===== 重置自动售货机 =====\n");

    // 重置商品数量
    for (int i = 0; i < numProducts; i++) {
        products[i].stock_quantity = products[i].total_quantity;
    }

    // 重置货币数量
    for (int i = 0; i < 4; i++) {
        money[i].quantity = 0;
    }

    printf("自动售货机已重置.\n");
}
