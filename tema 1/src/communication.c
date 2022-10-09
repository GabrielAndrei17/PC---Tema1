#include "communication.h"
#include "util_comm.h"

#include <stdio.h>


/* Task 1 - The Beginning */

void send_byte_message(void)
{
    /* TODO
     * Send the encoding of the characters: R, I, C, K
     */

    send_squanch('R'-'A'+1);
    send_squanch('I'-'A'+1);
    send_squanch('C'-'A'+1);
    send_squanch('K'-'A'+1);

}


void recv_byte_message(void)
{
    /* TODO
     * Receive 5 encoded characters, decode them and print
     * them to the standard output (as characters)
     *
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    for(short i=0;  i<5;  i++)
    {
       short character=recv_squanch();
       fprintf(stdout,"%c", (char)(character + 'A' -1) );
    }   
}


void comm_byte(void)
{
    /* TODO
     * Receive 10 encoded characters and send each character (the character is
     * still encoded) 2 times
     */

    for(short i=0;  i<10;  i++)
    {
       short ec=recv_squanch();
       send_squanch(ec);
       send_squanch(ec);
    }
}


/* Task 2 - Waiting for the Message */

void send_message(void)
{
    /* TODO
     * Send the message: HELLOTHERE
     * - send the encoded length
     * - send each character encoded
     */
    uint8_t len = (10<<2) ;
    send_squanch(len);
    send_squanch('H' - 'A' +1);
    send_squanch('E' - 'A' +1);
    send_squanch('L' - 'A' +1);
    send_squanch('L' - 'A' +1);
    send_squanch('O' - 'A' +1);
    send_squanch('T' - 'A' +1);
    send_squanch('H' - 'A' +1);
    send_squanch('E' - 'A' +1);
    send_squanch('R' - 'A' +1);
    send_squanch('E' - 'A' +1);
}


void recv_message(void)
{
    /* TODO
     * Receive a message:
     * - the first value is the encoded length
     * - length x encoded characters
     * - print each decoded character
     * 
     * ATTENTION!: Use fprintf(stdout, ...)
     */

    uint8_t len , lungime = 0;
    len = recv_squanch();
    len = (len>>2);
    for(uint8_t i=1;i<=8;i*=2)
    {
       if(len%2==1)
          lungime = i + lungime;
 
       len = (len>>1);
    }

    fprintf(stdout,"%d", lungime);
    for(uint8_t i=1; i<= lungime; i++)
    {
        short character = recv_squanch();
        fprintf(stdout,"%c", (char)(character + 'A' -1) );
    }

}


void comm_message(void)
{
    /* TODO
     * Receive a message from Rick and do one of the following depending on the
     * last character from the message:
     * - 'P' - send back PICKLERICK
     * - anything else - send back VINDICATORS
     * You need to send the messages as you did at the previous tasks:
     * - encode the length and send it
     * - encode each character and send them
     */
    uint8_t len , lungime = 0,character;
    len = recv_squanch();
    len = (len>>2);
    for(uint8_t i=1;i<=8;i*=2)
    {
       if(len%2==1)
          lungime = i + lungime;
 
       len = (len>>1);
    }

    for(uint8_t i=1; i<= lungime; i++)
        character = recv_squanch();
    if(character == 'P' - 'A' + 1)
    {
       send_squanch(10<<2);
       send_squanch('P' - 'A' +1);
       send_squanch('I' - 'A' +1);
       send_squanch('C' - 'A' +1);
       send_squanch('K' - 'A' +1);
       send_squanch('L' - 'A' +1);
       send_squanch('E' - 'A' +1);
       send_squanch('R' - 'A' +1);
       send_squanch('I' - 'A' +1);
       send_squanch('C' - 'A' +1);
       send_squanch('K' - 'A' +1);
    }
    else
    {
       send_squanch(11<<2);
       send_squanch('V' - 'A' +1);
       send_squanch('I' - 'A' +1);
       send_squanch('N' - 'A' +1);
       send_squanch('D' - 'A' +1);
       send_squanch('I' - 'A' +1);
       send_squanch('C' - 'A' +1);
       send_squanch('A' - 'A' +1);
       send_squanch('T' - 'A' +1);
       send_squanch('O' - 'A' +1);
       send_squanch('R' - 'A' +1);
       send_squanch('S' - 'A' +1);
    }
}


/* Task 3 - In the Zone */

void send_squanch2(uint8_t c1, uint8_t c2)
{
    /* TODO
     * Steps:
     * - "merge" the character encoded in c1 and the character encoded in c2
     * - use send_squanch to send the newly formed byte
     */
    uint8_t character=0 , p2= 1;
    for(uint8_t i =1;i<=8;i++)
        if(i%2==1)
        {
            character=(c2%2==1)*p2 + character;
            p2*=2;
            c2 = (c2>>1);
        }
        else
        {
            character=(c1%2==1)*p2 + character;
            p2*=2;
            c1 = (c1>>1);
        }
    send_squanch(character);    
        
}


uint8_t decode_squanch2(uint8_t c)
{
    /* TODO */
    /*
     * Decode the given byte:
     * - split the two characters as in the image from ocw.cs.pub.ro
     */

    uint8_t res = -1;
    uint8_t p1 = 1 , p2 = 1;
    uint8_t c1 = 0 , c2 = 0;

    for(uint8_t i=1;i<=8;i++)
       if(i%2==1)
       {
           c2=(c%2==1)*p2 + c2;
           c=(c>>1);
           p2=(p2<<1);
       }
       else
       {
           c1=(c%2==1)*p1 + c1;
           c=(c>>1);
           p1=(p1<<1);
       }
    c1 = (c1<<4);
    res = c1+c2;

    return res;
}
