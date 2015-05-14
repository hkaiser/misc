module global_data
  type global_type
     integer :: id
     integer :: n
     integer, allocatable, dimension(:) :: alive
  end type global_type
end module global_data

module global
  use global_data

  interface
    subroutine init(n, g)
      use global_data
      integer :: n
      type(global_type), pointer :: g
    end subroutine
  end interface

  interface
    subroutine print(g)
      use global_data
      type(global_type), pointer :: g
    end subroutine
  end interface

  interface
    subroutine term(g)
      use global_data
      type(global_type), pointer :: g
    end subroutine
  end interface

end module global

! %%%%%%%%%%%%%%%%%%% actual functionality %%%%%%%%%%%%%%%%%%%%%%%

subroutine init(n, g)
  use global
  implicit none

  !incoming variable
  integer :: n

  !loop variables
  integer :: i,j

  type(global_type), pointer :: g
  allocate(g)

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

  type(global_type), pointer :: g

  do i=1,g%n
     print*, i, g%alive(i)
  enddo

end subroutine print

subroutine term(g)
  use global
  implicit none

  type (global_type), pointer :: g

  deallocate(g)
end subroutine

! %%%%%%%%%%%%%%%%%%% c wrappers %%%%%%%%%%%%%%%%%%%%%%%

subroutine init_fort(n, global_c_ptr)
  use, intrinsic :: iso_c_binding
  use global
  implicit none

  integer :: n
  type (C_PTR), intent(out) :: global_c_ptr
  type (global_type), pointer :: gdata

  call init(n, gdata)

  global_c_ptr = C_LOC(gdata)

end subroutine init_fort

subroutine print_fort(global_c_ptr)
  use, intrinsic :: iso_c_binding
  use global
!  use interfaces
  implicit none

  type (C_PTR) :: global_c_ptr
  type (global_type), pointer :: g

  call C_F_POINTER(global_c_ptr,g)

  call print(g)
  print*, "n = ", g%n

end subroutine print_fort

subroutine term_fort(global_c_ptr)
  use, intrinsic :: iso_c_binding
  use global
!  use interfaces
  implicit none

  type (C_PTR) :: global_c_ptr
  type (global_type), pointer :: gdata

  call C_F_POINTER(global_c_ptr, gdata)
  call term(gdata)

end subroutine term_fort

