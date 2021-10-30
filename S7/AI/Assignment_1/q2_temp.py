import random

modes = {
    0 : "PvE" ,
    1 : "EvE" ,
}

class Game : 
    Player_1 = None
    Player_2 = None
    Mode = None
    Pile = None
    numberOfPiles = 0

    def __init__(self, mode) :
        self.Mode = mode
        if self.Mode == "PvE" :
            self.Player_1 = "User"
            self.Player_2 = "Computer"
        elif self.Mode == "EvE" :
            self.Player_1 = "Player_1"
            self.Player_2 = "Player_2"
        self.current_player = self.Player_1
    
    def simulate(self): 
        while self.get_empty() != 0 :
            print("Current Pile : {}".format(self.Pile))
            print("Current Player : {}".format(self.current_player))
            if self.current_player == "User" :
                pileNumber , stones = self.get_user_move()
            else :
                pileNumber , stones = self.get_computer_move()
            if self.Pile[pileNumber - 1] < stones :
                print("Invalid Move")
                continue
            print(f"{self.current_player} removes {stones:4d} stones from Pile {pileNumber:3d}")
            self.Pile[pileNumber - 1] -= stones
            self.switch_player()
        
        self.switch_player()
        print(f"{self.current_player} Wins")
    
    def set_piles(self,numberOfPiles,pile) :
        if len(pile) != numberOfPiles :
            raise ValueError("Pile size does not match number of piles")
        self.numberOfPiles = numberOfPiles
        self.Pile = pile

    def switch_player(self) :
        if self.current_player == self.Player_1 :
            self.current_player = self.Player_2
        else :
            self.current_player = self.Player_1
    
    def get_computer_move(self) :
        pileNumber = random.randint(1,self.numberOfPiles)
        while self.Pile[pileNumber - 1] == 0 :
            pileNumber = random.randint(1,self.numberOfPiles)
        stones = random.randint(1,self.Pile[pileNumber - 1])
        return pileNumber , stones
    
    def get_user_move(self) :
        mStr = input("Enter your move [PileNumber Stones] : ")
        pileNumber , stones = map(int,mStr.split())
        return pileNumber , stones

    def get_empty(self) :
        return self.Pile.count(0)

    def __str__(self) :
        return "Player 1 : {}\nPlayer 2 : {}\nMode : {}".format(self.Player_1, self.Player_2, modes[self.Mode])

def main() :
    print("Choose Game Mode :")
    print("      0 : PvE")
    print("      1 : EvE")
    
    try :
        mode = modes[int(input("Enter Mode : "))]
    except KeyError :
        print("Invalid Mode")
        exit()
    except Exception as e :
        print(f"Unhandled Error : {e}")
        exit()
    
    game = Game(mode)

    print("Enter number of piles : ")
    numberOfPiles = int(input())
    print("Enter Piles : ")
    pile = list(map(int,input().split()))
    
    game.set_piles(numberOfPiles,pile)

    game.simulate()

if __name__ == "__main__" :
    main()