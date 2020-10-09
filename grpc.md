Grpc uses http2 tech to transfer data quickly using binary format.

At aiva, this tech is being used as the backbone of the entire front-end back-end system to communicate using grpc-web.

## General Workflow

- proto file (just a text file with .proto ext) is written that shapes the data
- compiled with `protoc` command into js / ts
- `make sync` in front end will pull the compiled files into admin-ui
- the files are available to use directly with `require` (bc typescript)

## Proto3 Core Concepts

- Every directory usually has a bunch of proto files of the same package name (see below).
- Most of these will just define messages and enums, used to shape the input and outputs of the functions that will be used on the front end.
- There will most likely be one service.proto file where it takes in all data types from other proto files and defines the functions available to the client.
- Messages are named CapitalCamelCase and appended by Request or Response if used in a service function

### Syntax (general)

- `syntax = "proto3"` simply declares what syntax version. Must be the first line of proto file
- `package packageName.protected.driver_management.v1beta1;` Named after the directory.
- `option go_package = "github.com/compiled/go/blabla` Use a certain package when compiling to a particular language, in this case, go
- `import "/path/toFileName/"` imports all messages from that proto file to the PACKAGE namespace.
  To use, `nameOfPackage.messageName`. Note that the file name isn't needed in usage. Furthermore, if the current file that you're importing
  is in the same package as the imported file, you can simply declare the message or enum name directly

- a proto file does not need to define a service. It can just have the syntax, package, and a message

### Syntax (message and/or enum)

message is declared with message CapitalMessageName {}
The query name (field name) inside curly brackets are in lower_snake_case.
inside curly brackets, you need to define the type, name, and a field number like
`string start = 1;`
`uint32 hour = 2;`

Field numbers must start at 1, and 1-15 take 1 byte as opposed to numbers above 15 using 2 bytes.

```
message MsgName {
  uint32 number_of_cats = 1;
  string cat_name = 2;
}
```

Enums work similarly but is convention to CAP everything
Note that the enum field is 0 indexed.

```
enum Weekday {
    WEEKDAY_UNSPECIFIED = 0;
    WEEKDAY_MONDAY = 1;
    WEEKDAY_TUESDAY = 2;
    WEEKDAY_WEDNESDAY = 3;
    WEEKDAY_THURSDAY = 4;
    WEEKDAY_FRIDAY = 5;
    WEEKDAY_SATURDAY = 6;
    WEEKDAY_SUNDAY = 7;
}
```

An enum can be part of a message:

```
message SearchRequest {
  string query = 1;
  int32 page_number = 2;
  int32 result_per_page = 3;
  /* this simply defines an enum but isn't assigning a field */
  enum Corpus {
    UNIVERSAL = 0;
    WEB = 1;
    IMAGES = 2;
    LOCAL = 3;
    NEWS = 4;
    PRODUCTS = 5;
    VIDEO = 6;
  }
  /* This is finally declaring a field. Type is the newly defined Corpus, field name is corpus */
  Corpus corpus = 4;
}

```

Messages can be nested

#### Available Types on messages

uint32 - varialbe-length encoding
bool - boolean
string
bytes

### Syntax (service)

`package` name in proto file -> compiled web-grpc js file turns into '`packageName`.`serviceName`+"Client"'

example:

```

package aiva.management.v1beta1;

service DriverManagement {
  rpc someFunc(arg) returns (DataType) {}
  ... more functions
}
```

Will turn into js/ts file that exports aiva.management.v1beta1 objects with a DriverManagement property available.

So you will most likely pull that out

`const { DriverManagementClient } = "/path/to/that/compiled/grpc-web/file";`

### Client-side code

- Get client from a proto service, use something like
  ` const adminGrpcClient = new DriverClient();`
  This is usually used throughout multiple functions
  In that service proto file, you can see what args are necessary. Import those args from the compiled protos with those messages/enums as well.
- make a function that wraps the following:

- Make new request (message) objects that corresponds to the service function you want to use, `const request = new DriverSpecsRequest()`
- set args with set()`request.setId(MyId);`
- set additional headers as metadata `const metadata = { someKey: value }`, usually auth and api-keys
- return a Promise object where you will call the client method with request, metadata, and a callback

```
return new Promise((resolve, reject) => {
    adminGrpcClient.getDriverSpecByVendorAndName(request, metadata, (error, response) => {
      if (error && response == null) {
        console.error("Error: ", error);
        reject(error);
      } else {
        resolve(response.getDriverSpec());
      }
    });
  });
```
