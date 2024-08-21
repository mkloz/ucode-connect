const express = require('express');
const axios = require('axios');
const cheerio = require('cheerio');
const app = express();
const port = 3000;

app.use(express.json());
app.use(express.urlencoded({ extended: true }));

app.get('/', (_req, res) => {
  res.sendFile(__dirname + '/index.html');
});

app.post('/load-url', async (req, res) => {
  const { url } = req.body;
  try {
    const response = await axios.get(url);
    const html = response.data;
    const $ = cheerio.load(html);
    const bodyContent = $('body').html();
    res.json({ content: bodyContent });
  } catch (error) {
    console.error('Error fetching URL');
    res.status(500).json({ error: 'Failed to load the URL content.' });
  }
});

app.listen(port, () => {
  console.log(`Server is running on http://localhost:${port}`);
});
