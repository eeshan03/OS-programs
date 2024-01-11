#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE 100

int comp(const void *l, const void *n) {
   return (*(int*)l - *(int*)n);
}

void SCAN(int arr[], int size, int head, char* dn) {
   int seek_num = 0;
   int dt, cur_track;
   int leftside[MAX_SIZE], rightside[MAX_SIZE];
   int seek_seq[MAX_SIZE + 3];
   int m_scan = 0, s_scan = 0;
   if (strcmp(dn, "leftside") == 0)
      leftside[m_scan++] = 0;
   else if (strcmp(dn, "rightside") == 0)
      rightside[s_scan++] = MAX_SIZE - 1;
   for (int p_s = 0; p_s < size; p_s++) {
      if (arr[p_s] < head)
         leftside[m_scan++] = arr[p_s];
      if (arr[p_s] > head)
         rightside[s_scan++] = arr[p_s];
   }
   qsort(leftside, m_scan, sizeof(int), comp);
   qsort(rightside, s_scan, sizeof(int), comp);
   int go = 2;
   int ind = 0;
   while (go--) {
      if (strcmp(dn, "leftside") == 0) {
         for (int p_s = m_scan - 1; p_s >= 0; p_s--) {
            cur_track = leftside[p_s];
            seek_seq[ind++] = cur_track;
            dt = abs(cur_track - head);
            seek_num += dt;
            head = cur_track;
        }
        dn = "rightside";
      }
      else if (strcmp(dn, "rightside") == 0) {
         for (int p_s = 0; p_s < s_scan; p_s++) {
            cur_track = rightside[p_s];
            seek_seq[ind++] = cur_track;
            dt = abs(cur_track - head);
            seek_num += dt;
            head = cur_track;
         }
         dn = "leftside";
      }
   }
   printf("Num of seek process = %d\n", seek_num);
   printf("Sequence is: ");
   for (int p_s = 0; p_s < ind; p_s++) {
      printf("%d ", seek_seq[p_s]);
   }
   printf("\n");
}

int main() {
   int size, head;
   char dn[20];

   printf("Enter the number of elements in the disk queue: ");
   scanf("%d", &size);

   if (size > MAX_SIZE) {
      printf("Size exceeds maximum limit (%d).\n", MAX_SIZE);
      return 1;
   }

   int arr[MAX_SIZE];
   printf("Enter the disk queue elements:\n");
   for (int i = 0; i < size; i++) {
      scanf("%d", &arr[i]);
   }

   printf("Enter the initial head position: ");
   scanf("%d", &head);

   printf("Enter the direction (leftside/rightside): ");
   scanf("%s", dn);

   SCAN(arr, size, head, dn);
   return 0;
}
