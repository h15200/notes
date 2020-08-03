// sort tickets from start to end

// implementation - LL

// find first departure ticket

/*
[
b -> c,
d -> e,
a -> b,
c -> d
]
*/

// if destination doesn't show up as an arrival ('e')
// e is tail
// traverse back from tail
// if no ticket ENDS with a value, then that is the head

// array of two values representing departure and arrival [[a, b], [b, c]]

const sortTickets = (tickets) => {
  // loop all tickets, find first departure
  // make cache
  // check to see if current element[1] is in cache
  // if yes, delete element, if not, add
  const sorted = [];
  const cache = {}; // port: true
  for (let ticket of tickets) {
    cache.hasOwnProperties(ticket[1])
      ? delete cache[ticket[1]]
      : (cache[ticket[i]] = true);
  }
  // now cache should say { a: true }

  // look for a, push to sorted.
  // hold reference to the 2nd element of a array
  // for for that element, repeat
  for (let ticket of tickets) {
    let currentDeparture = [Object.keys(cache)[0]];

    if (ticket[0] === currentDeparture) {
      sorted.push(ticket);
      currentDeparture = ticket[1];
    }
  }
};
