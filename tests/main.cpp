#include <QtTest>
#include "../program/Markov_chain.h"
#include <string>
#include <vector>
class Test_Markov_chain : public QObject
{
    Q_OBJECT
private slots:
    void split_string_data();
    void split_string();
};



void Test_Markov_chain::split_string_data()
{
    QTest::addColumn<std::string>("Input string");
    QTest::addColumn<std::vector<std::string>>("Result");
    QTest::newRow("split_test_1") << "Hello! How are you?"
                                  << std::vector<std::string>({"Hello", "!", "How", "are", "you", "&"});
}

QTEST_MAIN(Test_Markov_chain)
#include "test.moc"
