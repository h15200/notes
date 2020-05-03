# Postman

Used to test backend easily

## setup

Connect by url
Set up 2 environments, dev and prod and use a variable instead of typing everything in

    Set url to  localhost:3000  in dev, leave the production empty

    Then (after deployment), set production url to heroku.com/blabla

Then in request, {{url}}/users

The pre-request Script and tests menu in each request allows for code, one for before the request and one for after the request

## auth testing in dev:

Make sure a login route is made that takes in a jwt and verifies, and logs in, and sends back the actual token

1.  set up ‘inherit from parent’ in auth for all requests that need authorization
2.  in the auth token entry point (usually the login) request, in Test
    If (pm.response.code === 200 { // if login was successful
    pm.environment.set(‘authToken’, pm.response.json().token) // sets pm variable
    }
    And in the dropdown of the project, edit, authorization, type “bearer token” and set to {{authToken}}

3.  In Test, set up so if create or login was successful, set authToken to the newest token value

if (pm.response.code === 200) { // or 201 if create
pm.environment.set('authToken', pm.response.json().token)
}

## Gotchas

Body of postman is text and not json!
