#include "XMLreader.h"

int main() {
  XMLRdr XMLDoc("boby.xml");
  int iObjCnt = XMLNode::GetObjectCnt();
  cout << "\nNumber of Node objects " << iObjCnt << endl;

  XMLNode* NodePtr = XMLDoc.GetRootNode();
  XMLNode* NodePtr2 = NodePtr->GetFirstChild();
  while (NodePtr2 != nullptr) {
    string sEname = NodePtr2->GetNodeName();
    cout << sEname.c_str();
    string sVal = NodePtr2->GetElementValue("phone");
    cout << "\tPhone\t:" << sVal.c_str() << endl;
    NodePtr2 = NodePtr->GetNextChild();
  }
  XMLDoc.ResetReading();
  XMLDoc.DeleteAll();
}
