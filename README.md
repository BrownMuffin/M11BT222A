
# M11BT222A
Arduino library for the Futaba M11BT222A display

![M11BT222A Display](https://repository-images.githubusercontent.com/326003214/beaef400-4c55-11eb-85aa-29c629da7963)

## Introduction
The [Futaba](http://www.futaba.co.jp/en/display/vfd/) M11BT222A is a [Vacuum Fluorescent Display (VFD)](https://en.wikipedia.org/wiki/Vacuum_fluorescent_display). The display is based around the Princeton Technology Corp. [PT6311](http://www.princeton.com.tw/Portals/0/Product/PT6311_10.pdf) VFD driver IC.

##  Table of contents

 - Introduction
 - [Connections](/#Connections)
 - [Digits](/#Digits)
	 - Usage
	 - Explained
- [PT6311](/#PT6311)
  - Display mode settings commands
  - Data setting commands
  - Address setting commands
  - Display control commands

## Connections
The display has a 8 pin PH 2.0mm connector, this is the pinout: 

1. +5V
2. GND
3. N/C
4. Enable (High = On)
5. Data In
6. GND
7. Serial Clock (Inversed)
8. Serial Strobe (Inversed)

## Digits
The M11BT222A has 6 7-segment displays with colons between every pair of digits. 

### Usage
Below are the different functions for controlling the digits

**showNumbers**
This function takes 6 numbers and 2 booleans. The digits and the colons are from left to right. The number can be used to show every hexadecimal value. The colons will be turned on with a  `true` and off with a `false`.

`void showNumbers(unsigned char val0, unsigned char val1, unsigned char val2, unsigned char val3, unsigned char val4, unsigned char val5, bool colon1, bool colon2);`

---
**showNumbers**
This function is similar to the on above, it only does not do anything with the colons. 

`void showNumbers(unsigned char val0, unsigned char val1, unsigned char val2, unsigned char val3, unsigned char val4, unsigned char val5);`

---
**showNumber**
This function takes one segment position and one number. The segment ranges from 0 to 5, with 0 being the left most digit. The number can be used to show every hexadecimal value.

`void showNumber(unsigned char seg, unsigned char val);`

---
**hideNumber**
This function turns a digit completely off. The segment ranges from 0 to 5, with 0 being the left most digit. 

`void hideNumber(unsigned char seg);`

---
**showNumberCusom**
This function takes one segment position and data for the digit. The segment ranges from 0 to 5, with 0 being the left most digit. The data is one byte long and can be used for turning one individual digit segments. Look in the explained segment below for more information.

`void showNumberCustom(unsigned char seg, unsigned char data);`

---
**showColon**
This function can turn on or off a single colon dot. The index ranges from 0 to 3 and the order is from top to bottom and from left to right. A `true` will turn on the colon dot and a `false` will turn it off.

`void showColon(int8_t index, bool visible);`

---
### Explained
The addresses of these displays are from left to right: `0x0F` `0x15` `0x16` `0x12` `0x13` `0x10`. The colons are in the digits around the colon and are in the MSB position.

The order of digit segments are:
| | 0 | 0 | 0 | 0 | |
|--|--|--|--|--|--|
| 2 |  |  |  |  | 1
| 2 |  |  |  |  | 1
| 2 |  |  |  |  | 1
| | 3 | 3 | 3 | 3 | 
| 5 |  |  |  |  | 4
| 5 |  |  |  |  | 4
| 5 |  |  |  |  | 4
| | 6 | 6 | 6 | 6 |

The digit character set is:
Digit | Binary | Hexadecimal
|--|--|--|
0 | `0111 0111` |  `0x77`
1 | `0001 0010` |  `0x12`
2 | `0110 1011` |  `0x6B`
3 | `0101 1011` |  `0x5B`
4 | `0001 1110` |  `0x1E`
5 | `0101 1101` |  `0x5D`
6 | `0111 1101` |  `0x7D`
7 | `0001 0011` |  `0x13`
8 | `0111 1111` |  `0x7F`
9 | `0101 1111` |  `0x5F`
A | `0011 1111` |  `0x3F`
B | `0111 1100` |  `0x7C`
C | `0110 0101` |  `0x65`
D | `0111 1010` |  `0x7A`
E | `0110 1101` |  `0x6D`
F | `0010 1101` |  `0x2D`

## Letters

### Usage

### Explained

## Icons

### Usage

### Explained

## Network 

### Usage

### Explained

## Blocks

### Usage

### Explained

## Dots

### Usage

### Explained

## Spinner

### Usage

### Explained


## PT6311
The PT6311 is a VDF driver IC. To control the display we have to send different commands from the Arduino to the IC. The topics below cover the commands used in this library, for more in depth information about the PT6311 please read the datasheet: http://www.princeton.com.tw/Portals/0/Product/PT6311_10.pdf

### Display mode settings commands
This command is used for setting the matrix size for the display, the PT6311 can handle different matrix sizes from 8 by 20 segments to 16 by 12 segments. For the M11BT222A we need 11 by 17 segments. The command for this is: `00xx 1010`, the value of the 'x' position are not relevant, the command in hexadecimal is: `0x0A`.

---
### Data setting commands
The data setting commands are for getting or setting specific data from the IC. In my library we only use one data setting command, this is used for sending incremental data to the IC. The command for this is: `01xx 0000`, the value of the 'x' position are not relevant, the command in hexadecimal is: `0x40`.

---
### Address setting commands
This is used for setting a RAM address, the address range is from 0 (`0x00`) to 47 (`0x2F`). The command for this is: `11xx xxxx`, the value of the 'x' makes up the desired address. 

---
### Display control commands
The PT6311 uses PWM to increase or decrease the brightness. The brightness ranges from 1 of 16 pulses to 14 of 16 pulses on. This command can also be used to turn of the display completely. The command for this is: `10xx y zzz` value of the 'x' position are not relevant, the value of 'y' is to enable (1) or disable (0) the display and the value of the 'z' position is setting the PWM. The brightness table is:
Code | Value
--|--
000 | 1/16
001 | 2/16
010 | 4/16
011 | 10/16
100 | 11/16
101 | 12/16
110 | 13/16
111 | 14/16
