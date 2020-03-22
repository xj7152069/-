!二维有限离散傅立叶变换
!g(M,N),u(M,N),uu(M,N),M,N为之前已定义的量，M为X方向的大小，N为Y方向的大小
!u(M,N)用于保存正变换得到的复数频谱，uu(M,N)用于保存反变换得到的复数信号
!定义ec和e_c两个函数，用于计算欧拉公式得到的指数函数

program main 

!real,allocatable::g(:,:)
!complex,allocatable::u(:,:),uu(:,:)
!integer M,N

complex c
complex,external::ec
complex,external::e_c
real pi,r
integer k,i,l,j
pi=3.1415926
r=1.0/((M*N)**0.5)  !r为振幅系数

do i=1,M
 do j=1,N
  u(i,j)=0.0    !建立空白数组
  uu(i,j)=0.0
 end do
end do

do k=1,M,1
  do l=1,N,1    !正变换
    do i=1,M,1
      do j=1,N,1
         u(k,l)=u(k,l)+(g(i,j)*e_c(k,i,M,l,j,N))*r
      end do
    end do
  end do
end do

do i=1,M,1
  do j=1,N,1    !反变换
    do k=1,M,1
      do l=1,N,1
         uu(i,j)=uu(i,j)+(u(k,l)*ec(k,i,M,l,j,N))*r
      end do
    end do
  end do
end do

end


function ec(k,i,M,l,j,N) !根据欧拉公式转换e指数函数
real pi
integer k,i,M,l,j,N
real u
complex::ec
pi=3.1415926
u=2*pi*((((k*i)/real(M)))+(((l*j)/real(N))))
ec=cmplx(cos(u),sin(u))
return
end


function e_c(k,i,M,l,j,N)
real pi
integer k,i,M,l,j,N
real u
complex::e_c
pi=3.1415926
u=2*pi*((((k*i)/real(M)))+(((l*j)/real(N))))
e_c=cmplx(cos(u),-sin(u))
return
end
