SUBROUTINE INIT(N, alive_c_ptr)
  use, intrinsic :: iso_c_binding
  IMPLICIT NONE
  
  type (c_ptr) :: alive_c_ptr
  integer (c_int), allocatable, target :: alive(:)
 
  INTEGER :: I, N
  
  N=31
  
  ALLOCATE(ALIVE(N))

  DO I=1,N
     print*,"i=",i
     ALIVE(I) = I
  ENDDO

  DO I=1,N
     PRINT*, "ALIVE",I,"=",alive(I)
  ENDDO  

  alive_c_ptr = c_loc(alive(1))

END SUBROUTINE INIT

SUBROUTINE PRINT(N, alive_c_ptr)
  use, intrinsic :: iso_c_binding
  IMPLICIT NONE

  INTEGER :: N,I
  type (c_ptr), intent (in) :: alive_c_ptr
  integer (c_int), pointer :: alive(:)
  
  call c_f_pointer(alive_c_ptr, alive,[N])

  PRINT*, "N = ", N
  PRINT*, "SIZEOF(ALIVE) =", sizeof(alive)/sizeof(c_int)
  DO I=1,N
     PRINT*, "ALIVE",I,"=",alive(I)
  ENDDO  

END SUBROUTINE PRINT
