Driver TODOS:

- test all create/delete crud

## actionable:

- getwell styling

## failing on create:

- afh
- tasks
- careteam
- epic
- fdb
- jci
- legacy
- patientsafe
- pointClickCare
- vocera

## failing after create:

- afh performOauth2Code
- getwell - (oauth2, clientCredentials) refreshAuth not working
- twilio - no status
- workxhub
  - (oauth2, clientCredentials) refreshAuth is working, but needsAuth true
  - deleteInstall failing
- smile
  - deleteInstall failing

## finished (CRUD and style):

- aiva-knowledge
- aive-remotelink
- aiva-tasks
- tels

## before making PR

`git rebase -i HEAD~n`

find n by going back to first commit on branch AFTER master

git log -g
