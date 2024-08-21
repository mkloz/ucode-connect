// server.js
const express = require('express');
const Note = require('./Note');
const NotePad = require('./NotePad');

const app = express();
const PORT = 3000;
const notePad = new NotePad('notes.json');

app.use(express.json());
app.use(express.static(__dirname));

app.get('/api/notes', (req, res) => {
  res.json(notePad.getNotes());
});

app.post('/api/notes', (req, res) => {
  const { name, importance, content } = req.body;
  const note = new Note(name, importance, content);
  notePad.addNote(note);
  res.status(201).json(note);
});

app.delete('/api/notes/:date', (req, res) => {
  const { date } = req.params;
  notePad.deleteNote(date);
  res.status(204).send();
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
