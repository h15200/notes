function spiralTraverse(array: number[][]): number[] {
  const output: number[] = [];

  const totalWidth = array[0].length;
  const totalHeight = array.length;

  let i = 0;
  while (output.length < totalWidth * totalHeight) {
    // get current bounds
    const startCol = i;
    const endCol = totalWidth - 1 - i;

    const startRow = i;
    const endRow = totalHeight - 1 - i;
    // formula is always array[ROW][COL]
    for (let i = startCol; i <= endCol; i++) {
      output.push(array[startRow][i]);
    }

    // go down to last row
    for (let i = startRow + 1; i <= endRow; i++) {
      output.push(array[i][endCol]);
    }

    // only if height exists
    // go from 2nd to last col in last row and go left
    if (endRow - startRow > 0) {
      for (let i = endCol - 1; i >= startCol; i--) {
        output.push(array[endRow][i]);
      }
    }

    // go up from endRow - 1 to row + 1
    // only if width exists
    if (endCol - startCol > 0) {
      for (let i = endRow - 1; i >= startRow + 1; i--) {
        output.push(array[i][startRow]);
      }
    }

    i++;
  }
  return output;
}

console.log(
  spiralTraverse([
    [1, 2, 3, 4],
    [12, 13, 14, 5],
    [11, 16, 15, 6],
    [10, 9, 8, 7],
  ])
);
