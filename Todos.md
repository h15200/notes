@hideaki So that list is the accounts (aka NluSystems) that have been set up. NluApps get published into those NluSystems.
So the relationship is: [NluApp] --[binding]--> [NluSystem]

The invocation is a property of the binding in the middle.
NluSystemBinding.invocation

So that relationship is set up in the screen where a single NluApp is being edited in "attach voice platforms"

## driverInstalls known issues

### failing on create

- epic (expected)
- pointClickCare

### smile

- toBeDeleted flag not deleting in back-end

### twilio

- not sending status
- can't see auth/config
- check out add table, multi selector if it's stale data after status is sorted out

### smartthings (oauth2, authCode)

- oAuth not set up
- can't see config/style

### workxhub (oauth2, clientCredentials)

- refreshAuth seems to be working, but still sending status.needsAuth true

### getwell (oauth2, clientCredentials)

- refreshAuth not implemented in back-end
