# report

- toBeDeleted was not working in smile, was fine in cbord
- UI should handle new submission. refactored

## waiting for back-end

- afh config can't handle multiple facilities

## actionable:

- add confirmation for dynamic table delete
- check and style other nested tables
- check getwell styling margin
- style smile

## KNOWN ISSUES:

### twilio

- not sending status
- can't see auth/config
- can't see style

### failing on create

- epic (expected)
- fdb (ask)
- patientsafe (ask)
- pointClickCare (ask)
- vocera (ask)

### globally deleteDriverInstall fails randomly

- error: driver does not exist, but works properly on refresh (driver was deleted)

### smartthings (oauth2, authCode)

- oAuth not set up
- can't see config/style

### workxhub (oauth2, clientCredentials)

- refreshAuth is working, but sending status.needsAuth true

### getwell (oauth2, clientCredentials)

- margins
- refreshAuth not implemented in back-end

## finished (CRUD and style, but not accounting for global known issues like delete failing) :

- aiva-knowledge
- aive-remotelink
- aiva-tasks
- careteam
- cbord
- clockwise
- legacy
- mailgun
- smile
- tels
