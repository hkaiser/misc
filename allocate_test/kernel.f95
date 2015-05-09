subroutine init(n, alive_c_ptr)
  use, intrinsic :: iso_c_binding
  implicit none
  
  type (c_ptr) :: alive_c_ptr
  real (c_double), allocatable, target, save :: alive(:)
 
  integer :: i, n
  
  real (c_double) :: j

  n=1
  
  allocate(alive(n))
  
  do I=1,n
     call random_number(j)
     alive(i) = j
  enddo

  do i=1,n
     write(12,*) alive(I)
  enddo  

  alive_c_ptr = c_loc(alive(1))

end subroutine init

subroutine print(n, alive_c_ptr)
  use, intrinsic :: iso_c_binding
  implicit none

  integer :: n,i
  type (c_ptr), intent (in) :: alive_c_ptr
  real (c_double), pointer :: alive(:)
  
  call c_f_pointer(alive_c_ptr, alive,[n])

  print*, "n = ", n
  do i=1,n
     write(13,*) alive(i)
  enddo  

end subroutine print
