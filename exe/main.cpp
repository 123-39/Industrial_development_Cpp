#include "XMLreader.h"

int main(int argc, char *argv[]) {
  string filename = argv[2];
  XMLRdr XMLDoc(filename);
  int iObjCnt = XMLNode::GetObjectCnt();
  cout << "Number of Node objects " << iObjCnt << endl;

  XMLNode* NodePtr = XMLDoc.GetRootNode();
  XMLNode* NodePtr2 = NodePtr->GetFirstChild();
  while (NodePtr2 != nullptr) {
    string sEname = NodePtr2->GetNodeName();
    cout << sEname.c_str();
    string sVal = NodePtr2->GetElementValue("phone");
    cout << "Phone: " << sVal.c_str() << endl;
    NodePtr2 = NodePtr->GetNextChild();
  }
  XMLDoc.ResetReading();
  XMLDoc.DeleteAll();
}
