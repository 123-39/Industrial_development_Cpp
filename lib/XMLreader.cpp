// Trenev Ivan
#include "XMLreader.h"

int XMLNode::iObjCnt;

XMLNode::XMLNode(string sName, XMLNode* Parent) {
  iObjCnt++;
  NodeCtr = 0;
  ParentNode = Parent;
  sNodeName = sName;
}

void XMLNode::DeleteAll() {
  for (XMLNodeMapIter TmpItr = XMLChildNodes.begin();
       TmpItr != XMLChildNodes.end(); TmpItr++) {
    if (TmpItr->second != nullptr) {
      if ((TmpItr->second->GetChildNodeCnt() != 0))
        TmpItr->second->DeleteAll();
      delete TmpItr->second;
    }
  }
  XMLChildNodes.clear();
  XMLChildElements.clear();
}

void XMLNode::ResetReading() {
  for (XMLNodeMapIter TmpItr = XMLChildNodes.begin(); TmpItr != XMLChildNodes.end(); TmpItr++) {
    if (TmpItr->second != nullptr) {
      if ((TmpItr->second->GetChildNodeCnt() != 0))
        TmpItr->second->ResetReading();
      ResetNodeCntr();
    }
  }
}

long XMLNode::GetChildNodeCnt() {
  return XMLChildNodes.size();
}

string XMLNode::GetElementValue(string sName) {
  return XMLChildElements[sName];
}

XMLNode* XMLNode::GetFirstChild() {
  NodeCtr = 0;
  return XMLChildNodes[NodeCtr++];
}

XMLNode* XMLNode::GetNextChild() {
  return XMLChildNodes[NodeCtr++];
}

XMLNode* XMLNode::AddChildNode(string sName) {
  static int iTmp;
  XMLNode* Tmp = new XMLNode(sName, this);
  XMLChildNodes[NodeCtr++] = Tmp;
  iTmp++;

  return Tmp;
}

void XMLNode::AddElementVal(string sKey, string sval) {
  XMLChildElements[sKey] = sval;
}

XMLRdr::XMLRdr(string sFileName) {
  sDocName = sFileName;
  XMLRootNode = nullptr;
  XMLTraverse = nullptr;
  if (ReadFile() == false)
    cout << "Unable to open file";
  else
    cout << "File opened successfuly";
}

bool XMLRdr::ReadFile() {
  FILE* fp = fopen(sDocName.c_str(), "r+");
//   mistake 1
   if (fp == nullptr)
     return false;
  char buf[1000];
  while (fgets(buf, 1000, fp)) {
    string sTmp = buf;
    sTmp = EatupWhiteSpace(sTmp);
    if (ProcessString(sTmp) == false) {
      XMLRootNode->DeleteAll();
      return false;
    }
  }
  if (XMLTraverse != nullptr)
    return false;
  fclose(fp);
  return true;
}

string XMLRdr::EatupWhiteSpace(string sInput) {
  int iStart = sInput.find_first_not_of(" \t\n");
  int iEnd = sInput.find_last_not_of(" \t\n");
  if (iStart == -1)
    return "";

  return std::string(sInput, iStart, iEnd - iStart + 1);
}

bool XMLRdr::ProcessString(string sInput) {
  // mistake 2
  if (sInput[0] != '<')
      return false;
  switch (sInput[1]) {
    case '?':
    case '!':
      return true;
      break;
    case '/':
      if (XMLTraverse == nullptr)
        return false;
      else {
        XMLTraverse->ResetNodeCntr();
        XMLTraverse = XMLTraverse->GetParentNode();
      }
      break;
    default: {
      sInput = sInput.substr(1);
      int iTmp = sInput.find_first_of("<");

      if (iTmp != -1) {
        iTmp = sInput.find_first_of(" \t>");
        string sKey = sInput.substr(0, iTmp);
        iTmp = sInput.find_first_of(">");
        sInput = sInput.substr(iTmp + 1);
        iTmp = sInput.find_first_of("<");
        string sVal = sInput.substr(0, iTmp);
        XMLTraverse->AddElementVal(sKey, sVal);
      } else {
        iTmp = sInput.find_first_of(" \t>");
        string sNodeName = sInput.substr(0, iTmp);
        if (XMLRootNode == nullptr) {
          XMLRootNode = new XMLNode(sNodeName.c_str(), nullptr);
          XMLTraverse = XMLRootNode;
        } else {
          XMLTraverse = XMLTraverse->AddChildNode(sNodeName);
        }
      }
      break;
    }
  }
  return true;
}

XMLRdr::~XMLRdr() {
  if ((XMLRootNode == nullptr) || (XMLNode::GetObjectCnt() == 0))
    return;
  DeleteAll();
  if (XMLRootNode != nullptr)
    delete XMLRootNode;
  if (!XMLNode::GetObjectCnt())
    cout << "\nAll Node Objects deleted";
}

string XMLRdr::GetDocName() {
  return sDocName;
}

string XMLRdr::GetRootName() {
  return sRootName;
}

XMLNode* XMLRdr::GetRootNode() {
  return XMLRootNode;
}

