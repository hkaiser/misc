      include 'kernel.f95'
      include 'global.f95'

      program main
      
      integer :: i,j
      
      integer, parameter :: n = 5
      integer, dimension(n) :: alive
      integer, dimension(n) :: numneighbors
      integer, dimension(20,n) :: neighbors
      
      do i=1,n
         alive(i) = 0
         numneighbors(i) = 2
         neighbors(1,i) = i-1
         neighbors(2,i) = i+1
      end do
      
      alive(1) = 1

      !periodic boundary...
      neighbors(1,1) = n
      neighbors(2,n) = 1

      call kernel(n,alive,numneighbors,neighbors)
      call kernel(n,alive,numneighbors,neighbors)

      do i=1,n
         print*, i, alive(i)
      enddo

      end program main
