#pragma once

#include "MemoryNode.h"


#include "MemoryNode.h"


class File : public MemoryNode {

public:

    File() {
        // ��ͨ�ļ�
        this->type = '-';
    }


public:

    // ����ļ�����
    void content();

};



