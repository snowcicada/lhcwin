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

    //根据年龄计算生肖的序号
    int getSxSeqForAge(int age);

    //根据序号获取生肖名称
    QString getSxNameForSeq(int seq);

    //根据年龄获取生肖名称
    QString getSxNameForAge(int age);

    //获取波段
    Qt::GlobalColor getSxColor(int age);

private:
    void initVariable();
    //长大了n岁
    void growYears(int year);
    //遍历所有生肖的岁数
    void printShengXiao();

    //variable
    ShengXiaoMap m_sxMap;
};

#endif // CSHENGXIAO_H
