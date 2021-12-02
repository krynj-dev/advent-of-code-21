import os


def task_one(depths):
    count = 0
    # Iterate through all depths
    for i in range(1, len(depths)):
        if depths[i] > depths[i-1]:
            count += 1
    return count

def task_two(depths):
    count = 0
    # Cheat: since only difference is first/last between measurements, you can just compare number i and i+3 to find difference
    for i in range(3, len(depths)):
        if depths[i] > depths[i-3]:
            count += 1
    return count


if __name__ == "__main__":

    f = open('input.txt', 'r')
    # Read input
    inp = f.readlines()
    # Convert entries to int
    inp = [int(x.strip('/n')) for x in inp]

    # Call task functions
    print(task_one(inp))

    print(task_two(inp))