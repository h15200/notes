Driver TODOS:

- config should not redirect
  - compDidUpdate
  - formikSubmitting off (check disabled)
- "This DriverInstall has been authenticated" should be hidden if there was an authErrorList.length
- itemMapper should be options array for documentation (value, {doNotCapitalize: true}), then on func side `if options.doNotCapitalize === true` and document `options object. doNotCapitalize defaults to false`

## actionable:

- test new config with properly working specs
- check getwell styling

## failing on create:

## known issues:

- failing on create

  - tasks
  - careteam
  - epic
  - fdb
  - jci
  - legacy
  - patientsafe
  - pointClickCare
  - vocera

- getwell - (oauth2, clientCredentials) refreshAuth not working
- twilio - no status
- workxhub

  - (oauth2, clientCredentials) refreshAuth is working, but needsAuth true
  - deleteInstall failing

- smile
  - deleteInstall failing

## finished (CRUD and style, but not accounting for global known issues like delete failing) :

- aiva-knowledge
- aive-remotelink
- aiva-tasks
- tels
