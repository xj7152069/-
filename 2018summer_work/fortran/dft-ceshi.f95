
!二维有限离散傅立叶变换测试
!g(M,N),u(M,N),uu(M,N),M,N为之前已定义的量，M为X方向的大小，N为Y方向的大小
!u(M,N)用于保存正变换得到的复数频谱，uu(M,N)用于保存反变换得到的复数信号
!定义ec和e_c两个函数，用于计算欧拉公式得到的指数函数

program main 

real g(40,10)
complex u(40,10),uu(40,10)
complex c
complex,external::ec
complex,external::e_c
real pi,r
integer k,i,M,l,j,N
pi=6.2831853071796/2


101 format(10(f8.6,1X))
open(unit=10,file="2.txt")  !测试结果储存在当前目录的2.txt中

M=40
N=10
r=1.0/((M*N)**0.5)  !r为振幅系数
write(10,*)"信号"
do i=1,M
 do j=1,N
  g(i,j)=(10+(i+j)**0.5)*0.0001
  if (i>=j) then
  g(i,j)=(sin(g(i,j))+cos(g(i,j))*(10+(i+j)**0.5))*0.01+g(i,j) !测试矩阵（信号）
  end if
  u(i,j)=0.0    
  uu(i,j)=0.0  !建立空白数组
 end do
end do

do i=1,M,1 
  write(10,101)(g(i,j),j=1,N,1) !用write内循环在文件中格式化输入数据
end do
write(10,101)


do k=1,M,1
  do l=1,N,1    !正变换
    do i=1,M,1
      do j=1,N,1
         u(k,l)=u(k,l)+(g(i,j)*e_c(k,i,M,l,j,N))*r
      end do
    end do
  end do
end do

write(10,*)"复数频谱"
do i=1,M,1 
  write(10,101)(u(i,j),j=1,N,1) !频谱为复数
end do
write(10,101)

do i=1,M,1
  do j=1,N,1    !反变换
    do k=1,M,1
      do l=1,N,1
         uu(i,j)=uu(i,j)+(u(k,l)*ec(k,i,M,l,j,N))*r
      end do
    end do
  end do
end do

write(10,*)"反变换得到的复数信号"
do i=1,M,1 
  write(10,101)(uu(i,j),j=1,N,1) !反变换得到的信号也是复数，虚部为零
end do

write(10,*)"复数信号的实部，与原信号相同"
do i=1,M,1 
  write(10,101)(abs(uu(i,j)),j=1,N,1) !反变换得到的信号也是复数，虚部为零
end do

end


function ec(k,i,M,l,j,N)    !根据欧拉公式转换e指数函数
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
