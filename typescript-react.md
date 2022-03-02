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
    <label>
      Italics Converter
      <input
        className={`${getIsFirstCharItalics() ? "italics" : ""}`}
        type="text"
        value={inputString}
        onChange={updateInput}
      />
    </label>
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

## NOTE with fetch

- fetch does NOT throw an error when a url is wrong
- the way to handle error is to manually throw or use error state by checking the response.ok. If `!response.ok`, then something went wrong

## typing separate props with default values

```
export function TestProps({
  num = 0,
  str = "N/A",
}: {
  num?: number; // must be optional if defaults are used
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

## common pattern with fetching, isMounted, and component error handling

```
import React, { useState, useEffect } from "react";
import "./practice.css";
import { Practicelist } from "./Practicelist";



export function ErrorComp({ msg }: { msg: string }) {
  return <div style={{ color: "red" }}>{`${msg}`}</div>;
}

export interface User {
  email: string;
  id: number;
}

async function fetchHelper(url: string): Promise<User[]> {
  let res;

    res = await fetch(url);
  if (!res.ok) {
    console.log("Error on fetch: ", );
    throw Error("Something went wrong during fetch");
  }

  let userData: User[];
  try {
    userData = await res.json();
  } catch (e: any) {
    console.log("Erorr on json()", e);
    throw Error("Something went wrong during json()");
  }

  return userData;
}

export function Practice() {
  const [data, setData] = useState<null | User[]>(null);
  const [isLoading, setIsLoading] = useState(false);
  const [errorMsg, setErrorMsg] = useState("");

  useEffect(() => {
    let isMounted = true;
    setIsLoading(true);

    (async () => {
      let userData: User[];
      try {
        userData = await fetchHelper(
          "https://jsonplaceholder.typicode.com/users",
        );
        if (isMounted) {
          setErrorMsg(e.message);
        }
        return;
      }
      // success
      if (isMounted) {
        setData(userData);
      }
    })();
    if (isMounted) setIsLoading(false);
    return () => {
      isMounted = false;
    };
  }, []);

  function increment(): void {
    setNum(num + 1);
  }

  return (
    <div className="container">
      <div>{num}</div>
      <div>
        <button onClick={increment}>Increment</button>
      </div>
      {isLoading || data === null ? (
        <div>Loading...</div>
      ) : errorMsg ? (
        <ErrorComp msg={errorMsg} />
      ) : (
        <Practicelist users={data} />
      )}
    </div>
  );
}
```

```
import React from "react";
import "./practiceList.css";
import { User } from "./Practice";

export function Practicelist({ users }: { users: User[] }) {
  return (
    <div className="user-list">
      {users.map((user) => {
        return (
          <ul key={user.id} className="user">
            <li>Name - {user.email}</li>
            <li>Id - {user.id}</li>
          </ul>
        );
      })}
    </div>
  );
}
```
