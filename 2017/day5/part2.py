from sys import stdin

lines = []
for line in stdin:
    if line == "\n":
        break
    lines.append(line.rstrip())

jumps = []
for line in lines:
    jumps.append(int(line))

instructionsLen = len(jumps)
instructionIndex = 0
clock = 0
while(instructionIndex >= 0 and instructionIndex < instructionsLen):
    clock += 1
    jump = jumps[instructionIndex]
    if (jumps[instructionIndex] >= 3):
        jumps[instructionIndex] -= 1
    else:
        jumps[instructionIndex] += 1
    instructionIndex += jump

print("Leaved after {} cycles". format(clock))