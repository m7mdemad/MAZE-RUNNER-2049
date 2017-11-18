DrawMaze MACRO
    PUSHA    
    
    
        RandomizeMaze        
        CalculateAddress
        
        MOV BX, ADDRESS
                         
                         
        ; PRINT AS LONG AS IT DIDN'T REACH '$' (SAME AS INT 21H , AH = 9)    
        PRINT:
            MOV AH, 2
            MOV DL, [BX]
            INT 21H
            INC BX
            CMP [BX], '$'
            JNZ PRINT
    
    POPA
                
ENDM DrawMaze   


RandomizeMaze MACRO 
    PUSHA
  
        ; GET SYSTEM TIME
        MOV AH, 2CH
        INT 21H
        
        ; MOVE HUNDREDTHS OF SECOND TO AX
        MOV AL, DL
        CBW
        
        ; TAKE HUNDREDTHS OF SECOND MOD NUMBER OF MAZES TO GET A RANDOM NUMBER
        DIV MAZES_N
        MOV RANDOM, AH

        
    POPA
        
ENDM RandomizeMaze


LoadMaze MACRO 
    PUSHA
  
        ; DECIDE WHICH FILE TO OPEN (WHICH MAZE DIFFICULTY)
        CMP MODE, '1'    ; CHECK IF THE MODE IS EASY
        JNZ HARD_MAZE  ; IF NOT GO TO HARD MAZE
        
        EASY_MAZE:
        
            MOV DX, OFFSET EASY_MAZE
            JMP CONTINUE
        
        HARD_MAZE:               
        
            MOV DX, OFFSET HARD_MAZE
            JMP CONTINUE
            
        ERROR:
            MOV AH, 4CH
            MOV AL, 0
            INT 21H
                                       
        
        CONTINUE:
            
            ; OPEN THE MAZE FILE
            MOV AH, 3DH
            MOV AL, 00
            INT 21H
            
            ; IF FILE COULDN'T BE FOUND, EXIT THE PROGRAM
            JC ERROR
            
            ; PUSH AX (FILE HANDLE)
            PUSH AX               
            
            ; CALCULATE THE AMOUNT OF BYTES TO BE SEEKED
            ; FROM THE MAZE FILE TO REACH THE RANDOM MAZE        
            MOV CL, RANDOM     
            MOV CH, 0
            
            ; CALCULATE OFFSET OF THE RANDOMLY SELECTED MAZE FROM THE BASE INDEX 
            MOV AX, ROWS
            MOV DX, COLS
            MUL DX                                               
            MUL CX
                  
            
            ; SEEK THE MAZE FILE TO THE SPECIFIC MAZE
            ; POP FILE HANDLE INTO BX      
            POP BX
            MOV CX, 0
            MOV DX, AX
            MOV AH, 42H
            MOV AL, 01H
            INT 21H
            
            ; CALCULATE NUMBER OF BYTES IN THE MAZE 
            MOV AX, ROWS
            MOV DX, COLS
            MUL DX
            
            ; READ THE MAZE FILE INTO MAZE VARIABLE
            MOV CX, AX
            MOV AH, 3FH
            MOV DX, OFFSET MAZE
            INT 21H  
            
            
            ; SAVE IT TO ADDRESS VARIABLE
            MOV ADDRESS, BX                        

        
    POPA
        
ENDM LoadMaze



CalculateAddress MACRO 
    PUSHA
    
        CMP MODE, 0    ; CHECK IF THE MODE IS EASY
        JNZ HARD_MAZE  ; IF NOT GO TO HARD MAZE
        
        EASY_MAZE:
        
            MOV BX, offset MAZE_E
            JMP CONTINUE
        
        HARD_MAZE:               
        
            MOV BX, offset MAZE_H                               
        
        CONTINUE:
        
            MOV CL, MAZE_NO     
            MOV CH, 0
            
            ; CALCULATE OFFSET OF THE RANDOMLY SELECTED MAZE FROM THE BASE INDEX 
            MOV AX, ROWS
            MOV DX, COLS
            MUL DX                                               
            ADD AX, 1       ; FOR THE '$' AT THE END OF THE STRING
            MUL CX
            
            ; ADD OFFSET TO INDEX OF MAZE TO BE PRINTED
            ADD BX, AX
            
            ; SAVE IT TO ADDRESS VARIABLE
            MOV ADDRESS, BX                        

    POPA
        
ENDM CalculateAddress






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