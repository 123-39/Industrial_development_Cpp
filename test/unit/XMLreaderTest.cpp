// Trenev Ivan

#include <gtest/gtest.h>
#include "XMLreader.h"

TEST(XMLparse, check_exist) {
    XMLRdr XMLDoc("../test/unit/boby.xml");
    int iObjCnt = XMLNode::GetObjectCnt();
    EXPECT_EQ(iObjCnt, 6);
    XMLDoc.ResetReading();
    XMLDoc.DeleteAll();
}

TEST(XMLparse, check_count) {
  XMLRdr XMLDoc("../test/unit/boby.xml");

  XMLNode* NodePtr = XMLDoc.GetRootNode();
  XMLNode* NodePtr2 = NodePtr->GetFirstChild();

  std::string ResNumb[5] = {"09844400873", "000000000", "11111111", "22222222",
                            "333333333"};

  for (int i = 0; i < 5; i++) {
    string sEname = NodePtr2->GetNodeName();
    cout << sEname.c_str();

    string sVal = NodePtr2->GetElementValue("phone");
    std::cout << sVal.c_str() << std::endl;
    EXPECT_EQ(sVal, ResNumb[i]);

    NodePtr2 = NodePtr->GetNextChild();
  }

  EXPECT_EQ(NodePtr2, nullptr);

  XMLDoc.ResetReading();
  XMLDoc.DeleteAll();
}

int main(int argc, char** argv) {
  testing::InitGoogleTest();
  return RUN_ALL_TESTS();
}

