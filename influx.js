/*
input string[][] assume "x" | "o" | ""

const board = [['x', 'o', ''], ['','',''], ['x','x','o']]

x o _
_ _ _
x x o

output: boolean 

3 conditions to check for either (3 x's, 3 o's)
  1. any horizontal winners x 3 
    if first item is "x" or "o", then coninue looking for only that char
    if first item is "" break
      if not, break to next row (including "")
    
    
  2. vertical x 3
    same logic as rows 
  3. diagonal x 2
    same logic

    board[y][x]
*/

function isDone(board) {
  // rows
  for (let i = 0; i < board[0].length; i++) {
    const rowIsDone = getRowIsDone(board[i]); // any type of 3 consecutive items
    if (rowIsDone) return true;
  }

  // cols
  for (let x = 0; x < 3; x++) {
    // y, x
    const colIsDone = getColIsDone(x); // any type of 3 consecutive items
    if (colIsDone) return true;
  }

  // diags
  // check upper left to lower right
  if (board[0][0] === "x" && board[1][1] === "x" && board[2][2] === "x") {
    return true;
  }
  if (board[0][0] === "o" && board[1][1] === "o" && board[2][2] === "o") {
    return true;
    // check lower left to upper right
  }
  if (board[2][0] === "x" && board[1][1] === "x" && board[0][2] === "x") {
    return true;
  }
  if (board[2][0] === "o" && board[1][1] === "o" && board[0][2] === "o") {
    return true;
  }

  return false;

  // HELPER FUNCTIONS
  function getRowIsDone(row) {
    // check row for 3 consecutive "x" or "o"
    // row ["x", "o", ""]
    if (row[0] === "o" && row[1] === "o" && row[2] === "o") {
      return true;
    } else if (row[0] === "x" && row[1] === "x" && row[2] === "x") {
      return true;
    } else return false;
  }
  function getColIsDone(xCoord) {
    // check col for 3 consecutive "x" or "o"
    if (
      board[0][xCoord] === "o" &&
      board[1][xCoord] === "o" &&
      board[2][xCoord] === "o"
    ) {
      console.log("line 62");
      return true;
    } else if (
      board[0][xCoord] === "x" &&
      board[1][xCoord] === "x" &&
      board[2][xCoord] === "x"
    ) {
      console.log("line 69");
      return true;
    } else return false;
  }
}

console.log(
  isDone([
    ["x", "o", "x"],
    ["o", "x", ""],
    ["o", "o", "x"],
  ]),
  //       x0   x1  x2
  //  y0 ["", "o", "o"],
  //  y1 ["", "", ""],
  //  y2 ["x", "x", "x"],

  // board[0][x], board[1][x], board[2][x]
);
