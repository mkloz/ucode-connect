// Note.js
class Note {
  constructor(name, importance, content) {
    this.name = name;
    this.importance = importance;
    this.content = content;
    this.date = new Date().toISOString();
  }
}

module.exports = Note;
