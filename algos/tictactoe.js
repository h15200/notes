// Tic Tac Toe on NODE only for TripleByte interview

// prompt user (readline?) 'Please enter your move (grid x, y) -> translate logic
// Human makes the first move as 'X'

// class GameBoard
// methods print(), addToken(x, y)

class Gameboard {
  board = [
    ['-', '|', '-', '|', '-'],
    ['-', '|', '-', '|', '-'],
    ['-', '|', '-', '|', '-'],
  ];

  print() {
    // print current board
    // row is each subArray
    this.board.forEach((row) => {
      console.log(row.join(''));
    });
  }

  // 0 indexed
  addToken(x, y, type) {
    // edge case if x,y is not 0 - 2 int, reject
    // if type is not 'O' or 'X'
    // board[y][x * 2]
    this.board[y][x * 2] = type;
  }

  isFull() {
    // this.board
    // check to see if positions 00, 02, 04, 10, 12, 14, 20, 22, 24 are not "-"
    for (let i = 0; i < this.board.length; i++) {
      // each row i
      for (let j = 0; j < this.board[i].length; j += 2) {
        if (this.board[i][j] === '-') return false;
      }
    }
    return true;
  }
}

const gameBoard = new Gameboard();
gameBoard.addToken(0, 0, 'X');
// gameBoard.addToken(0, 1, 'X');
// gameBoard.addToken(0, 2, 'X');
gameBoard.addToken(1, 0, 'X');
gameBoard.addToken(1, 1, 'X');
gameBoard.addToken(1, 2, 'X');
gameBoard.addToken(2, 0, 'X');
gameBoard.addToken(2, 1, 'X');
gameBoard.addToken(2, 2, 'X');
console.log(gameBoard.isFull());
