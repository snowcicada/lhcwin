#include "cshengxiao.h"

CShengXiao::CShengXiao()
{
    initVariable();
}

//�������������Ф�����
int CShengXiao::getSxSeqForAge(int age)
{
    int iAge = age;
    while (iAge > 12) {
        iAge -= 12;
    }
    QMapIterator<Age, SxType> it(m_sxMap);
    while (it.hasNext()) {
        it.next();
        if (it.value() == iAge) {
            return it.key();
        }
    }
    return Sx_Shu1;
}

//������Ż�ȡ��Ф����
QString CShengXiao::getSxNameForSeq(int seq)
{
    static QString sxArr[] = {
        "��", "ţ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"
    };
    if (seq >= 1 && seq <= 12) {
        return sxArr[seq-1];
    }
    return sxArr[0];
}

//���������ȡ��Ф����
QString CShengXiao::getSxNameForAge(int age)
{
    int seq = getSxSeqForAge(age);
    return getSxNameForSeq(seq);
}

//��ȡ����
Qt::GlobalColor CShengXiao::getSxColor(int age)
{
    static const int redArr[] = {1, 2, 7, 8, 12, 13, 18, 19, 23, 24, 29, 30, 34, 35, 40, 45, 46};
    static const int blueArr[] = {3, 4, 9, 10, 14, 15, 20, 25, 26, 31, 36, 37, 41, 42, 47, 48};
    static const int greenArr[] = {5, 6, 11, 16, 17, 21, 22, 27, 28, 32, 33, 38, 39, 43, 44, 49};

    int len = sizeof(redArr)/sizeof(redArr[0]);
    for (int i = 0; i < len; i++) {
        if (age == redArr[i]) {
            return Qt::red;
        }
    }

    len = sizeof(blueArr)/sizeof(blueArr[0]);
    for (int i = 0; i < len; i++) {
        if (age == blueArr[i]) {
            return Qt::blue;
        }
    }

    len = sizeof(greenArr)/sizeof(greenArr[0]);
    for (int i = 0; i < len; i++) {
        if (age == greenArr[i]) {
            return Qt::green;
        }
    }

    return Qt::black;
}

void CShengXiao::initVariable()
{
    //��ʼ��ʮ����Ф����С����
    //�������2007�������
/*
2007:
�� ţ������ �á����� �ߡ� �� �򡢺���� ���� ��
12	11	10	9	8	7	6	5	4	3	2	1
*/
    for (int i = 1; i <= 12; i++) {
        m_sxMap.insert(i, 13-i);
    }

    //�����˼���
    int iYear = QDate::currentDate().year() - 2007;
    growYears(iYear);
}

//������n��
void CShengXiao::growYears(int year)
{
    QMapIterator<Age, SxType> it(m_sxMap);
    while (it.hasNext()) {
        it.next();
        int minAge = it.value() + year;
        if (minAge > 12) {
            minAge -= 12;
        }
        m_sxMap[it.key()] = minAge;
    }
}

//����������Ф������
void CShengXiao::printShengXiao()
{
    static const QString sxArr[] = {
        "��", "ţ", "��", "��", "��", "��", "��", "��", "��", "��", "��", "��"
    };
    QMapIterator<Age, SxType> it(m_sxMap);
    while (it.hasNext()) {
        it.next();
        qDebug() << sxArr[it.key()-1] << " -> " << it.value();
    }
    qDebug() << "\n";
}
