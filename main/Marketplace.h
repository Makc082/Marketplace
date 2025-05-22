#pragma once
#include <string>

// структура користувача 
struct User {
    std::string username;
    std::string password;
};

// структура товару 
struct Product {
    int id = 0;
    std::string name;
    double price = 0.0;
    int categoryId = 0;
    int quantity = 0;
};

// структура стану системи 
struct SystemState {
    User* users;
    int userCount;
    int maxUsers;

    Product* products;
    int productCount;
    int maxProducts;
};

// прототипи функцій
void ClearInput();
void AllocateUserArray(User*&, int); // виділення пам’яті під масив користувачів
void ExpandUserArray(User*&, int&, int&); // подвоюємо масив користувачив
void AllocateProductArray(Product*&, int); // виділяємо пам’ять під масив продуктів
void ExpandProductArray(Product*&, int&, int&); // подвоюємо масив продуктів
void RegisterBuyer(SystemState&); // реєстрація покупця
int LoginBuyer(SystemState&); // вхід покупця
bool LoginSeller(); // вхід продавця
void InitProducts(SystemState&); // початкове наповнення товарами
void AddProduct(SystemState&); // додавання нового товару
void ViewProducts(const SystemState&); // перегляд усіх товарів
void AddToCart(const SystemState&, int*, int&); // додаємо товар до кошика
void ViewCart(const SystemState&, const int*, int); // перегляд кошика
