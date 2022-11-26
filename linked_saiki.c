#include <stdio.h>
#include <stdlib.h>
/*
再帰で連結リストに関する各々の操作(追加、挿入、削除)を実装したもの。
c言語の復習も兼ねている。
*/
struct cell {
    int element;
    struct cell *next;
};

struct cell *add(struct cell *init, int num) {
    //配列の要素が存在しない場合の条件処理
    if (init == NULL) {
        struct cell *new_cell = (struct cell *)malloc(sizeof(struct cell));//mallocでメモリを確保
        new_cell->element = num;//new_cellのelementにnumを格納
        new_cell->next = NULL;//次の要素は存在しないため、ヌルポインタとして扱う。
        return new_cell;
    }
    //配列に要素が存在する場合の条件処理
    else if (init != NULL){
        if (init->next != NULL){
            add(init->next,num);//再帰の内容は改良前にwhile文で行っていた　struct cell *c = init; c = c-> next;と同じ。
        }
        else{
            struct cell *new_cell = (struct cell *)malloc(sizeof(struct cell));//配列の終端に辿り着いたので、mallocでメモリを確保し要素をぶちこむ。
            new_cell->element = num;
            new_cell->next = NULL;
            init->next = new_cell;//c->next = new_cellと同じ処理、増やした要素へとポインタを差し替えておく。
        }
    }
    return init;
}
struct cell *insert(struct cell *init, int num, int index) {
    if (index == 0) {
        struct cell *new_cell = (struct cell *)malloc(sizeof(struct cell));//メモリを確保
        new_cell->element = num;//初期化
        new_cell->next = init;//生成した要素をそのままinitの先頭にガッちゃんこ
        return new_cell;
    }
    if ( index != 0){
        if (index > 1){
            insert(init->next,num,index-1);//c = c->next をwhile文で回したくなるが、それが出来ないため代わりにindexを利用。呼び出すことに-1していくことで、index == 1になると挿入を行うようにする。
        }
        else{
            struct cell *new_cell = (struct cell *)malloc(sizeof(struct cell));
            new_cell->element = num;
            new_cell->next = init->next;//次の要素へのポインタを、挿入した要素の前の要素が指していたポインタに組み替える。
            init->next = new_cell;//次の要素へ向けていたポインタを、挿入した要素へと組み替える。
        }  
    }
    return init;
}
struct cell *delete(struct cell *init, int index) {
    if (init == NULL){ //連結リスと自体が存在しない場合にNULLを返す。
        return NULL;
    }
    if (index == 0){
        struct cell *c = init->next;//ベースケース、ここで削除する要素のメモリを解放する。
        free(init);
        return c;
    }
    init -> next = delete(init->next,index-1);//insertの処理と同じで、indexを利用して削除したい要素まで辿り着く。indexが0になるとベースケースにかかる。
    return init;
}
void print_cell(struct cell *init) {
    if (init->next != NULL){//次の要素がNULLではない場合。
        printf("%d ",init->element);//要素を出力する。
        print_cell(init->next);//次の要素へと飛ぶ
    }
    if (init->next == NULL){//配列の終端に辿り着いた場合。
        printf("%d ",init->element);//要素を出力する。
        printf("\n");//改行を打って終了。
    }
}
int main(void) {
    struct cell *init = (struct cell *)malloc(sizeof(struct cell));
    init = NULL;
    // 追加
    init = add(init, 3);
    init = add(init,20);
    init = add(init,30);
    init = add(init,40);
    print_cell(init);
    init = insert(init,30,0);
    init = insert(init,50,4);
    print_cell(init);
    init = delete(init,3);
    init = delete(init,2);
    print_cell(init);
    return 0;
}
