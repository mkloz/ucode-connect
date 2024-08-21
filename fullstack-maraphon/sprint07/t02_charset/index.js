const express = require('express');
const iconv = require('iconv-lite');
const multer = require('multer');
const app = express();
const port = 3000;

app.use(express.urlencoded({ extended: true }));
app.use(express.static(__dirname));
app.use(multer().none());

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});

app.post('/convert', (req, res) => {
  const inputString = req.body.inputString;
  const charset = req.body.charset;
  const convertedStrings = [];

  if (charset.includes('utf8')) {
    convertedStrings.push(iconv.encode(inputString, 'utf8').toString('hex'));
  }
  if (charset.includes('utf16')) {
    convertedStrings.push(iconv.encode(inputString, 'utf16').toString('hex'));
  }
  if (charset.includes('latin1')) {
    convertedStrings.push(iconv.encode(inputString, 'latin1').toString('hex'));
  }

  res.send(convertedStrings);
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
