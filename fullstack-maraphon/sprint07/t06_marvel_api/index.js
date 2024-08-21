const express = require('express');
const axios = require('axios');
const path = require('path');
const crypto = require('crypto');

const app = express();
const PORT = process.env.PORT || 3000;
const MARVEL_API_PUB_KEY = '';
const MARVEL_API_PRIVATE_KEY = '';

app.use(express.static(__dirname));

app.get('/api/characters', async (req, res) => {
  try {
    let now = Date.now();
    let hash = crypto
      .createHash('md5')
      .update(now + MARVEL_API_PRIVATE_KEY + MARVEL_API_PUB_KEY)
      .digest('hex');

    const response = await axios.get(
      `https://gateway.marvel.com/v1/public/characters?apikey=${MARVEL_API_PUB_KEY}&hash=${hash}&ts=` +
        now,
    );
    res.json(response.data.data.results);
  } catch (error) {
    console.error('Error fetching characters:', error);
    res.status(500).send('Error fetching characters');
  }
});

app.get('/', (req, res) => {
  res.sendFile(path.join(__dirname, 'index.html'));
});

app.listen(PORT, () => {
  console.log(`Server is running on http://localhost:${PORT}`);
});
