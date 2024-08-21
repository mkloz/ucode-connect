const express = require('express');
const session = require('express-session');
const path = require('path');

const port = 3000;
const app = express();

app.use(express.json());
app.use(
  express.urlencoded({
    extended: true,
  }),
);
app.use(
  session({
    secret: 'superhero_secret',
    resave: false,
    saveUninitialized: true,
  }),
);

app.get('/', (req, res) => {
  if (req.session.hero) {
    res.send(`
      <html lang="en">
      <head>
        <meta charset="UTF-8">
        <title>Superhero Information</title>
      </head>
      <body>
        <h1>Superhero Information</h1>
        <div class="superhero-info">
          <p><strong>Real Name:</strong> ${req.session.hero.name}</p>
          <p><strong>Email:</strong> ${req.session.hero.email}</p>
          <p><strong>Age:</strong> ${req.session.hero.age}</p>
          <p><strong>About:</strong> ${req.session.hero.text}</p>
          <p><strong>Photo:</strong><br><img src="/uploads/${req.session.hero.photo}" alt="Superhero Photo"></p>
        </div>
        <a href="/">Go back to form</a>
      </body>
      </html>
    `);
  } else {
    res.sendFile(path.join(__dirname, 'index.html'));
  }
});

app.post('/', (req, res) => {
  req.session.hero = {
    name: req.body.name,
    email: req.body.email,
    age: req.body.age,
    text: req.body.text,
  };
  res.redirect('/');
});

app.post('/forget', (req, res) => {
  req.session.destroy();
  res.redirect('/');
});

app.listen(port, () => {
  console.log(`Server running at http://localhost:${port}/`);
});
