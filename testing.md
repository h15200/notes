Usually jest or mocha

Install as a dev depency
npm install --save-dev jest

In package.json under scripts, add “test”:” env-cmd ./config/test.env jest --watch” (--watch will run the tests on change on git, --watchAll will run all test files, see below for env-cmd explanation)
Add a tests dir, and name the files <something>.test.js

    Jest Config

In package.json, add

“jest” : { “testEnvironment“ : “node” } // default is browser-environment. Do this for backend

Jest installs test() as a global, so you don’t need to require it.
In the file, call test() - 1st arg string, 2nd arg function
If the function runs without throwing and error, the test passes

    		ENV

Jest must have the same env variables to test the routes properly
To do so:

Make another env file ‘test.env’ in your config dir
Copy everything the same except:

Possibly change the PORT to 3001 or something different
Definitely change the DATABASE_URL to from ‘...app-name’ to ‘...app-name-test’

Now use env-cmd (or whatever package you used in the main app)
And put the command before the test script

    		Npm supertest

Like jest, save as a dev dependency

npm i supertest --save-dev

Does not need to be connected to server to test routes, so you don’t want app.listen() to be called.

To do this, it’s best practice to have an app.js that imports express, routers, sets the port, etc.. with everything EXCEPT app.listen, module.exports = app

and have another file like index.js import that, and just call listen.

This way testing can be done on app.js before app.listen is called

    	MOCKS

To avoid packages like sendgrid firing off emails for every test,

create a directory called `__mocks__` in ‘tests’

Then depending on the module… for example, sendgrid is
require(‘@sendgrid/mail’)

So the first part is ANOTHER folder inside `__mocks__` and the name after the / is the file name.

So, make another dir inside `__mocks__` called @sendgrid, then create a file, mail.js inside THAT

`tests/__mocks__/@sendgrid/mail.js`

Then in mail.js module.exports { anyMethodsfromThisPackageYouUsed }
And set them up usually as an empty function UNLESS you are using the return values i
