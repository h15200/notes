## Formik prop methods and gotchas

- setFieldValue() is secretly async. await it if you want to change value, then check it. see timedEventPoliciesForm onSubmit near end. BUT better to use initVal manipulation (see below)
- validateForm will return no errors if form is untouched
- formik.submitForm() will validate form first, then stop process if errors exist.
- to add notification for submitForm(), you must add logic before your custom onSubmit handler. see driverInstallForm submit button onClick

## Yup validation

- you can validate on the spot with async isValid()

```
          Yup.array()
            .required("Required")
            .isValid([""])
            .then(data => console.error("is data valid? ['']", data));

```

- Yup.array().required("WARNING_STRING") will fail `[]`, but pass `['']`

## initVal

- when using initVal state to plug into formik, that can be manipulated with complex UI - form syncing. for example, a modal open/close in MUI will cause another re-render on the formik. You can call a state change to initVals within that modal before closing the modal to save the value directly to formik values without going through shananigans of async formikProp.submitForm() manipulation
