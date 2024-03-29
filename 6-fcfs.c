#include <stdio.h>

int main() {
    int pageFaults = 0;
    int frames = 3;
    int m, n, s, pages;

    printf("Enter the number of pages in the incoming stream: ");
    scanf("%d", &pages);

    int incomingStream[pages];

    printf("Enter the page reference string:\n");
    for (m = 0; m < pages; m++) {
        scanf("%d", &incomingStream[m]);
    }

    printf("Incoming \t Frame 1 \t Frame 2 \t Frame 3");
    int temp[frames];
    for (m = 0; m < frames; m++) {
        temp[m] = -1;
    }

    for (m = 0; m < pages; m++) {
        s = 0;

        for (n = 0; n < frames; n++) {
            if (incomingStream[m] == temp[n]) {
                s++;
                pageFaults--;
            }
        }
        pageFaults++;

        if ((pageFaults <= frames) && (s == 0)) {
            temp[m] = incomingStream[m];
        } else if (s == 0) {
            temp[(pageFaults - 1) % frames] = incomingStream[m];
        }

        printf("\n");
        printf("%d\t\t\t", incomingStream[m]);
        for (n = 0; n < frames; n++) {
            if (temp[n] != -1)
                printf(" %d\t\t\t", temp[n]);
            else
                printf(" - \t\t\t");
        }
    }

    printf("\nTotal Page Faults:\t%d\n", pageFaults);
    return 0;
}
