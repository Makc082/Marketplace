#include "marketplace.h"
#include <iostream>
#include <string>
using namespace std;

// �������� ����� 
void ClearInput() {
    cin.clear(); // ������� ������� �����
	while (cin.get() != '\n'); // ������� ����� �����
}

// �������� ����� ��� ������������ 
void AllocateUserArray(User*& users, int size) {
    if (size > 0 && size < 1000000) {
        users = new User[size];
    }
    else {
        users = nullptr;
    }
}

// ��������� ����� ������������
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
// �������� ����� ��� ������ 
void AllocateProductArray(Product*& products, int size) {
    if (size > 0 && size < 1000000) {
        products = new Product[size];
    }
    else {
        products = nullptr;
    }
}

// ��������� ����� ��������
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

// ��������� ������� 
void RegisterBuyer(SystemState& state) {
    
	if (state.userCount >= state.maxUsers) {
		ExpandUserArray(state.users, state.userCount, state.maxUsers);
	}

    string username, password;
    cout << "\n����: ";
    cin >> username;
    cout << "������: ";
    cin >> password;

	state.users[state.userCount++] = { username, password }; // ������ ������ �����������
    cout << "\n** ��������� ������! **\n";
}

// ���� �������
int LoginBuyer(SystemState& state) {
    string username, password;
    cout << "\n����: ";
    cin >> username;
    cout << "������: ";
    cin >> password;

    for (int i = 0; i < state.userCount; ++i) {
        if (state.users[i].username == username && state.users[i].password == password) {
            cout << "\n** ���� �������! **\n";
            return i;
        }
    }

    cout << "\n����� ���.\n";
    return -1;
}

// ���� �������� 
bool LoginSeller() {
    string username, password;
    cout << "\n��������� - ����: ";
    cin >> username;
    cout << "������: ";
    cin >> password;

    return (username == "seller" && password == "1234");
}

// ��������� ���������� �������� 
void InitProducts(SystemState& state) {
    state.products[0] = { 0, "������������� �����-���������� Makita", 10455.0, 1, 10 };
    state.products[1] = { 1, "������������ ������ ��������� MAKITA", 6399.0, 2, 8 };
    state.products[2] = { 2, "������������� ������ MAKITA", 10590.5, 1, 5 };
    state.products[3] = { 3, "������������� ���������� Makita", 5952.0, 3, 3 };
    state.products[4] = { 4, "�������� MAKITA", 22733.0, 2, 4 };
    state.productCount = 5;
}

// ��������� ������ ������
void AddProduct(SystemState& state) {
	if (state.productCount >= state.maxProducts) {
		ExpandProductArray(state.products, state.productCount, state.maxProducts);
	}

	cin.ignore(); // ������� ����� �����
    string name;
    double price;

    cout << "����� ������: ";
	getline(cin, name); // ������� ����� ������

    cout << "ֳ��: ";
    cin >> price;

	int quantity;
	cout << "ʳ������: ";
	cin >> quantity;
    ClearInput();

    state.products[state.productCount] = { 
        state.productCount, name, price, 0, quantity
    };
    state.productCount++;

    cout << "\n** ����� ������ ������! **\n";
}

// �������� ��� ������
void ViewProducts(const SystemState& state) {
    if (state.productCount == 0) {
        cout << "���� ������.\n";
        return;
    }

    cout << "\n--- ������ ������ ---\n";
    for (int i = 0; i < state.productCount; ++i) {
        const Product& p = state.products[i];
        cout << i + 1 << ". " << p.name << " - " << p.price << " ��� (ʳ������: " << p.quantity << ")\n";
    }
}

// ������ ����� �� ������ 
void AddToCart(const SystemState& state, int* cart, int& cartSize) {

	if (cartSize >= 5) {
		cout << "����� ������������.\n";
		return;
	}
    
    ViewProducts(state); 

    int index;
    cout << "������ ����� ������: ";
    cin >> index;
	ClearInput(); // ������� ����� �����

    if (index < 1 || index > state.productCount) {
        cout << "������� ����� ������.\n";
        return;
    }

    cart[cartSize++] = index - 1;
    cout << "����� ������ �� ������.\n";
}

// �������� ������ 
void ViewCart(const SystemState& state, const int* cart, int cartSize) {
    if (cartSize == 0) {
        cout << "����� �������.\n";
        return;
    }

	double total = 0; // �������� ����
    cout << "\n--- ��� ����� ---\n";
    for (int i = 0; i < cartSize; ++i) {
		Product p = state.products[cart[i]]; // �������� ����� �� ��������
        cout << i + 1 << ". " << p.name << " - " << p.price << " ���\n";
        total += p.price;
    }
    cout << "�������� ����: " << total << " ���\n";
}
