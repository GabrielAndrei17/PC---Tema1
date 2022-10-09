///ANDREI GABRIEL
//313CB

                                          A trip throughout TV Series?

/////////////////////////////////////////Part 1(gates.c)
////////Task 1 :
flip_bit - Ne folosim de functia get_bit pentru a afla ce valoare are bitul i si dupa caz 
il schimbam fie in 1 fie in 0

activate_bit - Asemanator cu flip_bit , dar bitul i il schimb mereu in 1 (construiesc un mask cu bitul i 1
si aplica operatorul | )

clear_bit -  Asemanator cu flip_bit , dar bitul i il schimb mereu in 0

///////Task 2:
Functiile sunt scrise conform schemelor circuitelor logice

///////Task 3:
full_adder - suma am aflat-o prin formula c^(a^b) , iar cary (a&b) | (c&(a^b)) si am codificat rezultatul
res = {cary suma} in binar

ripple_carry_adder - am adunat bitii lui a si b pana cand unul dintre a sau b a devenit 0(prin eliminarea bitilor)
am pastrat intr-un auxiliar suma bitilor (de pe ultima pozitie)cu functia full_addet ,apoi i-am decodificat,
suma adaugand-o la rezultat si caryul pastrandu-l pentru a fi adaugat la urmatorii biti
Daca a ramas un cary si am parcurs 64 de biti s-a facut overflow
 
//////////////////////////////////////Part 2(communication.c)
////////Task 1 :
send_byte_message - M-am folosit de codurile ASCII pentru a codifica mai usor caracterul

////////Task 2 :
send_message - am obtinut lungimea codificata prin shiftarea lungimii cu 2 pozutii la stanga

recv_message - am obtinut lungimea prin shiftarea la drapta cu 2 poz si luand din numar primii 4 biti

comm_message - am obtinut lungimea, am retinut ultimul caracter primit din mesaj si am transmis mesaj coraspunzator 
acestuia

//////////Task 3:
send_squanch2 - pe pozitiile impare ale caracterului se afla bitii de la c2 iar pe pozitiile pare, bitii lui c1 astfel 
se construieste caracterul

decode_squach2 - este operatia inversa ca cea de la functia anterioara, se construieste c1 si c2 din caracter si la final 
se concateneaza => mesajul

/////////////////////////////////////Part 3 (hunt.h)
///////////Task 1:
find_spell - se contorizeaza unde se termina ultima grupare de 4 biti consecutivi de 1, apoi se construieste numarul cu primii
16 biti

find_key - exact ca la find_apell am determinat unde se termina grupa de 3 biti si i-au ultimii 16 + 3 biti pentru formarea numarului

decrypt_spell - 
a = b ^ c | ^c
a^c = b^c^c => b=a^c, b-spell, a= encrypted spell, c= key

///////////Task 2:
choose_sword - Ecuatia monster se bazeaza pe observatia ca x^y=0 <=> x=y. Primul pas este aflarea numarului de biti activi a lui enemy
si dupa caz(par sau impar) se rezolva o ecuatie monster/human, iar la final se adauga tipul sabiei (0110 / 1001) construit cu ajutorul mask

//////////Task 3:
trial_of_the_grasses - se observa ca antibodys-low = 0 si antibodys-high = cocktail

trial_of_forrest_eyes - se trateaza cazurile particulare separat(map = 0 , map este farmta din biti de 1 , map are in mijloc 2 biti de 1)
astfel mai avem de tratat daca are index 3 sau 0 (prin tratarea fiecarui bit)(se intelege din cod).

trial_of_the_dreams -Se trateaza fiecare bit. Variabila cnt incepe sa numere bitii de 0 de la intalnirea primului 1 pana la ultimul
