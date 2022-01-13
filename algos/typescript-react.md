# list of quirks specific to TS + React

## when using input, use event types AND event.target types

```
import React, { useState } from "react";

export function PracticeInput() {
  const [inputString, setInputString] = useState("");

  function updateInput(e: React.ChangeEvent<HTMLInputElement>): void {
    setInputString((e.target as HTMLInputElement).value);
  }

  function getIsFirstCharItalics(): boolean {
    if (inputString[0] === "_") return true;
    else return false;
  }
  return (
    <input
      className={`${getIsFirstCharItalics() ? "italics" : ""}`}
      type="text"
      value={inputString}
      onChange={updateInput}
    />
  );
}

```

## typing props with destructuring

```
// some component file called with "data" prop which is fetched data

type User = {
  id: number;
  isDone: boolean;
  description: string;
}

// props only contains data, so you can destructure AND type like this

function MyComponent({data}: {data: User}) {
  // stuff
}


```

## typing separate props with default values

```
export function TestProps({
  num = 0,
  str = "N/A",
}: {
  num?: number; // must be optional if defautls are used
  str?: string; // same
}) {
  return (
    <div>
      <div>{num}</div>
      <div>{str}</div>
    </div>
  );
}
```
