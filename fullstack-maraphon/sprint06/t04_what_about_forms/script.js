document.addEventListener('DOMContentLoaded', () => {
  const form = document.getElementById('quiz-form');

  form.addEventListener('submit', async (event) => {
    event.preventDefault();

    const formData = new FormData(form);
    const params = new URLSearchParams();
    for (const pair of formData) {
      params.append(pair[0], pair[1]);
    }

    const response = await fetch('/submit', {
      method: 'POST',
      headers: {
        'Content-Type': 'application/x-www-form-urlencoded',
      },
      body: params,
    });

    const result = await response.text();
    document.getElementById('response').innerHTML = result;
  });
});
