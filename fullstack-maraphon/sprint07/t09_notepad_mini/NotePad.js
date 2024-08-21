// NotePad.js
const fs = require('fs');
const path = require('path');

class NotePad {
  constructor(filePath) {
    this.filePath = filePath;
    this.notes = this.loadNotes();
  }

  loadNotes() {
    if (fs.existsSync(this.filePath)) {
      const data = fs.readFileSync(this.filePath, 'utf-8');
      return JSON.parse(data);
    }
    return [];
  }

  saveNotes() {
    fs.writeFileSync(this.filePath, JSON.stringify(this.notes, null, 2));
  }

  addNote(note) {
    this.notes.push(note);
    this.saveNotes();
  }

  deleteNote(date) {
    this.notes = this.notes.filter((note) => note.date !== date);
    this.saveNotes();
  }

  getNotes() {
    return this.notes;
  }
}

module.exports = NotePad;
