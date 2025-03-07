# Embedded in Embedded Development

## Compiling reference

To compile the project

1. Open a new terminal
2. Run `./waf configure --board=<hardware>` replacing `<hardware>` with either `ASCII` or `DOT_MATRIX` depending on the board you have. This step should only need to be run once if successful.
3. Run `./waf build` to build or `./waf build -F` to build and flash the device.

## Communications Syncing Protocol
- Note information is transmitted to each device sequentially, ie. the first slave device receieves a message of what note it should be playing, then the second device receives its notes
- Assume that radio transmission is instantaneous, and buzzer start up is as well.

## Communications Note Encoding
*Each message contains 8 bytes*
| \[63:60\]     | \[59:40] | \[39:20\] | \[19:0\] |
| :-----------: | :------: | :-------: | :------: |
| Instrument ID | Note 3   | Note 2    | Note 1   |

### Intrument ID:
- Instrument ID is a 4 bit value describing what slave device is being addressed
- Intrument ID 0x00 is a universal ID and all instruments will respond to it

### Each note Packet

| \[19:18\] | \[17:16\]   | \[15:7\]      | \[6:0\]    |
| :-------: | :---------: | :-----------: | :--------: |
| Note ID   | Note Accent | Note Duration | MIDI Pitch |

### Note Duration:
| \[15:11\]    | \[9]        | \[8:7\]     |
| :----------: | :---------: | :---------: |
| Value x 10ms | Value x 5ms | Value x 1ms |


**Possible Alternative Bit arrangement:**

| B_7           | B_6                | B_5/B_4         | B_3 \[15:12\] | B_3 \[11:0\]/B_2   | B_1/B_0    |
| :-----------: | :-----------------:| :-------------: | :-----------: | :----------------: | :--------: |
| Instrument ID | Next Note Duration | Next Note Pitch | Note Accent   | 12b Note Durration | Note Pitch |

| B_7             | B_6               | B_5/B_4          | B_3             | B_2               | B_1/B_0          |
| :-------------: | :---------------: | :--------------: | :-------------: | :---------------: | :--------------: |
| Instrument 1 ID | Inst1 Note Timbre | Inst1 Note Pitch | Instrument 2 ID | Inst2 Note Timbre | Inst2 Note Pitch |
