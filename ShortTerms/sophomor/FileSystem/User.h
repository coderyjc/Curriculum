#pragma once
class User {
public:

    User() {}

    User(string userName, string passwd, int role) : userName(std::move(userName)), passwd(std::move(passwd)), role(role) {}

public:
    // �û���
    string userName;

    // ����
    string passwd;

    // Ȩ��
    int role;

};
