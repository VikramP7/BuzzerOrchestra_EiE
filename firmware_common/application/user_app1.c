/*!*********************************************************************************************************************
@file user_app1.c
@brief User's tasks / applications are written here.  This description
should be replaced by something specific to the task.

----------------------------------------------------------------------------------------------------------------------
To start a new task using this user_app1 as a template:
 1. Copy both user_app1.c and user_app1.h to the Application directory
 2. Rename the files yournewtaskname.c and yournewtaskname.h
 3. Add yournewtaskname.c and yournewtaskname.h to the Application Include and Source groups in the IAR project
 4. Use ctrl-h (make sure "Match Case" is checked) to find and replace all instances of "user_app1" with "yournewtaskname"
 5. Use ctrl-h to find and replace all instances of "UserApp1" with "YourNewTaskName"
 6. Use ctrl-h to find and replace all instances of "USER_APP1" with "YOUR_NEW_TASK_NAME"
 7. Add a call to YourNewTaskNameInitialize() in the init section of main
 8. Add a call to YourNewTaskNameRunActiveState() in the Super Loop section of main
 9. Update yournewtaskname.h per the instructions at the top of yournewtaskname.h
10. Delete this text (between the dashed lines) and update the Description below to describe your task
----------------------------------------------------------------------------------------------------------------------

------------------------------------------------------------------------------------------------------------------------
GLOBALS
- NONE

CONSTANTS
- NONE

TYPES
- NONE

PUBLIC FUNCTIONS
- NONE

PROTECTED FUNCTIONS
- void UserApp1Initialize(void)
- void UserApp1RunActiveState(void)


**********************************************************************************************************************/

#include "configuration.h"

/***********************************************************************************************************************
Global variable definitions with scope across entire project.
All Global variable names shall start with "G_<type>UserApp1"
***********************************************************************************************************************/
/* New variables */
volatile u32 G_u32UserApp1Flags; /*!< @brief Global state flags */

/*MUSIC*/
// MIDI Conversion to frequency
static u16 MIDIFREQ[128] = {0, 9, 9, 10, 10, 11, 12, 12, 13, 14, 15, 15, 16, 17, 18, 19, 21, 22, 23, 24, 26, 28, 29, 31, 33, 35, 37, 39, 41, 44, 46, 49, 52, 55, 58, 62, 65, 69, 73, 78, 82, 87, 92, 98, 104, 110, 117, 123, 131, 139, 147, 156, 165, 175, 185, 196, 208, 220, 233, 247, 262, 277, 294, 311, 330, 349, 370, 392, 415, 440, 466, 494, 523, 554, 587, 622, 659, 698, 740, 784, 831, 880, 932, 988, 1047, 1109, 1175, 1245, 1319, 1397, 1480, 1568, 1661, 1760, 1865, 1976, 2093, 2217, 2349, 2489, 2637, 2794, 2960, 3136, 3322, 3520, 3729, 3951, 4186, 4435, 4699, 4978, 5274, 5588, 5920, 6272, 6645, 7040, 7459, 7902, 8372, 8870, 9397, 9956, 10548, 11175, 11840, 12544};

// Song contains all intruments
static u8 song1[2][42][8] = {
    {{0xA0, 0xB7, 0x00, 0x01, 0x00, 0x00, 0xF4, 0x3C}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x3C}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x45}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x45}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x01, 0xE7, 0x43}, {0xA0, 0xB7, 0x00, 0x19, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x3E}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x3E}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x01, 0xE7, 0x3C}, {0xA0, 0xB7, 0x00, 0x19, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x01, 0xE7, 0x3E}, {0xA0, 0xB7, 0x00, 0x19, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x01, 0xE7, 0x3E}, {0xA0, 0xB7, 0x00, 0x19, 0x00, 0x00, 0xF4, 0x3C}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x3C}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x43}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x45}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x45}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x01, 0xE7, 0x43}, {0xA0, 0xB7, 0x00, 0x19, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x41}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x40}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x3E}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x00, 0xF4, 0x3E}, {0xA0, 0xB7, 0x00, 0x0C, 0x00, 0x01, 0xE7, 0x3C}},
    {{0xA1, 0xB7, 0x00, 0x01, 0x00, 0x01, 0xE7, 0x34}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x39}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x34}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x39}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x39}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x34}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x3C}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x39}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x37}, {0xA1, 0xB7, 0x00, 0x19, 0x00, 0x01, 0xE7, 0x34}}};

static u8 localSongIndex = 0;
static u8 songLengthAu8[2] = {42, 24};
static u8 instrumentCount = 2;

static u8 *songNotePitches;    // dynamically allocated list of note pitches
static u16 *songNoteDurations; // dynamically allocated list of note durrations
static u16 songLength = 0;
static u16 songCapacity = 64;

/*--------------------------------------------------------------------------------------------------------------------*/
/* Existing variables (defined in other files -- should all contain the "extern" keyword) */
extern volatile u32 G_u32SystemTime1ms;    /*!< @brief From main.c */
extern volatile u32 G_u32SystemTime1s;     /*!< @brief From main.c */
extern volatile u32 G_u32SystemFlags;      /*!< @brief From main.c */
extern volatile u32 G_u32ApplicationFlags; /*!< @brief From main.c */

extern u32 G_u32AntApiCurrentMessageTimeStamp;                           // From ant_api.c
extern AntApplicationMessageType G_eAntApiCurrentMessageClass;           // From ant_api.c
extern u8 G_au8AntApiCurrentMessageBytes[ANT_APPLICATION_MESSAGE_BYTES]; // From ant_api.c
extern AntExtendedDataType G_sAntApiCurrentMessageExtData;               // From ant_api.c

extern PixelBlockType G_sLcdClearLine7; /* from lcd-NHD-C12864LZ.c*/

/***********************************************************************************************************************
Global variable definitions with scope limited to this local application.
Variable names shall start with "UserApp1_<type>" and be declared as static.
***********************************************************************************************************************/
static fnCode_type UserApp1_pfStateMachine; /*!< @brief The state machine function pointer */
// static u32 UserApp1_u32Timeout;                           /*!< @brief Timeout counter used across states */

/**********************************************************************************************************************
Function Definitions
**********************************************************************************************************************/
static void UserApp1SM_WaitAntReady();
static void UserApp1SM_ChannelOpen();
static void UserApp1SM_WaitChannelOpen();
static void UserApp1SM_SongPlayBack();

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @publicsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*--------------------------------------------------------------------------------------------------------------------*/
/*! @protectedsection */
/*--------------------------------------------------------------------------------------------------------------------*/

/*!--------------------------------------------------------------------------------------------------------------------
@fn void UserApp1Initialize(void)

@brief
Initializes the State Machine and its variables.

Should only be called once in main init section.

Requires:
- NONE

Promises:
- NONE

*/
void UserApp1Initialize(void)
{
  // temporatily putting conversion of song data for transmission into song data for playback
  // dynamically allocate memory for incoming data

  // store song in more usable format
  songNotePitches = malloc(songCapacity);
  songNoteDurations = malloc(songCapacity * 2);

  for (u16 packetIndex = 0; packetIndex < songLengthAu8[localSongIndex]; packetIndex++)
  {
    if (songLength + 2 > songCapacity)
    {
      // if song length is out of space re-alocate to make bigger by twice as much
      songNotePitches = realloc(songNotePitches, songCapacity * 2);
      songNoteDurations = realloc(songNoteDurations, songCapacity * 2 * 2);
      songCapacity = songCapacity * 2;
    }

    // store song data using two note per packet byte structure
    songNotePitches[songLength] = song1[localSongIndex][packetIndex][4];
    songNoteDurations[songLength] = song1[localSongIndex][packetIndex][3] + song1[localSongIndex][packetIndex][2] * 256;
    songLength++;

    songNotePitches[songLength] = song1[localSongIndex][packetIndex][7];
    songNoteDurations[songLength] = song1[localSongIndex][packetIndex][6] + song1[localSongIndex][packetIndex][5] * 256;
    songLength++;
  }

  // ----------- BUZZER INITIALIZATION ---------------
  PWMAudioSetFrequency(BUZZER1, 0);
  PWMAudioOff(BUZZER1);

  // ----------- ANT INITIALIZATION ------------------
  AntAssignChannelInfoType sChannelInfo;
  if (AntRadioStatusChannel(U8_ANT_CHANNEL_USERAPP) == ANT_UNCONFIGURED)
  {
    sChannelInfo.AntChannel = U8_ANT_CHANNEL_USERAPP;
    sChannelInfo.AntChannelType = CHANNEL_TYPE_MASTER;
    sChannelInfo.AntChannelPeriodHi = U8_ANT_CHANNEL_PERIOD_HI_USERAPP;
    sChannelInfo.AntChannelPeriodLo = U8_ANT_CHANNEL_PERIOD_LO_USERAPP;

    sChannelInfo.AntDeviceIdHi = U8_ANT_DEVICE_ID_HI_USERAPP;
    sChannelInfo.AntDeviceIdLo = U8_ANT_DEVICE_ID_LO_USERAPP;
    sChannelInfo.AntDeviceType = U8_ANT_DEVICE_TYPE_USERAPP;
    sChannelInfo.AntTransmissionType = U8_ANT_TRANSMISSION_TYPE_USERAPP;

    sChannelInfo.AntFrequency = U8_ANT_FREQUENCY_USERAPP;
    sChannelInfo.AntTxPower = U8_ANT_TX_POWER_USERAPP;

    sChannelInfo.AntNetwork = ANT_NETWORK_DEFAULT;
    for (u8 i = 0; i < ANT_NETWORK_NUMBER_BYTES; i++)
    {
      sChannelInfo.AntNetworkKey[i] = ANT_DEFAULT_NETWORK_KEY;
    }
  }

  /* If good initialization, set state to Idle */
  if (AntAssignChannel(&sChannelInfo))
  {
    UserApp1_pfStateMachine = UserApp1SM_WaitAntReady;
  }
  else
  {
    /* The task isn't properly initialized, so shut it down and don't run */
    UserApp1_pfStateMachine = UserApp1SM_Error;
  }

} /* end UserApp1Initialize() */

/*!----------------------------------------------------------------------------------------------------------------------
@fn void UserApp1RunActiveState(void)

@brief Selects and runs one iteration of the current state in the state machine.

All state machines have a TOTAL of 1ms to execute, so on average n state machines
may take 1ms / n to execute.

Requires:
- State machine function pointer points at current state

Promises:
- Calls the function to pointed by the state machine function pointer

*/
void UserApp1RunActiveState(void)
{
  UserApp1_pfStateMachine();

} /* end UserApp1RunActiveState */

/*------------------------------------------------------------------------------------------------------------------*/
/*! @privatesection */
/*--------------------------------------------------------------------------------------------------------------------*/

/**********************************************************************************************************************
State Machine Function Definitions
**********************************************************************************************************************/
/*-------------------------------------------------------------------------------------------------------------------*/
static void UserApp1SM_WaitAntReady(void)
{
  if (AntRadioStatusChannel(U8_ANT_CHANNEL_USERAPP) == ANT_CONFIGURED)
  {
    if (AntOpenChannelNumber(U8_ANT_CHANNEL_USERAPP))
    {
      UserApp1_pfStateMachine = UserApp1SM_WaitChannelOpen;
    }
    else
    {
      UserApp1_pfStateMachine = UserApp1SM_Error;
    }
  }
} /* end UserApp1SM_WaitAntReady() */

static void UserApp1SM_WaitChannelOpen()
{
  if (AntRadioStatusChannel(U8_ANT_CHANNEL_USERAPP) == ANT_OPEN)
  {
    UserApp1_pfStateMachine = UserApp1SM_ChannelOpen;
  }
} /* end UserApp1SM_WaitChannelOpen() */

static void UserApp1SM_ChannelOpen()
{
  static u16 u16CurrentTimeMS = 0;

  static u8 doneTransmission = 0;

  static u8 currentIntrumentIndex = 1;
  static u8 currentInstrumentPacket = 0;

  static u8 currentLocalIntrumentIndex = 1;
  static u8 currentLocalPacketIndex = 0;
  static u8 currentLocalByteIndex = 0xFF;

  static u8 au8NotesMessage[] = {0, 0, 0, 0, 0xA5, 0, 0, 0};

  if (AntReadAppMessageBuffer())
  {
    if (G_eAntApiCurrentMessageClass == ANT_DATA)
    {
      // we have data from slaves
    }
    else if (G_eAntApiCurrentMessageClass == ANT_TICK)
    {
      // Channel period has occured time to send new data
      if (G_au8AntApiCurrentMessageBytes[ANT_TICK_MSG_EVENT_CODE_INDEX] == EVENT_TRANSFER_TX_COMPLETED)
      {
        // message ack good for next message
        if (currentIntrumentIndex < instrumentCount)
        {
          // still have instruments that need data
          currentInstrumentPacket++;
          if (currentInstrumentPacket >= songLengthAu8[currentIntrumentIndex])
          {
            currentIntrumentIndex++;
            currentInstrumentPacket = 0; // reset
            doneTransmission = currentIntrumentIndex >= instrumentCount ? 1 : 0;
          }
        }
      }
      else if (G_au8AntApiCurrentMessageBytes[ANT_TICK_MSG_EVENT_CODE_INDEX] == EVENT_TRANSFER_TX_FAILED)
      {
        // message send failed resend last message
        // Leave instrument and current packet indexes the same
      }

      // if we are done sending the song data send start of time message to all boards
      if (doneTransmission > 0)
      {
        // do local sequence
        LedOn(RED3);
        static u8 startTime = 0;
        static u8 au8StartMessage[8] = {0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff};
        if (startTime < 1)
        {
          AntQueueBroadcastMessage(U8_ANT_CHANNEL_USERAPP, au8StartMessage);
          startTime++;
        }
        else
        {
          PWMAudioOn(BUZZER1);
          UserApp1_pfStateMachine = UserApp1SM_SongPlayBack;
        }
      }
      else
      {
        // we are not done sending all the song data keep beaming
        for (u8 i = 0; i < 8; i++)
        {
          // loop through 8bytes of current packet to populate next outgoing message
          au8NotesMessage[i] = song1[currentIntrumentIndex][currentInstrumentPacket][i];
        }
        AntQueueAcknowledgedMessage(U8_ANT_CHANNEL_USERAPP, au8NotesMessage);
      }
    } /* end ant tick message*/
  } /* end AntReadAppMessageBuffer()*/
  u16CurrentTimeMS++;
} /* end UserApp1SM_ChannelOpen() */

static void UserApp1SM_SongPlayBack()
{
  static u16 u16CurrentTimeMS = 0;
  static u8 currentNoteIndex = 0;

  // checking to see if we are done the current note
  if (u16CurrentTimeMS >= songNoteDurations[currentNoteIndex])
  {
    // we are done the "current note"
    PWMAudioSetFrequency(BUZZER1, MIDIFREQ[songNotePitches[currentNoteIndex + 1]]);
    currentNoteIndex++;
    u16CurrentTimeMS = 0;
  }
  if (currentNoteIndex >= songLength)
  {
    PWMAudioOff(BUZZER1);
    UserApp1_pfStateMachine = UserApp1SM_ChannelOpen;
  }
  u16CurrentTimeMS++;
}

/*-------------------------------------------------------------------------------------------------------------------*/
/* Handle an error */
static void UserApp1SM_Error(void)
{
  LedOn(RED0);
} /* end UserApp1SM_Error() */

/*--------------------------------------------------------------------------------------------------------------------*/
/* End of File                                                                                                        */
/*--------------------------------------------------------------------------------------------------------------------*/
