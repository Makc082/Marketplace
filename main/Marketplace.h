#pragma once
#include <string>

// ��������� ����������� 
struct User {
    std::string username;
    std::string password;
};

// ��������� ������ 
struct Product {
    int id = 0;
    std::string name;
    double price = 0.0;
    int categoryId = 0;
    int quantity = 0;
};

// ��������� ����� ������� 
struct SystemState {
    User* users;
    int userCount;
    int maxUsers;

    Product* products;
    int productCount;
    int maxProducts;
};

// ��������� �������
void ClearInput();
void AllocateUserArray(User*&, int); // �������� ����� �� ����� ������������
void ExpandUserArray(User*&, int&, int&); // ��������� ����� ������������
void AllocateProductArray(Product*&, int); // �������� ������ �� ����� ��������
void ExpandProductArray(Product*&, int&, int&); // ��������� ����� ��������
void RegisterBuyer(SystemState&); // ��������� �������
int LoginBuyer(SystemState&); // ���� �������
bool LoginSeller(); // ���� ��������
void InitProducts(SystemState&); // ��������� ���������� ��������
void AddProduct(SystemState&); // ��������� ������ ������
void ViewProducts(const SystemState&); // �������� ��� ������
void AddToCart(const SystemState&, int*, int&); // ������ ����� �� ������
void ViewCart(const SystemState&, const int*, int); // �������� ������
