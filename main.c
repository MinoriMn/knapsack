#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#define MAX 2048
#define ITEMS_FILE_NAME "items.csv"

//物品データ
typedef struct _item{
  char name[32];
  double weight;
  double value;
  struct _item* next;
}n_item;

//物品読み込み
n_item* readItems(){
  FILE *fp;
  int ret;
  char buf[MAX]={0};
  char *ary[3] ;
  double data[2];

  fp = fopen( ITEMS_FILE_NAME, "r" );
  if( fp == NULL ){
    printf( "%sファイルが開けません\n", ITEMS_FILE_NAME );
    exit(-1);
  }
  printf("物品読み込み開始-----------\n");

  //項目名
  fgets(buf,MAX,fp);
  printf("%s", buf);

  n_item* item = (n_item*)malloc(sizeof(n_item));
  n_item* before = NULL;
  n_item* head = item;
  //物品ロード
  while(fgets(buf,MAX,fp) != NULL){
    /*文字列(char配列)をカンマで分割する*/
    ary[0] = strtok(buf,",");
    ary[1] = strtok(NULL,",");
    ary[2] = strtok(NULL,",");
    /*文字列(char配列)をdoubleに変換する*/
    data[0] = atof(ary[1]);
    data[1] = atof(ary[2]);

    strcpy(item->name, ary[0]);
    item->weight = data[0];
    item->value = data[1];

    item->next = (n_item*)malloc(sizeof(n_item));
    before = item;
    item = item->next;

    printf("%s %lf %lf\n", ary[0], data[0], data[1]);
  }
  printf("物品読み込み終了-----------\n");
  fclose(fp);

  free(item);
  if(before != NULL)before->next = NULL;

  return head;
}

//学習結果書き出し
void writeLearningData(n_item* head){
  //物品データ解放
  n_item* item = head;
  while(item != NULL){
    n_item* tmp = item;
    item = item->next;
    free(tmp);
  }
}

//物品サイズの取得
int getItemsLength(n_item* head){
  int itemsLength=0;
  n_item* item = head;
  while(item != NULL){
    itemsLength++;
    item = item->next;
  }
  return itemsLength;
}

int main(){
  n_item* itemsHead = readItems();

  printf("物品サイズ: %d\n", getItemsLength(itemsHead));

  writeLearningData(itemsHead);
}
