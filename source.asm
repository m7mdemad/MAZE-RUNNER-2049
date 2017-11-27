include 'macros.inc'
  
  
        .MODEL HUGE
        .STACK 64
        .DATA
          
RANDOM              DB       0  ; THE RANDOM NUBMBER RETURNED BY RANDOMIZE MACRO
MAZES_N             DB       38 ; NUMBER OF MAZES AVAILABLE FOR EACH MODE
MODE                DB       '2'; '1'->EASY  ,  '2'->HARD
ROWS                DW       81 ; NUMBER OF CHARS IN THE ROW
COLS                DW       21 ; NUMBER OF CHARS IN THE COL
INDEX               DW       ?  ; INDEX RETURNED BY GETINDEX MACRO          
EASY_MAZE           DB       "MAZE_E.txt",0
HARD_MAZE           DB       "MAZE_H.txt",0
MAZE                DB       2100 DUP('$')

X1                  DB       0 ; PLAYER 1 POSITION
Y1                  DB       1

X2                  DB       0 ; PLAYER 2 POSITION
Y2                  DB       1

BOMBX               DB       50 DUP(-1) ; ARRAY OF BOMBS X COORDINATES
BOMBY               DB       50 DUP(-1) ; ARRAY OF BOMBS Y COORDINATES
                                
BOMB_ACTIVE         DB       50 DUP(3)  ; 0-> ACTIVE, 1-> PLAYER1 PLANTED IT BUT NOT YET ACTIVE
                                        ; 2-> PLAYER2 PLANTED BOMB

B_COUNT             DW       1
         
BOMB_T_S            DB       100 DUP(63) ; SECOND - TIME THE BOMB PLANTED IN (3 IS EQUAL TO POSTPONE)
BOMB_T_M            DB       100 DUP(0)  ; MINUTE

P1_POSTPONE         DB       0 ; FREEZE PLAYER ONE FOR P1_POSPONE MOVES
P2_POSTPONE         DB       0 ; FREEZE PLAYER TWO FOR P2_POSPONE MOVES
        
MOTION_DELAY        DB       50
FIRE_DELAY          DB       50
        
RAND_1              DB      4 DUP (0)
RAND_2              DB      1,2,3,4


RAND_2_LNS          DB      4

R_COUNT             DB      0
R1                  DB      0
R2                  DB      0
  
        

HOLD_FIRE_1         DB      0
HOLD_FIRE_2         DB      0
        

;====== KEYS SCANCODE ============
UP_ARROW		    DB   	48H
DOWN_ARROW	     	DB		50H
RIGHT_ARROW		    DB		4DH
LEFT_ARROW		    DB		4BH


UP_ARROW_PER		EQU   	48H
DOWN_ARROW_PER		EQU		50H
RIGHT_ARROW_PER		EQU		4DH
LEFT_ARROW_PER		EQU		4BH



W_LETTER    		DB		11H
A_LETTER    		DB		1EH
S_LETTER		    DB		1FH
D_LETTER		    DB		20H  


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
        
        DrawMaze
        

        MAINLOOP:
                
                
			PrintPlayers
			PrintBombs  
			DetectAction
			
			TestBombs 1,X1,Y1
			TestBombs 2,X2,Y2
			
			CheckBombs
			
			JMP MAINLOOP
			
            
            
            


        ; TERMINATE
        MOV AH, 4CH
        MOV AL, 0
        INT 21H


MAIN    ENDP
        END MAIN