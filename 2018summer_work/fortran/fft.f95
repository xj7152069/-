
program main

real a1,a2,g(8),g1(4),g2(4)
integer M,N,I,J,a,a0,K,t,t1

a0=0
N=8
a=N
t=log(real(N))/log(2.0)
t1=t
do I=1,N
g(I)=I-1
end do
write(*,*)g
do while(t>1)
t=t-1
a=a/2
 do I=1,(N/a)/2,1
  do J=1,a,1
     g1(J)=g(2*J-1+a0)
     g2(J)=g(2*J+a0)
      do K=1,a,1
         g(K+a0)=g1(K)
         g(K+a+a0)=g2(K)
      end do
  end do
 a0=a0+a
end do

end do
write(*,*)g

end
