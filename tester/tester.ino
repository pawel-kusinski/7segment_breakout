/*====================================================================================================================*\
 * MIT License
 *
 * Copyright (c) 2023 Pawel Kusinski
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
\*====================================================================================================================*/

/* Test code for a BCD to 7-Segment Breakout Board.
 * It displays a sequence of digits. Each digit changes every 1000 ms.
 * The last display is blank. The Decimal Point is lit up every second digit.
 * BI, RBI, and LT should be pulled up.
 *
 *  _         _    _         _         _    _    _                   _         B
 * | |    |   _|   _|  |_|  |_   |_     |  |_|  |_|   _    _   |_|  |_   |_   L A
 * |_|    |  |_    _|    |   _|  |_|    |  |_|    |  |_    _|        _   |_   N K
 * 
 * Pins connections.
 * From LSB to MSB. The first array element is board input A, and the last one is board input D.
 */
const int bcd_pins[] = {2, 3, 4, 5};
const int dp_pin = 6;

void setup() {
    /* Set BCD pins and DP pin as OUTPUT */
    for (int i = 0; i < 4; i++) {
        pinMode(bcd_pins[i], OUTPUT);
    }

    pinMode(dp_pin, OUTPUT);
}

void loop() {
    for (int i = 0; i <= 15; i++) {
        displayBCD(i);
        delay(1000);
    }
}

void displayBCD(int number) {
    /* Convert the decimal number to a binary array that can be applied to A, B, C, and D inputs */
    int bcd[4];

    for (int i = 0; i < 4; i++) {
        bcd[i] = (number >> i) & 1;
    }

    /* Set BCD input pins based on the binary array */
    for (int i = 0; i < 4; i++) {
        digitalWrite(bcd_pins[i], bcd[i]);
    }

    /* Turn on the DP for even numbers */
    digitalWrite(dp_pin, (number % 2 == 0) ? HIGH : LOW);
}
