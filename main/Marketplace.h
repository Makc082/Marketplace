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

// прототипи функц≥й
void ClearInput();
void AllocateUserArray(User*&, int); // вид≥ленн€ памТ€т≥ п≥д масив користувач≥в
void ExpandUserArray(User*&, int&, int&); // подвоюЇмо масив користувачив
void AllocateProductArray(Product*&, int); // вид≥л€Їмо памТ€ть п≥д масив продукт≥в
void ExpandProductArray(Product*&, int&, int&); // подвоюЇмо масив продукт≥в
void RegisterBuyer(SystemState&); // реЇстрац≥€ покупц€
int LoginBuyer(SystemState&); // вх≥д покупц€
bool LoginSeller(); // вх≥д продавц€
void InitProducts(SystemState&); // початкове наповненн€ товарами
void AddProduct(SystemState&); // додаванн€ нового товару
void ViewProducts(const SystemState&); // перегл€д ус≥х товар≥в
void AddToCart(const SystemState&, int*, int&); // додаЇмо товар до кошика
void ViewCart(const SystemState&, const int*, int); // перегл€д кошика
