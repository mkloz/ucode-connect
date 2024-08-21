document.addEventListener('DOMContentLoaded', () => {
  loadNotes();
});

async function loadNotes() {
  const response = await fetch('/api/notes');
  const notes = await response.json();
  displayNotes(notes);
}

async function createNote() {
  const noteName = document.getElementById('noteName').value;
  const noteImportance = document.getElementById('noteImportance').value;
  const noteContent = document.getElementById('noteContent').value;

  const note = {
    name: noteName,
    importance: noteImportance,
    content: noteContent,
  };

  const response = await fetch('/api/notes', {
    method: 'POST',
    headers: {
      'Content-Type': 'application/json',
    },
    body: JSON.stringify(note),
  });

  if (response.ok) {
    loadNotes();
    clearForm();
  }
}

function displayNotes(notes) {
  const noteList = document.getElementById('noteList');
  noteList.innerHTML = '';

  notes.forEach((note) => {
    const listItem = document.createElement('li');
    listItem.innerHTML = `
          ${note.date} > <a href="#" onclick="viewNoteDetails('${note.date}')">${note.name}</a> 
          <a href="#" onclick="deleteNote('${note.date}')">DELETE</a>
      `;
    noteList.appendChild(listItem);
  });
}

async function viewNoteDetails(date) {
  const response = await fetch('/api/notes');
  const notes = await response.json();
  const note = notes.find((note) => note.date === date);

  document.getElementById('detailName').innerText = note.name;
  document.getElementById('detailDate').innerText = note.date;
  document.getElementById('detailNameDisplay').innerText = note.name;
  document.getElementById('detailImportance').innerText = note.importance;
  document.getElementById('detailText').innerText = note.content;
}

async function deleteNote(date) {
  const response = await fetch(`/api/notes/${date}`, {
    method: 'DELETE',
  });

  if (response.ok) {
    loadNotes();
  }
}

function clearForm() {
  document.getElementById('noteName').value = '';
  document.getElementById('noteImportance').value = 'low';
  document.getElementById('noteContent').value = '';
}
