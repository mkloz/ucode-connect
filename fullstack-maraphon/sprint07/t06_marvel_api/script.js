async function fetchCharacters() {
  try {
    const response = await fetch('/api/characters');
    const characters = await response.json();
    displayCharacters(characters);
  } catch (error) {
    console.error('Error fetching characters:', error);
  }
}

function displayCharacters(characters) {
  const container = document.getElementById('characters-container');
  characters.forEach((character) => {
    const characterDiv = document.createElement('div');
    characterDiv.classList.add('character');
    characterDiv.innerHTML = `
                <h2>${character.name}</h2>
                <img src="${character.thumbnail.path}.${
      character.thumbnail.extension
    }" alt="${character.name}">
                <p>${character.description || 'No description available'}</p>
            `;
    container.appendChild(characterDiv);
  });
}

fetchCharacters();
