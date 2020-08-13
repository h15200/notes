/*
 * Given an array of strings, group anagrams together.
 * Input: ["eat", "tea", "tan", "ate", "nat", "bat"]
 * Output:
[
  ["ate","eat","tea"],
  ["nat","tan"],
  ["bat"]
]
All inputs will be in lowercase.
The order of your output does not matter.
*/

const anagramSort = (array) => {
  // helper compare
  const isAnagram = (word1, word2) => {
    const cache1 = {};
    const cache2 = {};
    // make two objects with word counters
    for (let char of word1) {
      cache1[char] = cache1[char] + 1 || 1;
    }
    for (let char of word2) {
      cache2[char] = cache2[char] + 1 || 1;
    }
    // if number of chars match, delete key
    for (const key in cache1) {
      if (!key in cache2) return false;
      if (cache1[key] === cache2[key]) {
        delete cache1[key];
        delete cache2[key];
      }
    }
    // if both caches are empty, they are anagrams
    if (!Object.keys(cache1).length && !Object.keys(cache2).length) return true;
    return false;
  };

  // initialize first subarray with first item
  const output = [[array[0]]];

  // iterate through array starting from 2nd item
  for (let i = 1; i < array.length; i++) {
    // keep track of if an anagram was found in an existing subarray
    let found;
    // iterate through output
    for (let j = 0; j < output.length; j++) {
      // if current is an anagram of subarray, push into subarray
      if (isAnagram(array[i], output[j][0])) {
        output[j].push(array[i]);
        found = true;
      }
    }
    // if no buddy was found, start a new subarray
    if (!found) output.push([array[i]]);
  }
  return output;
};

console.log(anagramSort(['eat', 'tea', 'tan', 'ate', 'nat', 'bat']));
