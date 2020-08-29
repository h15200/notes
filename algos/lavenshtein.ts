function levenshteinDistance(str1: string, str2: string): number {
  /*
	DP 2 - d array based on operations
	INSERT = str1 -> (str2 - 1)  + 1
	DELETE = (str1 - 1) -> str2 + 1
	REPLACE = (str1 - 1) -> (str2 - 1) + 1
	
	str1 = 'abc'
	atr2 = 'yabd'
	
	      '' , 'y', 'a', 'b', 'd'
	 ''   [0 ,  1,   2,   3 ,  4 ]
	'a'   [1    1    1    2    3 ]
	'b'   [2    2    2    1    2 ]
	'c'   [3    3    3    2    2  ]
	
	make a 2d array of length str1 + 1
	each subarray length is str2 + 1
	answer will be on dpArr[dpArr.length -1][dpArr[0].length - 1]
	*/

  const dpArr: number[][] = [];
  // push subarrays into dpArr
  for (let i = 0; i < str1.length + 1; i++) {
    // now loop through str2
    // if first row,
    if (i === 0) {
      let subArr = [];
      for (let j = 0; j < str2.length + 1; j++) {
        subArr.push(j); //[0, 1, 2, 3 etc.]
      }
      dpArr.push(subArr);
      // console.log(dpArr);
    }
    // for all rows starting 2nd
    else {
      dpArr.push([]);
      for (let j = 0; j < str2.length + 1; j++) {
        if (j === 0) dpArr[i][j] = dpArr[i - 1][j] + 1;
        else if (j !== 0) {
          // if chars are same
          if (str1[i - 1] === str2[j - 1]) dpArr[i][j] = dpArr[i - 1][j - 1];
          else {
            dpArr[i][j] =
              Math.min(dpArr[i - 1][j], dpArr[i][j - 1], dpArr[i - 1][j - 1]) +
              1;
          }
        }

        // if not
        // if chars are same, just diagonal
        // if not
        // Math.min(left, up, diagonal) + 1
      }
    }
  }
  console.log(dpArr);
  return dpArr[dpArr.length - 1][dpArr[0].length - 1];
}
console.log(levenshteinDistance('abc', 'yabd'));
