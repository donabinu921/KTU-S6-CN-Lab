#include<stdio.h>  // Includes standard input/output functions

int main()
{
    // Declare variables
    int incoming, outgoing, buck_size, n, store = 0;

    // Prompt user for bucket size, outgoing rate, and number of inputs
    printf("Enter the bucket size, outgoing rate and no of inputs\n");
    scanf("%d %d %d", &buck_size, &outgoing, &n);

    // Loop for each incoming packet
    while (n != 0)
    {
        // Prompt user for the size of the incoming packet
        printf("Enter the incoming packet size: ");
        scanf("%d", &incoming);
        
        // Display the size of the incoming packet
        printf("\nThe incoming packet size: %d\n", incoming);

        // Check if the incoming packet can fit in the bucket
        if (incoming <= (buck_size - store))
        {
            // Add incoming packet to the bucket
            store += incoming;
            printf("The bucket size %d out of %d\n", store, buck_size);
        }
        else
        {
            // If packet size exceeds available space, drop the excess packets
            printf("Dropped %d no of packets\n", incoming - (buck_size - store));
            // Fill the bucket to its capacity
            store = buck_size;
            printf("The bucket size %d out of %d\n", store, buck_size);
        }

        // Simulate outgoing packet transfer
        store -= outgoing;

        // Ensure bucket size does not go negative
        if (store < 0)
        {
            store = 0;
        }

        // Display the remaining packets in the bucket after outgoing packets
        printf("After outgoing %d packets left out of %d in buffer\n", store, buck_size);
        
        // Decrement the number of incoming packets to be processed
        n--;
    }
}
