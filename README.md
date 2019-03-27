# Connect 4
## How to install
- git pull https://github.com/BConquest/cs201-project.git 
- have ncurses installed
- cd cs201-project
- make
- ./cnct
- can type `help` in most places to get a list of valid commands

## How to play
- 1) enter a gamemode from menu by typing `game`
- 2) choose to play against `computer` or another `player`
- 2a) if playing against a `computer` have choice of
	- easy -> computer plays randomly
	- hard -> the ai chooses the best move
	- impossible -> plays randomly and plays the best move (2 moves)
- 3) to play a peice type column number that you want to play in (columns start at 1)

## Config File
- player1 requires it to be an ascii character anything else will break it
- player2 is the same as player1
- DEBUG - when this is set to 0 then the terminal will not be cleared but a newline is printed

# TODO
- Make AI the best
- get A
