# Yup Validation

- yup.object.shape({}) to make a schema to pass to Formik (usually)

## Immediate testing

- you can validate on the spot with async isValid()

```
          Yup.array()
            .required("Required")
            .isValid([""])
            .then(data => console.error("is data valid? ['']", data));

```

## Gotchas

- Yup.mixed(), Yup.string(), Yup.number() etc.. will never trigger without .required() chained

- Yup.array().required("WARNING_STRING") will fail `[]`, but pass `['']`

## Conditional Validation

### for 1 other field

```
const schema = Yup.object.shape({
...,
basicCardTitle: Yup.mixed().when("visualStyleType", (visualStyleType, schema) => {
    if (visualStyleType === RENDERABLE_VISUAL_STYLE_TYPE.BASIC_CARD) {
      return schema.required("Required for Basic Card");
      // this will chain to Yup.mixed() conditionally
    }

    return schema; // Yup.mixed() if not basicCard, no requirement
  }),
})


```

### for more than 1 other field

- for a test with 2 individual fields, make a new validation field and expose it additional to the component. use the object.is construct

```
  timeStartIsBeforeTimeEnd: Yup.mixed().when(["startTime", "endTime"], {
    is: (startTime, endTime) => {
      return startTime && endTime && moment(startTime).unix() >= moment(endTime).unix();
    },
    then: Yup.mixed().required("Time Starting must be before Time Ending"),
  }),

  // note how the syntax is slightly different. Instead of chaining, this is replacing the initial yup object in the <then> field
```
