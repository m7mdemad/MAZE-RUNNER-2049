include maze-drawing-macro.inc




GetIndex MACRO X,Y
    PUSHA
  
    MOV INDEX,00
    MOV BL,Y
    MOV AL,81
    MUL BL
    ADD INDEX,AX
    ADD INDEX,X
    
        
    POPA
        
ENDM GetIndex






        .MODEL HUGE
        .STACK 64
        .DATA
          
RANDOM      DB       0  ; THE RANDOM NUBMBER RETURNED BY RANDOMIZE MACRO
MAZES_N     DB       38 ; NUMBER OF MAZES AVAILABLE FOR EACH MODE
MODE        DB       '1'; '1'->EASY  ,  '2'->HARD
ROWS        DW       81 ; NUMBER OF CHARS IN THE ROW
COLS        DW       21 ; NUMBER OF CHARS IN THE COL
INDEX       DB       ?  ; INDEX RETURNED BY GETINDEX MACRO          
EASY_MAZE   DB  "MAZE_E.txt",0
HARD_MAZE   DB  "MAZE_H.txt",0
MAZE        DB  2100 DUP('$')

; MAXIMUM NUMBER OF MAZES IN EACH MODE IS: 38

        ; EASY MAZE SPECS: 26 10 3 2 0
                
        ; HARD MAZE SPECS: 39 10 2 2 0
        
        
        .code
MAIN    PROC FAR               
        MOV AX,@DATA
        MOV DS,AX
        
        DrawMaze
        
;        
;       ; MOV AH,02
;;        MOV BH,00
;         MOV DL,78 ; BL 3RD   X
;         MOV DH,00 ; BL TOL   Y
;;        INT 10H
;        GetIndex dl,dh
;        mov ah,2
;        mov dl,'M'
;        int 21h
;           

        ; TERMINATE
        MOV AH, 4CH
        MOV AL, 0
        INT 21H


MAIN    ENDP
        END MAIN