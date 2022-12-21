// Trenev Ivan
#pragma once

#include <iostream>
#include <map>
#include <string>

using namespace std;

class XMLNode;

typedef map<int, XMLNode*> XMLNodeMap;
typedef XMLNodeMap::iterator XMLNodeMapIter;
typedef map<string, string> XMLStringMap;

class XMLNode {
 public:
  XMLNode(string sName, XMLNode*);
  ~XMLNode() { iObjCnt--; };
  string GetElementValue(string sName);
  XMLNode* GetFirstChild();
  XMLNode* GetNextChild();
  long GetChildNodeCnt();
  XMLNode* GetParentNode() { return ParentNode; };
  void DeleteAll();
  XMLNode* AddChildNode(string sName);
  void AddElementVal(string sKey, string sval);
  void ResetNodeCntr() { NodeCtr = 0; };
  void ResetReading();
  string GetNodeName() { return sNodeName; };
  static int GetObjectCnt() { return iObjCnt; };

 private:
  string sNodeName;
  int NodeCtr;
  XMLNode* ParentNode;
  XMLNodeMap XMLChildNodes;
  XMLStringMap XMLChildElements;
  static int iObjCnt;
};

class XMLRdr {
 public:
  XMLRdr(string sFileName);
  ~XMLRdr();
  string GetDocName();
  string GetRootName();
  XMLNode* GetRootNode();
  bool ReadFile();
  string EatupWhiteSpace(string);
  bool ProcessString(string);
  void ResetReading() { XMLRootNode->ResetReading(); };
  void DeleteAll() { XMLRootNode->DeleteAll(); };

 private:
  string sDocName;
  string sRootName;
  XMLNode* XMLRootNode;
  XMLNode* XMLTraverse;
};

