module global
  type global_type
     integer :: id
     integer :: n 
     integer, allocatable, dimension(:) :: alive
  end type global_type
end module global

subroutine init(n, g)
  use global
  implicit none

  !incoming variable
  integer :: n

  !loop variables
  integer :: i,j

  type(global_type) :: g

  g%n = n

  print*, "initializing n to ", n

  ! allocate array
  allocate(g%alive(g%n))

  ! initialize arrays
  do i=1,g%n
     g%alive(i) = i
  end do  

end subroutine init

subroutine print(g)
  use global
  implicit none

  !loop variables
  integer :: i,j

  type(global_type) :: g

  do i=1,g%n
     print*, i, g%alive(i)
  enddo

end subroutine print

! %%%%%%%%%%%%%%%%%%% c wrappers %%%%%%%%%%%%%%%%%%%%%%%

subroutine init_fort(n, global_c_ptr)
  use, intrinsic :: iso_c_binding
  use global
  implicit none

  integer :: n
  type (c_ptr), intent(out) :: global_c_ptr
  type (global_type), target :: g

  call init(n, g)
  
  global_c_ptr = c_loc(g)

end subroutine init_fort

subroutine print_fort(global_c_ptr)
  use, intrinsic :: iso_c_binding
  use global
  implicit none

  type (c_ptr) :: global_c_ptr
  type (global_type), pointer :: g

  call c_f_pointer(global_c_ptr,g)

!  call print(g)
  print*, "n = ", g%n

end subroutine print_fort
