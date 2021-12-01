#include<iostream>

#include<vector>

#include<stdio.h>

//_____________Global variables and functions________________________
const int G_bits[] = {
  32768,
  16384,
  8192,
  4096,
  2048,
  1024,
  512,
  256,
  128,
  64
};
const int G_sbm = 8 * sizeof(char);
const int G_sh = sizeof(unsigned short int);
const int G_sz_number = G_sbm * G_sh;
const int G_ldispb = G_sz_number - 1;
unsigned short int G_M[10];
int G_numberNode = 10;
//___________________________________________________________________

class Node {

  std::vector < Node * > children;
  static std::vector < Node * > lastNodes;
  static std::vector < int > listPrintfNodes;
  Node * parent;
  int key;
  public:
    Node(const int key = 0, Node * parent = NULL): key(key), parent(parent) {
      if (key == 0) {
        lastNodes.push_back(this);
        listPrintfNodes.clear();
      }

    }

    ~Node() {

      if (parent == NULL)
        lastNodes.clear();

      for (int i = 0; i < children.size(); i++) {
        delete children[i];
      }

    }

  void addNode(Node * node) {
    node -> parent = this;
    children.push_back(node);
  }

  void addNode(const unsigned short int N) {

    int szLastNode = lastNodes.size();
    for (int n = 0; n < szLastNode; n++) {

      for (int i = 0; i < G_numberNode; i++) {
        if ((N & G_bits[i])) {
          if ((G_M[lastNodes[n] -> key] & G_bits[i])) {
            if (!lastNodes[n] -> isAncestor(i)) {
              Node * tmpNode = new Node(i);
              lastNodes[n] -> addNode(tmpNode);
              addLastNodes(tmpNode); //adicionando a lista de ultimos
            }

          }
        }
      }

    }

    if (szLastNode != 0)
      lastNodes.erase(lastNodes.begin(), lastNodes.begin() + szLastNode);

  }

  bool isAncestor(const int key) {

    Node * tmpNode = this;
    while (tmpNode -> parent != NULL) {
      if (tmpNode -> key == key)
        return true;
      tmpNode = tmpNode -> parent;
    }

    return (tmpNode -> key == key) ? true : false;
  }

  int sizeLastNodes() const {
    return lastNodes.size();
  }

  void addLastNodes(Node * node) {
    lastNodes.push_back(node);
  }

  void clearLastNodes() {

    lastNodes.clear();

  }

  void printfNode() {

    for (int i = 0; i < lastNodes.size(); i++) {

      Node * tempNode = lastNodes[i];
      listPrintfNodes.clear();

      while (tempNode -> parent != NULL) {
        listPrintfNodes.push_back(tempNode -> key + 1);
        tempNode = tempNode -> parent;
      }

      printf("(%d", 1);

      for (int j = listPrintfNodes.size() - 1; j >= 0; j--)
        printf(",%d", listPrintfNodes[j]);

      printf(")\n");

    }

  }

};

std::vector < Node * > vlaux; //truco para inicializar un std vector vacio
std::vector < Node * > Node::lastNodes = {};
std::vector < int > Node::listPrintfNodes = {};

int main() {

  unsigned short int aux[10], tmp;
  int n, d;
  char ch, s[5];

  while (true) {
    //______________________________________________________________________________
    //Leyendo datos
    scanf("%d", & n);
    G_numberNode = n; //Estableciendo longitud de impresion
    scanf("%d", & d);

    for (int i = 0; i < n; i++) {
      G_M[i] = 0;
      for (int j = 0; j < n; j++) {
        scanf("%hhu", & ch);
        if (ch == 1) {
          G_M[i] = G_M[i] + G_bits[j];
          aux[i] = G_M[i];
        }
      }
    }

    //creando nodo raiz
    Node * node = new Node;
    node -> addNode(G_M[0]);

    for (int l = 0; l < d - 1; l++) {

      //multiplicando matriz
      for (int i = 0; i < n; i++) {
        tmp = 0;
        for (int j = 0; j < n; j++) {
          if ((aux[i] & G_bits[j])) {
            tmp = tmp | G_M[j];
          }
        }
        aux[i] = tmp;
      }

      node -> addNode(aux[0]);

    }

    if (node -> sizeLastNodes())
      node -> printfNode();
    else
      printf("no walk of length %d\n", d);

    delete node;

    if (scanf("%s", s) == EOF)
      break;

    printf("\n");

  }

  printf("\n");
  return 0;
}
