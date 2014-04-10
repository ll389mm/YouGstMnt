//#include <QtCore/QString>
#include <QtTest/QtTest>
//#include <QtCore/QCoreApplication>

#include <iostream>
#include "label.h"
#include "labelmanager.h"
#include "configuration.h"
#include "configuration.h"
#include "implementationmanager.h"

class UnitTestTest : public QObject
{
    Q_OBJECT
    
public:
    UnitTestTest();
    
private Q_SLOTS:
    void initTestCase();
    void cleanupTestCase();

    void testClass_Label();
    void testClass_AbstractLabelManager();
    void testClass_Configuration();
    void testClass_AbstractConfigurationManager();
    void test();


//    void testCase1();
//    void testCase1_data();
};

UnitTestTest::UnitTestTest() {}

void UnitTestTest::initTestCase() {}

void UnitTestTest::cleanupTestCase() {}

void UnitTestTest::testClass_Label() {
    Label la("chair", "/home/lionel/");
    std::cout << la.getName() << '\t' <<
                 la.getImageDirectory() << '\t' <<
                 std::endl;
    la.setImageDirectory(std::string("/root/"));
    std::cout << la.getImageDirectory() << std::endl;
    Label laa = la;
    std::cout << laa.getName() << '\t' <<
                 laa.getImageDirectory() << '\t' <<
                 std::endl;
}

void UnitTestTest::testClass_AbstractLabelManager() {
//    ImplementationManager *im = ImplementationManager::getInstance();
//    LabelManager *m = new LabelManager;
//    std::cout << "initial label count: " << m->labelCount() << std::endl;
//    Label l1("chair"), l2("desk"), l3("computer", "my PC"), l4("door");
//    m->addLabel(l1); m->addLabel(l2); m->addLabel(l3); m->addLabel(l4);
//    m->addLabel(Label("desk", "my desk hi"));
//    std::cout << "initial labels' names: " << l1.getName() << ", " <<
//                 l2.getName() << ", " << l3.getName() << ", " <<
//                 l4.getName() << ", " << std::endl;
//    std::cout << "label count: " << m->labelCount() << std::endl;
//    std::cout << "label name " << l3.getName() << std::endl;
//    m->deleteLabelByName(l1.getName());
//    m->deleteLabelByName("newyork");
//    int n = m->labelCount();
//    std::vector<Label> ls;
//    int num = m->copyAllLabels(ls, n);
//    std::cout << "after delete and copy, the label number is: " << num <<
//                 "\nthey are: ";
//    for (int i = 0; i < num; i++) {
//        std::cout << ls[i].getName() << ", ";
//    }
//    std::cout << std::endl;
//    LabelManager *mm = new LabelManager;
//    std::cout << "after get default manager again, label count: " <<
//                 mm->labelCount() << std::endl;
//    ImplementationManager *imm = ImplementationManager::getInstance();
//    imm->releaseImplementation("AbstractLabelManager");
}

void UnitTestTest::testClass_Configuration() {
    Configuration conf("igpr.seeingeye");
    conf.set(std::string("chen"), std::string("yucong"));
    conf.set(std::string("guo"), std::string("jin"));
    conf.set(std::string("huang"), std::string("rong"));
    std::cout << "domain name: " << conf.getDomain() << std::endl;
    std::cout << "key chen's value is: " << conf.get("chen") << std::endl;
    conf.set("chen", "youliang");
    std::cout << "after reset, key chen's value is: " <<
                 conf.get("chen") << std::endl;
    std::cout << "key how's value: " << conf.get("how") << std::endl;
    Configuration conff(conf);
    std::cout << "after copy: " << conff.getDomain() << conff.get("chen") <<
                 ", " << conff.get("guo") << ", " <<
                 conff.get("huang") << std::endl;
    Configuration confff;
    confff.load(conff);
    std::cout << "after load: " << confff.getDomain() << confff.get("chen") <<
                 ", " << confff.get("guo") << ", " <<
                 confff.get("huang") << std::endl;
}

//void UnitTestTest::testClass_AbstractConfigurationManager() {
//    ImplementationManager *im = ImplementationManager::getInstance();
//    //AbstractConfigurationManager *lm = (AbstractConfigurationManager*)im->getImplementation("AbstractConfigurationManager");
//    std::cout << "domain count: " << lm->domainCount() << std::endl;
//    Configuration conf1("igpr.seeingeye");
//    conf1.set(std::string("chen"), std::string("yucong"));
//    conf1.set(std::string("guo"), std::string("jin"));
//    conf1.set(std::string("huang"), std::string("rong"));
//    lm->addConfiguration(conf1);
//    std::cout << "domain count: " << lm->domainCount() << std::endl;
//    Configuration conf2("igpr.seeingeye.ustb");
//    conf2.set(std::string("chen"), std::string("yucong"));
//    conf2.set(std::string("guo"), std::string("jin"));
//    conf2.set(std::string("huang"), std::string("rong"));
//    lm->addConfiguration(conf2);
//    std::cout << "domain count: " << lm->domainCount() << std::endl;
//    std::cout << lm->getConfigurationByDomainName("igpr.seeingeye")->
//                 get("huang") << std::endl;
//    im->releaseImplementation("AbstractConfigurationManager");
//}

void UnitTestTest::test() {
//    ImplementationManager *im = ImplementationManager::getInstance();
//    LabelManager *lm = new LabelManager;
////    AbstractConfigurationManager *cm =
////            (AbstractConfigurationManager*)im->getImplementation("AbstractConfigurationManager");
//    std::cout << im << std::endl;
//    std::cout << im << std::endl;
}



//void UnitTestTest::testCase1()
//{
//    QFETCH(QString, data);
//    QVERIFY2(true, "Failure");
//}

//void UnitTestTest::testCase1_data()
//{
//    QTest::addColumn<QString>("data");
//    QTest::newRow("0") << QString();
//}


QTEST_MAIN(UnitTestTest)

#include "tst_unittesttest.moc"
