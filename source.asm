include 'macros.inc'
  
  
        .MODEL HUGE
        .STACK 64
        .DATA
          
RANDOM              DB       0  ; THE RANDOM NUBMBER RETURNED BY RANDOMIZE MACRO
MAZES_N             DB       38 ; NUMBER OF MAZES AVAILABLE FOR EACH MODE
MODE                DB       '1'; '1'->EASY  ,  '2'->HARD
ROWS                DW       81 ; NUMBER OF CHARS IN THE ROW
COLS                DW       21 ; NUMBER OF CHARS IN THE COL
INDEX               DW       ?  ; INDEX RETURNED BY GETINDEX MACRO          
EASY_MAZE           DB       "MAZE_E.txt",0
HARD_MAZE           DB       "MAZE_H.txt",0
MAZE                DB       2100 DUP('$')

INTRO_FILE       	DB       "INTRO.txt",0
INTRO       		DB       2100 DUP('$')
     
OPTIONS_FILE      	DB       "OPTION.txt",0
     
MODES_FILE       	DB       "MODE.txt",0
MODES       		DB       2100 DUP('$')

RULES_FILE	       	DB       "RULES.txt",0
RULES				DB		 2100 DUP('$')

SCORE_FILE          DB       "SCORE.txt",0
SCOREBAR            DB       2100 DUP('$')

NAME1_FILE			DB		 "P1_NAME.txt",0
NAME2_FILE			DB		 "P2_NAME.txt",0
NAMES				DB		 2100 DUP('$')

P1_NAME				DB		 20, ?, 21 DUP('$') ; STORE THE NAME OF PLAYER1
P2_NAME				DB		 20, ?, 21 DUP('$') ; STORE THE NAME OF PLAYER2

             
WINNER_NO           DB       ? 
WINNER_FILE			DB		 "WIN.txt",0
WIN 				DB		 2100 DUP('$')    


X1                  DB       0 ; PLAYER 1 POSITION
Y1                  DB       1

X2                  DB       0 ; PLAYER 2 POSITION
Y2                  DB       1 

P1_CHAR             DB       1
P2_CHAR             DB       2
BOMB_CHAR           DB       15

BOMBX               DB       50 DUP(-1) ; ARRAY OF BOMBS X COORDINATES
BOMBY               DB       50 DUP(-1) ; ARRAY OF BOMBS Y COORDINATES
                                
BOMB_ACTIVE         DB       50 DUP(3)  ; 0-> ACTIVE, 1-> PLAYER1 PLANTED IT BUT NOT YET ACTIVE
                                        ; 2-> PLAYER2 PLANTED BOMB

B_COUNT             DW       1 

P1_POSTPONE         DB       0 ; FREEZE PLAYER ONE FOR P1_POSPONE MOVES
P2_POSTPONE         DB       0 ; FREEZE PLAYER TWO FOR P2_POSPONE MOVES
        
MOTION_DELAY        DB       20
FIRE_DELAY          DB       15
        
RAND_1              DB      4 DUP (0)
RAND_2              DB      1,2,3,4


RAND_2_LNS          DB      4
     

HOLD_FIRE_1         DB      0 ; HOLD THE FIRE OF PLAYER1 FOR HOLD_FIRE_1 MOVES
HOLD_FIRE_2         DB      0 ; HOLD THE FIRE OF PLAYER2 FOR HOLD_FIRE_2 MOVES
        
                             
XP                  DB      ?
YP                  DB      ?
                              
ASCII_RESULT        DB      3 dup('$')                              
                              

END_GAME            DB      0 

;====== KEYS SCANCODE ============
                       
                       
; CHANGE ON STEPPING ON BOMB
UP_ARROW		    DB   	48H
DOWN_ARROW	     	DB		50H
RIGHT_ARROW		    DB		4DH
LEFT_ARROW		    DB		4BH
                         


W_LETTER    		DB		11H
A_LETTER    		DB		1EH
S_LETTER		    DB		1FH
D_LETTER		    DB		20H  
                       
                       
; NEVER CHANGE
UP_ARROW_PER		EQU   	48H
DOWN_ARROW_PER		EQU		50H
RIGHT_ARROW_PER		EQU		4DH
LEFT_ARROW_PER		EQU		4BH



W_LETTER_PER		EQU		11H
A_LETTER_PER		EQU		1EH
S_LETTER_PER		EQU		1FH
D_LETTER_PER		EQU		20H  



F_LETTER		    EQU		21H
M_LETTER		    EQU		32H
    
      


; MAXIMUM NUMBER OF MAZES IN EACH MODE IS: 38

        ; EASY MAZE SPECS: 26 10 3 2 0
                
        ; HARD MAZE SPECS: 39 10 2 2 0
        
        
        .code                
MAIN    PROC FAR               
        MOV AX,@DATA
        MOV DS,AX
        
		   
		   
		                    
		GETTING_STARTED:
    		
    		GetName P1_NAME,NAME1_FILE
    		Options
    		GetName P2_NAME,NAME2_FILE
    		SetInitials
    		GetMode
    		PrintRules
            DrawIntro
            SLEEP 20
            DrawMaze
            DrawScorebar
            SetNames
            FlushBuffer
            
                  MAINLOOP:     
            
             CMP END_GAME,0
             JNZ WIN_SCREEN
                
                
			PrintPlayers
			PrintBombs  
			DetectAction
			
			TestBombs 1,X1,Y1
			TestBombs 2,X2,Y2
			
			CheckBombs 
			   
			SetScore
			 
			Winner
			
			JMP MAINLOOP
			
            
            
        WIN_SCREEN:
                 
            DrawWinScreen 
            SLEEP 50
            
        
       

MAIN    ENDP
        END MAIN 
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
        
    