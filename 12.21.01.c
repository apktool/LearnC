/**
 * @file 12.21.01.c
 * @brief 棋盘覆盖
 * @author LiWenGang
 * @date 2016-12-21
 */
#include <stdio.h>
#include <stdlib.h>

#define SIZE 8

static int title = 1;    //title表示L型骨牌的编号
static int board[SIZE][SIZE];

void ChessBoard(int tr, int tc, int dr, int dc, int size);
void ChessPrint();

int main(int argc, char* argv[]){
	//方便测试，假设特殊方格位置在第三行第三列
	ChessBoard(0, 0, 5, 2, SIZE);
	ChessPrint();
	return 0;
}

/**
 * @brief ChessBoard 
 *
 * @Param tr
 * @Param tc
 * @Param dr
 * @Param dc
 * @Param size=2^k 
 *
 * @note 棋盘的规格为2^k * 2^k
 */
void ChessBoard(int tr, int tc, int dr, int dc, int size){
	if(1 == size){
		return;
	}
     
	int t = title++;    //L型骨牌号
	int s = size / 2;    //分割棋盘

	//覆盖左上角子棋盘
	if(dr < tr + s && dc < tc + s){
		//特殊方格在此棋盘中
		ChessBoard(tr, tc, dr, dc, s);
	}else{
		//此棋盘无特殊方格
		//用t号L型骨牌覆盖右下角
		board[tr + s - 1][tc + s - 1] = t;
		//覆盖其余方格
		ChessBoard(tr, tc, tr + s - 1, tc + s - 1, s);
	}

	//覆盖右上角
	if(dr < tr + s && dc >= tc + s){
		//特殊方格在此棋盘中
		ChessBoard(tr, tc + s, dr, dc, s);
	}else{
		//此子棋盘中无特殊方格
		//用t号L型骨牌覆盖左下角
		board[tr + s - 1][tc + s] = t;
		//覆盖其余方格
		ChessBoard(tr, tc + s, tr + s - 1, tc + s, s);
	}

	//覆盖左下角子棋盘
	if(dr >= tr + s && dc < tc + s){
		//特殊方格在此棋盘中
		ChessBoard(tr + s, tc, dr, dc, s);
	}else{
		//用t号L型骨牌覆盖右上角
		board[tr + s][tc + s -1] = t;
		//覆盖其余方格
		ChessBoard(tr + s, tc, tr + s, tc + s - 1, s);
	}


	//覆盖右下角子棋盘
	if(dr >= tr + s && dc >= tc + s){
		//特殊方格在此棋盘中
		ChessBoard(tr + s, tc + s, dr, dc, s);
	}else{
		//用t号L型骨牌覆盖左上角
		board[tr + s][tc + s] = t;
		//覆盖其余方格
		ChessBoard(tr + s, tc + s, tr + s, tc + s, s);
	}
}

//打印
void ChessPrint(){
	int i;
	int j;
	for(i = 0; i < SIZE; i++){
		for(j = 0; j < SIZE; j++){
			printf("%4d", board[i][j]);
		}
		printf("\n");
	}
}
