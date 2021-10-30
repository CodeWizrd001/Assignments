Piles = None 

def get_successors(state):
    successors = []
    for i in range(state[0]):
        successors.append((i,state[1]))
    for i in range(state[1]):
        successors.append((state[0],i))
    return successors

def minimax(state,maximizingPlayer):
    successors = get_successors(state)
    # print(successors)
    if (0,0) in successors:
        return (0,0) , 1 if maximizingPlayer else -1
    best_successor = None
    if maximizingPlayer :
        best_value = -1
        for successor in successors:
            value = minimax(successor,False)[1]
            if value >= best_value:
                best_value = value
                best_successor = successor
    else:
        best_value = 1
        for successor in successors:
            value = minimax(successor,True)[1]
            if value <= best_value:
                best_value = value
                best_successor = successor
    return best_successor , best_value
    

players = {
    1 : "Player",
    -1 : "Computer"
}

moves = {
    'Player' : [] ,
    'Computer' : []
}

def valid_move(pile,stones):
    if pile >= len(Piles) or pile < 0:
        return False
    if stones > Piles[pile-1] or stones < 1:
        return False
    return True

def main():
    global Piles
    Piles = list(map(int, input("Enter Stones in the two piles (Space separated) : ").split()))
    while sum(Piles) :
        p , s = map(int, input("Enter Pile and Stones to be removed (Space separated [Pile,Stones]) : ").split())
        while not valid_move(p,s):
            print("Invalid Move")
            p , s = map(int, input("Enter Pile and Stones to be removed (Space separated [Pile,Stones]) : ").split())
        Piles[p-1] -= s
        print("{} removed {} stones from pile {}".format(players[1],s,p))
        print("Resulting Piles : {}".format(Piles))
        moves['Player'].append((p,s))
        if sum(Piles) == 0:
            print("{} wins".format(players[1]))
            print("Moves : {}".format(moves['Player']))
            break

        s , v = minimax(Piles,False)
        changedPile = 0
        removedStones = 0
        for i in range(len(s)):
            if Piles[i] != s[i] :
                changedPile = i+1
                removedStones = Piles[i] - s[i]
            Piles[i] = s[i]
        
        print("{} removed {} stones from pile {}".format(players[-1],removedStones,changedPile))
        print("Resulting Piles : {}".format(Piles))
        moves['Computer'].append((changedPile,removedStones))
        if sum(Piles) == 0:
            print("{} wins".format(players[-1]))
            print("Moves : {}".format(moves['Computer']))
            break

if __name__ == '__main__':
    main()