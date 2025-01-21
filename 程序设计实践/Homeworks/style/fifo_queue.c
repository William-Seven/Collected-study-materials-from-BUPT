#include <stdio.h>
#include <stdlib.h>

/* 实现一个整数为成员的先进先出队列 */
struct fifo_queue_item
{
   int item_value;
   struct fifo_queue_item* next_item;
};

struct fifo_queue
{
   struct fifo_queue_item* queue_head;
   struct fifo_queue_item* queue_tail;
};

// push a item_value to queue back
void fifo_queue_push_back(struct fifo_queue* queue, int item_value)
{
   struct fifo_queue_item* item = (struct fifo_queue_item*)malloc(sizeof(struct fifo_queue_item));
   item->item_value = item_value;
   item->next_item = NULL;
   if(queue->queue_head == NULL)
   {
      queue->queue_head = queue->queue_tail = item;
      return;
   }
   queue->queue_tail->next_item = item;
   queue->queue_tail = item;
}

// pop a item_value from queue front
int fifo_queue_pop_front(struct fifo_queue* queue, int* value)
{
   if(queue->queue_head != NULL)
   {
      struct fifo_queue_item* item = queue->queue_head;
      if(item->next_item == NULL)
      {
         queue->queue_head = NULL;
         queue->queue_tail = NULL;
      }
      else
         queue->queue_head = item->next_item;
      *value = item->item_value;
      free(item);
      return 1;
   }
   else
      return 0;
}

int main()
{
   struct fifo_queue queue;
   queue.queue_head = queue.queue_tail = NULL;

   int i;
   for(i = 0; i < 10; i++)
   {
      fifo_queue_push_back(&queue, i);
      printf("push to back: %d\n", i);
   }
   for(i = 0; i < 11; i++)
   {
      int value;
      int success = fifo_queue_pop_front(&queue, &value);
      if(success)
         printf("pop from front: %d\n", value);
      else
         printf("pop from front fail\n");
   }
}
