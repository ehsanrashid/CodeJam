/*
00462 - Bridge Hand Evaluator

In the card game "Bridge", players must assess the strength of their hands prior to bidding against one another. Most players use a point-count scheme which employs the following rules:

Each ace counts 4 points. Each king counts 3 points. Each queen counts 2 points. Each jack counts one point.
Subtract a point for any king of a suit in which the hand holds no other cards.
Subtract a point for any queen in a suit in which the hand holds only zero or one other cards.
Subtract a point for any jack in a suit in which the hand holds only zero, one, or two other cards.
Add a point for each suit in which the hand contains exactly two cards.
Add two points for each suit in which the hand contains exactly one card.
Add two points for each suit in which the hand contains no cards.
A suit is stopped if it contains an ace, or if it contains a king and at least one other card, or if it contains a queen and at least two other cards.

During the opening assessment, the three most common possibilities are:

If the hand evaluates to fewer than 14 points, then the player must pass.
One may open bidding in a suit if the hand evaluates to 14 or more points. Bidding is always opened in one of the suits with the most cards.
One may open bidding in ``no trump'' if the hand evaluates to 16 or more points ignoring rules 5, 6, and 7 and if all four suits are stopped. A no trump bid is always preferred over a suit bid when both are possible.
*/

#include <stdio.h>
#include <string.h>

const char *suits = "SHDC";

int getSuit(char c)
{ 
    for (int i = 0; i < 4; ++i) 
        if (suits[i] == c) 
            return i; 
}

char line[1024];

void main()
{
    while (fgets(line, 1024, stdin))
    {
        int score = 0, stopped = 0;
        int sc[4] = {0, 0, 0, 0};
        int ace[4] = {0, 0, 0, 0};
        int jack[4] = {0, 0, 0, 0};
        int king[4] = {0, 0, 0, 0};
        int queen[4] = {0, 0, 0, 0};

        for (char *p = strtok(line, " "); p != NULL; p = strtok(NULL, " "))
        {
            /* Rule 1 */
                 if (p[0] == 'A') score += 4;
            else if (p[0] == 'K') score += 3;
            else if (p[0] == 'Q') score += 2;
            else if (p[0] == 'J') score += 1;
            
            int s = getSuit(p[1]);
            sc[s]++; 
            ace[s] += (p[0] == 'A');
            king[s]+= (p[0] == 'K');
            queen[s] += (p[0] == 'Q');
            jack[s] += (p[0] == 'J');
        }
        for (int i = 0; i < 4; ++i)
        {
            /* Rules 2, 3, 4 */
            if (king[i] && sc[i] < 2) --score;
            if (queen[i] && sc[i] < 3) --score;
            if (jack[i] && sc[i] < 4) --score;
            if (ace[i] || (king[i] && sc[i] >= 2) || (queen[i] && sc[i] >= 3) || (jack[i] && sc[i] >= 4)) 
                stopped++;
        }

        if (score >= 16 && stopped == 4)
        { // Bid no trump
            puts("BID NO-TRUMP");
        } 
        else 
        {
            int max_sc = 0, play;
            for (int i = 0; i < 4; ++i)
            {
                if (sc[i] == 2) score++; // Rule 5
                if (sc[i] < 2) score += 2; // Rules 6 and 7
                if (sc[i] > max_sc)
                {
                    max_sc = sc[i];
                    play = i;
                }
            }
            if (score < 14)
            { 
                puts("PASS");
            }
            else
            { 
                printf("BID %c\n", suits[play]);
            }
        }
    }
}
