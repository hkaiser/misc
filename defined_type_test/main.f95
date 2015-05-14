!      include 'kernel.f95'
  include 'global.f95'
  
  program main
    use global
    implicit none
    
    integer :: time, temp, n_timesteps
    type(global_type) :: g1
    type(global_type) :: g2
    
    n_timesteps = 7

    call init(g1,1)
    call init(g2,2)
    
    ! seed single alive cell
    g1%alive(3) = 1   

    ! timestepping loop
    do time=1,n_timesteps
       print*,'timestep'

       call kernel(g1)
       call kernel(g2)
       
       ! boundary exchange
       temp=g1%alive(g1%n)
       g1%alive(g1%n)=g2%alive(1)
       g2%alive(1)=temp
       
    end do

    call print(g1)
    call print(g2)

  end program main
  
