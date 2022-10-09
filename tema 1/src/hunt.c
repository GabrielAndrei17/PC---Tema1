#include "hunt.h"
#include <stdio.h>

/* Task 1 - Axii */

uint16_t find_spell(uint64_t memory)
{
    /* TODO */
    /*
     * The spell is 16 bits and they are in the memory exactly after 5
     * consecutive bits of 1:
     *
     *            high                                             low
     *                [][][x]...[x][x][x][1][1][1][1][1][]...[][][]
     *                    |----16bits---|
     *                          Spell
     *
     * There is only 1 group of 5 consecutive bits of 1 and the other groups
     * have less than consecutive bits of 1
     * Steps:
     * - find 5 consecutive bits of 1
     * - the NEXT 16 bits == spell
     */
    uint16_t res = 0 ,p2=1;
    uint8_t cnt = 0;
    while(cnt !=5)
    {
        if(memory%2==1)
          cnt++;
        else
          cnt=0;
        memory= (memory>>1);
    }
    for(uint8_t i=1;i<=16;i++)
    {
        res = (memory%2==1)*p2 + res;
        p2*=2;
        memory=(memory>>1);
    }

    return res;
}


uint16_t find_key(uint64_t memory)
{
    /*
     * The key is 16 bits and they are in the memory exactly before 3
     * consecutive bits of 1:
     *
     *                high                                           low
     *                     [][][][1][1][1][x][x]...[x][x][]...[][][]
     *                                    |----16bits---|
     *                                           Key
     * Steps:
     * - find 3 consecutive bits of 1
     * - the PREVIOUS 16 bits == key
     */
    uint64_t p2=1,memoryCPY = memory;
    uint8_t cnt=0, poz=0;
    uint16_t res = 0;

    /* TODO */
    while(cnt !=3)
    {
        if(memoryCPY%2==1)
          cnt++;
        else
          cnt=0;
        memoryCPY= (memoryCPY>>1);
        poz++;
    }
    memory=(memory>>(poz-16-3));

    for(uint8_t i=1;i<=16;i++)
    {
        res = (memory%2==1)*p2 + res;
        p2*=2;
        memory=(memory>>1);
    }
    return res;
}


uint16_t decrypt_spell(uint16_t spell, uint16_t key)
{
    /*
     * Find the spell knowing that
     * spell_encrypted = spell_plaintext ^ key
     */

    uint16_t res = -1;

    /* TODO */
    res = spell ^ key;

    return res;
}


/* Task 2 - Sword Play */

uint32_t choose_sword(uint16_t enemy)
{
    /*
     * Help Geralt construct a sword that will give him an advantage in battle.
     * The steps we will follow:
     * - choose the corect sword
     * - brand the sword with the correct runes such that the equation
     * for that specific enemy type is true
     *
     * How does the sword look (Sword template):
     *  [][][][] [0][0][0]...[0][0][0] [][][][][][][][][][][][][][][][]
     *  -------- --------------------- --------------------------------
     *     Type    Does not matter      The "Value" such that the equation
     *                               from 2 holds depending on the enemy type
     *    4 bits      12 bits                     16 bits
     *
     * 1. Type of the sword:
     * - 1001 - Silver Sword - for monsters
     * - 0110 - Steel Sword - for humans
     *
     *  If the number of active bits from variable "enemy" is even == Monster
     *  else == Human
     *
     * 2.
     * Monster Equation:
     *    Value ^ (Enemy & (1 - Enemy)) = 0
     *
     * Human Equation:
     *    Value + Enemy = 0
     */

    uint32_t res = -1;

    /* TODO */
    uint32_t mask;
    uint8_t number = 0;
    
    mask = enemy;
    while(enemy!=0)
    {
        if(enemy%2==1)
           number++;
        enemy=(enemy>>1);   
    }
    enemy = mask;
    if(number%2==0)
    {
       mask = (9<<28);
       res = enemy&(1-enemy);
       res+=mask;
    }
    else
    {
       mask = (6<<28);
       res = -enemy;
       res+=mask + (1<<16);
       
    }
    return res;
}


/* Task 3 - The Witcher Trials */

uint32_t trial_of_the_grasses(uint16_t cocktail)
{
    /*
     * To become a witcher one must survive a cocktail of different
     * herbs. The body should generate the correct antibodies to
     * neutralize the given cocktail.
     *
     *
     * The antibodies need to respect the following properties:
     *   (antibodies_high & cocktail) ^ (antibodies_low | cocktail) = 0
     *   antibodies_low & antibodies_high = 0
     *   antibodies_low | antibodies_high = cocktail
     *
     * Where:
     *  [][][]...[][][] | [][][]...[][][]
     *  ---------------   ---------------
     *  antibodies_high    antibodies_low
     *      16 bits           16 bits
     *      -------------------------
     *              antibodies
     */

    uint32_t res = (cocktail<<16);

    /* TODO */

    return res;
}


uint8_t trial_of_forrest_eyes(uint64_t map)
{
    /*
     * For the next trail, the candidate is tied up and blindfolded.
     * They are also taken to a forest and they should return until
     * the next morning.
     *
     * The candidate knows that there are 4 possibilities for the forest:
     * Brokilon, Hindar, Wolven Glade and Caed Dhu.
     *
     * The candidate also knows those forests by heart, but first you
     * need to identify the forest.
     *
     * The characteristics for 3 of the forests are as follows:
     * - Brokilon - has ONLY groups of 4 trees (or a forest without any tree)
     *   Ex: a group of 4 trees: "...00111100..."
     * - Hindar - has ONLY 2 trees in the MIDDLE
     * - Wolven Glade - FULL of trees
     *
     * The "map" variable encodes the following information:
     * - 1 tree
     * - 0 patch of grass
     *
     * You should put in the "res" variable the index for the identified
     * forrest.
     * - Brokilon - index 0
     * - Hindar - index 1
     * - Wolven Glade - index 2
     * - Caed Dhu - index 3
     */

    /* TODO */
    if( map== 0)
        return 0;
    if(map == (~0))
        return 2;
    if(map ==(3L<<31))
        return 1;

    uint8_t ok = 1, cnt1= 0;
    while(ok == 1 && map!=0)
    {
        if(map%2==1)
        {
            cnt1++;
            if(cnt1>4)
               ok=0;
        }
        else
        {
            if(cnt1!=4 && cnt1!=0)
               ok=0;
            cnt1=0;
        }
        map/=2;
    }
    if(ok == 1)
       return 0;
    else
       return 3;
    
}


uint8_t trial_of_the_dreams(uint32_t map)
{
    /*
     * For this final trial, the candidates go into a trance and when
     * they woke up they would be a fully fledged witcher.
     *
     * For this task, you need to help the witcher find the number
     * of steps that would take the candidate from the dream realm to
     * the real world.
     *
     * The "map" variable would have only 2 bits of 1:
     * - candidate location
     * - portal location
     *
     * You should put in the "res" variable the distance from the
     * candidate position to the portal.
     *
     *  Ex:
     *  [0][0][0][0][0][0]....[1][0][0][0][0][1][0]....[0][0][0]
     *
     *  res = 5
     */

    uint8_t res = -1;

    /* TODO */
    uint8_t cnt=0;
    while(map!=0)
    {
        if(map%2==1)
        {
          if(cnt == 0)
            cnt++;
          else
            map/=2; 
        }
        else
            if(cnt!=0)
              cnt++;
        map/=2;   
    }
    res = cnt;

    return res;
}
