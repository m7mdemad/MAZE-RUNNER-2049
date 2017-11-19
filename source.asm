include maze-drawing-macro.inc
include player-movement-macro.inc




        .MODEL HUGE
        .STACK 64
        .DATA
          
RANDOM      DB       0  ; THE RANDOM NUBMBER RETURNED BY RANDOMIZE MACRO
MAZES_N     DB       38 ; NUMBER OF MAZES AVAILABLE FOR EACH MODE
MODE        DB       '2'; '1'->EASY  ,  '2'->HARD
ROWS        DW       81 ; NUMBER OF CHARS IN THE ROW
COLS        DW       21 ; NUMBER OF CHARS IN THE COL
INDEX       DW       ?  ; INDEX RETURNED BY GETINDEX MACRO          
EASY_MAZE   DB  "MAZE_E.txt",0
HARD_MAZE   DB  "MAZE_H.txt",0
MAZE        DB  2100 DUP('$')

X1          DB       0
Y1          DB       1

X2          DB       0
Y2          DB       1



;====== KEYS SCANCODE ============
UP_ARROW		EQU		48H
DOWN_ARROW		EQU		50H
RIGHT_ARROW		EQU		4DH
LEFT_ARROW		EQU		4BH

W_LETTER		EQU		11H
A_LETTER		EQU		1EH
S_LETTER		EQU		1FH
D_LETTER		EQU		20H      

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
			HandlePlayerMovement
			
			JMP MAINLOOP
			
            
            
            


        ; TERMINATE
        MOV AH, 4CH
        MOV AL, 0
        INT 21H


MAIN    ENDP
        END MAIN