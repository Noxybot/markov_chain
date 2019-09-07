
#include <QMetaType>
#include <QtTest>
#include "../program/Markov_chain.h"
#include <string>
#include <vector>
#include <QString>
#include <QVector>
#include <algorithm>
#include <iostream>

std::vector<std::string> cast_vector(const QVector<QString> &vec)
{
    std::vector<std::string> res(vec.size());
    std::transform(vec.begin(), vec.end(), res.begin(), [](QString str) {return str.toStdString();});
    return res;
}
QVector<QString> cast_vector(const std::vector<std::string> &vec)
{
    QVector<QString> res(vec.size());
    std::transform(vec.begin(), vec.end(), res.begin(), [](std::string str) {return QString(str.c_str());});
    return res;
}


char *toString(const QVector<QString> & vec)
{
    QString res;
    for (const auto &elem : vec) {
        res.append(elem);
        res.append(" ");
    }

    return QTest::toString(res);
}




class Test_Markov_chain : public QObject
{
Q_OBJECT
private slots:
    void split_string_data();
    void split_string();
};



void Test_Markov_chain::split_string_data()
{
    QTest::addColumn<QString>("Input_string");
    QTest::addColumn<QVector<QString>>("Result");
    QTest::newRow("split_test_1") << "Hello! How are you?"
                                  << QVector<QString>({"Hello", "!", "How", "are", "you", "?"});
    QTest::newRow("split_test_2") << "Hello!!! How are you???"
                                  << QVector<QString>({"Hello", "!", "How", "are", "you", "?"});
}

void Test_Markov_chain::split_string()
{
    QFETCH(QString, Input_string);
    QFETCH(QVector<QString>, Result);
    QCOMPARE(cast_vector(Markov_chain::Split_string(Input_string.toStdString())), Result);
    //QVERIFY(shit == (std::vector<std::string>)res);
}

QTEST_MAIN(Test_Markov_chain)
#include "main.moc"
