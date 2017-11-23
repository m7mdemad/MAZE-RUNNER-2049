DrawMaze MACRO
    PUSHA    
    
        RandomizeMaze 
        LoadMaze
		
		;; SET CURSOR TO INVISIBLE
		RemoveCursor
		
		;; CLEAR THE SCREEN
		MOV AH, 06
		MOV AL, 00
		MOV BH, 07
		MOV CH, 00
		MOV CL, 00
		MOV DH, 24
		MOV DL, 79
		INT 10H
    
		;; MOVE CURSOR TO START OF SCREEN
		MOV AH, 02
		MOV BH, 00
		MOV DL, 00
		MOV DH, 00
		INT 10H
		
		
        MOV BX, OFFSET MAZE
		PUSH BX
                         
                         
        ;; PRINT AS LONG AS IT DIDN'T REACH '$' (SAME AS INT 21H , AH = 9)    
        PRINT:
			CMP [BX], ' '
			JZ INCREMENT
			
			CMP [BX], 13
			JZ INCREMENT
			
			
			CMP [BX], 10
			JZ NEW_LINE
			
			
			mov ah,9 ;Display
			mov al,' ' ;SPACE
			mov bh,0 ;Page 0
			mov cx,1h ;1 time
			mov bl,033H ;
			int 10h
			JMP INCREMENT
			
			NEW_LINE:
				mov ah,3h
				mov bh,0h
				int 10h
				MOV DL, 0
				INC DH
				mov ah,2
				int 10h
				JMP CHECK
				
			INCREMENT:
				mov ah,3h
				mov bh,0h
				int 10h
				INC DL
				mov ah,2
				int 10h
				
			CHECK:
				POP BX
				INC BX
				PUSH BX
				CMP [BX], '$'
				JNZ PRINT
    
    
    POPA
                
ENDM DrawMaze   


RandomizeMaze MACRO 
    PUSHA
  
        ;; GET SYSTEM TIME
        MOV AH, 2CH
        INT 21H
        
        ;; MOVE HUNDREDTHS OF SECOND TO AX
        MOV AL, DL
        CBW
        
        ;; TAKE HUNDREDTHS OF SECOND MOD NUMBER OF MAZES TO GET A RANDOM NUMBER
        DIV MAZES_N
        MOV RANDOM, AH

        
    POPA
        
ENDM RandomizeMaze


LoadMaze MACRO 
    PUSHA
  
        ;; DECIDE WHICH FILE TO OPEN (WHICH MAZE DIFFICULTY)
        CMP MODE, '1'    ;; CHECK IF THE MODE IS EASY
        JNZ H_MAZE  ;; IF NOT GO TO HARD MAZE
        
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
            
            ;; OPEN THE MAZE FILE
            MOV AH, 3DH
            MOV AL, 00
            INT 21H
            
            ;; IF FILE COULDN'T BE FOUND, EXIT THE PROGRAM
            JC ERROR
            
            ;; PUSH AX (FILE HANDLE)
            PUSH AX               
            
            ;; CALCULATE THE AMOUNT OF BYTES TO BE SEEKED
            ;; FROM THE MAZE FILE TO REACH THE RANDOM MAZE        
            MOV CL, RANDOM     
            MOV CH, 0
            
            ;; CALCULATE OFFSET OF THE RANDOMLY SELECTED MAZE FROM THE BASE INDEX 
            MOV AX, ROWS
            MOV DX, COLS
            MUL DX                                               
            MUL CX
                  
            
            ;; SEEK THE MAZE FILE TO THE SPECIFIC MAZE
            ;; POP FILE HANDLE INTO BX      
            POP BX
            MOV CX, 0
            MOV DX, AX
            MOV AH, 42H
            MOV AL, 01H
            INT 21H
            
            ;; CALCULATE NUMBER OF BYTES IN THE MAZE 
            MOV AX, ROWS
            MOV DX, COLS
            MUL DX
            
            ;; READ THE MAZE FILE INTO MAZE VARIABLE
            MOV CX, AX
            MOV AH, 3FH
            MOV DX, OFFSET MAZE
            INT 21H  
            
    POPA
        
ENDM LoadMaze



GetIndex MACRO X,Y
    PUSHA
  
    MOV BL,Y
    MOV AL,81
    MUL BL
    MOV BL, X
    MOV BH, 0
    ADD AX, BX
    MOV INDEX, AX
        
    POPA
        
ENDM GetIndex


HandlePlayerMovement MACRO
    PUSHA
		
		LOCAL MOVE_UP1
		LOCAL MOVE_RIGHT1
		LOCAL MOVE_LEFT1
		LOCAL MOVE_DOWN1
		
		LOCAL MOVE_UP2
		LOCAL MOVE_RIGHT2
		LOCAL MOVE_LEFT2
		LOCAL MOVE_DOWN2
		
		
		LOCAL CONTINUE
		
		;; CHECK IF A KEY WAS PRESSED
		MOV AH, 01
		INT 16H
		JZ CONTINUE
		
		FlushBuffer
		
		CMP AH, UP_ARROW
		JZ MOVE_UP1
		
		CMP AH, LEFT_ARROW
		JZ MOVE_LEFT1
		
		CMP AH, DOWN_ARROW
		JZ MOVE_DOWN1
		
		CMP AH, RIGHT_ARROW
		JZ MOVE_RIGHT1
		
		CMP AH, W_LETTER
		JZ MOVE_UP2
		
		CMP AH, A_LETTER
		JZ MOVE_LEFT2
		
		CMP AH, S_LETTER
		JZ MOVE_DOWN2
		
		CMP AH, D_LETTER
		JZ MOVE_RIGHT2
		
		JMP CONTINUE
		
		
		MOVE_UP1:
		    MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveUp X1, Y1
			JMP CONTINUE

		MOVE_LEFT1:
			MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveLeft X1, Y1
			JMP CONTINUE

		MOVE_DOWN1:
			MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveDown X1, Y1
			JMP CONTINUE
			
		MOVE_RIGHT1:
		    MOD_P1_POSTPONE
			ClearPosition X1, Y1
			MoveRight X1, Y1
			JMP CONTINUE

		MOVE_UP2:
		    MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveUp X2, Y2
			JMP CONTINUE

		MOVE_LEFT2:
			MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveLeft X2, Y2
			JMP CONTINUE

		MOVE_DOWN2:
		    MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveDown X2, Y2
			JMP CONTINUE
			
		MOVE_RIGHT2:
		    MOD_P2_POSTPONE
			ClearPosition X2, Y2
			MoveRight X2, Y2
			JMP CONTINUE

    
		CONTINUE:
		
    POPA
ENDM HandlePlayerMovement
    
    
MoveUp	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; SUBTRACT 1 FROM Y TO REPRESENT GOING UPWARDS
		MOV CL, Y
		SUB CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex X, CL
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP

		
		;; CHANGE THE Y POSITION OF THE PLAYER TO THE NEW POSITION
		MOV Y, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveUp

MoveLeft	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; ADD 1 TO X TO REPRESENT GOING RIGHT
		MOV CL, X
		SUB CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex CL, Y
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP

		;; CHANGE THE X POSITION OF THE PLAYER TO THE NEW POSITION
		MOV X, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveLeft

MoveDown	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; SUBTRACT 1 FROM Y TO REPRESENT GOING UPWARDS
		MOV CL, Y
		ADD CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex X, CL
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP

		
		;; CHANGE THE Y POSITION OF THE PLAYER TO THE NEW POSITION
		MOV Y, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			Peep
		
		CONTINUE:
			
	
	POPA
ENDM MoveDown

MoveRight	MACRO	X,Y
	PUSHA
		
		LOCAL MAKE_PEEP
		LOCAL CONTINUE
		
		;; ADD 1 TO X TO REPRESENT GOING RIGHT
		MOV CL, X
		ADD CL, 1
		
		;; GET INDEX OF X,Y PLACE IN THE MAZE ARRAY
		GetIndex CL, Y
		
		;; CHECK IF THE MAZE IS EMPTY AT THAT INDEX
		MOV BX, INDEX
		CMP MAZE[BX], ' '
		JNZ MAKE_PEEP


		;; CHANGE THE X POSITION OF THE PLAYER TO THE NEW POSITION
		MOV X, CL
		
		JMP CONTINUE
		
		
		MAKE_PEEP:
			Peep
		
		CONTINUE:
			

	POPA
ENDM MoveRight

ClearPosition MACRO X, Y
    PUSHA
    
        ;; MOVE CURSOR TO X,Y POSITION
		MOV AH, 02
		MOV BH, 00
		MOV DL, X
		MOV DH, Y
		INT 10H
		
		;; CLEAR THAT PLACE 
		MOV AH, 02
		MOV DL, ' '
		INT 21H
		
    
    POPA
ENDM ClearPosition

Peep MACRO
	PUSHA
	
		;; MAKE PEEP SOUND
		MOV AH, 02H
		MOV DL, 07H
		INT 21H
		
	POPA

ENDM Peep

PrintPlayers MACRO
    PUSHA
	
		;; MOVE CURSOR TO X1,Y2 POSITION
		MOV AH, 02
		MOV BH, 00
		MOV DL, X1
		MOV DH, Y1
		INT 10H
		
		;; PRINT PLAYER 1
		MOV AH, 09
		MOV BH, 00
		MOV AL, 'I'
		MOV CX, 01
		MOV BL, 0FH
		INT 10H
		
		;; MOVE CURSOR TO X2,Y2 POSITION
		MOV AH, 02
		MOV BH, 00
		MOV DL, X2
		MOV DH, Y2
		INT 10H
		
		;; PRINT PLAYER 2 
		MOV AH, 09
		MOV BH, 00
		MOV AL, 'M'
		MOV CX, 01
		MOV BL, 0FH
		INT 10H


		
    POPA
    
ENDM PrintPlayers

RemoveCursor MACRO
	PUSHA

		MOV AH, 01H
		MOV CX, 2607H
		INT 10H
		
	POPA

ENDM RemoveCursor


FlushBuffer MACRO
		PUSHA
			
			MOV AH, 00
			INT 16H
		
		POPA
ENDM FlushBuffer



MOD_P1_POSTPONE MACRO
		PUSHA
		LOCAL END_1
		LOCAL END_2
		
			CMP P1_POSTPONE,0
			JNZ END_1
			
			MOV AL,UP_ARROW_PER
			MOV UP_ARROW,AL
			
			MOV AL,DOWN_ARROW_PER
			MOV DOWN_ARROW,AL
			
			MOV AL,LEFT_ARROW_PER
			MOV LEFT_ARROW,AL
			
			MOV AL,RIGHT_ARROW_PER
			MOV RIGHT_ARROW,AL
			
			JMP END_2
			
			END_1:
			      DEC P1_POSTPONE
                  JMP END_2
				  
	        END_2:	
		POPA
ENDM MOD_P1_POSTPONE


MOD_P2_POSTPONE MACRO
		PUSHA
		LOCAL END_1
		LOCAL END_2
		
			CMP P2_POSTPONE,0
			JNZ END_1
			
			MOV AL,W_LETTER_PER
			MOV W_LETTER,AL
			
			MOV AL,S_LETTER_PER
			MOV S_LETTER,AL
			
			MOV AL,A_LETTER_PER
			MOV A_LETTER,AL
			
			MOV AL,D_LETTER_PER
			MOV D_LETTER,AL
			
			JMP END_2
			
			END_1:
			      DEC P2_POSTPONE
                  JMP END_2
				  
	        END_2:	
		POPA
ENDM MOD_P2_POSTPONE


DetectAction MACRO
    PUSHA
     LOCAL CONTINUE
		;; CHECK IF A KEY WAS PRESSED
		MOV AH, 01
		INT 16H
		JZ CONTINUE
		        

		HandlePlayerFire
		HandlePlayerMovement
		
		
		
		JMP CONTINUE
        
CONTINUE:
    POPA
        
ENDM DetectAction




TestBombs MACRO X,Y,S
   PUSHA
   LOCAL NEXT
      LEA SI,BOMBX
	  LEA DI,BOMBY
	  
	  MOV CX,B_COUNT
	  
      COMPARE_X:
	       
		   CMP [SI],X
		   JZ COMPARE_Y
		   JNZ NEXT
	       
	  COMPARE_Y:
           
		   CMP [DI],Y
           JNZ NEXT
           Explode CX,S
		   
       NEXT:
            
           INC SI
           INC DI
           LOOP COMPARE_X		   
   
   POPA  
ENDM TestBombs

 

Explode MACRO COUNT,S
   PUSHA

        ResetXY COUNT
		ClearLoc COUNT
        Bang S
      			

   POPA
ENDM Explode


ClearLoc MACRO N
  PUSHA

		LEA SI,BOMBX
		ADD SI,N
		MOV DL,[SI]

		LEA DI,BOMBY
		ADD DI,N 
		MOV DH,[DI]

		MOV AH,3H
		MOV BH,0H
		INT 10H

		MOV AH,9
		MOV BH,0
		MOV AL,44H
		MOV CX,5H
		MOV BL,000H
		INT 10H


  POPA
ENDM ClearLoc

;;------------------------------------
ResetXY MACRO N
  PUSHA

		LEA SI,BOMBX
		ADD SI,N

		LEA DI,BOMBY
		ADD DI,N

		MOV [SI],-1 ;; NOT SURE
		MOV [DI],-1 ;; NOT SURE


  POPA	
ENDM ResetXY
;;---------------------------------------

Bang MACRO 
  PUSHA

	    CMP S,1
        JNZ P_2
		MOV P1_POSTPONE,10
		Shuffle1
		
        P_2:
            MOV P2_POSTPONE,10
            Shuffle2			

  POPA	
ENDM Bang

;;------------------------------------------UP->1,DOWN->2,LEFT->3,RIGHT->4
Shuffle1 MACRO 
  PUSHA
        
		LEA SI,RAND_1
	    
        Randomize [SI]
		Select_UP_1 [SI]
		INC R_COUNT
		INC SI
		
		Randomize [SI]
		Unique [SI]
		Select_DOWN_1 [SI]
		INC R_COUNT
		INC SI
		
		Randomize [SI]
		Unique [SI]
		Select_LEFT_1 [SI]
		INC R_COUNT
		INC SI
		
		Randomize [SI]
		Unique [SI]
		Select_RIGHT_1 [SI]
		
		SUB R_COUNT,3
		
	    
  POPA	
ENDM Shuffle1
;;--------------------------------------------

Select_UP_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL DOWN_1 
	LOCAL RIGHT_1
	LOCAL LEFT_1
	
        CMP S,1
        JZ END_IT
		
		CMP S,2
		JZ DOWN_1
		
        CMP S,3
        JZ LEFT_1

        CMP S,4
        JZ RIGHT_1
		
        DOWN_1:
		    MOV AL,DOWN_ARROW
            MOV UP_ARROW,AL
            JMP END_IT
        
        LEFT_1:
		    MOV AL,LEFT_ARROW
            MOV UP_ARROW,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW
            MOV UP_ARROW,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_UP_1
;;--------------------------------------------

Select_DOWN_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_1 
	LOCAL RIGHT_1
	LOCAL LEFT_1
	
        CMP S,1
        JZ UP_1
		
		CMP S,2
		JZ END_IT
		
        CMP S,3
        JZ LEFT_1

        CMP S,4
        JZ RIGHT_1
		
        UP_1:
		    MOV AL,UP_ARROW
            MOV DOWN_ARROW,AL
            JMP END_IT
        
        LEFT_1:
		    MOV AL,LEFT_ARROW
            MOV DOWN_ARROW,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW
            MOV DOWN_ARROW,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_DOWN_1
;;--------------------------------------------

Select_LEFT_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_1 
	LOCAL DOWN_1
	LOCAL RIGHT_1
	
        CMP S,1
        JZ UP_1
		
		CMP S,2
		JZ DOWN_1
		
        CMP S,3
        JZ END_IT

        CMP S,4
        JZ RIGHT_1
		
        UP_1:
		    MOV AL,UP_ARROW
            MOV LEFT_ARROW,AL
            JMP END_IT
        
        DOWN_1:
		    MOV AL,DOWN_ARROW
            MOV LEFT_ARROW,AL
            JMP END_IT
			
		RIGHT_1:
		    MOV AL,RIGHT_ARROW
            MOV LEFT_ARROW,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_LEFT_1
;;--------------------------------------------

Select_RIGHT_1 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_1 
	LOCAL DOWN_1
	LOCAL LEFT_1
	
        CMP S,1
        JZ UP_1
		
		CMP S,2
		JZ DOWN_1
		
        CMP S,3
        JZ LEFT_1

        CMP S,4
        JZ END_IT
		
        UP_1:
		    MOV AL,UP_ARROW
            MOV RIGHT_ARROW,AL
            JMP END_IT
        
        DOWN_1:
		    MOV AL,DOWN_ARROW
            MOV RIGHT_ARROW,AL
            JMP END_IT
			
		LEFT_1:
		    MOV AL,LEFT_ARROW
            MOV RIGHT_ARROW,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_RIGHT_1


;;--------------------------------------------W->1,2->S,3->A,4->D
Shuffle2 MACRO 
  PUSHA
        
		LEA SI,RAND_2
	    
        Randomize [SI]
		Select_UP_2 [SI]
		INC R_COUNT
		INC SI
		
		Randomize [SI]
		Unique [SI]
		Select_DOWN_2 [SI]
		INC R_COUNT
		INC SI
		
		Randomize [SI]
		Unique [SI]
		Select_LEFT_2 [SI]
		INC R_COUNT
		INC SI
		
		Randomize [SI]
		Unique [SI]
		Select_RIGHT_2 [SI]
		
		SUB R_COUNT,3
		
	    
  POPA	
ENDM Shuffle1
;;--------------------------------------------

Select_UP_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL DOWN_2 
	LOCAL RIGHT_2
	LOCAL LEFT_2
	
        CMP S,1
        JZ END_IT
		
		CMP S,2
		JZ DOWN_2
		
        CMP S,3
        JZ LEFT_2

        CMP S,4
        JZ RIGHT_2
		
        DOWN_2:
		    MOV AL,S_LETTER
            MOV W_LETTER,AL
            JMP END_IT
        
        LEFT_2:
		    MOV AL,A_LETTER
            MOV W_LETTER,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,D_LETTER
            MOV W_LETTER,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_UP_2
;;--------------------------------------------

Select_DOWN_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_2 
	LOCAL RIGHT_2
	LOCAL LEFT_2
	
        CMP S,1
        JZ UP_2
		
		CMP S,2
		JZ END_IT
		
        CMP S,3
        JZ LEFT_2

        CMP S,4
        JZ RIGHT_2
		
        UP_2:
		    MOV AL,W_LETTER
            MOV S_LETTER,AL
            JMP END_IT
        
        LEFT_2:
		    MOV AL,A_LETTER
            MOV S_LETTER,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,D_LETTER
            MOV S_LETTER,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_DOWN_2
;;--------------------------------------------

Select_LEFT_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_2 
	LOCAL DOWN_2
	LOCAL RIGHT_2
	
        CMP S,1
        JZ UP_1
		
		CMP S,2
		JZ DOWN_2
		
        CMP S,3
        JZ END_IT

        CMP S,4
        JZ RIGHT_2
		
        UP_2:
		    MOV AL,W_LETTER
            MOV A_LETTER,AL
            JMP END_IT
        
        DOWN_2:
		    MOV AL,S_LETTER
            MOV A_LETTER,AL
            JMP END_IT
			
		RIGHT_2:
		    MOV AL,D_LETTER
            MOV A_LETTER,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_LEFT_2
;;--------------------------------------------

Select_RIGHT_2 MACRO S
   PUSHA
    LOCAL END_IT
	LOCAL UP_2 
	LOCAL DOWN_2
	LOCAL LEFT_2
	
        CMP S,1
        JZ UP_2
		
		CMP S,2
		JZ DOWN_2
		
        CMP S,3
        JZ LEFT_2

        CMP S,4
        JZ END_IT
		
        UP_2:
		    MOV AL,W_LETTER
            MOV D_LETTER,AL
            JMP END_IT
        
        DOWN_1:
		    MOV AL,S_LETTER
            MOV D_LETTER,AL
            JMP END_IT
			
		LEFT_1:
		    MOV AL,A_LETTER
            MOV D_LETTER,AL
            JMP END_IT
        		
                      
   POPA
ENDM Select_RIGHT_2


;;--------------------------------------------
Unique MACRO  R
  PUSHA
    
	  LEA BX,RAND_1
	  MOV CX,4
	  
LOOP1:
      CMP CX,B_COUNT
      JZ Ignore
	  
      CMP [BX],[BX+CX]
	  JZ AGAIN
	  
      LOOP LOOP1
	  
	  
AGAIN:  Randomize R	 
        JMP LOOP1
		
Ignore: LOOP LOOP1	  
		
  POPA	
ENDM Unique

;;--------------------------------------------
Randomize MACRO R
    PUSHA
  
        ;; GET SYSTEM TIME
        MOV AH, 2CH
        INT 21H
        
        ;; MOVE HUNDREDTHS OF SECOND TO AX
        MOV AL, DL
        CBW
        
        ;; TAKE HUNDREDTHS OF SECOND MOD NUMBER OF MAZES TO GET A RANDOM NUMBER
        MOV BL,4
		DIV BL
        MOV R, AH
		ADD R,1

        
    POPA        
ENDM Randomize

;;---------------------------------------------------------------





     
PrintBombs MACRO
  PUSHA
	  LOCAL NEXT
	  LEA SI,BOMBX
	  LEA DI,BOMBY
		
	  MOV CX,50
		
	  LOOP_BOMBS:
		    MOV AH,-1
		    CMP [SI],AH
			  JZ NEXT
			
		     ;;MOVE CURSOR
		     MoveCursor [SI],[DI]
		     ;;PRINT
		     PlantBomb
             JMP NEXT			
			
		     NEXT:
			  INC SI
		      INC DI
			  LOOP LOOP_BOMBS
			
  POPA
ENDM PrintBombs


HandlePlayerFire MACRO
    PUSHA
		LOCAL CONTINUE

		;; CHECK IF A KEY WAS PRESSED
		MOV AH, 01
		INT 16H
		JZ CONTINUE
		
		
		
		CMP AH, M_LETTER
		JZ FIRE1
		
		CMP AH, F_LETTER
		JZ FIRE2
		
		JMP CONTINUE
		
		FIRE1:
			FIRE X1, Y1
;			FlushBuffer
			JMP CONTINUE
			
		FIRE2:
			FIRE X2, Y2
;			FlushBuffer
			JMP CONTINUE


    
    
		CONTINUE:
		
  POPA
        
ENDM HandlePlayerFire

;;-------------------------------

Fire MACRO X, Y
    PUSHA

  MOV DL,X
  MOV DH,Y
  MOV AH,02H
  MOV BH,0
  INT 10H 
  
  ;;MoveCursor X,Y
 ; PlantBomb
  ;;AddBomb X,Y

    LEA BX,BOMBX
    ADD BX,B_COUNT
    MOV AL,X
    MOV [BX],AL
   
    FlushBuffer  
    MOV BX,00
	
    LEA BX,BOMBY
    ADD BX,B_COUNT
    MOV AH,Y
    MOV [BX],AH
	

   LEA BX,BOMBY
    ADD BX,B_COUNT
    MOV AL,Y
    MOV BOMBY,AL
	
    INC B_COUNT
   
   
  
  
  POPA
        
ENDM Fire

;;-------------------------------
MoveCursor MACRO X,Y
    PUSHA
	
  MOV DL,X
  MOV DH,Y
  MOV AH,02H
  MOV BH,0
  INT 10H 
  
  POPA
        
ENDM MoveCursor

;;-------------------------------
PlantBomb MACRO
    PUSHA
	
  MOV AH,9
  MOV BH,0
  MOV AL,'O'
  MOV CX,1H
  MOV BL,04fH
  INT 10H
    
	POPA
        
ENDM PlantBomb

;;-------------------------------
AddBomb MACRO X,Y
   PUSHA
   
    
    StoreSec
    StoreMin
   
   
    
    LEA BX,BY
    ADD BX,B_COUNT
    MOV AL,Y
    MOV [BX],AL
	
   
   
    LEA BX,BOMBX
    ADD BX,B_COUNT
    MOV AL,X
    MOV [BX],AL
   
    LEA BX,BOMBY
    ADD BX,B_COUNT
    MOV AL,Y
    MOV [BX],AL
	
	
	INC B_COUNT
   
   
    ;;StoreX X
    ;;StoreY Y
   
   
   POPA
   
ENDM AddBomb

;;-------------------------------
StoreSec MACRO
   PUSHA
   
   LEA BX,BOMB_T_S
   ADD BX,B_COUNT
   MOV AH, 2CH                  
   INT 21H    
   MOV [BX],DH
   
   POPA
   
ENDM StoreSec
;;-------------------------------
StoreMin MACRO
   PUSHA
   
   LEA BX,BOMB_T_M
   ADD BX,B_COUNT
   MOV AH, 2CH                  
   INT 21H    
   MOV [BX],CL
   
   POPA
   
ENDM StoreMin
;;-------------------------------
StoreX MACRO X
   PUSHA
   
   LEA BX,BOMBX
   ADD BX,B_COUNT
   MOV AL,X
   MOV [BX],AL
   
   POPA
   
ENDM StoreX
;;-------------------------------
StoreY MACRO Y
   PUSHA
   
   LEA BX,BOMBY
   ADD BX,B_COUNT
   MOV AL,Y
   ;;MOV BOMBY,AL
   INC B_COUNT
   
   POPA
   
ENDM StoreY