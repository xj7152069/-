set -x
suaddhead <high_modeldata.bin ns=1200 | sushw key=dt a=1000 | \
sushw key=fldr,tracf a=1,1 b=0,1 c=1,0 j=191,401|\
sushw key=sx,gx a=2100,100 b=0,10 c=20,20 j=191,401|\
suchw key1=offset key2=gx key3=sx b=1 c=-1|\
sushw key=cdp a=1 b=1 c=4 j=401> all_modeldata.su 
 susort <all_modeldata.su >modeldata_cdp.su cdp offset
 suximage <modeldata_cdp.su perc=97

#a,b,c,j对应各自的key
#a:initial value in ensemble(初始值)
#b:increment in ensemble（组内增量）
#c:increment between ensembles（组间增量）
#j:traces in a ensemble（最大值）
1
#suchw: calculate some unknown header with some known headers
#       key1=a+b*key2+c*key3

