#pragma once
#include <vector>
#include "MemoryNode.h"

class Directory : public MemoryNode {

public:


    Directory() {
        // Ŀ¼
        this->type = 'd';
    }

    // Ŀ¼�ڵ�������ڵ�
    vector<MemoryNode> subNode;

public:

    // ����Ŀ¼
    int makeDirectory(string options, vector<string> params) override;

    int touch(string options, vector<string> params) override;

    // ɾ��Ŀ¼ ǰ����Ϊ�� rmdir
    bool removeDirectory();

    // �г�Ŀ¼������ļ�
    void list(string options, vector<string> params) override;

    // ��ǰĿ¼�����Ŀ¼�ĸ���
    int numberOfSubDirNode();

    // ��ǰĿ¼������ļ�����
    int numberOfFileNode();

};
