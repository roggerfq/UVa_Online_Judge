#include <stdio.h>

#include <stdlib.h>


typedef struct typeSoldier {
  int B;
  int J;
}
Soldier;

Soldier squad[1001];

int comp(const void * a,
  const void * b) {

  const Soldier * tmp_a = (Soldier * ) a;
  const Soldier * tmp_b = (Soldier * ) b;

  return (tmp_b -> J - tmp_a -> J);

}

int main() {

  int N, ac, aux, max, i, nc = 0;

  while (1) {

    scanf("%d", & N);
    if (N == 0) break;

    for (i = 0; i < N; i++) {

      scanf("%d", & (squad[i].B));
      scanf("%d", & (squad[i].J));

    }

    qsort(squad, N, sizeof(squad[0]), comp);

    aux = 0;
    ac = 0;
    for (i = 0; i < N; i++) {
      ac += squad[i].B;
      max = ac + squad[i].J;
      if (max > aux)
        aux = max;

    }

    nc++;
    printf("Case %d: %d\n", nc, aux);

  }

  return 0;
}
