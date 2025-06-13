#include <iostream>
#include <string>
#include <chrono>
#include "vector1_2.h"

// ���ڲ����ƶ��������
class MoveTestClass
{
private:
    static int copy_count;
    static int move_count;
    static int construction_count;
    std::string data;
    int id;

public:
    // ���캯��
    MoveTestClass(int value = 0) : id(value), data("data_" + std::to_string(value))
    {
        ++construction_count;
        std::cout << "���� MoveTestClass(" << id << "), �ܹ������: " << construction_count << std::endl;
    }

    // �������캯��
    MoveTestClass(const MoveTestClass& other) : id(other.id), data(other.data)
    {
        ++copy_count;
        ++construction_count;
        std::cout << "�������� MoveTestClass(" << id << "), ��������: " << copy_count << std::endl;
    }

    // �ƶ����캯�� (C++11)
    MoveTestClass(MoveTestClass&& other) noexcept : id(other.id), data(std::move(other.data))
    {
        ++move_count;
        ++construction_count;
        other.id = -1;  // ���Ϊ���ƶ�
        std::cout << "�ƶ����� MoveTestClass(" << id << "), �ƶ�����: " << move_count << std::endl;
    }

    // ������ֵ������
    MoveTestClass& operator=(const MoveTestClass& other)
    {
        if (this != &other)
        {
            id = other.id;
            data = other.data;
            ++copy_count;
            std::cout << "������ֵ MoveTestClass(" << id << "), ��������: " << copy_count << std::endl;
        }
        return *this;
    }

    // �ƶ���ֵ������ (C++11)
    MoveTestClass& operator=(MoveTestClass&& other) noexcept
    {
        if (this != &other)
        {
            id = other.id;
            data = std::move(other.data);
            other.id = -1;  // ���Ϊ���ƶ�
            ++move_count;
            std::cout << "�ƶ���ֵ MoveTestClass(" << id << "), �ƶ�����: " << move_count << std::endl;
        }
        return *this;
    }

    ~MoveTestClass()
    {
        std::cout << "���� MoveTestClass(" << id << ")" << std::endl;
    }

    int getId() const { return id; }
    const std::string& getData() const { return data; }

    static void resetCounters()
    {
        copy_count = 0;
        move_count = 0;
        construction_count = 0;
    }

    static void printStats()
    {
        std::cout << "=== ͳ����Ϣ ===" << std::endl;
        std::cout << "�ܹ������: " << construction_count << std::endl;
        std::cout << "��������: " << copy_count << std::endl;
        std::cout << "�ƶ�����: " << move_count << std::endl;
        std::cout << "=================" << std::endl;
    }
};

int MoveTestClass::copy_count = 0;
int MoveTestClass::move_count = 0;
int MoveTestClass::construction_count = 0;

// �����ƶ����캯��
void testMoveConstructor()
{
    std::cout << "\n=== �����ƶ����캯�� ===\n";

    MoveTestClass::resetCounters();

    // ����Դ����
    vector<MoveTestClass> source;
    source.push_back(MoveTestClass(1));
    source.push_back(MoveTestClass(2));
    source.push_back(MoveTestClass(3));

    std::cout << "\n����Դ������ɣ�size = " << source.getSize() << std::endl;
    MoveTestClass::printStats();

    // �ƶ�����
    std::cout << "\nִ���ƶ�����...\n";
    vector<MoveTestClass> target(std::move(source));

    std::cout << "\n�ƶ��������:" << std::endl;
    std::cout << "Ŀ������ size = " << target.getSize() << std::endl;
    std::cout << "Դ���� size = " << source.getSize() << " (Ӧ��Ϊ0)" << std::endl;

    MoveTestClass::printStats();
}

// �����ƶ���ֵ������
void testMoveAssignment()
{
    std::cout << "\n=== �����ƶ���ֵ������ ===\n";

    MoveTestClass::resetCounters();

    // ����Ŀ������
    vector<MoveTestClass> target;
    target.push_back(MoveTestClass(10));
    target.push_back(MoveTestClass(20));

    // ����Դ����
    vector<MoveTestClass> source;
    source.push_back(MoveTestClass(1));
    source.push_back(MoveTestClass(2));
    source.push_back(MoveTestClass(3));

    std::cout << "\n��ֵǰ:" << std::endl;
    std::cout << "Ŀ������ size = " << target.getSize() << std::endl;
    std::cout << "Դ���� size = " << source.getSize() << std::endl;

    // �ƶ���ֵ
    std::cout << "\nִ���ƶ���ֵ...\n";
    target = std::move(source);

    std::cout << "\n�ƶ���ֵ���:" << std::endl;
    std::cout << "Ŀ������ size = " << target.getSize() << std::endl;
    std::cout << "Դ���� size = " << source.getSize() << " (Ӧ��Ϊ0)" << std::endl;

    MoveTestClass::printStats();
}

// �����ƶ��汾�� push_back
void testMovePushBack()
{
    std::cout << "\n=== �����ƶ��汾�� push_back ===\n";

    MoveTestClass::resetCounters();

    vector<MoveTestClass> v;

    std::cout << "\n���Կ����汾�� push_back:\n";
    MoveTestClass obj1(100);
    v.push_back(obj1);  // �����汾

    std::cout << "\n�����ƶ��汾�� push_back:\n";
    v.push_back(MoveTestClass(200));  // �ƶ��汾����ʱ����

    std::cout << "\n������ʽ�ƶ��� push_back:\n";
    MoveTestClass obj3(300);
    v.push_back(std::move(obj3));  // ��ʽ�ƶ�

    std::cout << "\n������С: " << v.getSize() << std::endl;
    MoveTestClass::printStats();
}

// �����ƶ��汾�� insert
void testMoveInsert()
{
    std::cout << "\n=== �����ƶ��汾�� insert ===\n";

    MoveTestClass::resetCounters();

    vector<MoveTestClass> v;
    v.push_back(MoveTestClass(1));
    v.push_back(MoveTestClass(3));

    std::cout << "\n��ʼ�����������, size = " << v.getSize() << std::endl;

    std::cout << "\n���Կ����汾�� insert:\n";
    MoveTestClass obj2(20);
    v.insert(1, obj2);  // ��λ��1���룬�����汾

    std::cout << "\n�����ƶ��汾�� insert:\n";
    v.insert(1, MoveTestClass(10));  // ��λ��1���룬�ƶ��汾

    std::cout << "\n������С: " << v.getSize() << std::endl;
    MoveTestClass::printStats();
}

// ���ܶԱȲ���
void performanceComparison()
{
    std::cout << "\n=== ���ܶԱȲ��� ===\n";

    const int N = 1000;

    // ���Կ�������
    {
        MoveTestClass::resetCounters();
        auto start = std::chrono::high_resolution_clock::now();

        vector<MoveTestClass> v;
        for (int i = 0; i < N; ++i)
        {
            MoveTestClass obj(i);
            v.push_back(obj);  // �����汾
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "�����汾 - ʱ��: " << duration.count() << " ΢��\n";
        MoveTestClass::printStats();
    }

    // �����ƶ�����
    {
        MoveTestClass::resetCounters();
        auto start = std::chrono::high_resolution_clock::now();

        vector<MoveTestClass> v;
        for (int i = 0; i < N; ++i)
        {
            v.push_back(MoveTestClass(i));  // �ƶ��汾����ʱ����
        }

        auto end = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

        std::cout << "�ƶ��汾 - ʱ��: " << duration.count() << " ΢��\n";
        MoveTestClass::printStats();
    }
}

int main()
{
    try
    {
        testMoveConstructor();
        testMoveAssignment();
        testMovePushBack();
        testMoveInsert();
        performanceComparison();

        std::cout << "\n=== �����ƶ����������� ===\n";
    }
    catch (const std::exception& e)
    {
        std::cout << "�����쳣��ֹ: " << e.what() << std::endl;
    }

    return 0;
}