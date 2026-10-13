#include <iostream>
#include <cstdlib>
using namespace std;

int isCheckMate = 0;

int board[8][8];
bool cMove = 1;
int checkBy[2] = {10, 10};
int checkCount = 0;

int kingW[2] = {0, 4};
int kingB[2] = {7, 4};

bool isLegal(int sRow, int sColumn, int row, int column);
bool check();
bool checkCheck();
bool checkToIsLegal(int sRow, int sColumn, int row, int column);

bool staleMate(int canMove)
{

	if(cMove)
	{
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(board[i][j] > 0 && board[i][j] != 6)
				{
					for(int k = 0; k < 8; k++)
					{
						for(int l = 0; l < 8; l++)
						{
							if(checkToIsLegal(i, j, k, l))
							{
								return 0;
							}
						}
					}
				}
			}
		}
		return 1;
		
	} else {
		
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(board[i][j] < 0 && board[i][j] != -6)
				{
					for(int k = 0; k < 8; k++)
					{
						for(int l = 0; l < 8; l++)
						{
							if(checkToIsLegal(i, j, k, l))
							{
								return 0;
							}
						}
					}
				}
			}
		}
		return 1;
	}

}

int checkMate()
{	
	int Row;
	int Col;
	
	if(cMove)
	{
		Row = kingW[0];
		Col = kingW[1];
	} else {
		Row = kingB[0];
		Col = kingB[1];
	}
	
	int canMove = 0;
	
	//Upper row
	canMove += checkToIsLegal(Row, Col, Row + 1, Col);
	canMove += checkToIsLegal(Row, Col, Row + 1, Col + 1);
	canMove += checkToIsLegal(Row, Col, Row + 1, Col - 1);
	
	//Same row
	canMove += checkToIsLegal(Row, Col, Row, Col + 1);
	canMove += checkToIsLegal(Row, Col, Row, Col - 1);
	
	//lower row
	canMove += checkToIsLegal(Row, Col, Row - 1, Col);
	canMove += checkToIsLegal(Row, Col, Row - 1, Col + 1);
	canMove += checkToIsLegal(Row, Col, Row - 1, Col - 1);
	
	
	
	
	//can we take the check by piece
	
	
	bool canTakeCheckBy = 0;
	
	if(cMove)
	{
		for(int i = 0; i < 8; i++)
		{
			
			for(int j = 0; j < 8; j++)
			{
				if(board[i][j] > 0 && board[i][j] != 6)
				{
					
					canTakeCheckBy = isLegal(i, j, checkBy[0], checkBy[1]);
					
				}
			}
			if(canTakeCheckBy)
			{
				break;
			}
		}
	} else {
		for(int i = 0; i < 8; i++)
		{
			for(int j = 0; j < 8; j++)
			{
				if(board[i][j] < 0 && board[i][j] != -6)
				{
					canTakeCheckBy = isLegal(i, j, checkBy[0], checkBy[1]);
				
				}
			}
			if(canTakeCheckBy)
			{
				break;
			}
		}
	}
	
	if(canTakeCheckBy)
	{
		//is there any check other then check by piece which we can take
		int tempValue = board[checkBy[0]][checkBy[1]];
		
		board[checkBy[0]][checkBy[1]] = 0;
		
		bool isCheck = check();
		
		if(isCheck)
		{
			canTakeCheckBy = 0;
		}
		
		board[checkBy[0]][checkBy[1]] = tempValue;
	}
	

	if(canMove == 0 && !check())
	{
		if(staleMate(canMove))
		{
			return -1;
		}
	}
	
	if(canMove == 0 && check() && !canTakeCheckBy)
	{
		return 1;
	} else {
		
		return 0;
	}
}
bool check()
{
	cMove ? cMove = 0 : cMove = 1;
	
	bool isCheck = 0;
	
	bool legal = 0;
	

	
	for(int i = 0; i < 8; i++)
	{
		for(int j = 0; j < 8; j++)
		{
			if(cMove)
			{
				if(board[i][j] > 0)
				{
					legal = isLegal(i, j, kingB[0], kingB[1]);
					
					
					if(legal)
					{	
					//	cout << "Check on " << kingB[0] + 1 << kingB[1] + 1 << " From " << board[i][j] << endl;
						
						checkBy[0] = i;
						checkBy[1] = j;
						isCheck = 1;
						goto bottom;
					}
				}
			} else {
				if(board[i][j] < 0)
				{
					
					legal = isLegal(i, j, kingW[0], kingW[1]);
					
					if(legal)
					{	
					
					//	cout << "Check on " << kingW[0] + 1 << kingW[1] + 1 << " From " << board[i][j] << endl;
						
						checkBy[0] = i;
						checkBy[1] = j;
						isCheck = 1;
						goto bottom;
						
					}
				
				}
			}
			
			
		}
	}
	
	bottom:
		cMove? cMove = 0 : cMove = 1;
		return isCheck;
}
	

	
void iniBoard(){


	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			board[i][j] = 0;
			if(i == 1)
			{
				board[i][j] = 1;
			} else if(i == 6)
			{
				board[i][j] = -1;
			}
		}	
		
	}
	

	
	// --- WHITE PIECES (Row 0) ---
    board[0][0] = 4;   // Rook
    board[0][1] = 2;   // Knight
	board[0][2] = 3;   // Bishop
    board[0][3] = 5;   // Queen
    board[0][4] = 6;   // King
	board[0][5] = 3; //Bishop
    board[0][6] = 2;   // Knight
    board[0][7] = 4;   // Rook

	

    // --- BLACK PIECES (Row 7) ---
    board[7][0] = -4;  // Rook
    board[7][1] = -2;  // Knight
    board[7][2] = -3;  // Bishop
    board[7][3] = -5;  // Queen
	board[7][4] = -6;  // King
    board[7][5] = -3;  // Bishop
    board[7][6] = -2;  // Knight
    board[7][7] = -4;  // Rook
	
	
}
void printBoard(){
	
	cout << "\n\t";
	for(int i = 8; i > 0; i--)
	{
		cout << i << "\t";
	}
	
	cout << endl;
	cout << endl;
	
	for(int i = 7; i >= 0; i--){
		
		cout << i+1 << "\t";
		for(int j = 7; j >= 0; j--){
			if(board[i][j] == 0){
				cout << "."<< "\t";
			}else {
				cout << board[i][j]<< "\t";
			}
		}	
		
		cout << endl;
		cout << endl;
	}
	
	(cMove)? cout << "\t\t\t---(White Move)---" << endl : cout << "\t\t\t---(Black Move)---" << endl;
	
	cout << "\tWhite King: " << kingW[0] + 1 << 1 + kingW[1] << "\t\tBlack King: " << kingB[0] + 1  << 1 + kingB[1] << endl;
}
bool valPawn(int sRow, int sCol, int row, int col)
{
	int piece = board[sRow][sCol];
	int target = board[row][col];
	
	if(piece == 1)
	{
		if(board[row][col] == 0 && col == sCol) // build up
		{
			if(row == sRow + 1)
			{
				return 1;
			} else if(row == sRow + 2 && board[sRow+1][sCol] == 0 && sRow == 1)
			{
				return 1;
			} else {
				return 0;
			}
		} else if(board[row][col] < 0 && row == sRow+1 && (col == sCol+1 || col == sCol - 1)){
			return 1;
		} else {
			return 0;
		}
		
	} 
	
	if(piece == -1)
	{
		
		
		if(board[row][col] == 0 && col == sCol) // build up
		{
			if(row == sRow - 1)
			{
				return 1;
			} else if(row == sRow - 2 && board[sRow-1][sCol] == 0 && sRow == 6)
			{
				return 1;
			} else {
				return 0;
			}
		} else if(board[row][col] > 0 && row == sRow-1 && (col == sCol-1 || col == sCol + 1)){
			return 1;
		} else {
			return 0;
		}
	}	
	
	
	return 0;
	
}
bool valKnight(int sRow, int sCol, int row, int col)
{
	int piece = board[sRow][sCol];
	if(piece == 2){
		if(board[row][col] <= 0){
			int dRow = abs(row - sRow);
			int dCol = abs(col - sCol);
			
			if ((dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2)) {
			    return 1;
			} else {
				return 0;
			}	
		} else {
			return 0;
		} 
	}
	
	if(piece == -2){
		if(board[row][col] >= 0){
			int dRow = abs(row - sRow);
			int dCol = abs(col - sCol);
			
			if ((dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2)) {
			    return 1;
			} else {
				return 0;
			}	
		} else {
			return 0;
		} 
	}
	
	
}
bool valBishop(int sRow, int sCol, int row, int col)
{
	
	int dRow = (row - sRow);
	int dCol = (col - sCol);
	
	int x = sRow;
	int y = sCol;
	
//	if(dRow > 0){
//		x = sRow + 1;
//	} else {
//		x = sRow -1;
//	}
//	if(dCol > 0)
//	{
//		y = dRow + 1;
//	} else {
//		y = dRow -1;
//	}
	
	if(abs(dRow) == abs(dCol))
	{
		
		while(true)
		{
			
			if(dRow > 0 && dCol > 0)
			{
				x++;
				y++;
			} else if(dRow > 0 && dCol < 0)
			{
				x++;
				y--;
			} else if(dRow < 0 && dCol > 0)
			{
				x--;
				y++;
			} else if(dRow < 0 && dCol < 0)
			{
				x--;
				y--;
			}	
			if(x == row)
			{
				break;
			}
			if(board[x][y] != 0)
			{
				
				return 0;
			}
		}
		return 1;
	} else {
		return 0;
	}
//	int i;
//	int j;
//	
//
//	
//	if(sRow < row)
//	{
//		if(sCol < col)
//		{
//			i = sRow + 1;
//			j = sCol + 1;
//			while(i < row)
//			{
//				if(board[i][j] != 0)
//				{
//					return 0;
//				}
//				
//				i++;
//				j++;
//			}
//			return 1;
//		}else if(sCol > col )
//		{
//			i = sRow + 1;
//			j = sCol - 1;
//			while(i < row)
//			{
//				if(board[i][j] != 0)
//				{
//					return 0;
//				}
//				
//				i++;
//				j--;
//			}
//			return 1;
//		}
//	} else if(sRow > row)
//	{
//		if(sCol < col)
//		{
//			i = sRow - 1;
//			j = sCol + 1;
//			
//			while(i > row)
//			{
//				if(board[i][j] != 0)
//				{
//					return 0;
//				} 
//				
//				
//				i--;
//				j++;
//			}
//			return 1;
//		}else if(sCol > col)
//		{
//			i = sRow - 1;
//			j = sCol - 1;
//			while(i > row)
//			{
//				if(board[i][j] != 0)
//				{
//					return 0;
//				}
//				i--;
//				j--;
//			}
//			return 1;
//		}
//	}	
//	
//	return 0;

}
bool valRook(int sRow, int sCol, int row, int col)
{
	int piece = board[sRow][sCol];
	
	if(sCol == col)
	{
		
		if(row > sRow)
		{
			for(int i = sRow + 1; i < row; i++)
			{
				if(board[i][sCol] != 0){
					
					
					return 0;
				}
			}
			return 1;
		} else if(row < sRow)
		{
			for(int i = sRow - 1; i > row; i--)
			{
				if(board[i][sCol] != 0){
					
					return 0;
				}
			}
			return 1;
		}
	}
		
	if(row == sRow)
	{
		if(col > sCol)
		{
			for(int i = sCol + 1; i < col; i++)
			{
				if(board[sRow][i] != 0){
					return 0;
				}
			}
			return 1;
		} else if(col < sCol)
		{
			for(int i = sCol - 1; i > col; i--)
			{
				if(board[sRow][i] != 0){
					return 0;
				}
			}
			return 1;
		}
	}
	
	return 0;
	
	
	
}
bool valQueen(int sRow, int sCol, int row, int col)
{
	int dRow = abs(row - sRow);
	int dCol = abs(col - sCol);
	
	
	
	if(row == sRow || col == sCol)
	{
		return valRook(sRow, sCol, row, col);
	}else if(dRow == dCol)
	{
		return valBishop(sRow, sCol, row, col);
	}
	return 0;
}
bool valKing(int sRow, int sCol, int row, int col)
{
	int dRow = abs(row - sRow);
	int dCol = abs(col - sCol);
	
	if((dRow == 1 || dRow == 0) && (dCol == 1 || dCol == 0))
	{
		return 1;
			
	} else {
		return 0;
	}
}


bool isLegal(int sRow, int sColumn, int row, int column)
{
	
	
	
	
	//check if king attacking king
	if(board[row][column] == abs(6))
	{
		return 0;
	}
	
	if(cMove && board[sRow][sColumn] < 0)
	{
		return 0;
	} else if(!cMove && board[sRow][sColumn] > 0)
	{
		return 0;
	}
	
	
	if(sRow < 0 || sRow > 7 || sColumn < 0 || sColumn > 7
	|| row < 0 || row > 7 || column < 0 || column > 7 )
	{
		return 0;
		
	}
	
	if(sRow == row && sColumn == column)
	{
		return 0;
	}
	
	int piece = board[sRow][sColumn];
	int target = board[row][column];
	
	if(piece > 0 && target > 0 || piece < 0 && target < 0)
	{
		return 0;
	}
	
	switch(abs(piece)){
		case 1: {
			return valPawn(sRow, sColumn, row, column);
			break;
		}
		case 2: {
			return valKnight(sRow, sColumn, row, column);
			break;
		}
		case 3: {
			return valBishop(sRow, sColumn, row, column);
			break;
		}
		case 4: {
			return valRook(sRow, sColumn, row, column);
			break;
		}
		case 5: {
			return valQueen(sRow, sColumn, row, column);
			
			break;
		} 
		case 6:{
			return valKing(sRow, sColumn, row, column);
			break;
		}
	}
	
	
	
}

bool checkToIsLegal(int sRow, int sColumn, int row, int column)
{
	
	bool legal = isLegal(sRow, sColumn, row, column);
	
	if(!legal)
	{
		return 0;
	}
	
	if(board[sRow][sColumn] == 6)
	{
		kingW[0] = row;
		kingW[1] = column;
	
	} else if(board[sRow][sColumn] == -6) {
		kingB[0] = row;
		kingB[1] = column;
	}
	
	
	int tempValue = board[row][column];
	board[row][column] = board[sRow][sColumn];
	board[sRow][sColumn] = 0;
	
	bool isCheck = 0;
	isCheck = check();
	
	
	if(board[row][column] == 6)
	{
		kingW[0] = sRow;
		kingW[1] = sColumn;
	
	} else if(board[row][column] == -6) {
		kingB[0] = sRow;
		kingB[1] = sColumn;
	}
	
	board[sRow][sColumn] = board[row][column];
	board[row][column] = tempValue;
	
	
	
	if(isCheck)
	{	
		return 0;
	} else {
		return 1;
	}
	
}
void move(bool currentMove){
	
	int select;
	int sRow, sColumn;
	bool isThere = 0;	
	
	int target;
	bool legalMove = 0;
	int row, column;
	
	//select piece
	
	bool isCheck = 0;
	while(!legalMove){
		
		while(true)
		{
			cout << "Select (R x C): ";
			cin >> select;
			
			sColumn = select % 10;
			
			sRow = (select - (select % 10))/10;
			
			sRow -= 1;
			sColumn -= 1;
			
			
			if(board[sRow][sColumn] > 0)
			{
				if(cMove)
				{
					cout << "Selected: " << board[sRow][sColumn] << endl;
					break;
				} else {
					cout << "Invalid Piece" << endl;
				}
			}else if(board[sRow][sColumn] < 0)
			{
				if(!cMove)
				{
					cout << "Selected: " << board[sRow][sColumn] << endl;
					break;
				} else {
					cout << "Invalid Piece" << endl;
				
				}
			} else {
				cout << "No piece at " << sRow << " " << sColumn << endl;
			}
		}

		//Move piece
		 
		cout << "Move(RxC): ";
		cin >> target;
		
		row = (target - (target % 10))/10;
		column = target % 10;
		row -= 1;
		column -= 1;
		
	
		legalMove = checkToIsLegal(sRow, sColumn, row, column);
		
		
		if(legalMove)
		{
			
			
			if(board[sRow][sColumn] == 6)
			{
				kingW[0] = row;
				kingW[1] = column;
			
			} else if(board[sRow][sColumn] == -6) {
				kingB[0] = row;
				kingB[1] = column;
			}
			board[row][column] = board[sRow][sColumn];
			board[sRow][sColumn] = 0;
			
			int promo; // promote the pawn
			if(board[row][column] == 1 && row == 7)
			{
				
				do{
					cout << "Promote the pieace into [2, 3, 4, 5]: ";
					cin >> promo;
					if(promo >= 2 && promo <= 5)
					{
						cout << "Promoted" << endl;
						break;
					} else {
						cout << "Invalid pieace" << endl;
					}
				}while(true);
				
				board[row][column] = promo;
			}
			
			if(board[row][column] == -1 && row == 0)
			{
				
				do{
					cout << "Promote the pieace into [-2, -3, -4, -5]: ";
					cin >> promo;
					if(promo <= -2 && promo >= -5)
					{
						cout << "Promoted" << endl;
						break;
					} else {
						cout << "Invalid pieace" << endl;
					}
				}while(true);
				
				board[row][column] = promo;
			}
			
			cout << "----(Succes)----" << endl;
//			isCheck = check();
//			
//			if(isCheck) {
//				
//				
//				legalMove = 0;
//				
//				if(board[row][column] == 6)
//				{
//					kingW[0] = sRow;
//					kingW[1] = sColumn;
//				} else if(board[row][column] == -6)
//				{
//					kingB[0] = sRow;
//					kingB[1] = sColumn;
//				}
//				board[sRow][sColumn] = board[row][column];
//		
//				board[row][column] = 0;
//				
//			} else {
//				cout << "----(Succes)----" << endl;
//			}
					
		} else {
			cout << "----(Move Failed)----" << endl;
		}
		
		
		
		
		
	}
}
	

int main(){	
	
	iniBoard();
	//		cMove(current move):	if cMove = 1 white move
	//								if cMove = 0 black move	
	
	int mate = 0;
	
	while(true)
	{
		printBoard();
		
		if(check())
		{
			if(cMove)
			{
				cout << "Check on " << kingW[0]+ 1 << 1 + kingW[1] << " by " << checkBy[0] + 1 << 1 + checkBy[1] << endl;
			} else {
				cout << "Check on " << kingB[0] + 1<< 1 + kingB[1] << " by " << checkBy[0] + 1 << 1 + checkBy[1]  << endl;
			}
		}

		mate = checkMate();
		
		if(mate == 1)
		{
			cout << "CheckMate by: ";
			
			cMove ? cout << "Black" : cout << "White";
			cout << endl;
			
			break;
		} else if(mate == -1)
		{
			cout << "Stale Mate: White = 1/2 | Black = 1/2\n";
			break;
		}

		move(cMove);
	
		(cMove)? cMove = 0 : cMove = 1;
	}
//	
	
	return 0;
}
