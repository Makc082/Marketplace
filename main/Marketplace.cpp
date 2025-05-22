#include "marketplace.h"
#include <iostream>
#include <string>
using namespace std;

// очищення вводу 
void ClearInput() {
    cin.clear(); // скидаємо помилки вводу
	while (cin.get() != '\n'); // чистемо буфер вводу
}

// виділення пам’яті для користувачів 
void AllocateUserArray(User*& users, int size) {
    if (size > 0 && size < 1000000) {
        users = new User[size];
    }
    else {
        users = nullptr;
    }
}

// подвоюємо масив користувачив
void ExpandUserArray(User*& users, int& oldSize, int& size) {
    int newSize = size * 2;
    User* newUsers = new User[newSize];

    for (int i = 0; i < oldSize; i++) {
        newUsers[i] = users[i];
    }

    delete[] users;
    users = newUsers;
    size = newSize;

}
// виділення пам’яті для товарів 
void AllocateProductArray(Product*& products, int size) {
    if (size > 0 && size < 1000000) {
        products = new Product[size];
    }
    else {
        products = nullptr;
    }
}

// подвоюємо масив продуктів
void ExpandProductArray(Product*& products, int& oldSize, int& size) {
    int newSize = size * 2;
    Product* newProducts = new Product[newSize];
    for (int i = 0; i < oldSize; i++) {
        newProducts[i] = products[i];
    }
    delete[] products;
    products = newProducts;
    size = newSize;
}

// реєстрація покупця 
void RegisterBuyer(SystemState& state) {
    
	if (state.userCount >= state.maxUsers) {
		ExpandUserArray(state.users, state.userCount, state.maxUsers);
	}

    string username, password;
    cout << "\nЛогін: ";
    cin >> username;
    cout << "Пароль: ";
    cin >> password;

	state.users[state.userCount++] = { username, password }; // додаємо нового користувача
    cout << "\n** Реєстрація успішна! **\n";
}

// вхід покупця
int LoginBuyer(SystemState& state) {
    string username, password;
    cout << "\nЛогін: ";
    cin >> username;
    cout << "Пароль: ";
    cin >> password;

    for (int i = 0; i < state.userCount; ++i) {
        if (state.users[i].username == username && state.users[i].password == password) {
            cout << "\n** Вхід успішний! **\n";
            return i;
        }
    }

    cout << "\nНевірні дані.\n";
    return -1;
}

// вхід продавця 
bool LoginSeller() {
    string username, password;
    cout << "\nПродавець - логін: ";
    cin >> username;
    cout << "Пароль: ";
    cin >> password;

    return (username == "seller" && password == "1234");
}

// початкове наповнення товарами 
void InitProducts(SystemState& state) {
    state.products[0] = { 0, "Акумуляторний дриль-шурупокрут Makita", 10455.0, 1, 10 };
    state.products[1] = { 1, "Акумуляторна кутова шліфмашина MAKITA", 6399.0, 2, 8 };
    state.products[2] = { 2, "Акумуляторний лобзик MAKITA", 10590.5, 1, 5 };
    state.products[3] = { 3, "Акумуляторний перфоратор Makita", 5952.0, 3, 3 };
    state.products[4] = { 4, "Штроборіз MAKITA", 22733.0, 2, 4 };
    state.productCount = 5;
}

// додавання нового товару
void AddProduct(SystemState& state) {
	if (state.productCount >= state.maxProducts) {
		ExpandProductArray(state.products, state.productCount, state.maxProducts);
	}

	cin.ignore(); // очищуємо буфер вводу
    string name;
    double price;

    cout << "Назва товару: ";
	getline(cin, name); // зчитуємо назву товару

    cout << "Ціна: ";
    cin >> price;

	int quantity;
	cout << "Кількість: ";
	cin >> quantity;
    ClearInput();

    state.products[state.productCount] = { 
        state.productCount, name, price, 0, quantity
    };
    state.productCount++;

    cout << "\n** Товар додано успішно! **\n";
}

// перегляд усіх товарів
void ViewProducts(const SystemState& state) {
    if (state.productCount == 0) {
        cout << "Немає товарів.\n";
        return;
    }

    cout << "\n--- Список товарів ---\n";
    for (int i = 0; i < state.productCount; ++i) {
        const Product& p = state.products[i];
        cout << i + 1 << ". " << p.name << " - " << p.price << " грн (Кількість: " << p.quantity << ")\n";
    }
}

// додаємо товар до кошика 
void AddToCart(const SystemState& state, int* cart, int& cartSize) {

	if (cartSize >= 5) {
		cout << "Кошик переповнений.\n";
		return;
	}
    
    ViewProducts(state); 

    int index;
    cout << "Введіть номер товару: ";
    cin >> index;
	ClearInput(); // очищуємо буфер вводу

    if (index < 1 || index > state.productCount) {
        cout << "Невірний номер товару.\n";
        return;
    }

    cart[cartSize++] = index - 1;
    cout << "Товар додано до кошика.\n";
}

// перегляд кошика 
void ViewCart(const SystemState& state, const int* cart, int cartSize) {
    if (cartSize == 0) {
        cout << "Кошик порожній.\n";
        return;
    }

	double total = 0; // загальна сума
    cout << "\n--- Ваш кошик ---\n";
    for (int i = 0; i < cartSize; ++i) {
		Product p = state.products[cart[i]]; // отримуємо товар за індексом
        cout << i + 1 << ". " << p.name << " - " << p.price << " грн\n";
        total += p.price;
    }
    cout << "Загальна сума: " << total << " грн\n";
}
