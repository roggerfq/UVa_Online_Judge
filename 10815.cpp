#include<iostream>

#include <vector>

#include <string>

#include <iterator>

#include <stdio.h>

using namespace std;

class Node {

  Node * parent;
  Node * children[26];
  int depth;
  char c;
  bool flag_terminal;
  static int szNodes;
  public:

    //por defecto se establece todo nodo como terminal por conveniencia
    Node(Node * parent = NULL, char c = 0, bool flag_terminal = true): parent(parent), c(c), flag_terminal(flag_terminal) {

      if (parent == NULL)
        depth = 0;
      else
        depth = 1 + parent -> depth;

      for (int i = 0; i < szNodes; i++)
        children[i] = NULL;

    }

  void splitNode() {

    for (int j = 0; j < listWords.size(); j++) {

      if ((listWords[j]).size() == depth)
        wordPrint = listWords[j];
      else {
        const char * c = (listWords[j]).c_str();
        int index = c[depth] - 97;
        if (children[index] == NULL) { //crear nodo
          children[index] = new Node(this, c[depth]);
          children[index] -> listWords.push_back(listWords[j]);
          //si el nodo tiene al menos un hijo entonces no es un nodo terminal           
          setNodeTerminal(false);

        } else { //adicionar palabras

          children[index] -> listWords.push_back(listWords[j]);

        }

      }
    }

    for (int i = 0; i < szNodes; i++) {
      if (children[i] != NULL)
        children[i] -> splitNode();
    }

  }

  void setNodeTerminal(bool flag) {
    flag_terminal = flag;
  }

  bool nodeIsTerminal() const {
    return flag_terminal;
  }

  string wordPrint;
  vector < string > listWords;

  void printNode() {

    if (!wordPrint.empty())
      cout << wordPrint << endl;

    for (int i = 0; i < szNodes; i++) {
      if (children[i] != NULL)
        children[i] -> printNode();
    }

  }

};

int Node::szNodes = 26;

const char G_table[256] = {
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  97,
  98,
  99,
  100,
  101,
  102,
  103,
  104,
  105,
  106,
  107,
  108,
  109,
  110,
  111,
  112,
  113,
  114,
  115,
  116,
  117,
  118,
  119,
  120,
  121,
  122,
  0,
  0,
  0,
  0,
  0,
  0,
  97,
  98,
  99,
  100,
  101,
  102,
  103,
  104,
  105,
  106,
  107,
  108,
  109,
  110,
  111,
  112,
  113,
  114,
  115,
  116,
  117,
  118,
  119,
  120,
  121,
  122,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0
};

char G_ch[201];

void split(std::vector < string > & listWords, string & str) {

  const char * c = str.c_str();
  int li = 0;
  char aux;

  for (int i = 0; i <= str.length(); i++) {

    aux = G_table[c[i]];
    if (aux == 0) {

      if (i > li)
        listWords.push_back(str.substr(li, i - li));
      li = i + 1;

    } else {
      str[i] = aux;
    }

  }

}

int main() {

  string str;
  Node mynode;

  mynode.listWords.clear();

  while (std::getline(cin, str)) {
    split(mynode.listWords, str);

  }

  mynode.splitNode();
  mynode.printNode();
  cout << endl;

  return 0;
}
