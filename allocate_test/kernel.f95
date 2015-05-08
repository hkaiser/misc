SUBROUTINE INIT(N, alive_c_ptr) bind (C, name="init_")
  use, intrinsic :: iso_c_binding
  IMPLICIT NONE
  
  type (c_ptr), intent (out) :: alive_c_ptr
  integer (c_int), allocatable, target, dimension (:) :: alive

  INTEGER :: I, N
  
  N=10
  
  ALLOCATE(ALIVE(N))

  DO I=1,N
     ALIVE(I) = I
  ENDDO

  alive_c_ptr = c_loc(alive)

END SUBROUTINE INIT

SUBROUTINE PRINT(N, alive_c_ptr) 
  use, intrinsic :: iso_c_binding
  IMPLICIT NONE

  INTEGER :: N,I
  type (c_ptr), intent (in) :: alive_c_ptr
  INTEGER (c_int), DIMENSION(:), pointer :: ALIVE
  
  call c_f_pointer(alive_c_ptr, alive,[N])

  PRINT*, "N = ", N
  DO I=1,N+5
     PRINT*, "ALIVE",I,"=",ALIVE(I)
  ENDDO  

END SUBROUTINE PRINT
