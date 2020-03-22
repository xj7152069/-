
//生成单点脉冲记录

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include<iomanip>
#include<math.h>
#include<vector>

using namespace std;
 float p[198][306];
int main()
{
 int i,j;
 ofstream outf;

 for(i=0;i<198;i++)
   {for(j=0;j<306;j++)
     {if(j==153 && i==20)
       p[i][j]=1.0;
      else
       p[i][j]=0.0;
      }
    }

outf.open("mc");
for(j=0;j<306;j++)
  {for(i=0;i<198;i++)
     {outf.write((char*)&p[i][j],sizeof(p[i][j]));}}
      outf.close();
     cout<<"the data has been saved as mc"<<endl;

return 0;
}
