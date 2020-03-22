set -x
suaddhead <1_all.bin ns=2000 | sushw key=dt a=500 | \
sushw key=fldr,tracf a=1,1 b=0,1 c=1,0 j=55,24|\
sushw key=sx,gx a=-6,0 b=0,3 c=1.5,0 j=55,24|\
suchw key1=offset key2=gx key3=sx b=1 c=-1|\
sushw key=cdp a=1 b=2 c=2 j=24> 1_all.su 
 susort <1_all.su >1_cdp.su cdp offset
 suximage <1_cdp.su perc=99

#a,b,c,j对应各自的key
#a:initial value in ensemble(初始值)
#b:increment in ensemble（组内增量）
#c:increment between ensembles（组间增量）
#j:traces in a ensemble（最大值）

#suchw: calculate some unknown header with some known headers
#       key1=a+b*key2+c*key3

