const express = require('express');
const session = require('express-session');
const crypto = require('crypto');
const multer = require('multer');
const app = express();
const port = 3000;

app.use(express.json());
app.use(express.urlencoded({ extended: true }));
app.use(express.static(__dirname));
app.use(multer().none());

app.use(
  session({
    secret: 'supersecret',
    resave: false,
    saveUninitialized: true,
  }),
);

app.get('/', (req, res) => {
  res.sendFile(__dirname + '/index.html');
});

app.post('/save', (req, res) => {
  // console.dir(req);
  const password = req.body.password;
  const salt = req.body.salt;
  const hashedPassword = crypto
    .createHash('sha256')
    .update(password + salt)
    .digest('hex');
  req.session.hashedPassword = hashedPassword;
  req.session.salt = salt;
  res.send(hashedPassword);
});

app.post('/guess', (req, res) => {
  const guess = req.body.guess;
  const hashedGuess = crypto
    .createHash('sha256')
    .update(guess + req.session.salt)
    .digest('hex');
  if (hashedGuess === req.session.hashedPassword) {
    res.send('Hacked!');
    req.session.destroy();
  } else {
    res.status(403).send('Access denied!');
  }
});

app.post('/clear', (req, res) => {
  req.session.destroy();
  res.send('Session cleared');
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
