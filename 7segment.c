// Copyright (c) 2012 John Norrbin

#include <wiringPi.h>
#include <stdio.h>

// 7Segment Number
void sevenSegmentNumber(int num)
{
    /*
        Pin Layout - wrPi (BCM)
        -----------------------

                       A: 0 (17)
                     -----
         (21) 2 :F /      / B: 7 (4)
                    ----- G: 3 (22)
        (25) 6 :E /      / C: 4 (23)
                   -----
                     D: 5 (24)
    */
    #define A 0
    #define B 7
    #define C 4
    #define D 5
    #define E 6
    #define F 2
    #define G 3

    // Numbers To 7Seg (On: 0, Off: 1)
    int numbers[10][7] =
    {
        // A, B, C, D, E, F, G
         { 1, 1, 1, 1, 1, 1, 0 }, // 0
         { 0, 1, 1, 0, 0, 0, 0 }, // 1
         { 1, 1, 0, 1, 1, 0, 1 }, // 2
         { 1, 1, 1, 1, 0, 0, 1 }, // 3
         { 0, 1, 1, 0, 0, 1, 1 }, // 4
         { 1, 0, 1, 1, 0, 1, 1 }, // 5
         { 1, 0, 1, 1, 1, 1, 1 }, // 6
         { 1, 1, 1, 0, 0, 0, 0 }, // 7
         { 1, 1, 1, 1, 1, 1, 1 }, // 8
         { 1, 1, 1, 1, 0, 1, 1 }  // 9
    };

    // Setup Pins
    pinMode(A, OUTPUT);
    pinMode(B, OUTPUT);
    pinMode(C, OUTPUT);
    pinMode(D, OUTPUT);
    pinMode(E, OUTPUT);
    pinMode(F, OUTPUT);
    pinMode(G, OUTPUT);

    // Write Segments
    digitalWrite(A, !numbers[num][0]);
    digitalWrite(B, !numbers[num][1]);
    digitalWrite(C, !numbers[num][2]);
    digitalWrite(D, !numbers[num][3]);
    digitalWrite(E, !numbers[num][4]);
    digitalWrite(F, !numbers[num][5]);
    digitalWrite(G, !numbers[num][6]);
}

// 7 Segment Decimal Point
void sevenSegmentDecimal(int state)
{
    /*
        Pin Layout - wrPi (BCM)
        -----------------------
        ¦  DP: 1 (18)
    */
    #define DP 1

    // Setup Pins
    pinMode(DP, OUTPUT);

    // Write Segments
    digitalWrite(DP, !state);
}

// Main
int main(void)
{
    // Initialize WiringPi
    if (wiringPiSetup() == -1)
    {
        return 1;
    }

    // Variables
    char c;
    int i;

    // Handle Newline And Crtl-C In Program
    system ("/bin/stty raw");

    // Infinite Loop
    while(1)
    {
        // Get Char
        c = getchar();

        // Exit
        if ((c == '\r') || (c == '\n') || (c == '\x03'))
        {
            break;
        }

        // Display Number On 7Segment
        i = (c - '0');
        if (i >= 0 && i < 10)
        {
            sevenSegmentNumber(i);
        }

        // Set Decimal
        if (c == '.')
        {
            sevenSegmentDecimal(1);
        }
        else if (c == ',')
        {
            sevenSegmentDecimal(0);
        }
    }

    // Reset Terminal
    system ("/bin/stty cooked");

    // Exit
    return 0;
}
