program main  !读数据

real,allocatable :: g(:,:),x(:),y(:)
integer I,J,i,j  !假设为文件大小
real dx,dy,xmin,xmax,ymin,ymax    !假设为坐标间隔以及最大最小坐标位置

open(unit=10,file="2.txt",status="old")   
allocate(g(I,J))   !为可变数组给定大小
allocate(x(I))
allocate(y(J))

x(1)=xmin   !给定坐标系
x(I)=xmax
y(1)=ymin
y(J)=ymax
do i=2,I-1,1
 x(i)=x(i-1)+dx
end do
do j=2,J-1,1
 y(j)=y(j-1)+dy
end do

!close(unit=10)
!从文件中格式化读取矩阵数据，文件名为 2.txt
do j=1,J,1
  read(10,104)(s2(i,j),i=1,I,1)
104 format(5(F8.3,1X))
end do

open(unit=11,file="1.txt",status="new")  !新建文件1.txt，将数据写入 
do j=1,J,1 
  write(11,101)(ss(i,j),i=1,I,1) !用write内循环在文件中格式化输入矩阵
101 format(5(F8.3,1X))
end do

end
