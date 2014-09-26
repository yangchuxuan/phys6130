#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
  char fname[120];
  char output_dir[120];
  for(int i=0;i<10;i++){
	 sprintf_s(output_dir,"./lalala/lalala%d/",i);   
	 mkdir(output_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
   }
    
  return 0;
}
