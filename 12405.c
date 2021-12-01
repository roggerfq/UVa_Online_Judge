#include<stdio.h>

int main() {

  int i, j, N, l, ac, num;
  char str[102];
  int flag;

  scanf("%d", & N);

  for (i = 1; i <= N; i++) {

    scanf("%d", & l);
    scanf("%s", str);

    flag = 0;
    ac = 0;
    num = 0;
    for (j = 0; j < l; j++) {

      if (str[j] == '.')
        flag = 1;

      if (flag) {

        ac++;
        if (ac == 3) {
          num++;
          ac = 0;
          flag = 0;
        }

      }

    }

    if (ac != 0)
      num++;

    printf("Case %d: %d\n", i, num);

  }

  return 0;

}
