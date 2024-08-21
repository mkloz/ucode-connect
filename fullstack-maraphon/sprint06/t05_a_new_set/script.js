const form = document.querySelector('form');

form.addEventListener('submit', async (event) => {
  event.preventDefault();

  const formData = new FormData(form);

  const response = await fetch('/', {
    method: 'POST',
    body: formData,
  });

  const result = await response.text();
  document.getElementById('result').innerHTML = result;
});
