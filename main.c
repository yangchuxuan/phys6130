#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(void){
  char output_dir[120];
  for(int i=0;i<10;i++){
	 snprintf(output_dir,sizeof(output_dir),"./lalala/lalala%d/",i);
	 printf("%s\n",output_dir);   
	 mkdir(output_dir, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
   }
    
  return 0;
}
