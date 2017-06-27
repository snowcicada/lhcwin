#ifndef CSHENGXIAO_H
#define CSHENGXIAO_H

#include <QtCore>

typedef int Age;
typedef int SxType;
typedef QMap<Age, SxType> ShengXiaoMap;

class CShengXiao
{
public:
    static const int Sx_Shu1    = 1;
    static const int Sx_Niu2    = 2;
    static const int Sx_Hu3     = 3;
    static const int Sx_Tu4     = 4;
    static const int Sx_Long5   = 5;
    static const int Sx_She6    = 6;
    static const int Sx_Ma7     = 7;
    static const int Sx_Yang8   = 8;
    static const int Sx_Hou9    = 9;
    static const int Sx_Ji10    = 10;
    static const int Sx_Gou11   = 11;
    static const int Sx_Zhu12   = 12;

public:
    CShengXiao();

    //�������������Ф�����
    int getSxSeqForAge(int age);

    //������Ż�ȡ��Ф����
    QString getSxNameForSeq(int seq);

    //���������ȡ��Ф����
    QString getSxNameForAge(int age);

    //��ȡ����
    Qt::GlobalColor getSxColor(int age);

private:
    void initVariable();
    //������n��
    void growYears(int year);
    //����������Ф������
    void printShengXiao();

    //variable
    ShengXiaoMap m_sxMap;
};

#endif // CSHENGXIAO_H
