const express = require('express');
const path = require('path');
const { urlencoded } = require('express');
const app = express();

const PORT = process.env.PORT || 3000;

app.use(express.json());
app.use(urlencoded({ extended: true }));
console.log(__dirname);

app.use('/assets', express.static(path.resolve(__dirname, '../client/assets')));

app.get('/', (req, res) => {
  return res
    .status(200)
    .sendFile(path.resolve(__dirname, '../client/index.html'));
});

app.get('/test', (req, res) => {
  return res
    .status(200)
    .sendFile(path.resolve(__dirname, '../client/test.html'));
});

// 404
app.use('*', (req, res) => {
  console.log('route not set up');
  return res.sendStatus(404);
});

// global error handling
app.use((err, req, res, next) => {
  console.log(err);
  return res.sendStatus(500);
});

app.listen(PORT, () => {
  console.log(`listening on port ${PORT}`);
});
