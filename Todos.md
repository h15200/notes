## driverInstalls known issues

### failing on create

- epic (expected)
- pointClickCare

### smile

- toBeDeleted flag not deleting in back-end

### smartthings (oauth2, authCode)

- oAuth not set up
- can't see config/style

### workxhub (oauth2, clientCredentials)

- refreshAuth seems to be working, but still sending status.needsAuth true

### twilio

- db value for COUNTRY (type ENUM) is sending `[""]` on a fresh driverInstall instead of using spec.DefaultValues, which is `["US"]`
