#pragma once
#include <iostream>
#include <vector>

using namespace std;

class MemoryNode {

public:

    MemoryNode() {
        authority = "rwxr--r--";
        user = "root";

    }

public:
    // �ڵ����ͣ�d��ʾĿ¼��-��ʾ�ļ�
    char type;

    // Ȩ�� rwx ģʽ
    string authority;

    // �ļ�����, �û���
    string user;

    // ��������
    string createDate;

    // ��һ���޸�����
    string updateDate;

    // �ڵ����ƣ�Ŀ¼�������ļ�����
    string name;

    // ��һ���ڵ�
    MemoryNode* parent{};



public:

    virtual void list(string options, vector<string> params) {}
    virtual int makeDirectory(string options, vector<string> params) {}
    virtual int touch(string options, vector<string> params) {}

};
