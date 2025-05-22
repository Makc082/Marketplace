#include <iostream>
#include <windows.h>
#include "marketplace.h"
using namespace std;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251); 

	int initialUserSize = 10; // початковий розмір масиву користувачів
	int initialProductSize = 50; // початковий розмір масиву товарів
	const int maxCartSize = 5; // максимальний розмір кошика

    User* users;
    Product* products;
    AllocateUserArray(users, initialUserSize);
    AllocateProductArray(products, initialProductSize);

	SystemState state{ users, 0, initialUserSize, products, 0, initialProductSize }; // ініціалізація стану системи
    InitProducts(state); // Початкові товари

    int cart[maxCartSize]; 
    int cartSize = 0; 

	// вибір ролі
    while (true) {
        cout << "\n[1] Покупець\n[2] Продавець\n[0] Вихід\n\nВаш вибір: ";
        int choice;
        cin >> choice;
        ClearInput();

		// реєстрація або вхід
        if (choice == 1) {
            while (true) {
                cout << "\n[1] Зареєструватися\n[2] Увійти\n[0] Назад\n\nВаш вибір: ";
                int bChoice;
                cin >> bChoice;
                ClearInput();

				// вибір дій покупця
                if (bChoice == 1) RegisterBuyer(state);
                else if (bChoice == 2) {
                    int index = LoginBuyer(state);
                    if (index != -1) {
                        while (true) {
                            cout << "\n[1] Переглянути товари\n[2] Додати до кошика\n[3] Переглянути кошик\n[0] Вихід\n\nВаш вибір: ";
                            int act;
                            cin >> act;
                            ClearInput();

                            if (act == 1) ViewProducts(state); 
                            else if (act == 2) AddToCart(state, cart, cartSize);
                            else if (act == 3) ViewCart(state, cart, cartSize);
                            else if (act == 0) break;
                        }
                    }
                }
                else if (bChoice == 0) break;
            }

        }
		// вхід та вибор дій продавця
        else if (choice == 2) {
            if (LoginSeller()) {
                while (true) {
                    cout << "\n[1] Додати товар\n[2] Переглянути товари\n[0] Вихід\n\nВаш вибір: ";
                    int sChoice;
                    cin >> sChoice;
                    ClearInput();

                    if (sChoice == 1) AddProduct(state);
                    else if (sChoice == 2) ViewProducts(state);
                    else if (sChoice == 0) break;
                }
            }
            else {
                cout << "\n** Невірні дані продавця **\n";
            }

        }
        else if (choice == 0) break;
        else cout << "\n** Невірний вибір. **\n";
    }

    delete[] users;
    delete[] products;

    return 0;
}
