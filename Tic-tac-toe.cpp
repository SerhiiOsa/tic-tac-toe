#include <iostream>
#include <stdlib.h>
#include <ctime>
#include <bits/stdc++.h>
#include<string>
#include<cstring>
#include<cctype>
#include<typeinfo>
#include<cstdlib>
#include<stdio.h>
#include <conio.h>
using namespace std;

const int size=5; //The game board size is 5*5
int	ai_level=3; //The level of AI (default - the highest)
	//Showing the main_menu function
void Show_main_menu();
	//Showing the options_menu function
void Show_options_menu();
	//Showing the rules function
void Show_rules();
	//Whose turn will be the first function	
void First_turn(char *f_t, char cr, char nl);
	//Changing player who turn next function
void Next_turn(char *n_t, char cr, char nl);
	//Showing gameplay screen function
void Show_game_screen(char n_t, char g_s[][size], int m, int n);
	//Turn checking function
void Turn(bool *exit_round, char n_t, int g_b[][size], int mi, int ni, char g_s[][size], int ms, int ns );
	//For checking backend part function (only while codding/testing)
void Show_how_it_runs(int g_b_cr[][size], int mc, int nc, int g_b_nl[][size], int mn, int nn);
	//Diagonale checking for rezult function
bool Diagonale_check(int arr[][size], int m, int n, int line_counter_value);
	//Check if smb won the game function
bool Check_for_win_combination(int g_d[][size], int m, int n);
	//Check for only draw result function
bool Check_for_draw(int g_b_cr[][size], int mc, int nc, int g_b_nl[][size], int mn, int nn);
	//AI turn processing function
void AI_turn(char n_t, int g_b[][size], int mi, int ni, int g_b_op[][size], int mio, int nio, char g_s[][size], int ms, int ns );
	//searching for pottentional winner combination function (puts between two)
int Check_between_two(int g_b[][size], int mi, int ni, char g_s[][size], int ms, int ns);
	//searching for pottentional winner combination function (puts next to two)	
int Check_next_to_two(int g_b[][size], int mi, int ni, char g_s[][size], int ms, int ns);
/*			--------------------------------------
						Here the programm starts!!!
			--------------------------------------
*/			
int main() {
	bool end_the_game=0; //leave the programm if true
	string menu_mod;
		char now_turn; //Whose turn is it now
		char crosses='X', nulles='O'; //players(crosses - player1, nulles - player2) and symbols that are used (can be changed in options menu)
					//Main menu
	while(!end_the_game){
		system("cls");
		Show_main_menu();
			//Choosing option from main menu
		menu_mod="0";
		cout<<"\nPlease choose option from menu\n";
		while(menu_mod!="1" && menu_mod!="2" && menu_mod!="3" && menu_mod!="4" && menu_mod!="5" && menu_mod!="6"){
			cin>>menu_mod;
			cout<<"Wrong option, please try from the menu\n";
		}
		system("cls");
		if(menu_mod=="6") // Quit the game
			end_the_game=1;
		if(menu_mod=="3"){ //Options
			bool to_main_menu=0; //Return to the main menu if true
			while(!to_main_menu){
				system("cls");
				Show_options_menu();
					//Choosing option from options menu
				string option_mod="0";
				cout<<"\nPlease choose option from menu\n";
				while(option_mod!="1" && option_mod!="2" && option_mod!="3"){
					cin>>option_mod;
					cout<<"Wrong option, please try from the menu\n";					
				}
				if(option_mod=="1"){ //Changing AI level
					string ai_level_string;
					do{
						system("cls");
						cout<<"\tChanging AI level\n";
						cout<<"\nChange to:\t low - Press 1\n\t\t middle - Press 2\n\t\t high - Press 3\n";
						cin>>ai_level_string; //Changing level of AI for single player mod
					}while(ai_level_string!="1" && ai_level_string!="2" && ai_level_string!="3");
					ai_level = (ai_level_string=="1"?1:(ai_level_string=="2"?2:3));
				}
				if(option_mod=="2"){ //Changing gaming symbols
					system("cls");
					cout<<"\n\tEnter your player (or first player) game symbol\t ";
					cin>>crosses; //changing symbol for human or 1st player in two players game mod
					cout<<"\n\tEnter computer (or second player) game symbol\t ";
					cin>>nulles; //changing symbol for computer or 2nd player in two players game mod
				}
				system("cls");
				if(option_mod=="3") //Return to the main menu
					to_main_menu=1;
			}
		}
		if(menu_mod=="4") 	//Reading rules	
			Show_rules();
		if(menu_mod=="5"){    //Information about the program	
			cout<<"\n\n\t\tTIC-TAC-TOE 5x5 ver 1.0\n\n";
			cout<<"\tMade by Serhii Osavelyuk 12.01.23.\n";
			cout<<"\tIt was a project after learning beginner course of C++ in Vinnitsya IT Academy.\n\n";
			system("pause");
		}
		if(menu_mod=="1" || menu_mod=="2"){ //single player or two players mods
		/* * * * * * * * * * * * * * * * * * * *
				Here the game starts
		* * * * * * * * * * * * * * * * * * * */
		bool win=0, draw=0; //win or draw end resaults
			//Gameplay boards for calculation
		int game_board_cr[][size]={ //for 1st player (human)
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,0,0,0,0},
		};
			int game_board_nl[][size]={ //for 2nd player (or computer)
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,0,0,0,0},
			{0,0,0,0,0},
		};
			//Gameplay board for screen
		char game_screen[][size]={
			{' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' '},
			{' ',' ',' ',' ',' '}
		};
		First_turn(&now_turn, crosses, nulles);
			//game playing loop
		for(int i=0;i<size*size;i++){
			bool exit_round=0; //leaving current game if true
			if(menu_mod=="1")
				cout<<"\t\t\t\tSingle player game\n\n";
			if(menu_mod=="2")
				cout<<"\t\t\t\tTwo players game\n\n";
			Show_game_screen(now_turn, game_screen, size, size);
			if(win==1)
				break;
			if(draw==1){
				cout<<"\n\n            Here will be no winner in the round:)\n\nIf you want return to the main menu press \"Esc\"\n\n";
				if (_getch()==27)
	    			break;
			}
			if(now_turn==crosses){  //human
				//Show_how_it_runs(game_board_cr, size, size, game_board_nl, size, size);
				Turn(&exit_round, now_turn, game_board_cr, size, size, game_screen, size, size);
					if (exit_round==1)
						break;
				win=Check_for_win_combination(game_board_cr, size, size);
			}
			else{  //computer
				//Show_how_it_runs(game_board_cr, size, size, game_board_nl, size, size);
				if(menu_mod=="1")
				AI_turn(now_turn, game_board_nl, size, size, game_board_cr, size, size, game_screen, size, size);
				else if(menu_mod=="2")
				Turn(&exit_round, now_turn, game_board_nl, size, size, game_screen, size, size);
					if (exit_round==1)
						break;
				win=Check_for_win_combination(game_board_nl, size, size);	
			}
			if(win==0){ //After smb win the will be no turnes at last and we do not need changing turn
				Next_turn(&now_turn, crosses, nulles);
			}
			draw=Check_for_draw(game_board_cr, size, size, game_board_nl, size, size);
			system("cls");	
		}
		if(win==1)
			cout<<"\n\n             "<<now_turn<<"  won :)\n\n";		
		else
			cout<<"\n\n             Friendshtip won ;)\n\n";
		system("pause");
		}		
	}
}

	//Showing the main_menu function
void Show_main_menu(){
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t\t\t";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
	cout<<"\xBA                          \xBA\t\t\t\t\t";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xBA Single Player   Press 1  \xBA\t\t\t\t\t";
	cout<<"\xBA About           Press 5  \xBA\n";
	cout<<"\xBA                          \xBA\t\t\t\t\t";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t\t\t\t";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xBA Two Players     Press 2  \xBA\n";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xBA Options         Press 3  \xBA\n";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\t\t\t\t\t";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
	cout<<"\xBA                          \xBA\t\t\t\t\t";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xBA Rules           Press 4  \xBA\t\t\t\t\t";
	cout<<"\xBA Quite the game  Press 6  \xBA\n";
	cout<<"\xBA                          \xBA\t\t\t\t\t";
	cout<<"\xBA                          \xBA\n";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\t\t\t\t\t";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
}

	//Showing the options_menu function
void Show_options_menu(){
cout<<"\n\n\t\t\t\tOptions\n";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
	cout<<"\xBA                        \xBA\n";
	cout<<"\xBA AI level\tPress 1  \xBA\n";
	cout<<"\xBA                        \xBA\n";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
	cout<<"\xBA                        \xBA\n";
	cout<<"\xBA Game symbols\tPress 2  \xBA\n";
	cout<<"\xBA                        \xBA\n";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
	cout<<"\xC9\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBB\n";
	cout<<"\xBA                        \xBA\n";
	cout<<"\xBA Quit options\tPress 3  \xBA\n";
	cout<<"\xBA                        \xBA\n";
	cout<<"\xC8\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xBC\n";
}

	//Showing the rules function
void Show_rules(){
	cout<<"\n\n\t\t\tRULES FOR TIC-TAC-TOE 5x5 \n\n";
	cout<<"\t1. The game is played on a grid that's 5 squares by 5 squares.\n";
	cout<<"\t2. Default you are X, your friend (or the computer in this case) is O.\n";
	cout<<"\tPlayers take turns putting their marks in empty squares.\n";
	cout<<"\t3. The first player to get 4 of his/her marks in a row\n";
	cout<<"\t(up, down, across, or diagonally) is the winner.\n";
	cout<<"\t4. When all 25 squares are full, the game is over.\n";
	cout<<"\tIf no player has 4 marks in a row, the game ends in a tie.\n\n";
	cout<<"\n\n\t\t\tHow to play\n\n";
	cout<<"\tAll visual buttons in all the menus and cells in the game board have their own digits.\n";			
	cout<<"\tTo make your choice in the game or option menus press one digit and press\"Enter\" button.\n";
	cout<<"\tTo make your turn in the game use two digits pressing buttons and press \"Enter\" button.\n";
	cout<<"\tYou can exit current game pressing exit button (\"e\") end \"Enter\".\n\n";						
	system("pause");
}

	//Whose turn will be the first function	
void First_turn(char *f_t, char cr, char nl){
	int random;
	srand(time(NULL));
	random=rand()%10+1;
	if(random%2==0)
		*f_t = cr;		
	else
		*f_t = nl;
}

	//Changing player who turn next function
void Next_turn(char *n_t, char cr, char nl){
	if(*n_t == cr)
		*n_t = nl;		
	else
		*n_t = cr;			
}

	//Showing gameplay screen function
void Show_game_screen(char n_t, char g_s[][size], int m, int n){
	cout<<"\t\tTurn "<<n_t<<"\n\n";
	cout<<"     1    2    3    4    5\n";
	for(int i=0;i<m;i++){
		cout<<"   ";
		for(int j=0;j<n;j++){
			cout<<"\xCD\xCD\xCD\xCD\xCD";
		}
		cout<<"\n "<<i+1;		
		for(int k=0;k<n;k++){
			cout<<" \xBA ";
			cout<<g_s[i][k]<<" ";	
		}
		cout<<" \xBA\n";
	}
	cout<<"   \xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD\xCD";	
}

	//Turn checking function
void Turn(bool *exit_round, char n_t, int g_b[][size], int mi, int ni, char g_s[][size], int ms, int ns){
	char turn_char[] = " "; //getting turn as string from keyboard
	int turn; //player's turn
	cout<<"\n\nEnter two digits for turn (row and column)\n";
	cout<<"To leave the round press \"e\"(EXIT)\n";
	for(;;){
		for(int i=0;i<2;i++){
			cin>>turn_char[i];
			if(turn_char[i]=='e'){
				*exit_round=1;				
				break;
			}
		}
		if(*exit_round==1)
			break;
		turn=0;	
		for(int i=0;i<2;i++){
			turn=turn*10+turn_char[i]-48;
		}
		if(turn/10<1 || turn/10>5 || turn%10<1|| turn%10>5) 		//Check if the number is correct
			cout<<"Wrong turn. Try again\n";
		else if(g_s[turn/10-1][turn%10-1]!=' ')					//Check if the number is still available
			cout<<"The cell is already filled. Try an other one\n";
		else
			break;	
	}	
	g_b[turn/10-1][turn%10-1]=1;
	g_s[turn/10-1][turn%10-1]=n_t;								
}

	//For checking backend part (only while codding/testing)
void Show_how_it_runs(int g_b_cr[][size], int mc, int nc, int g_b_nl[][size], int mn, int nn){
	cout<<"\n\n";
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<g_b_cr[i][j]<<"   ";
		}	
		cout<<"\n\n";
	}
	cout<<"\n\n";
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			cout<<g_b_nl[i][j]<<"   ";
		}	
		cout<<"\n\n";
	}
	
}

	//Check if smb won the game function
bool Check_for_win_combination(int g_d[][size], int m, int n){
	int line_counter=0, line_counter_value=4;
	bool win=0;
		//Row checking
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(g_d[i][j]==1){
				line_counter++;
				if(line_counter==line_counter_value)
					win=1;
			}else
				line_counter=0;
		}
		line_counter=0;
	}
		//Coloumn checking
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(g_d[j][i]==1){
				line_counter++;
				if(line_counter==line_counter_value)
					win=1;
			}else
				line_counter=0;
		}
		line_counter=0;
	}
		//Diagonale checking
	if(Diagonale_check(g_d, size, size, line_counter_value)==1)
	     win=1;
	     
	return win;
}

	//Diagonale checking for rezult function
bool Diagonale_check(int arr[][size], int m, int n, int line_counter_value){
	bool rezult=0;
	if(arr[0][0]+arr[1][1]+arr[2][2]+arr[3][3]==line_counter_value || arr[1][1]+arr[2][2]+arr[3][3]+arr[4][4]==line_counter_value ||
	   arr[0][1]+arr[1][2]+arr[2][3]+arr[3][4]==line_counter_value || arr[1][0]+arr[2][1]+arr[3][2]+arr[4][3]==line_counter_value ||
	   arr[4][0]+arr[3][1]+arr[2][2]+arr[1][3]==line_counter_value || arr[3][1]+arr[2][2]+arr[1][3]+arr[0][4]==line_counter_value ||
	   arr[0][3]+arr[1][2]+arr[2][1]+arr[3][0]==line_counter_value || arr[1][4]+arr[2][3]+arr[3][2]+arr[4][1]==line_counter_value)
	   	rezult=1;
	     
	return rezult;
}

	//Check for only draw result function
bool Check_for_draw(int g_b_cr[][size], int mc, int nc, int g_b_nl[][size], int mn, int nn){
	bool cr_draw=1, nl_draw=1;
	int line_counter=0, line_counter_value=0;
		//Checking cross board for a draw for nulles
		//Row checking
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(g_b_cr[i][j]==0){
				line_counter++;
				if(line_counter==4)
					nl_draw=0;
			}else
				line_counter=0;
		}
		line_counter=0;
	}
		//Coloumn checking
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(g_b_cr[j][i]==0){
				line_counter++;
				if(line_counter==4)
					nl_draw=0;
			}else
				line_counter=0;
		}
		line_counter=0;
	}
		//Diagonale checking
	if(Diagonale_check(g_b_cr, size, size, line_counter_value)==1)
	   	nl_draw=0;
		//Checking null board for a draw for crosses
		//Row checking
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(g_b_nl[i][j]==0){
				line_counter++;
				if(line_counter==4)
					cr_draw=0;
			}else
				line_counter=0;
		}
		line_counter=0;
	}
		//Coloumn checking
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(g_b_nl[j][i]==0){
				line_counter++;
				if(line_counter==4)
					cr_draw=0;
			}else
				line_counter=0;
		}
		line_counter=0;
	}
		//Diagonale checking
		if(Diagonale_check(g_b_nl, size, size, line_counter_value)==1)
	   	cr_draw=0;      
	return cr_draw*nl_draw;
}

	//AI turn processing
void AI_turn(char n_t, int g_b[][size], int mi, int ni, int g_b_op[][size], int mio, int nio, char g_s[][size], int ms, int ns ){
	int turn=0; //player's turn
	cout<<"\n\nComputer is thinking\t";
		//searching for winner combination (1st step)
	for(int i=0;i<size;i++){
		for(int j=0;j<size;j++){
			if(g_s[i][j]==' '){
				g_b[i][j]=1;
				if(Check_for_win_combination(g_b, size, size)==1){
					turn=(i+1)*10+(j+1);
					break;
				}else
					g_b[i][j]=0;			
			}
			if(turn!=0)
				break;
		}
		if(turn!=0)
			break;
	}
	if(turn==0){
			//searching for opponent winner combination (2nd step)
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(g_s[i][j]==' '){
				g_b_op[i][j]=1;
				if(Check_for_win_combination(g_b_op, size, size)==1){
					turn=(i+1)*10+(j+1);
					g_b_op[i][j]=0;
					break;
				}else
					g_b_op[i][j]=0;			
				}
			if(turn!=0)
				break;
			}
		if(turn!=0)
			break;
		}	
	}
	if(turn==0 && ai_level>1){
			//searching for pottentional winner combinations (3-4th steps)	
		turn=Check_between_two(g_b, size, size, g_s, size, size);
	}
	if(turn==0 && ai_level>1){
		turn=Check_next_to_two(g_b, size, size, g_s, size, size);
	}			
	if(turn==0 && ai_level>1){
			//searching for opponent pottentional winner combination (5-6th steps)
		turn=Check_between_two(g_b_op, size, size, g_s, size, size);
	}
	if(turn==0 && ai_level>1){
		turn=Check_next_to_two(g_b_op, size, size, g_s, size, size);
	}
	if(turn==0 && ai_level>2){
			//Smart turn at the beginning (7th step)			
		if(g_s[2][2]==' ')
			turn=33;
		else if(g_s[3][1]==' ')
			turn=42;
		else if(g_s[3][3]==' ')
			turn=44;
		else if(g_s[1][1]==' ')
			turn=22;
		else if(g_s[1][3]==' ')
			turn=24;			
	}	
	if(turn==0){
			//Random turn - if no other logical turns (8th step)
		srand(time(NULL));
		for(int i=0;;i++){
			if(i==100000) //used for faster AI turning (giving AI time for loop)
				break;
			turn=rand()%45+11;
			if(turn/10<1 || turn/10>5 || turn%10<1|| turn%10>5);	//Check if the number is correct			
			else if(g_s[turn/10-1][turn%10-1]!=' ');				//Check if the number is still available
			else
				break;
		}
	}
	if(turn==0){
			//Searching for turn from the begining (used for faster AI turning) (9th step)
		for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(g_s[i][j]==' '){
					turn=(i+1)*10+(j+1);
					break;	
				}
			}
		}
	}
		//getting turn
	g_b[turn/10-1][turn%10-1]=1;
	g_s[turn/10-1][turn%10-1]=n_t;								
}

	//searching for pottentional winner combination (puts between two)
int Check_between_two(int g_b[][size], int mi, int ni, char g_s[][size], int ms, int ns){
	int turn=0;
	for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(g_s[i][j]==' '){
					if((g_b[i-1][j-1]==1 && g_b[i+1][j+1]==1 && g_s[i-2][j-2]==' ' && g_s[i+2][j+2]==' ') || 
					(g_b[i-1][j]==1 && g_b[i+1][j]==1 && g_s[i-2][j]==' ' && g_s[i+2][j]==' ') ||
					(g_b[i-1][j+1]==1 && g_b[i+1][j-1]==1 && g_s[i-2][j+2]==' ' && g_s[i+2][j-2]==' ') || 
					(g_b[i][j-1]==1 && g_b[i][j+1]==1 && g_s[i][j-2]==' ' && g_s[i][j+2]==' ')){
						turn=(i+1)*10+(j+1);
						break;								
					}
				}
				if(turn!=0)
				break;
			}
			if(turn!=0)
			break;
		}
	return turn;	
}

	//searching for pottentional winner combination (puts next to two)	
int Check_next_to_two(int g_b[][size], int mi, int ni, char g_s[][size], int ms, int ns){
	int turn=0;
	for(int i=0;i<size;i++){
			for(int j=0;j<size;j++){
				if(g_s[i][j]==' '){
					if((g_b[i-1][j-1]==1 && g_b[i-2][j-2]==1 && g_s[i-3][j-3]==' ' && g_s[i+1][j+1]==' ') || 
					(g_b[i-1][j]==1 && g_b[i-2][j]==1 && g_s[i-3][j]==' ' && g_s[i+1][j]==' ') ||
					(g_b[i-1][j+1]==1 && g_b[i-2][j+2]==1 && g_s[i-3][j+3]==' ' && g_s[i+1][j-1]==' ') || 
					(g_b[i][j+1]==1 && g_b[i][j+2]==1 && g_s[i][j+3]==' ' && g_s[i][j-1]==' ') ||
					(g_b[i+1][j+1]==1 && g_b[i+2][j+2]==1 && g_s[i+3][j+3]==' ' && g_s[i-1][j-1]==' ') || 
					(g_b[i+1][j]==1 && g_b[i+2][j]==1 && g_s[i+3][j]==' ' && g_s[i-1][j]==' ') ||	
					(g_b[i+1][j-1]==1 && g_b[i+2][j-2]==1 && g_s[i+3][j-3]==' ' && g_s[i-1][j+1]==' ') || 
					(g_b[i][j-1]==1 && g_b[i][j-2]==1 && g_s[i][j-3]==' ' && g_s[i][j+1]==' ')){
						turn=(i+1)*10+(j+1);
						break;								
					}
				}
				if(turn!=0)
				break;
			}
			if(turn!=0)
			break;
		}
	return turn;	
}
