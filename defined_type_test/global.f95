module global
  type g
     integer, parameter :: n = 5
     integer, dimension(n) :: alive
     integer, dimension(n) :: numneighbors
     integer, dimension(20,n) :: neighbors
  end type g
end module global
