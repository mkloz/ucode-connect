const express = require('express');
const path = require('path');
const fs = require('fs');
const { ListAvengerQuotes } = require('./ListAvengerQuotes');
const { AvengerQuote } = require('./AvengerQuote');
const { data } = require('./mock-data');

const app = express();
const PORT = process.env.PORT || 3000;
app.use(express.static(__dirname));

fs.writeFileSync(path.join(__dirname, 'avenger_quote.xml'), '');

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.post('/create', (req, res) => {
  listQuotes.toXML();

  res.redirect('/');
});

app.get('/before-conversion', (req, res) => {
  res.json(listQuotes.quotes);
});

app.get('/after-conversion', (req, res) => {
  listQuotes.fromXML();

  if (listQuotes.length === 0) {
    res.status(404).json({ message: 'No quotes found' });
    return;
  }

  res.json(listQuotes.quotes);
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});

const listQuotes = new ListAvengerQuotes();
data.forEach((quote) => {
  listQuotes.addQuote(new AvengerQuote(quote));
});
