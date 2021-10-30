import random

states = {
    0: "Clean",
    1: "Dirty"
}

SUCK = "SUCK"
LEFT = "LEFT"
RIGHT = "RIGHT"

def performance(dirt):
    return len(dirt)-sum(dirt)

def Simulate(dirt, start, steps):
    # Simulate the performance of the robot
    position = start
    Path = []
    Path.append(position + 1)
    print(f"Environment : [{states[dirt[0]]},{states[dirt[1]]}]")
    print(f"Start Position - {position + 1:4d}  ::  Performance Measure - {performance(dirt)}")
    print("Simulation Start")
    for i in range(steps):
        if dirt[position] == 1:
            dirt[position] = 0
            print(f"Position - {position + 1:4d}  ::  Action - {SUCK:5s}  ::  Performance Measure - {performance(dirt)}")
        else:
            nextPosition = random.randint(0,1)
            if nextPosition == position and position == 0:
                print(f"Position - {position + 1:4d}  ::  Action - {LEFT:5s}  ::  Performance Measure - {performance(dirt)}")
            elif nextPosition == position and position == 1:
                print(f"Position - {position + 1:4d}  ::  Action - {RIGHT:5s}  ::  Performance Measure - {performance(dirt)}")
            elif nextPosition != position and position == 0:
                print(f"Position - {position + 1:4d}  ::  Action - {RIGHT:5s}  ::  Performance Measure - {performance(dirt)}")
            elif nextPosition != position and position == 1:
                print(f"Position - {position + 1:4d}  ::  Action - {LEFT:5s}  ::  Performance Measure - {performance(dirt)}")
            else :
                print("Error")
            position = nextPosition
        Path.append(position + 1)
    return Path

def main():
    steps = 1000 # number of steps

    dirt = [0,0]
    start = 0 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

    dirt = [0,0]
    start = 1 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

    dirt = [0,1]
    start = 0 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

    dirt = [0,1]
    start = 1 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

    dirt = [1,0]
    start = 0 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

    dirt = [1,0]
    start = 1 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

    dirt = [1,1]
    start = 0 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

    dirt = [1,1]
    start = 1 # start position
    graph = Simulate(dirt, start, steps)
    print("Path Graph")
    print('->'.join(map(str, graph)))
    print("")

if __name__ == '__main__':
    main()