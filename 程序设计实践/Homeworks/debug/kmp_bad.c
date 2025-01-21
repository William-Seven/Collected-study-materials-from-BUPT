#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int g_sleep_seconds;

#define TRUE 1
#define FALSE 0
typedef int BOOL;

// 构建表达pattern回退位置的next表返回
// next[n]的含义是，pattern[n]之前的部分，前缀=后缀的最大长度
int* build_next(const char* pattern, int length)
{
   int next[256];
   next[0] = -1; // 初始化next[0]为-1
   int n = 1; // next的游标，0已经赋过了，从1开始算
   int i = -1; // pattern的游标，初始值为-1，指向即将要匹配的前缀的最后一位
   while(n < length)
   {
      if(i == -1) // 如果pattern游标为初始值
      {
         printf("i = -1, so next[%d] = 0\n", n);
         next[n] = 0; // next[n]肯定为0，因为没有前缀和后缀匹配
         i = 0; // 下一循环会尝试匹配pattern[0]和pattern[n-1]
         n++; 
      }
      else if(pattern[n - 1] == pattern[i]) // 出现了前缀=后缀，pattern[n - 1]：后缀的最后一位，pattern[i]：前缀的最后一位
      {
         printf("p[%d]:%c == p[%d]:%c, so next[%d] = %d\n", n - 1, pattern[n - 1], i, pattern[i], n, i + 1);
         i++;
         next[n] = i; // 说明，当前能匹配的前缀和后缀又多了一位
         n++;
      }
      else // 不匹配，前面积累前缀后缀匹配长度无效了，只好退回去匹配上一个可能的前缀
      {
         printf("p[%d]:%c != p[%d]:%c, so i(%d) back to next[%d](%d)\n", n - 1, pattern[n - 1], i, pattern[i], i, i, next[i]);
         i = next[i];
      }
   }
   return next;
}

// 打印构建好的next表
void print_next(const char* pattern, int* next, int length)
{
   printf("\npattern: ");
   for(int i = 0; i <= length; i++)
      printf(" %c ", pattern[i]);
   printf("\n");
   printf("next:    ");
   for(int i = 0; i <= length; i++)
      printf("%2d ", next[i]);
   printf("\n\n");
}

// 下面是几个打印相关的小函数支持
void print_chars(int count, char c)
{
   for(int i = 0; i < count; i++)
      printf("%c", c);
}
void print_spaces(int count)
{
   print_chars(count, ' ');
}
// line_back和line_clear这两个函数windows下执行有问题，这个不算本题要求寻找的BUG
void line_back()
{
#ifndef WIN32
   printf("\033[1A"); //回到上一行
#else
   printf("\n");
#endif
}
void line_clear()
{
#ifndef WIN32
   printf("\r");
   printf("\033[K");  //清除该行
#endif
}

// 打印当前的匹配状态
// 参数s：数据
// 参数i：数据的当前指针
// 参数j：pattern的当前指针
// 参数head：前面预留的空白
// 参数match：当前字符是否匹配，1匹配，0不匹配
void print_match_state(const char* s, int i, int j, int head, BOOL match)
{
   line_back(); // 回到上一行
   line_clear(); // 清空上一行

   // 打印匹配状态。
   // 已经匹配的，打印竖线。
   // 新的匹配，如果匹配也打印竖线，否则打印x
   print_spaces(head); 
   print_chars(j, '|');
   printf("%c", match ? '|': 'x');

   // 打印当前数据
   printf("\n");
   line_clear();
   if(i <= head)
   {
      print_spaces(head - i + j);
      printf("%s", s);
   }
   else
      printf("%s", s + i - j - head);
   fflush(stdout);
}

// 进行kmp匹配，显示匹配过程
// 参数s：要匹配的数据
// 参数pattern：要匹配的模式
// 参数next：模式的next表
// 参数pattern_length：模式的长度
const char* kmp(const char* s, const char* pattern, int* next, int pattern_length)
{
   int i = 0; // 数据s的游标
   int j = 0; // pattern的游标

#define HEAD_SPACE_COUNT 20
   print_spaces(HEAD_SPACE_COUNT);
   printf("%s\n\n", pattern);
   print_spaces(HEAD_SPACE_COUNT);
   printf("%s", s);
   fflush(stdout);

   while (s[i] != 0 && j < pattern_length)
   {
      sleep(g_sleep_seconds);
      if(s[i] == pattern[j]) // 如果匹配，那么数据和parrern的游标同时右移1位
      {
         print_match_state(s, i, j, HEAD_SPACE_COUNT, TRUE);
         i++;
         j++;
      }
      else
      {
         if(j == 0) // 不匹配，并且pattern游标为0（第一位就不匹配），那么数据游标右移1位，pattern游标维持0
         {
            print_match_state(s, i, j, HEAD_SPACE_COUNT, FALSE);
            i++;
         }
         else
         {
            print_match_state(s, i, j, HEAD_SPACE_COUNT, FALSE);
            j = next[j]; // 不匹配，并且pattern游标不是0，pattern根据next指示回退，数据游标不动
         }
      }
   }
   // 从循环出来，如果pattern游标到了末尾，那么表示匹配成功
   if (j >= pattern_length)
      return s + i - pattern_length; // 返回数据匹配pattern的起始位置指针
   return NULL;
}

// 参数1：pattern
// 参数2：要匹配的数据
// 参数3：每一步等待的时间，整数，秒为单位。默认1秒。
int main(int argc, const char* argv[])
{
   if(argc < 3)
   {
      printf("Usage: %s pattern text [sleep]\n", argv[0]);
      return 1;
   }
   const char* pattern = argv[1];
   const char* text = argv[2];
   g_sleep_seconds = 1;
   if(argc == 4)
      g_sleep_seconds = atoi(argv[3]);

   int pattern_length = strlen(pattern);
   int* next = build_next(pattern, pattern_length);
   print_next(pattern, next, pattern_length);

   const char* p = kmp(text, pattern, next, pattern_length);
   sleep(g_sleep_seconds);
   if(p == NULL)
      printf("\n\nnot match\n\n");
   else
      printf("\n\nmatch at %ld\n\n", p - text);
   return 0;
}
