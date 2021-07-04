#include <string>
#include <algorithm>

#include "FileSystem.h"

// ��ʼ��
void FileSystem::init() {
    // ��ʼ���û���������
    this->user = User("root", "333", 0);
    // ��·��Ϊ /
    this->currentPath = "/";
    // �����µĸ�ָ��
    this->root = new Directory();
    // ��ǰ�ڵ�˫�˶���
    this->currentNode.push_back(this->root);
}

bool FileSystem::login() {
    this->commendLine();
    cout << "�������û���: ";
    string userName;
    cin >> userName;
    cout << "����������: ";
    string userPwd;
    cin >> userPwd;
    cin.get();
    if ("root" == userName && "333" == userPwd)
        this->commendLine();
    else {
        cout << "�û�����������󣬵�¼ʧ��" << endl;
        cout << "�����˳�" << endl;
        return false;
    }
}

void FileSystem::commendLine() {

    string command;

    while (true) {
        cout << "[" + this->user.userName + "@localhost " + currentPath + "] # ";
        // ����������
        getline(cin, command);
        if ("exit" == command) {
            // �����˳�
            cout << "Bye";
            break;
        }
        if (-1 == execute(command)) {
            cout << "ERROR!" << endl;
        }
    }
}

// ���������
int FileSystem::execute(string command) {

    /**
     * ���� = ָ�� + ѡ�� + ����
     * ָ�� - ��һ��string�洢
     * ѡ�� - �����ñ����ķ�ʽ����Ϊ���ࣩ
     * ���� - ��vector����Ϊ�����кܶ����
     */
     // ָ��
    string instruction;
    // ��ʱ����ѡ��
    string options;
    // ����
    vector<string> params;

    int flag = 0; // ��û�з��ֿո���������ˣ����ǵڼ����ˣ�
    int lastIdx = 0; // ��һ���ո��λ��

    // �ַ�������ϴӦ����������У�����ж���Ŀո�������ȥ��


    // ɨһ���ַ�������ȡָ�ѡ��Ͳ���
    for (int i = 0; i < command.length(); i++) {
        if (command[i] == ' ') {
            // ���ֿո�
            if (!flag) {
                // ��һ�η��ֿո񣬽�ȡinstruction
                instruction = command.substr(0, i);
                flag++;
                lastIdx = ++i;
            }
            else {
                if (command[lastIdx] == '-') {
                    // ˵����ѡ��
                    lastIdx += 1;
                    options += command.substr(lastIdx, i - lastIdx);
                }
                else {
                    params.push_back(command.substr(lastIdx, i - lastIdx));
                }
                lastIdx = ++i;
            }
        }
    }
    // ˢ��һ��û�з��ֿո���ָ����� ����
    if (!flag) {
        instruction = command;
    }
    else {
        // ����пո����Ȼ���������һ���ո�֮���ѡ����߲���
        // ��ʱ��Ҫ�������н�ȡ���ж�
        if (command[lastIdx] == '-') {
            options += command.substr(++lastIdx, command.length() - lastIdx);
        }
        else {
            params.push_back(command.substr(lastIdx, command.length() - lastIdx));
        }
    }

    // ���ˣ�ָ�ѡ��������Ѿ������ȡ
    // ��ָ����������
    string newOption = ""; newOption += options[0];
    sort(options.begin(), options.end());
    // ָ����ϴ����ͬ����ĸȥ��
    if (options.length() != 1) {
        for (int i = 1; i < options.length(); ++i) {
            if (options[i] != options[i - 1]) {
                newOption += options[i];
            }
        }
    }
    options = newOption;
    // ��ϴ��ɣ�����ָ��ַ���
    return commandDispatcher(instruction, options, params);
}


int FileSystem::commandDispatcher(string instruction, string options, vector<string> parameters) {

    if ("ls" == instruction) {
        if (this->currentNode.back()->type != 'd') return -1;
        else this->currentNode.back()->list(options, parameters);
    }
    else if ("mkdir" == instruction) {
        if (parameters.size() != 1) return -1;
        if (parameters[0][0] == '/') return this->root->makeDirectory(options, parameters);
        else return this->currentNode.back()->makeDirectory(options, parameters);
    }
    else if ("cd" == instruction) {
        if (options != "" || parameters.size() != 1) return -1;
        if (instruction == "." || instruction == "./") return 0;
        else return this->changeDirectory(options, parameters);
    }
    else if ("touch" == instruction) {
        if (parameters.size() != 1) return -1;
        if (parameters[0][0] == '/') return this->root->touch(options, parameters);
        else return this->currentNode.back()->touch(options, parameters);
    }
    else if ("rmdir" == instruction) {

    }
    else if ("rm" == instruction) {

    }
    else if ("tree" == instruction) {

    }
    else if ("find" == instruction) {

    }
    else if ("pwd" == instruction) {
        cout << currentPath << endl;
    }
}


int FileSystem::changeDirectory(string options, vector<string> parameters) {

    /**
     * .
     * ..
     * ./usr/dir/die2
     * /asd/we/qwe/ert/sdf/
     */


}
