SUBROUTINE INIT(N, alive_c_ptr)
  use, intrinsic :: iso_c_binding
  IMPLICIT NONE
  
  type (c_ptr) :: alive_c_ptr
  real (c_double), allocatable, target, save :: alive(:)
 
  INTEGER :: I, N
  
  real (c_double) :: j

  N=1000000
  
  ALLOCATE(ALIVE(N))
  
  DO I=1,N
     call random_number(j)
     ALIVE(I) = j
  ENDDO

  DO I=1,N
     WRITE(12,*) alive(I)
  ENDDO  

  alive_c_ptr = c_loc(alive(1))

END SUBROUTINE INIT

SUBROUTINE PRINT(N, alive_c_ptr)
  use, intrinsic :: iso_c_binding
  IMPLICIT NONE

  INTEGER :: N,I
  type (c_ptr), intent (in) :: alive_c_ptr
  real (c_double), pointer :: alive(:)
  
  call c_f_pointer(alive_c_ptr, alive,[N])

  PRINT*, "N = ", N
  DO I=1,N
     WRITE(13,*) alive(I)
  ENDDO  

END SUBROUTINE PRINT
