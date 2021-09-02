// rotate a number[][] matrix 90 degrees
// [1,2]  =>  [3, 1]
// [3,4]      [4, 2]

function rotate(matrix: number[][]): number[][] {
  let layer = 0;
  while (layer < Math.floor(matrix.length / 2)) {
    const first = layer;
    const last = matrix.length - 1 - layer;
    for (let i = first; i < last; i++) {
      const offset = i - layer; // this increases as i increases - going across the top row
      // top left matrix[first][i]
      // top right matrix[first + offset][last]
      // lower right matrix[last][last - offset]
      // lower left matrix[last - offset][first]

      // swap three times

      [matrix[first][i], matrix[first + offset][last]] = [
        matrix[first + offset][last],
        matrix[first][i],
      ];

      [matrix[first][i], matrix[last - offset][first]] = [
        matrix[last - offset][first],
        matrix[first][i],
      ];
      [matrix[last][last - offset], matrix[last - offset][first]] = [
        matrix[last - offset][first],
        matrix[last][last - offset],
      ];
    }
    layer++;
  }

  return matrix;
}

console.log(
  rotate([
    [1, 2],
    [3, 4],
  ]),
);

console.log(
  rotate([
    [1, 2, 3],
    [4, 5, 6],
    [7, 8, 9],
  ]),
);

console.log(
  rotate([
    [1, 2, 3, 4],
    [5, 6, 7, 8],
    [9, 10, 11, 12],
    [13, 14, 15, 16],
  ]),
);
// console.log('rotate[[1]]', rotate([[1]]))
// console.log('rotate[[1, 2], [3,4]]', rotate([[1,2], [3,4]]))
// console.log('rotate[[1, 2, 3], [4, 5, 6], [7, 8, 9]]', rotate([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))
// console.log('rotate[[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]', rotate([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12], [13, 14, 15, 16]]))
