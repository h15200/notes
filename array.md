Static vs Dynamic under the hood

if in Javascript, const a = [3]; will default to a DYNAMIC array, meaning it makes 2x the amount of space in memory just in case you want to add more.

a.push(4); // is O(1) because there is space in memory carved out for that slot.

When all of the doubles are used, the next addition will need to be copied and moved to a different segment in memory, but that will have DOUBLE the amount again!
