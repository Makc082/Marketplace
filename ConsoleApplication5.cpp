#include <iostream>
#include <windows.h>
#include <string>
using namespace std;

// структура товарів
struct Product {
	int id;
	char name[50];
	float price;
	int sellerId;
	int quantity; // кількість на складі
};

// структура кошика
struct BasketItem {
	int productId;
	char name[50];
	float price;
	int sellerId;
};

// структура користувача
struct User {
	int id;
	char username[50];
	char password[50];
	BasketItem basket[50];
	int basketCount;
};

// структура зберігання стану системи
struct SystemState {
	User* users;
	int userCount;
	Product* products;
	int productCount;
};

// виділення пам’яті під масив користувачів
void AllocateUserArray(User*& users, int& size) {
	if (size > 0 && size < 1000000) {
		users = new User[size];
	}
	else {
		users = nullptr;
	}
}

// подвоюємо масив користувачів
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

// виділення пам’яті під масив продуктів
void AllocateProductArray(Product*& products, int& size) {
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

// перевірка на зайнятий логін
bool IsUsernameTaken(User*& users, int& userCount, const char* username) {
	for (int i = 0; i < userCount; i++) {
		if (strcmp(users[i].username, username) == 0) {
			return true;
		}
	}
	return false;
}

// реєстрація користувача
void RegisterUser(User*& users, int& userCount, int& size) {
	if (userCount >= size) {
		ExpandUserArray(users, userCount, size);
	}
	User newUser;
	newUser.id = userCount;
	cout << "Введіть логін: ";
	cin >> newUser.username;
	if (IsUsernameTaken(users, userCount, newUser.username)) {
		cout << "Цей логін вже зайнятий.\n";
		return;
	}
	cout << "Введіть пароль: ";
	cin >> newUser.password;
	newUser.basketCount = 0; // ініціалізація кошика
	users[userCount++] = newUser;
	cout << "Реєстрація успішна! Ваш ID: " << newUser.id << "\n";
}

// авторизація користувача
int LoginUser(User*& users, int& userCount) {
	char username[50];
	char password[50];
	cout << "Введіть логін: ";
	cin >> username;
	cout << "Введіть пароль: ";
	cin >> password;
	for (int i = 0; i < userCount; i++) {
		if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
			cout << "Авторизація успішна! Ваш ID: " << users[i].id << "\n";
			return users[i].id;
		}
	}
	cout << "Неправильний логін або пароль.\n";
	return -1;
}

// показ товару
void ShowCatalog(Product* products, int count) {
	cout << "\nКаталог товарів:\n";
	for (int i = 0; i < count; i++) {
		cout << i + 1 << ". [ID: " << products[i].id << "] "
			<< products[i].name << " — " << products[i].price << " грн"
			<< " (Продавець ID: " << products[i].sellerId << ")\n";
	}
}

// Додавання товару в кошик
void AddToBasket(User& user, SystemState& state) {
	if (user.basketCount >= 5) {
		cout << "Кошик повний!\n";
		return;
	}
	ShowCatalog(state.products, state.productCount);
	int choice;
	cout << "Оберіть товар за номером: ";
	cin >> choice;
	if (choice < 1 || choice > state.productCount) {
		cout << "Невірний вибір!\n";
		return;
	}
	const Product& selected = state.products[choice - 1];
	BasketItem& item = user.basket[user.basketCount];
	item.productId = selected.id;
	strcpy_s(item.name, sizeof(item.name), selected.name);
	item.price = selected.price;
	item.sellerId = selected.sellerId;
	user.basketCount++;
	cout << "Додано в кошик: " << selected.name << "\n";
}

// Перегляд кошика
void ShowBasket(const User& user) {
	cout << "\nВаш кошик:\n";
	if (user.basketCount == 0) {
		cout << "(порожній)\n";
		return;
	}
	for (int i = 0; i < user.basketCount; i++) {
		cout << "- " << user.basket[i].name
			<< " — " << user.basket[i].price << " грн"
			<< " (ID товару: " << user.basket[i].productId
			<< ", продавець: " << user.basket[i].sellerId << ")\n";
	}
}

// Додавання нового товару продавцем
void AddProduct(SystemState& state, int& size) {
	if (state.productCount >= size) {
		ExpandProductArray(state.products, state.productCount, size);
	}
	Product newProduct;
	newProduct.id = state.productCount;
	cout << "Назва товару: ";
	cin.ignore();
	cin.getline(newProduct.name, 50);
	cout << "Ціна товару: ";
	cin >> newProduct.price;
	cout << "Кількість на складі: ";
	cin >> newProduct.quantity;
	newProduct.sellerId = 0; // можна замінити на авторизованого продавця
	state.products[state.productCount++] = newProduct;
	cout << "Товар успішно додано!\n";
}

// Вивід усіх товарів
void ShowAllProducts(Product* products, int count) {
	cout << "\n--- Список товарів ---\n";
	for (int i = 0; i < count; ++i) {
		cout << "ID: " << products[i].id << "\n";
		cout << "Назва: " << products[i].name << "\n";
		cout << "Ціна: " << products[i].price << " грн\n";
		cout << "Кількість: " << products[i].quantity << "\n\n";
	}
}

// Кабінет продавця
void SellerDashboard(SystemState& state) {
	int choice;
	int size = 100; // Максимальна кількість товарів
	do {
		cout << "\n--- Кабінет продавця ---\n"
		     << "1. Додати товар\n"
		     << "2. Переглянути список товарів\n"
		     << "0. Вийти\n"
		     << "Ваш вибір: ";
		cin >> choice;
		switch (choice) {
		case 1:
			AddProduct(state, size);
			break;
		case 2:
			ShowAllProducts(state.products, state.productCount);
			break;
		case 0:
			cout << "Вихід із кабінету продавця...\n";
			break;
		default:
			cout << "Невірний вибір.\n";
		}
	} while (choice != 0);
}

// Меню після входу в акаунт
void UserSession(User& user, SystemState& state) {
	int Choice;
	do {
		cout << "\n1. Додати товар у кошик\n"
			 << "2. Переглянути кошик\n"
			 << "3. Вийти з акаунту\n"
			 << "Ваш вибір: ";
		cin >> Choice;
		switch (Choice) {
		case 1:
			AddToBasket(user, state);
			break;
		case 2:
			ShowBasket(user);
			break;
		case 3:
			cout << "Вихід з акаунту...\n";
			break;
		default:
			cout << "Невірний вибір.\n";
		}
	} while (Choice != 3);
}

// головне меню
void MainMenu(SystemState& state, int& size) {
	int currentUserId = -1;
	int choice;
	do {
		cout << "\n--- Маркетплейс ---\n"
		     << "1. Я покупець\n"
		     << "2. Я продавець\n"
	         << "3. Вийти\n"
		     << "Ваш вибір: ";
		cin >> choice;
		switch (choice) {
		case 1:
			int innerChoice; 
				cout << "1. Зареєструватися\n"
				     << "2. Увійти\n"
				     << "Ваш вибір : ";
			cin >> innerChoice;
			if (innerChoice == 1) {
				RegisterUser(state.users, state.userCount, size);
			}
			else if (innerChoice == 2) {
				currentUserId = LoginUser(state.users, state.userCount);
				if (currentUserId != -1) {
					UserSession(state.users[currentUserId], state);
				}
			}
			else {
				cout << "Невірний вибір.\n";
			}
			break;
		case 2:
			cout << "Вхід для продавця\n";
			// Простий вхід без перевірки даних
			SellerDashboard(state);
			break;
		case 3:
			cout << "До побачення!\n";
			break;
		default:
			cout << "Невірний вибір.\n";
		}
	} while (choice != 3);
}

int main() {
	SetConsoleOutputCP(1251); // консоль одразу україномовна
	User* users = nullptr;
	int userCount = 0;
	int sizeAr = 100;
	AllocateUserArray(users, sizeAr);

	Product* products = nullptr;
	int productCount = 5;
	AllocateProductArray(products, productCount);

	products[0] = { 0, "Акумуляторний дриль-шурупокрут Makita", 10455.0, 1, 10 };
	products[1] = { 1, "Акумуляторна кутова шліфмашина MAKITA", 6399.0, 2, 8 };
	products[2] = { 2, "Акумуляторний лобзик MAKITA", 10590.5, 1, 5 };
	products[3] = { 3, "Акумуляторний перфоратор Makita", 5952.0, 3, 3 };
	products[4] = { 4, "Штроборіз MAKITA", 22733.0, 2, 4 };

	SystemState state{ users, userCount, products, productCount };

	MainMenu(state, sizeAr);

	delete[] state.users;
	delete[] state.products;
	return 0;
}
