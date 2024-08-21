const saveForm = document.getElementById('saveForm');
const guessForm = document.getElementById('guessForm');
const clearButton = document.getElementById('clearButton');
const hashedPasswordElement = document.getElementById('hashedPassword');

saveForm.addEventListener('submit', async (event) => {
  event.preventDefault();
  const formData = new FormData(saveForm);
  const response = await fetch('/save', {
    method: 'POST',
    body: formData,
  });
  if (response.ok) {
    const data = await response.text();
    hashedPasswordElement.innerText = data;
  }
});

guessForm.addEventListener('submit', async (event) => {
  event.preventDefault();
  const formData = new FormData(guessForm);
  const response = await fetch('/guess', {
    method: 'POST',
    body: formData,
  });
  if (response.ok) {
    const message = await response.text();
    alert(message);
  } else {
    alert('Access denied!');
  }
});

clearButton.addEventListener('click', async () => {
  const response = await fetch('/clear', { method: 'POST' });
  if (response.ok) {
    hashedPasswordElement.innerText = '';
    alert('Session cleared');
  }
});
