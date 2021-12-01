#include<iostream>

#include<stdio.h>

#include <vector>


using namespace std;

const char hextable[] = {
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
  1,
  2,
  3,
  4,
  5,
  6,
  7,
  8,
  9,
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
  10,
  11,
  12,
  13,
  14,
  15
};

const bool bittable[][4] = {
  {
    0,
    0,
    0,
    0
  },
  {
    0,
    0,
    0,
    1
  },
  {
    0,
    0,
    1,
    0
  },
  {
    0,
    0,
    1,
    1
  },
  {
    0,
    1,
    0,
    0
  },
  {
    0,
    1,
    0,
    1
  },
  {
    0,
    1,
    1,
    0
  },
  {
    0,
    1,
    1,
    1
  },
  {
    1,
    0,
    0,
    0
  },
  {
    1,
    0,
    0,
    1
  },
  {
    1,
    0,
    1,
    0
  },
  {
    1,
    0,
    1,
    1
  },
  {
    1,
    1,
    0,
    0
  },
  {
    1,
    1,
    0,
    1
  },
  {
    1,
    1,
    1,
    0
  },
  {
    1,
    1,
    1,
    1
  }
};

const int wt = 204;
const int ht = 201;
bool img[ht][wt]; //4*51
bool visited_img[ht][wt];
const int zl = 52;
char line[zl]; //52 por el caracter /0
int H, W, Wi;

class Node {

  vector < int > borderi;
  vector < int > borderj;
  vector < Node * > children;
  static int letters[6];
  bool state;
  public:

    Node() {

      state = false;

      for (int j = 0; j < Wi; j++) {
        if ((!img[0][j]) && (!visited_img[0][j]))
          explore(0, j);
      }

      for (int j = 0; j < Wi; j++) {
        if ((!img[H - 1][j]) && (!visited_img[H - 1][j]))
          explore(H - 1, j);
      }

      for (int i = 1; i < H - 1; i++) {
        if ((!img[i][0]) && (!visited_img[i][0]))
          explore(i, 0);
      }

      for (int i = 1; i < H - 1; i++) {
        if ((!img[i][Wi - 1]) && (!visited_img[i][Wi - 1]))
          explore(i, Wi - 1);
      }

      if (borderi.size() == 0) {
        children.push_back(new Node(0, 0));
      } else {

        for (int i = 0; i < borderi.size(); i++) {
          if (!visited_img[borderi[i]][borderj[i]]) {
            children.push_back(new Node(borderi[i], borderj[i]));
          }
        }

      }

    }

  Node(int i, int j) {

    state = img[i][j];
    explore(i, j);

    for (int i = 0; i < borderi.size(); i++) {
      if (!visited_img[borderi[i]][borderj[i]]) {
        children.push_back(new Node(borderi[i], borderj[i]));
      }
    }

  }

  void explore(int i, int j) {

    if (visited_img[i][j])
      return;

    if (img[i][j] != state) {
      borderi.push_back(i);
      borderj.push_back(j);
      return;
    }

    visited_img[i][j] = true;

    if (i + 1 < H) {

      if (j - 1 >= 0)
        explore(i + 1, j - 1);

      explore(i + 1, j);

      if (j + 1 < Wi)
        explore(i + 1, j + 1);

    }

    if (i - 1 >= 0) {

      if (j - 1 >= 0)
        explore(i - 1, j - 1);

      explore(i - 1, j);

      if (j + 1 < Wi)
        explore(i - 1, j + 1);

    }

    if (j - 1 >= 0)
      explore(i, j - 1);

    if (j + 1 < Wi)
      explore(i, j + 1);

  }

  void printfLetter(int cas) {

    for (int i = 0; i < 6; i++)
      letters[i] = 0;

    for (int i = 0; i < children.size(); i++) {
      int index = children[i] -> children.size();
      letters[index] = letters[index] + 1;
    }

    cout << "Case " << cas << ": ";
    for (int i = 0; i < letters[1]; i++)
      cout << "A";
    for (int i = 0; i < letters[5]; i++)
      cout << "D";
    for (int i = 0; i < letters[3]; i++)
      cout << "J";
    for (int i = 0; i < letters[2]; i++)
      cout << "K";
    for (int i = 0; i < letters[4]; i++)
      cout << "S";
    for (int i = 0; i < letters[0]; i++)
      cout << "W";
    cout << endl;

  }

};

int Node::letters[6] = {};

int main() {

  int cas = 0;

  while (true) {

    scanf("%d", & H);
    scanf("%d", & W);
    if (H == 0)
      break;

    for (int i = 0; i < H; i++) {
      scanf("%s", line);
      for (int j = 0; j < W; j++) {

        int index = 4 * j;
        int num = hextable[line[j]];
        for (int l = 0; l < 4; l++)
          img[i][index + l] = bittable[num][l];

      }

    }

    Wi = 4 * W;

    for (int i = 0; i < ht; i++) {
      for (int j = 0; j < wt; j++) {
        visited_img[i][j] = false;
      }
    }

    Node node;
    cas++;
    node.printfLetter(cas);

  }

  return 0;
}
