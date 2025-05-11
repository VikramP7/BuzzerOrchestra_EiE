import mido
import math

path = "Tetris.mid"

def ToHex(value):
    out = ""
    value = int(value)
    while(value > 0):
        if value %16 >= 10:
            out = chr((value%16)+55)+out
        else:
            out = str(value%16)+out
        value = int(value/16)
    out = "0"*max(0,2-len(out)) + out
    return out


def MidiConvert(path):
    mid = mido.MidiFile(path, clip=True)
    print(mid)
    useconds_per_beat = 0
    song_name = "Unknown"
    tempo_bpm = -1
    ms_per_tick = -1
    ticks_per_beat = mid.ticks_per_beat

    # Parse header trunk
    for msg in mid.tracks[0]:
        if msg.is_meta:
            print(msg)
            if msg.type == 'set_tempo':
                useconds_per_beat = msg.tempo
            elif msg.type == 'track_name':
                song_name = msg.name

    # https://www.recordingblogs.com/wiki/time-division-of-a-midi-file
    # 1tick = microsecondsPerBeat/ticksPerBeat in microseconds
    ms_per_tick = (useconds_per_beat/ticks_per_beat)*1000 

    # set up song structure
    active_melody = [] # describes what note is active on each song track
    song_tracks = [] # list of list of tuples containing (note, durration)
    max_tracks = 3
    for i in range(max_tracks):
        song_tracks.append([])
        active_melody.append(0)

    # parse music (track) trunk
    current_time = 0
    for track in mid.tracks:#[1:]:
        for msg in track:
            current_time += msg.time
            if msg.type == 'note_on':
                # find an avalible channel
                current_melody = -1
                for melody in range(len(active_melody)):
                    if active_melody[melody] == 0 and current_melody == -1:
                        current_melody = melody
                if current_melody != -1:
                    song_tracks[current_melody].append((active_melody[current_melody], current_time))
                    active_melody[current_melody] = msg.note
            if msg.type == 'note_off' or (msg.type == 'note_on' and msg.velocity ==0):
                # find the channel that started the note
                # find an avalible channel
                current_melody = -1
                for melody in range(len(active_melody)):
                    if active_melody[melody] == msg.note:
                        current_melody = melody
                if current_melody != -1:
                    song_tracks[current_melody].append((active_melody[current_melody], current_time))
                active_melody[current_melody] = 0

    # using differences in time-stamps find note durations
    for track in range(max_tracks):
        #song_tracks[track] = song_tracks[track][1:]
        note = len(song_tracks[track])-1
        while note > 0:
            song_tracks[track][note] = (song_tracks[track][note][0], song_tracks[track][note][1] - song_tracks[track][note-1][1])
            note -= 1

    print(song_tracks)
    
    for track in range(max_tracks):
        number_of_packets = math.ceil(len(song_tracks[track])/2.0)
        print("static u8 song"+str(track)+"["+str(number_of_packets)+"][8] = {",end='')
        note = 0
        note_byte = 0
        while note < len(song_tracks[track]):
            if(note_byte == 0):
                # instrument ID takes form of hex A#, and B7 is project ID
                print("{0xA" + str(track) + ", ", end='') # start byte
                print("0xB7, ", end="")
            duration = song_tracks[track][note][1]
            duration_top_hex = ToHex(int(duration/256))
            duration_bottom_hex = ToHex(int(duration%256))
            tone  = song_tracks[track][note][0]
            tone_hex = ToHex(tone)
            # print out two byte note durration
            print("0x"+duration_top_hex+", 0x" + duration_bottom_hex + ", ", end="")
            print("0x"+tone_hex, end="")
            note_byte += 1
            if note_byte == 1:
                # only one note has been entered into 8-byte message
                print(", ", end="")
            elif note_byte == 2:
                # second note in the 8-byte message end the current message
                print("},", end="")
                note_byte = 0
            note += 1
        # end the current track variable
        print("}")
    
        
            

            


                

            
        
        


if __name__ == "__main__":
    MidiConvert(path)