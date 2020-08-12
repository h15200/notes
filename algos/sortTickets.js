// sort tickets from start to end

// what is input? { LA: NY , SF: BOS, etc.. }

const sortTickets = (tickets) => {
  // loop all tickets, find first departure
  // make cache { city, departure, city, arrival }
  const cache = {};
  // loop through stack
  for (const departurePort in stack) {
    // if cache already has departure port, delete. if not, add
    departurePort in cache
      ? delete cache[departurePort]
      : (cache[departurePort] = 'departure');
    // if cache already has arrival port, delete. if not, add
    const arrival = stack[departurePort];
    arrival in cache ? delete cache[arrival] : (cache[arrival] = 'arrival');
  }

  // at this point cache should have 2 things. PORT: 'arrival' and PORT: 'departure'
  // make output
  const origin = Object.keys(cache).find((key) => cache[key] === 'departure');
  const last = Object.keys(cache).find((key) => cache[key] === 'arrival');

  const output = [];
  output.push([origin, stack[origin]]);

  // now find the rest from the stack until the last city is reached
  console.log('output is', output);

  while (output[output.length - 1][1] !== last) {
    for (const key in stack) {
      const currentPort = output[output.length - 1][1];
      if (key === currentPort) output.push([key, stack[key]]);
    }
  }
  console.log(output);
};

const stack = {
  NY: 'LA',
  BOS: 'SEATTLE',
  SEATTLE: 'TOKYO',
  LA: 'BOS',
};

sortTickets(stack);
