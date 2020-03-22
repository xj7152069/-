program main             !fortran编程实验

integer b,c,s(9),I,J
character d*7,na*20,nb*9
real a,ss(10,10),s2(10,10),s4(5)
real,allocatable :: s1(:,:),s5(:,:)         !定义语句必须放在最前面
complex s3

nb="-------------"
do N=1,19,1
na=trim(na)//"@"
end do
write(*,*)na
write(*,*)nb

write(*,*)"&            
& hellow world"     
write(*,*)s3**2    !语句连接

a=0.5
b=0.5
c=a/b
M1=4
N1=4
122 read(*,*)N1

if(M1/=N1) then
write(*,*)"false"
goto 122
else 
write(*,*)"true"
end if

do N1=0,8,1
s(N1+1)=N1+76
write(*,*)s(N1+1)
end do



open(unit=10,file="2.txt")    
do M1=1,5,1
 do N1=1,5,1
  ss(M1,N1)=M1+N1
end do
end do


do M1=1,5,1 
  write(10,101)(ss(M1,N1),N1=1,5,1) !用write内循环在文件中格式化输入矩阵
101 format(5(F5.2,1X))
end do


read(*,*)I
a1=1.5878
d="hellow!"
write(*,*)"a= ",sin(a)+c,d
write(*,*)I

read(*,*)M,N
allocate(s1(M,N))   !为可变数组给定大小

do M1=1,M,1
 do N1=1,N,1
 s1(M1,N1)=M1+N1
 write(*,105)s1(M1,N1)
105 format(1X,F5.2)
 end do
end do

close(unit=10)
open(unit=11,file="2.txt")      !从文件中格式化读取矩阵数据
do N1=1,5,1
read(11,104)(s2(N1,M1),M1=1,5,1)
104 format(5(F5.2,1X))
end do

do M1=1,5,1 
  write(*,*)(s2(M1,N1),N1=1,5)
end do

write(*,*)
call du()    !调用子程序
call er()

end


subroutine er()  !打开二进制文件
real s
open(unit=14,file="dat2.bin",access="direct",&
& form="formatted",recl=4,status="old")
end

subroutine du()    !子程序，试探矩阵大小
real s4(5)
I=0
close(11)
open(unit=12,file="2.txt") 
!do while(1>0)
10 read(12,*,end=108)(s4(N1),N1=1,5)
I=I+1
write(*,*)I
goto 10
!end do
108 write(*,*)I
end 
