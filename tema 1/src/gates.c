#include "gates.h"

#include <stdio.h>
#include <assert.h>

/* Task 1 - Bit by Bit */

uint8_t get_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint8_t res = -1;

    /* TODO
     *
     * "res" should be 1 if the bit is active, else 0
     */
    nr = (nr>>i );
    res = nr % 2 ;  ///shiftam numarul la dreapta nu i pozitii ramanand bitul i pe prima pozitie

    return res;
}


uint64_t flip_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit flipped
     */
    uint64_t mask = 1;
    mask = (mask << i) ;

    if( get_bit(nr , i) == 1 )
    {
        mask = (~mask) ;
        res = (nr & mask) ;
    }
    else
    {
        res = (nr | mask);
        
    }
    
    return res;
}


uint64_t activate_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = 0xFF;

    /* TODO
     *
     * Return the "nr" with the ith bit "1"
     */

    uint64_t mask = 1;
    mask = (mask << i) ;
    res = (nr | mask);

    return res;
}


uint64_t clear_bit(uint64_t nr, uint8_t i)
{
    assert(i <= 8 * sizeof nr);

    uint64_t res = -1;

    /* TODO
     *
     * Return the "nr" with the ith bit "0"
     */

    uint64_t mask = 1;
    mask = (mask << i) ;

    mask = (~mask) ;
    res = (nr & mask) ;

    return res;
}


/* Task 2 - One Gate to Rule Them All */

uint8_t nand_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    return !(a & b);
}


uint8_t and_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the and gate */
    if( nand_gate(a , b) )
      res = 0 ;
    else
      res = 1 ;
      
    return res;
}


uint8_t not_gate(uint8_t a)
{
    assert (a == 0 || a == 1);

    uint8_t res = -1;

    /* TODO - Use the nand gate to implement the not gate */

    res = nand_gate(a , a);

    return res;
}


uint8_t or_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the or gate */
    res =  nand_gate( not_gate(a) ,not_gate(b)  ) ;

    return res;
}


uint8_t xor_gate(uint8_t a, uint8_t b)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);

    uint8_t res = -1;

    /* TODO - Use the previously defined gates to implement the xor gate */

    res = nand_gate(     nand_gate(a,nand_gate(a,b) ),    nand_gate(b,nand_gate(a,b) )  );

    return res;
}


/* Task 3 - Just Carry the Bit */

uint8_t full_adder(uint8_t a, uint8_t b, uint8_t c)
{
    assert (a == 0 || a == 1);
    assert (b == 0 || b == 1);
    assert (c == 0 || c == 1);

    uint8_t res = -1;

    /* TODO - implement the full_adder using the previous gates
     * Since the full_adder needs to provide 2 results, you should
     * encode the sum bit and the carry bit in one byte - you can encode
     * it in whatever way you like
     */

    uint8_t suma = xor_gate(c ,xor_gate(a,b));
    uint8_t cary = or_gate(and_gate(a,b),and_gate(c,xor_gate(a,b)));
    // res =bit1  bit0
    // bit1=cary  ,  bit0 = suma
    
    res = 2 * cary + suma ;
    return res;
}


uint64_t ripple_carry_adder(uint64_t a, uint64_t b)
{
    uint64_t res = -1;

    /* TODO
     * Use the full_adder to implement the ripple carry adder
     * If there is ANY overflow while adding "a" and "b" then the
     * result should be 0
     */
    int c=0 ,bit=0 ,putere2=1;
    res=0;
    while( a!=0 || b!=0 )
    {
        uint8_t aux= full_adder(c , a%2 , b%2);
        a=(a>>1);  
        b=(b>>1);
        res = (aux%2)*putere2 + res;
        bit++;
        putere2=(putere2<<1);
        c = (aux/2) %2;
    }
    if(c!=0)
    {
       if (bit<64)
          res=c*putere2 + res;
        else
          res=0;
    }     
    return res;
}