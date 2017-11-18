DrawMaze MACRO
    PUSHA    
    
        RandomizeMaze 
        LoadMaze

		; CLEAR THE SCREEN
		MOV AH, 06
		MOV AL, 00
		MOV BH, 07
		MOV CH, 00
		MOV CL, 00
		MOV DH, 24
		MOV DL, 79
		INT 10H
    
		; MOVE CURSOR TO START OF SCREEN
		MOV AH, 02
		MOV BH, 00
		MOV DL, 00
		MOV DH, 00
		INT 10H
		
		
        MOV BX, OFFSET MAZE
                         
                         
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
        JNZ H_MAZE  ; IF NOT GO TO HARD MAZE
        
        E_MAZE:
        
            MOV DX, OFFSET EASY_MAZE
            JMP CONTINUE
        
        H_MAZE:               
        
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
            
    POPA
        
ENDM LoadMaze
