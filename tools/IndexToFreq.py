print("static u16 MIDIFREQ[128] = {", end='')
for i in range(0,128):
    print(round(440*(2**((i-69)/12))),end='')
    print(", ", end='')
print("};")

while 1:
    try:
        n = int(input("Val: "))
        print(round(440*(2**((i-69)/12))))
    except:
        pass