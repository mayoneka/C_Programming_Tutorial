#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(void)
{
  /* 構造体 result を定義 */
  typedef struct _result{
    short int id;
    char name[16];
    short int score;
    struct _result *next;
  } result;

  int i;              /* ループカウンタ */
  result *p, *start;  /* 構造体のポインタ */

  /* 元データを配列で準備 */
  char _name[5][16] = {"Taro","Hanako","Sayaka","Miki","Hiroshi"};
  short int _score[5] = {50, 60, 70, 80, 30};

  for (i=0; i<5; i++) {
    if (i==0) {
      /* 先頭の構造体を生成 */
      p = malloc(sizeof(result));
      /* メモリ確保した領域を0クリア */
      memset(p, 0, sizeof(p));
      start = p;  /* 先頭を保存 */
    } else {
      p->next = malloc(sizeof(result));
      memset(p->next, 0, sizeof(p));
      p = p->next;
    }
    /* IDはカウンタ変数から生成 */
    p->id = (short int)i+1;
    /* 2項目を代入 */
    strcpy(p->name, _name[i]);
    p->score = _score[i];
    p->next = NULL;
  }

  /* 構造体のリンクをたどって先頭からメンバを表示 */
  printf("ID\tName\tScore\n");
  p = start;  /* ポインタを先頭に */
  while (p != NULL) {
    printf("%04d\t%s\t%d\n", p->id, p->name, p->score);
    p = p->next;
  }

  /* 課題 1. 先頭から 3 番目までの人を削除してから表示する */
 
  /* 課題 2. 2人追加する */
 

  /* メモリクリア */
  result *temp;
  while (p != NULL) {
    temp = p->next;
    free(p);
    p = temp;
  }
  return (0);
}