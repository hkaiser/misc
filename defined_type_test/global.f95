module global
  type global_type
     integer :: id
     integer :: n 
     integer, allocatable, dimension(:) :: alive
     integer, allocatable, dimension(:) :: numneighbors
     integer, allocatable, dimension(:,:) :: neighbors
  end type global_type
end module global

subroutine init(g,domain_id)
  use global
  implicit none

  !incoming variable
  integer :: domain_id

  !loop variables
  integer :: i,j

  type(global_type) :: g

  g%id = domain_id
  g%n = 10

  ! allocate arrays 
  allocate(g%alive(g%n))
  allocate(g%numneighbors(g%n))
  allocate(g%neighbors(20,g%n))

  ! initialize arrays
  do i=1,g%n
     g%alive(i) = 0
     g%numneighbors(i) = 2
     g%neighbors(1,i) = i-1
     g%neighbors(2,i) = i+1
  end do  

  !end cases
  g%numneighbors(1) = 1
  g%neighbors(1,1) = 2
  g%numneighbors(g%n) = 1
  g%neighbors(1,g%n) = g%n-1

end subroutine init

subroutine kernel(g)
  use global
  implicit none

  !incoming variables 
  type (global_type) :: g
  
  !loop variables
  integer :: i,j

  !temp variables
  integer :: sum
  integer, dimension(g%n) :: new_alive

  do i=1,g%n
     new_alive(i)=0
     if (g%alive(i).eq.1) then
        new_alive(i)=0
     else
        sum=0
        do j=1,g%numneighbors(i)
           sum=sum+g%alive(g%neighbors(j,i))
        end do
        if (sum.gt.0) then
           new_alive(i)=1
        end if
     end if
  end do

  g%alive(:) = new_alive(:)

end subroutine kernel

subroutine print(g)
  use global
  implicit none

  !loop variables
  integer :: i,j

  type(global_type) :: g

  print*, "domain_id = ", g%id
  do i=1,g%n
     print*, i, g%alive(i)
  enddo

end subroutine print
