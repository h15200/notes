## FS - path

File System api's usually ask for the direct path from the ROOT dir of the project. Don't use relative path './'

Don't forget to encode it so that you don't get a buffer, but a string when you read a file
Pass in an options object with encoding: 'utf-8'

```
fs.readFileSync('project.csv', {
  encoding: 'utf-8'
})
```
