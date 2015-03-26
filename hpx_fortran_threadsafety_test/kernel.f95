SUBROUTINE KERNEL()
  IMPLICIT NONE

  INTEGER :: I

  REAL*8 :: N
  COMMON/VARIABLES/ N

  INTEGER :: TEMP

  TEMP = 0

  DO I=1,1000
     TEMP=N/I+TEMP
  ENDDO

  N=TEMP
  
  
!!$  !These must match the #define statements in main.cpp  
!!$  INTEGER, PARAMETER :: N_MAX = 20
!!$  INTEGER, PARAMETER :: MAX_NEIGHBORS = 20
!!$
!!$  INTEGER :: N 
!!$  INTEGER, DIMENSION(N_MAX) :: ALIVE
!!$  INTEGER, DIMENSION(N_MAX) :: NUMNEIGHBORS
!!$  INTEGER, DIMENSION(MAX_NEIGHBORS,N_MAX) :: NEIGHBORS
!!$  COMMON/VARIABLES/ N, ALIVE, NUMNEIGHBORS, NEIGHBORS
!!$
!!$  INTEGER, DIMENSION(N_MAX) :: NEW_ALIVE            
!!$
!!$  !LOOP VARIABLES
!!$  INTEGER :: I
!!$  INTEGER :: J
!!$  
!!$  !TEMP VARIABLES
!!$  INTEGER :: SUM
!!$
!!$  ! DEBUGGING
!!$!  PRINT*, "FORTRAN:  N=",N
!!$
!!$  
!!$  !LOOP OVER NODES
!!$  DO I=1,N
!!$!     PRINT*, "FORTRAN: NODE=", I, "ALIVE = ", ALIVE(I)
!!$!     PRINT*, "FORTRAN: NODE=", I, "NUMNEIGHBORS = ", NUMNEIGHBORS(I)
!!$     
!!$     NEW_ALIVE(I)=0
!!$     IF(ALIVE(I).eq.1) THEN
!!$        NEW_ALIVE(I)=0
!!$        DO J=1,NUMNEIGHBORS(I)
!!$!           PRINT*, "I=",I, "NEIGHBOR=", NEIGHBORS(J,I)+1
!!$        ENDDO
!!$     ELSE
!!$        SUM=0
!!$        DO J=1,NUMNEIGHBORS(I)
!!$           SUM=SUM+ALIVE(NEIGHBORS(J,I)+1)
!!$!           PRINT*, "I=",I, "NEIGHBOR=", NEIGHBORS(J,I)+1, "NEIGHBOR ALIVE=", ALIVE(NEIGHBORS(J,I)+1)
!!$        ENDDO
!!$        IF(SUM.gt.0)THEN
!!$           !PRINT*, "SUM=", SUM
!!$           NEW_ALIVE(I)=1
!!$        ENDIF
!!$     ENDIF
!!$     !         PRINT*, "FORTRAN: I=",I," NEW_ALIVE=",NEW_ALIVE(I)
!!$  ENDDO
!!$  
!!$  
!!$  DO I=1,N
!!$     ALIVE(I)=NEW_ALIVE(I)
!!$  ENDDO

  
END SUBROUTINE KERNEL
