#include <stdio.h>

// 将一个长字符串，按照空白字符分开，存放在一个字符串数组中
// 返回分解出来的短字符串数量
// 输入参数argv，存放返回的字符串的数组
// 输入参数buffer，输入的长字符串
// 返回值：正确返回>0，错误返回0
int process_str(char* argv[], const char* buffer)
{
   int argc = 0;
   int j = 0;
   int i = 0;

   while(buffer[i] != 0)
   {
      while(buffer[i] == ' ' || buffer[i] == '\t' )
         i++;
      if(buffer[i] != 0)
      {
         while(buffer[i] != ' ' && buffer[i] != '\t' && buffer[i] != 0)
         {
            argv[argc][j] = buffer[i];
            i++;
            j++;
            if(j >= 31)
               break;
         }
         if(j >= 31)
            break;
         argv[argc][j] = 0;
         argc++;
         j = 0;
         if(argc >= 30)
            break;
      }
   }
   if(buffer[i] != 0)
   {
      printf("invalid command.\n");
      return 0;
   }
   return argc;
}

int main()
{
   char* argv[30];
   int i;
   for(i = 0; i < 30; i++)
      argv[i] = new char[32];
   int argc = process_str(argv, " kjsf  ks  ks dhf ksdjh ksdjfh skdjf skdf skdjf sdkjf kjsdhf   ");
   for(i = 0; i < argc; i++)
      printf("argv[%d] = %s\n", i, argv[i]);
   return 0;
}

