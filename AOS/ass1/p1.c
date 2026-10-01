#include <stdio.h>
#include <unistd.h>       // fork(), pipe(), read(), write(), close()
#include <sys/types.h>    // pid_t
#include <sys/wait.h>     // waitpid()

#define EMI 800
#define WITHDRAW 600
#define DEPOSIT 1000

/* Message: type + amount
   1 = EMI, 2 = Withdrawal, 3 = Deposit */
void sendMessage(int fd, int type, int amount)
{
    int msg[2] = {type, amount};
    write(fd, msg, sizeof(msg));            // Send message through pipe
}

void display(int freeHead, int busy)
{
    printf("\nHash Queues:\n");
    printf("H0: B10(%s)\n", busy ? "Busy" : "Free");
    printf("H1: B11(Busy)\n");
    printf("H2: B12(Busy)\n");

    if(freeHead == -1)
        printf("Free List: NULL\n");
    else
        printf("Free List: B10 -> NULL\n");
}

void emi(int pipeOut, int pipeIn, int balance, int freeHead)
{
    if(balance < EMI && freeHead == -1) {
        printf("EMI: Waiting -> Scenario 4\n");
        read(pipeIn, &balance, sizeof(balance));   // Wait for parent
    }

    sendMessage(pipeOut, 1, EMI);                  // Send EMI request
}

void withdrawal(int pipeOut, int pipeIn, int busy)
{
    if(busy) {
        printf("Withdrawal: B10 busy -> Scenario 5\n");
        read(pipeIn, &busy, sizeof(busy));         // Wait for parent
    }

    sendMessage(pipeOut, 2, WITHDRAW);             // Send withdrawal request
}

void deposit(int pipeOut)
{
    printf("Deposit: %d added\n", DEPOSIT);

    sendMessage(pipeOut, 3, DEPOSIT);              // Send deposit request
}

int main()
{
    int childToParent[2];
    int parentToChild[2];

    pipe(childToParent);                            // Pipe 1: children -> parent
    pipe(parentToChild);                            // Pipe 2: parent -> children

    int balance = 500;
    int freeHead = -1;                              // Free List empty
    int busy = 1;                                   // B10 busy

    printf("Initial Balance: %d\n", balance);
    display(freeHead, busy);

    pid_t e = fork();                               // Create EMI process

    if(e == 0) {
        close(childToParent[0]);
        close(parentToChild[1]);

        emi(childToParent[1], parentToChild[0],
            balance, freeHead);

        return 0;
    }

    pid_t w = fork();                               // Create Withdrawal process

    if(w == 0) {
        close(childToParent[0]);
        close(parentToChild[1]);

        withdrawal(childToParent[1], parentToChild[0], busy);

        return 0;
    }

    pid_t d = fork();                               // Create Deposit process

    if(d == 0) {
        close(childToParent[0]);
        close(parentToChild[1]);

        deposit(childToParent[1]);

        return 0;
    }

    /* Parent */
    close(childToParent[1]);
    close(parentToChild[0]);

    int msg[2];

    /* Wait for Deposit message */
    read(childToParent[0], msg, sizeof(msg));

    if(msg[0] == 3) {
        balance += msg[1];

        printf("\nParent: Deposit received\n");
        printf("Balance = %d\n", balance);

        /* Release B10 */
        busy = 0;
        freeHead = 0;

        printf("B10 released\n");
        display(freeHead, busy);

        /* Send updated state to EMI and Withdrawal */
        write(parentToChild[1], &balance, sizeof(balance));
        write(parentToChild[1], &balance, sizeof(balance));
    }

    /* Receive EMI/Withdrawal requests */
    read(childToParent[0], msg, sizeof(msg));

    if(msg[0] == 1) {
        balance -= msg[1];
        printf("EMI: %d paid, Balance = %d\n",
               msg[1], balance);
    }
    else {
        balance -= msg[1];
        printf("Withdrawal: %d, Balance = %d\n",
               msg[1], balance);
    }

    read(childToParent[0], msg, sizeof(msg));

    if(msg[0] == 1) {
        balance -= msg[1];
        printf("EMI: %d paid, Balance = %d\n",
               msg[1], balance);
    }
    else {
        balance -= msg[1];
        printf("Withdrawal: %d, Balance = %d\n",
               msg[1], balance);
    }

    waitpid(e, NULL, 0);                            // Wait for EMI
    waitpid(w, NULL, 0);                            // Wait for Withdrawal
    waitpid(d, NULL, 0);                            // Wait for Deposit

    printf("\nFinal Balance: %d\n", balance);
    display(freeHead, busy);

    close(childToParent[0]);
    close(parentToChild[1]);

    return 0;
}
