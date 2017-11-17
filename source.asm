PrintString MACRO String
    PUSHA
    MOV BX, offset String
    
    PrintAgain:
        MOV AH, 2
        MOV DL, [BX]
        INT 21H
        INC BX
        CMP [BX], '$'
        JNZ PrintAgain
    
    POPA
                
ENDM PrintString   





GetIndex MACRO X,Y
    PUSHA
  
    MOV BL,Y 
    MOV AL,ROWS
    MUL BL
    MOV INDEX,AX
    MOV AL,X  
    CBW
    ADD INDEX,AX
    
        
    POPA
        
ENDM GetIndex

             
             
             
Player1Motion MACRO Z
    PUSHA
    
      LEA BX,MAZE_E
      
      cmp Z,72 ; UP? 
      jnz IsDown
      MOV CX,INDEX
      SUB CX,81 ; MOVE UP
      ADD BX,CX
      
      CMP [BX],' ' ; TEST IF IT'S ALLOWED OR NOT
      JNZ BELL 
      MOV [BX],'M'
      SUB BX,CX
      ADD BX,INDEX
      MOV [BX],' '
      MOV INDEX,CX
      
     ; int 16h
      jmp END_IT  
              
IsDown: 
      cmp Z,80 ; DOWN? 
      jnz IsRight
      MOV CX,INDEX
      ADD CX,81 ; MOVE DOWN
      ADD BX,CX
      
      CMP [BX],' ' ; TEST IF IT'S ALLOWED OR NOT
      JNZ BELL 
      MOV [BX],'M'
      SUB BX,CX
      ADD BX,INDEX
      MOV [BX],' '
      MOV INDEX,CX
      
      ;int 16h
      jmp END_IT 
      
IsRight:
      cmp Z,77 ; RIGHT? 
      jnz IsLeft
      MOV CX,INDEX
      ADD CX,1 ; MOVE RIGHT
      ADD BX,CX
      
      CMP [BX],' ' ; TEST IF IT'S ALLOWED OR NOT
      JNZ BELL 
      MOV [BX],'M'
      SUB BX,CX
      ADD BX,INDEX
      MOV [BX],' '
      MOV INDEX,CX
      
      ;int 16h
      jmp END_IT
       
       
IsLeft:
      cmp Z,75 ; LEFT? 
      jnz BELL
      MOV CX,INDEX
      SUB CX,1 ; MOVE LEFT
      ADD BX,CX
      
      CMP [BX],' ' ; TEST IF IT'S ALLOWED OR NOT
      JNZ BELL     ; NOT ALLOWED
      MOV [BX],'M' ; ALLOWED
      SUB BX,CX
      ADD BX,INDEX
      MOV [BX],' '
      MOV INDEX,CX
      
     ; int 16h
      jmp END_IT
      
BELL:
     MOV AH,02H
     MOV DL,07H
     INT 21H
      
END_IT:      

     POPA
     MOV AH,00
     JMP CHECK
        
ENDM GetIndex

             
             
             

        .MODEL HUGE
        .STACK 64
        .DATA
          
MAZE_NO DB       0  ; THE ORDER NUBMBER OF THE MAZE INSIDE THE MODE
MODE    DB       0  ; 0->EASY  ,  1->HARD
ROWS    DB       81 ; NUMBER OF CHARS IN THE ROW
COL     DB       21 ; NUMBER OF CHARS IN THE COL
INDEX   DW       ?  ; INDEX RETURNED BY GetIndex MACRO                                                                                    


        ; 26, 10, 3, 2
                
MAZE_E  DB       '+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+',10,13
        DB       '         |     |              |     |           |  |           |              |',10,13
        DB       '+  +--+  +  +  +  +--+--+  +--+  +  +  +--+--+  +  +  +--+--+  +  +--+  +--+--+',10,13
        DB       '|  |     |  |     |     |     |  |  |     |     |     |           |     |     |',10,13
        DB       '+--+  +  +  +--+--+  +  +--+  +  +  +--+  +  +  +  +--+  +--+--+--+  +--+  +  +',10,13
        DB       '|     |     |     |  |        |  |  |     |  |  |     |     |     |     |  |  |',10,13
        DB       '+  +--+--+  +  +--+  +--+--+--+  +  +  +--+  +  +--+  +--+  +  +  +--+  +--+  +',10,13
        DB       '|        |  |     |        |  |  |  |  |     |     |  |     |  |  |     |     |',10,13
        DB       '+--+  +  +  +--+  +--+--+  +  +  +  +  +  +--+--+  +  +  +--+  +  +  +--+  +--+',10,13
        DB       '|     |  |     |     |  |  |     |     |     |  |     |  |     |  |     |     |',10,13
        DB       '+--+--+  +--+--+--+  +  +  +--+  +--+--+--+  +  +--+--+  +--+--+  +--+  +--+  +',10,13
        DB       '|     |        |     |     |     |           |  |     |  |           |  |     |',10,13
        DB       '+  +  +--+--+  +  +--+--+  +  +--+  +--+--+--+  +  +  +  +  +--+--+  +  +  +--+',10,13
        DB       '|  |        |  |     |        |     |     |        |  |     |        |  |     |',10,13
        DB       '+  +--+--+  +  +--+  +--+--+--+  +--+  +  +  +--+--+  +  +--+--+--+--+  +--+  +',10,13
        DB       '|  |     |  |     |              |     |  |        |  |              |        |',10,13
        DB       '+  +--+  +  +  +  +--+--+  +--+  +  +--+  +--+--+  +  +--+--+--+  +  +--+--+  +',10,13
        DB       '|     |     |  |  |        |     |     |  |     |  |     |  |     |        |  |',10,13
        DB       '+  +  +--+--+--+  +  +--+--+  +--+--+--+  +  +--+  +--+  +  +  +--+--+--+--+  +',10,13
        DB       '|  |              |        |              |           |        |               ',10,13
        DB       '+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+',10,13
        DB       '$'
  
        
        DB       '+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+',10,13
        DB       '                  |        |     |        |           |     |        |        |',10,13
        DB       '+  +--+--+--+--+  +  +--+--+  +--+  +--+  +  +--+--+  +  +--+  +--+  +--+--+  +',10,13
        DB       '|  |           |  |  |     |  |     |     |  |     |  |     |     |           |',10,13
        DB       '+  +  +--+--+  +  +  +  +  +  +  +--+  +--+--+  +  +  +  +  +--+  +  +--+--+--+',10,13
        DB       '|  |  |        |  |     |  |  |  |  |     |     |     |  |  |     |        |  |',10,13
        DB       '+  +  +  +--+--+  +  +--+  +  +  +  +  +  +  +--+--+--+  +  +  +--+--+--+  +  +',10,13
        DB       '|  |  |  |        |     |     |  |  |  |     |     |     |  |     |        |  |',10,13
        DB       '+  +--+  +  +  +--+--+  +--+--+  +  +  +--+--+  +  +  +--+  +--+  +  +--+--+  +',10,13
        DB       '|        |  |     |           |  |     |     |  |     |  |     |  |     |     |',10,13
        DB       '+--+--+--+  +--+  +--+  +--+  +  +  +--+  +  +  +--+--+  +  +  +  +--+  +  +  +',10,13
        DB       '|  |     |     |  |     |     |  |     |  |           |     |  |  |  |  |  |  |',10,13
        DB       '+  +  +  +--+  +--+  +--+--+--+  +--+--+  +--+--+--+  +--+--+  +  +  +  +  +  +',10,13
        DB       '|  |  |     |     |              |                 |  |     |     |  |     |  |',10,13
        DB       '+  +  +--+  +--+  +--+--+--+--+  +  +--+  +--+--+  +  +  +--+--+--+  +--+--+  +',10,13
        DB       '|  |     |  |     |           |     |        |     |              |     |     |',10,13
        DB       '+  +  +  +  +  +--+  +--+--+  +--+--+  +  +  +  +--+--+--+--+--+  +--+  +  +--+',10,13
        DB       '|  |  |  |  |              |  |        |  |  |     |  |        |  |  |  |     |',10,13
        DB       '+  +--+  +  +--+--+  +--+  +  +  +--+--+--+  +--+  +  +  +--+  +  +  +  +--+  +',10,13
        DB       '|        |           |     |     |              |        |     |     |         ',10,13
        DB       '+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+',10,13
        DB       '$'
        
        
        DB       '+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+',10,13
        DB       '      |  |        |     |     |     |     |              |     |     |     |  |',10,13
        DB       '+--+  +  +  +--+  +  +  +  +  +  +  +  +  +--+--+  +--+  +--+  +  +  +--+  +  +',10,13
        DB       '|  |  |     |     |  |     |  |  |     |        |  |  |     |  |  |     |     |',10,13
        DB       '+  +  +--+--+  +  +  +--+--+--+  +--+  +--+--+  +  +  +  +  +  +  +--+  +  +--+',10,13
        DB       '|  |     |     |  |  |        |  |     |     |  |     |  |     |     |        |',10,13
        DB       '+  +--+  +  +--+--+  +  +--+  +  +--+--+  +--+  +--+--+  +--+--+--+  +  +--+  +',10,13
        DB       '|  |     |        |  |     |  |  |     |                 |        |  |     |  |',10,13
        DB       '+  +  +--+--+--+  +  +  +--+  +  +  +  +--+--+  +--+--+--+  +--+  +  +--+  +  +',10,13
        DB       '|           |  |     |  |     |  |  |     |     |              |  |  |  |  |  |',10,13
        DB       '+--+  +  +  +  +--+  +--+  +--+  +  +--+  +  +--+--+--+--+--+  +  +  +  +  +  +',10,13
        DB       '|     |  |     |  |     |     |  |  |     |                    |     |     |  |',10,13
        DB       '+  +--+  +  +--+  +--+  +  +--+  +--+  +--+--+  +--+--+--+--+--+  +--+--+--+--+',10,13
        DB       '|     |  |              |     |  |        |     |     |  |     |        |     |',10,13
        DB       '+--+  +  +--+--+--+--+--+--+  +  +  +  +  +--+--+  +  +  +  +  +--+--+  +  +  +',10,13
        DB       '|     |  |           |     |  |     |  |     |     |     |  |  |     |     |  |',10,13
        DB       '+  +--+--+  +--+--+  +  +  +  +--+--+--+--+  +  +--+  +--+  +  +  +  +--+--+  +',10,13
        DB       '|           |     |     |     |     |        |     |  |  |  |     |  |        |',10,13
        DB       '+--+--+  +--+  +  +  +  +--+--+  +  +  +--+--+--+  +  +  +  +--+--+--+  +--+  +',10,13
        DB       '|        |     |     |           |                 |     |              |      ',10,13
        DB       '+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+--+',10,13
        DB       '$'
          
          
          
        ; 39, 10, 2, 2
MAZE_H  DB       '+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+',10,13
        DB       '    |   |                   |         |         |   |     |   |           |   |',10,13
        DB       '+-+ + +-+ +-+-+ +-+-+-+-+-+ + +-+-+-+ + +-+-+-+-+ + +-+-+ + +-+ +-+-+-+-+ + + +',10,13
        DB       '|   |         | |         | | |   | | |           |   |   |     |   | |   | | |',10,13
        DB       '+ +-+-+-+ +-+ + +-+-+ +-+ + + + + + + +-+-+-+-+-+-+-+ + +-+-+-+-+-+ + + +-+ + +',10,13
        DB       '|   |     |   | |   |   | | | | |   | |     |     |   |   |         |       | |',10,13
        DB       '+-+ + +-+-+-+-+ + + +-+ + + + + +-+-+ +-+-+ + +-+ + + +-+ + +-+-+-+-+-+-+ +-+-+',10,13
        DB       '| | | |       |   | |   |   | |       |     | |   | |   | |   |           |   |',10,13
        DB       '+ + + + +-+-+ +-+-+ + +-+-+-+ +-+-+-+-+ +-+-+ +-+-+-+-+ + + + + +-+-+-+ +-+ + +',10,13
        DB       '|   | |     |       |   |   |     |     |   |           | | | | |       |   | |',10,13
        DB       '+-+ + +-+-+ +-+-+-+ +-+ + + +-+-+ + +-+-+-+ +-+-+ +-+-+-+ + +-+ +-+-+ +-+-+-+ +',10,13
        DB       '| | |   | |   |   |   |   | |     |     |   |   |   |           |     |     | |',10,13
        DB       '+ + +-+ + +-+ + + +-+-+-+-+ + +-+-+-+-+ + +-+ +-+-+ + +-+ +-+-+-+ +-+-+ + +-+ +',10,13
        DB       '| |   | | | | | |         | | |       |     |       | |   |   | | |   | |   | |',10,13
        DB       '+ + + + + + + + +-+-+-+ +-+ + +-+-+-+ +-+ +-+ +-+-+-+-+ + + + + + + +-+ +-+ + +',10,13
        DB       '| | | | |     |   |   |       |   |   |                 | | |   |     |   |   |',10,13
        DB       '+ + +-+ +-+-+-+-+ + + +-+-+ +-+ + + +-+ + +-+ +-+-+-+-+-+-+ +-+-+-+ + +-+-+ +-+',10,13
        DB       '| |     |   |     | |     |     |   |   | |   |   |   |   | |       |         |',10,13
        DB       '+ +-+-+-+ + + +-+-+ +-+-+-+-+-+ +-+-+-+-+ + +-+ + + + +-+ + +-+-+ +-+-+-+-+ + +',10,13
        DB       '|         |                   |           |     |   |     |       |         |  ',10,13
        DB       '+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+',10,13
        DB       '$'
        
        DB       '+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+',10,13
        DB       '  |     |     |       |       |   |   |   |         |   |         |   |   |   |',10,13
        DB       '+ + + + + +-+ + +-+ + + +-+-+ +-+ + + + + + + +-+-+ + + + +-+ +-+-+ + + + +-+ +',10,13
        DB       '|   | | | |   | |   |   |   | |   | | | |   |   |   | | |   |   |   |   |     |',10,13
        DB       '+-+-+ + +-+ +-+ + +-+-+-+ + + + +-+ + + +-+-+-+-+ +-+ + +-+ + + + +-+-+-+-+-+ +',10,13
        DB       '| |   |   | |   | | |   | |   | |   | | |   |         |     | | |   | |       |',10,13
        DB       '+ + +-+ + + +-+-+ + + + + +-+-+ + +-+ +-+ + + +-+-+-+-+-+-+-+ +-+-+ + + +-+-+ +',10,13
        DB       '|   |   | | |   | |   | |   |   |   |     |   |             |       |   |     |',10,13
        DB       '+ +-+-+-+ + + + + + +-+ +-+ + +-+-+ +-+-+-+ +-+ +-+-+-+-+-+ +-+-+-+-+ +-+ +-+-+',10,13
        DB       '| |   |       |   |   |     |   |   | |   |     |         | | |   |   |   |   |',10,13
        DB       '+ +-+ +-+-+ +-+-+-+-+ +-+-+-+-+ + +-+ + + +-+-+-+ +-+ +-+-+ + + + + +-+ +-+ + +',10,13
        DB       '| |   |   | |             |   | |     | |   |   |   | |     |   |   | | |   | |',10,13
        DB       '+ + +-+ +-+ +-+-+ +-+-+-+ +-+ + +-+-+-+ +-+ + + +-+ +-+ +-+ +-+-+-+-+ + + +-+ +',10,13
        DB       '|   | |     |     | |                 | | | | |   |     |   | |         |   | |',10,13
        DB       '+ +-+ +-+-+-+ + +-+ + +-+-+-+ + +-+-+ + + + + +-+ +-+-+-+ +-+ + +-+-+ + +-+-+ +',10,13
        DB       '| |         | |   |   | |     |     |   | | |   | | |         | | |   |   |   |',10,13
        DB       '+ + + +-+-+-+ +-+-+-+-+ + +-+-+-+-+ +-+-+ + +-+ + + + +-+-+-+-+ + + +-+-+ + +-+',10,13
        DB       '| | | |     |       | | |       | |     |       | |   |       | |   |     |   |',10,13
        DB       '+ +-+ + +-+ +-+-+-+ + + +-+-+-+ + +-+ +-+-+-+-+-+ +-+ + +-+-+ + + +-+-+-+-+-+ +',10,13
        DB       '|     |   |           |             |           |     |     |   |              ',10,13
        DB       '+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+',10,13
        DB       '$'
        
        DB       '+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+',10,13
        DB       '  |         |   |   |     |   |     |   |   |   |         |     |     |     | |',10,13
        DB       '+ + +-+-+-+ + + +-+ + + +-+ + + +-+ + +-+ + +-+ +-+-+-+-+ + +-+ + +-+ + +-+ + +',10,13
        DB       '| | | |     | |     | |   | |     |   |   |   | |     |   |   | |   | |   |   |',10,13
        DB       '+ + + + +-+-+ +-+-+-+ +-+ +-+-+-+ +-+-+ +-+-+ + + +-+ + +-+-+-+ +-+-+ +-+ + +-+',10,13
        DB       '|   |     |   |     | | |   |   | |     |     | |   |   |     |     |   | |   |',10,13
        DB       '+-+-+-+-+ + +-+ +-+-+ + +-+ + +-+ + +-+-+ +-+-+ +-+-+ +-+-+ + +-+-+ +-+ + +-+ +',10,13
        DB       '|         |   |   |   |   | |       |     |   | |     |   | | |     |     | | |',10,13
        DB       '+ +-+-+-+-+ + +-+ + +-+ + + + +-+ +-+ +-+-+ + + + +-+-+ + +-+ + + +-+ + +-+ + +',10,13
        DB       '|   | |     |   |   |   | | |   |   |   |   | | |     | |     | | | | | |   | |',10,13
        DB       '+-+ + + +-+-+-+ +-+ +-+-+ + +-+-+ + +-+ + +-+ + +-+-+ + +-+-+-+ + + + +-+ +-+ +',10,13
        DB       '|   |   |     |   | |   |   |     |   |     | | |   | | |       |   | |   |   |',10,13
        DB       '+ +-+ +-+ +-+-+-+ + + + + +-+ +-+-+-+-+-+-+-+ + + + + + + +-+-+-+-+-+ + +-+ +-+',10,13
        DB       '|   | |   |     | |   | | |   |               | | | | | |       |   | |   | | |',10,13
        DB       '+-+ + + + + +-+ + +-+-+ + + +-+ +-+-+ +-+-+-+-+ +-+ + + + +-+ + +-+ + +-+ + + +',10,13
        DB       '|   |   | | |   |   |   |     | |   | |         |   |   |   | | |     | | | | |',10,13
        DB       '+ +-+ +-+ + + +-+-+ + +-+-+-+ + + + +-+ +-+-+ +-+ +-+ +-+-+-+ + + + + + + + + +',10,13
        DB       '| |   |   | |       | |   |   |   |       |   |     | |       | | | |   |   | |',10,13
        DB       '+ +-+-+ +-+ +-+-+-+-+ + + + +-+-+-+-+-+ + + +-+ +-+-+ + +-+-+-+ + + +-+-+-+-+ +',10,13
        DB       '|         |           | |   |           | |                   |   |            ',10,13
        DB       '+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+',10,13
        DB       '$'
        
        
        .code
MAIN    PROC FAR               
        MOV AX,@DATA
        MOV DS,AX
        
                         
        MOV DL,00 ; BL 3RD   X
        MOV DH,01 ; BL TOL   Y
        GetIndex dl,dh
        MOV BX, INDEX
        MOV MAZE_E[BX],'M'            

        
      ;  PrintString MAZE_E
  
CHECK:  
        


        MOV AH,00
        MOV AH,1
        INT 16H
        JZ CHECK
        Player1Motion AH
        
        
        HLT
MAIN    ENDP
        END MAIN