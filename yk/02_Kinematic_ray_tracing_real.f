	PARAMETER(PI=3.1415926536)
	!PARAMETER(NX=1201,NZ=601)
	PARAMETER(NX=901,NZ=901)
        !PARAMETER(NX=3617,NZ=1500)
	PARAMETER(DZ=10.,DX=10.)
	PARAMETER(dsita_takeoff=PI/180.)
	EXTERNAL F

	DIMENSION Y(10),D(10),B(10),C(10),G(10),E(10)
	DIMENSION V(NZ,NX)
	DIMENSION V_RAY(NZ,NX)
	DIMENSION V_RAY2(NZ,NX)  ! Two type of ray plotted on Vmodel
	DOUBLE PRECISION Y,D,T,H,B,C,G,E
	REAL Px,Pz
        DIMENSION Vx(NZ,NX)
        DIMENSION Vz(NZ,NX)
        DIMENSION Vxx(NZ,NX)
        DIMENSION Vxz(NZ,NX)
        DIMENSION Vzz(NZ,NX)

	CHARACTER*128 FN1,FN2,FN3,FN4 
	CHARACTER*128 FN31,FN32,FN33,FN34,FN35 
	CHARACTER*128 FN91   ! Ray traj from Analyt_solution
	CHARACTER*128 FN92   ! Two type of ray plotted on Vmodel

*+++++++ READ Velocity model
	FN1='v3000_x0.09_z0.09_plus_gauss_ball_big.dat'
	!FN1='v3000_x0.09_z0.09_plus_gauss_ball_small.dat'
	!FN1='./v3000_nx901_nz901_gauss_ball.dat'
	!FN1='./v3000_nx901_nz901.dat'
        !FN1='timodel_vp_nx3617_nz1500_smth.dat'
	OPEN(1,FILE=FN1,ACCESS='DIRECT',RECL=1*NZ)
	DO IX=1,NX
	READ(1,REC=IX) (V(IZ,IX),IZ=1,NZ)
	ENDDO
	CLOSE(1)

*+++++++ TMP FOR TEST 
	!DO IX=1,NX
	!DO IZ=1,NZ
	!   V(IZ,IX)=2000.  ! TMP FOR TEST
	!ENDDO
	!ENDDO

	CALL DERIVATE(V,Vx,Vz,Vxx,Vxz,Vzz,NX,NZ,Dx,Dz)

        !FN31='vx.dat'
        !FN32='vz.dat'
        !FN33='vxx.dat' 
        !!FN34='vzz.dat'
        !FN35='vxz.dat'
        !OPEN(31,FILE=FN31,ACCESS='DIRECT',RECL=1*NZ)
        !OPEN(32,FILE=FN32,ACCESS='DIRECT',RECL=1*NZ)
        !OPEN(33,FILE=FN33,ACCESS='DIRECT',RECL=4*NZ)
        !OPEN(34,FILE=FN34,ACCESS='DIRECT',RECL=4*NZ)
        !OPEN(35,FILE=FN35,ACCESS='DIRECT',RECL=4*NZ)
        !DO IX=1,NX
        !WRITE(31,REC=IX) (Vx(IZ,IX),IZ=1,NZ)
        !WRITE(32,REC=IX) (Vz(IZ,IX),IZ=1,NZ)
        !WRITE(33,REC=IX) (Vxx(IZ,IX),IZ=1,NZ)
        !WRITE(34,REC=IX) (Vzz(IZ,IX),IZ=1,NZ)
        !WRITE(35,REC=IX) (Vxz(IZ,IX),IZ=1,NZ)
        !ENDDO
        !CLOSE(31)
        !CLOSE(32)
        !CLOSE(33)
        !CLOSE(34)
        !CLOSE(35)
        !WRITE(*,*) FN31,FN32,FN33,FN34,FN35
        !pause

*+++++++ Prepare a Velocity model with ray plotted
	DO IX=1,NX
	DO IZ=1,NZ
	   V_RAY(IZ,IX)=V(IZ,IX)
	ENDDO
	ENDDO

	Xmin=0.
	Zmin=0.
	Xmax=(NX-1)*DX
	Zmax=(NZ-1)*DZ

*+++++++ Give a start position for ray tracing 
        X_start=0.
        Z_start=0.
        !X_start=18000.
        !Z_start=14000.

	WRITE(*,*)'X_start,Z_start=',X_start,Z_start
        IX_start=INT(X_start/DX+0.5)+1
        IZ_start=INT(Z_start/DZ+0.5)+1
	!WRITE(*,*)'IX_start,IZ_start=',IX_start,IZ_start
	!WRITE(*,*)'V(',IZ_start,IX_start,')=',V(IZ_start,IX_start)

	IRAY=0
	!DO 9 SITA_takeoff = 0., PI/2,dsita_takeoff   ! LOOP AGAINST Ray_takeoff Angle STARTS
        DO 9 SITA_takeoff=55*PI/180.,85*PI/180.,dsita_takeoff   ! LOOP AGAINST Ray_takeoff Angle STARTS
	IRAY=IRAY+1
        IF(IRAY.GT.135) GOTO 12 
	WRITE(*,*)'*** IRAY=',IRAY,' SITA_takeoff=',SITA_takeoff,
     +' (',SITA_takeoff*180/PI,' degree)'
*+++++++ Give a start P parameter for ray tracing 
        Px=SIN(SITA_takeoff)/V(IZ_start,IX_start)
        Pz=COS(SITA_takeoff)/V(IZ_start,IX_start)
        Arc=0
        Q1=1
        P1=0
        Q2=0
        P2=1
        Travel_t=0
	!WRITE(*,*)'Px_start,Pz_start=',Px,Pz
        !WRITE(*,*)'Q1_start,P1_start=',Q1,P1
        !WRITE(*,*)'Q2_start,P2_start=',Q2,P2
c       PAUSE

*+++++++ Give initial value for Runge-Kutta 
	T=0.0
	Y(1)=X_start  ! INITIAL VALUE OF Y(1)
	Y(2)=Z_start  ! INITIAL VALUE OF Y(2)
        Y(3)=Px       ! INITIAL Px
        Y(4)=Pz       ! INITIAL Pz
        Y(5)=Arc      ! INITIAL Arc Length
        Y(6)=Q1       ! INITIAL
        Y(7)=P1       ! INITIAL
        Y(8)=Q2       ! INITIAL
        Y(9)=P2       ! INITIAL
        Y(10)=Travel_T! INITIAL
        !WRITE(*,*)Y(1),Y(2),Y(3),Y(4),Y(5),Y(6),Y(7),Y(8),Y(9),Y(10)
        H=0.1  ! STEP LENGTH OF INTEGRATION
        M=10  ! NUMBER OF EQUATIONS
	EPS=1.0E-05
        V_old=V(IZ_start,IX_start)
        V_new=V_old
	X_old=X_start
	Z_old=Z_start
	Ray_Arc=0.
	DO 10 I=1,9999999
	  CALL GRKT2(T,H,Y,M,F,EPS,D,B,C,G,E,NX,NZ,V,Dx,Dz,
     +Vx,Vz,X_old,Z_old,V_old,V_new,Vxx,Vzz,Vxz)
	  T=T+H
	  X=Y(1)
	  Z=Y(2)
	  Px=Y(3)
	  Pz=Y(4)
          Arc=Y(5)
          Q1=Y(6)
          P1=Y(7)
          Q2=Y(8)
          P2=Y(9)
          Travel_T=Y(10)
        !WRITE(*,*)Y(1),Y(2),Y(3),Y(4),Y(5),Y(6),Y(7),Y(8),Y(9),Y(10)
        !WRITE(*,*)I,Y(1),Y(2),Y(3)*V_new,Y(4)*V_new
          IF(X.LT.0) THEN
             GOTO 11
          ENDIF
          IF(Z.LT.0) THEN
             GOTO 11
          ENDIF
          IF(X.GT.Xmax) THEN
             GOTO 11
          ENDIF
          IF(Z.GT.Zmax) THEN
             GOTO 11
          ENDIF

	  IF(X.LT.Xmin) THEN 
             WRITE(*,*)' RAY HIT LEFT BOUNDARY, STOP'
             WRITE(*,*)'*** FINAL X,Z,Travel_T of RAY',IRAY,'=',
     +X_old,Z_old,Travel_T
             GOTO 11 
	  ELSEIF(X.GT.Xmax) THEN 
             WRITE(*,*)'RAY HIT RIGHT BOUNDARY, STOP'
             WRITE(*,*)'*** FINAL X,Z,Travel_T of RAY',IRAY,'=',
     +X_old,Z_old,Travel_T
             GOTO 11 
	  ELSEIF(Z.LT.Zmin) THEN 
             WRITE(*,*)'RAY HIT UPPER BOUNDARY, STOP'
             WRITE(*,*)'*** FINAL X,Z,Travel_T of RAY',IRAY,'=',
     +X_old,Z_old,Travel_T
             GOTO 11 
	  ELSEIF(Z.GT.Zmax) THEN 
             WRITE(*,*)'RAY HIT LOWER BOUNDARY, STOP'
             WRITE(*,*)'*** FINAL X,Z,Travel_T of RAY',IRAY,'=',
     +X_old,Z_old,Travel_T
             GOTO 11 
	  ENDIF
	  !One_Step_Arc=SQRT((X-X_old)**2+(Z-Z_old)**2)
	  !Ray_Arc=Ray_Arc+One_Step_Arc
	  !WRITE(*,*)'*******************************T=',T
	  !WRITE(*,*)'Ray_Arc,V_old,V_new='
	  !WRITE(*,*) Ray_Arc,V_old,V_new
	  !WRITE(*,*)'X,Z,Px,Pz,Arc,Q1,P1,Q2,P2='
	  !WRITE(*,*) X,Z,Px,Pz,Arc,Q1,P1,Q2,P2
	  !WRITE(*,*)'Q1*P1-P1*Q1=',Q1*P1-P1*Q1
	  !WRITE(*,*)'Q2*P2-P2*Q2=',Q2*P2-P2*Q2
	  !WRITE(*,*)'P2*Q1-Q2*P1=',P2*Q1-Q2*P1
	  !WRITE(*,*)'Q1*P2-P1*Q2=',Q1*P2-P1*Q2
	  !WRITE(*,*)'IZ,IX=',IZ,IX
          IX=INT(X/DX+0.5)+1   ! only for plot ray on vmodel 
          IZ=INT(Z/DZ+0.5)+1   ! only for plot ray on vmodel
          V_RAY(IZ,IX)=V(IZ,IX)+1000. ! TRACE RAYS IN VMODEL
	  X_old=X
	  Z_old=Z
	  V_old=V_new
10	CONTINUE   ! LOOP AGAINST RAY_ARC ENDS
11	CONTINUE
9	CONTINUE   ! LOOP AGAINST SITA ENDS
50	FORMAT(1X,'T=',F7.3,1X,'Y(1)=',D13.6,1X,'Y(2)=',D13.6,1X,
c    +  'Y(3)=',D13.6,1X,'Y(4)=',D13.6)
     +  'X=',f13.6,1X,'Z=',f13.6)

12	CONTINUE
	!FN2='vel_dome_nx1201_nz601_ray_fold.dat'
	FN2='v3000_x0.09_z0.09_plus_gauss_ball_big_ray_plot.dat'
	!FN2='stra_model_smooth_nz401_nx601_ray_fold.dat'
	!FN2='vp_change_along_depth_901_901_ray_plot_yk.dat'
	!FN2='./v1500_0.0x_0.5z_nx901_nz901_ray_plot.pc.dat'
	!FN2='./v3000_nx901_nz901_gauss_ball_ray_plot.dat'
	!FN2='./v3000_gauss_ball_55du_10ray_plot.dat'
        !FN2='timodel_vp_nx3617_nz1500_ray_plot_test.dat'
	OPEN(2,FILE=FN2,ACCESS='DIRECT',RECL=1*NZ)
	DO IX=1,NX
	WRITE(2,REC=IX) (V_RAY(IZ,IX),IZ=1,NZ)
	ENDDO
	CLOSE(2)
	WRITE(*,*)FN2
	END
*******************************************************************
	SUBROUTINE GRKT2(T,H,Y,M,F,EPS,D,B,C,G,E,NX,NZ,V,Dx,Dz,
     +Vx,Vz,X_old,Z_old,V_old,V_new,Vxx,Vzz,Vxz)
	DIMENSION Y(M),D(M),A(10),B(M),C(M),G(M),E(M)
	DOUBLE PRECISION Y,D,A,B,C,G,T,H,X,HH,E
	REAL Px,Pz,DVx,DVz
        REAL V(NZ,NX)
        REAL Vx(NZ,NX)
        REAL Vz(NZ,NX)
        REAL Vxx(NZ,NX)
        REAL Vzz(NZ,NX)
        REAL Vxz(NZ,NX)

	!WRITE(*,*)'*** ENTER GRKT2'
	HH=H
	N=1
	P=1+EPS
	X=T
	DO 5 I=1,M
5	C(I)=Y(I)
10	IF (P.GE.EPS) THEN
	  A(1)=HH/2.0
	  A(2)=A(1)
	  A(3)=HH
	  A(4)=HH
	  DO 20 I=1,M
	    G(I)=Y(I)
	    Y(I)=C(I)
20	  CONTINUE
	  DT=H/N
	  T=X
	  DO 100 J=1,N 
	    !CALL F(T,Y,M,D,NX,NZ,V,Dx,Dz,Vx,Vz)
	    CALL F(T,Y,M,D,NX,NZ,V,Dx,Dz,Vx,Vz,X_old,Z_old,V_old,V_new,
     +             Vxx,Vzz,Vxz)
	    DO 30 I=1,M
	    E(I)=Y(I)
30	    B(I)=Y(I)
	    DO 50 K=1,3
	      DO 40 I=1,M
	        Y(I)=E(I)+A(K)*D(I)
	        B(I)=B(I)+A(K+1)*D(I)/3.0
40	      CONTINUE
	      TT=T+A(K)
	      !CALL F(TT,Y,M,D,NX,NZ,V,Dx,Dz,Vx,Vz)
	      CALL F(T,Y,M,D,NX,NZ,V,Dx,Dz,Vx,Vz,X_old,Z_old,V_old,V_new,
     +             Vxx,Vzz,Vxz)
50	    CONTINUE
	    DO 60 I=1,M
60	    Y(I)=B(I)+HH*D(I)/6.0
	    T=T+DT
100	  CONTINUE
	  P=0.0
	  DO 110 I=1,M
	    Q=ABS(Y(I)-G(I))
	    IF (Q.GT.P) P=Q
110	  CONTINUE
	  HH=HH/2.0
	  N=N+N
	  GOTO 10
	END IF
	T=X
	RETURN
	END
*******************************************************************
	SUBROUTINE F(T,Y,M,D,NX,NZ,V,Dx,Dz,Vx,Vz,X_old,Z_old,V_old,V_new,
     +              Vxx,Vzz,Vxz)
	DIMENSION Y(M),D(M)
	DOUBLE PRECISION Y,D,T
	REAL Px,Pz,DVx,DVz
	REAL V(NZ,NX) 
	REAL Vx(NZ,NX) 
	REAL Vz(NZ,NX) 
        REAL Vxx(NZ,NX)
        REAL Vzz(NZ,NX)
        REAL Vxz(NZ,NX)

        X=Y(1)
        Z=Y(2)
        Px=Y(3)
        Pz=Y(4)
        Arc=Y(5)
        Q1=Y(6)
        P1=Y(7)
        Q2=Y(8)
        P2=Y(9)
        Travel_T=Y(10)
        delta_x=X-X_old
        delta_z=Z-Z_old
	!WRITE(*,*)'X,Z=',X,Z
	!WRITE(*,*)'X_old,Z_old=',X_old,Z_old
	!WRITE(*,*)'delta_x,delta_z=',delta_x,delta_z
        Iz=INT(Z/DZ+0.5)+1   ! too coarse, need to modify
        Ix=INT(X/DX+0.5)+1   ! too coarse, need to modify
        !V_new=V(Iz,Ix)       ! V_new should be obtained by interpolation
        DVx  =Vx(Iz,Ix)
        DVz  =Vz(Iz,Ix)
        V_new=V_old+delta_x*DVx+delta_z*DVz
        Vnn=(Vxx(Iz,Ix)*Y(4)*Y(4)-2.0*Vxz(Iz,Ix)*Y(3)*Y(4)
     +   +Vzz(Iz,Ix)*Y(3)*Y(3))*V_new*V_new
	!WRITE(*,*)'V_new1,V_new=',V_new1,V_new
	!pause
	! DVX and DVz should be updated in real time !
	D(1)=V_new*Px
	D(2)=V_new*Pz
	D(3)=-1*DVx/(V_new*V_new)
	D(4)=-1*DVz/(V_new*V_new)
        D(5)=1
        D(6)=V_new*P1
        D(7)=-1*Vnn*Q1/(V_new*V_new)
        D(8)=V_new*P2
        D(9)=-1*Vnn*Q2/(V_new*V_new)
        D(10)=1/V_new

	RETURN
	END
*******************************************************************
	SUBROUTINE DERIVATE(V,Vx,Vz,Vxx,Vxz,Vzz,NX,NZ,Dx,Dz)

	DIMENSION V(NZ,NX)
	DIMENSION Vx(NZ,NX)
	DIMENSION Vz(NZ,NX)
	DIMENSION Vxx(NZ,NX)
	DIMENSION Vzz(NZ,NX)
	DIMENSION Vxz(NZ,NX)


 	! Vx: First order derivate of V along X direction
	DO Iz=1,NZ
	DO Ix=2,NX-1
	   Vx(Iz,Ix)=(V(Iz,Ix+1)-V(Iz,Ix-1))/(2.*Dx)
	ENDDO
	ENDDO
	DO Iz=1,NZ
	   Vx(Iz,1)=Vx(Iz,2)
	   Vx(Iz,Nx)=Vx(Iz,Nx-1)
	ENDDO
 	! Vz: First order derivate of V along Z direction
	DO Ix=1,NX
	DO Iz=2,NZ-1
	   Vz(Iz,Ix)=(V(Iz+1,Ix)-V(Iz-1,Ix))/(2.*Dz)
	ENDDO
	ENDDO
	DO Ix=1,NX
	   Vz(1,Ix)=Vz(2,Ix)
	   Vz(Nz,Ix)=Vz(Nz-1,Ix)
	ENDDO
 	! Vxx: Second order derivate of V along X direction
	DO Iz=1,NZ
	DO Ix=2,NX-1
	   Vxx(Iz,Ix)=(Vx(Iz,Ix+1)-Vx(Iz,Ix-1))/(2.*Dx)
	ENDDO
	ENDDO
	DO Iz=1,NZ
	   Vxx(Iz,1)=Vxx(Iz,2)
	   Vxx(Iz,Nx)=Vxx(Iz,Nx-1)
	ENDDO
 	! Vzz: Second order derivate of V along Z direction
	DO Ix=1,NX
	DO Iz=2,NZ-1
	   Vzz(Iz,Ix)=(Vz(Iz+1,Ix)-Vz(Iz-1,Ix))/(2.*Dz)
	ENDDO
	ENDDO
	DO Ix=1,NX
	   Vzz(1,Ix)=Vzz(2,Ix)
	   Vzz(Nz,Ix)=Vzz(Nz-1,Ix)
	ENDDO
 	! Vxz: Second order mixed derivate of V along Z then along X direction
	DO Iz=1,NZ
	DO Ix=2,NX-1
	   Vxz(Iz,Ix)=(Vz(Iz,Ix+1)-Vz(Iz,Ix-1))/(2.*Dx)
	ENDDO
	ENDDO
	DO Iz=1,NZ
	   Vxz(Iz,1)=Vxz(Iz,2)
	   Vxz(Iz,Nx)=Vxz(Iz,Nx-1)
	ENDDO

	RETURN
	END
*******************************************************************
